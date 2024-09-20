#include "pch.h"
#include "framework.h"
#include "LaserInterface2NN.h"
#include "AKGHWCDummy6Axis.h"
#include "AKGDummyInterface.h"
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <lm.h>
#include <direct.h>

#pragma comment(lib, "Netapi32.lib")
using namespace std;

CAKGHWCDummy6Axis::CAKGHWCDummy6Axis(void)
{
	m_recvData = "";
	m_csIpAdd = "192.168.101.22";
	m_iPort = 58174;
	m_bConnect = FALSE;
	m_cClient.SetParentDlg(this);
	m_cServer.SetParentDlg(this);
	m_bTimerPause = 0;
	m_bDataReceived = TRUE;
}

CAKGHWCDummy6Axis::~CAKGHWCDummy6Axis(void)
{
	m_cClient.Close();
	m_cServer.Close();
}

void CAKGHWCDummy6Axis::ConnectToServer(const CString& csIpAdress, int iPortNum, BOOL bISServer)
{
	if (!m_bConnect)
	{
		m_bConnect = InitSocketConnection(bISServer, iPortNum);
	}

	if (m_bConnect)
	{
		if (!bISServer)
		{
			m_cClient.Connect(csIpAdress, iPortNum);
			long lError = GetLastError();

			if (PathFileExists(_T("D://MSG.txt")))
			{
				CString csError;
				csError.Format(_T("MSG=%ld %d"), lError, m_bConnect);
				AfxMessageBox(csError);
			}
		}
		else
		{
			AddToLog(_T("TCP IP Server Start..."));
		}
	}
	else
	{
		AddToLog(_T("TCP IP Connection establishment failed."));
	}
}

BOOL CAKGHWCDummy6Axis::InitSocketConnection(BOOL bISServer, int iPort)
{
	WSADATA wsaData;

	// Initialize WinSock
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
	{
		MessageBox(NULL, _T("WSAStartup() error"), _T("Error"), MB_OK);
		WSACleanup();
		return FALSE;
	}

	// Check WinSock version
	if (wsaData.wVersion != MAKEWORD(1, 1))
	{
		MessageBox(NULL, _T("No WinSock version 1.1 support found"), _T("Error"), MB_OK);
		WSACleanup();
		return FALSE;
	}

	if (bISServer)
	{
		setServerListenForClient(iPort);
	}
	else
	{
		m_bConnect = m_cClient.Create();

		if (!m_bConnect)
		{
			CString csError;
			csError.Format(_T("ERROR: MSG=%ld %d"), GetLastError(), m_bConnect);
			AddToLog(csError);
		}
	}

	return m_bConnect;
}

void CAKGHWCDummy6Axis::DisconnectFromServer()
{
	if (m_bConnect)  // Check if connected
	{
		m_cClient.ShutDown();  // Gracefully shutdown the client socket
		m_cClient.Close();     // Close the client socket connection
		m_bConnect = 0;    // Reset the connection flag

		AddToLog(_T("TCP/IP client disconnected successfully."));
	}
	else
	{
		AddToLog(_T("No active TCP/IP connection found."));
	}

	// Cleanup Winsock
	WSACleanup();
}


void CAKGHWCDummy6Axis::setServerListenForClient(int port)
{
	if (!m_cServer.Create(port)) {
		CString errorMsg;
		errorMsg.Format(_T("Failed to create server on port %d"), port);
		AfxMessageBox(errorMsg);
		return;
	}

	if (!m_cServer.Listen()) {
		CString errorMsg;
		errorMsg.Format(_T("Unable to listen on port %d, please try another port"), port);
		m_cServer.Close();
		AfxMessageBox(errorMsg);
		return;
	}
}

void CAKGHWCDummy6Axis::OnAccept()
{
	CString strIP;
	UINT port;
	if (m_cServer.Accept(m_cClient))
	{
		m_cClient.GetSockName(strIP, port);
		//m_status="Client Connected,IP :"+ strIP;
		m_cClient.Send(_T("Connected To Server"), static_cast<int>(_tcslen(_T("Connected To Server"))));
		AddToLog(_T("Connected To Server"), static_cast<int>(_tcslen(_T("Connected To Server"))));
	}
	else
	{
		AfxMessageBox(_T("Cannoot Accept Connection"));
	}
}

void CAKGHWCDummy6Axis::OnReceive()
{
	Sleep(10);
	// Prepare for receiving data
	m_recvData.Empty();
	resetBuffer();
	CHAR cBuff[1024] = { 0 };

	// Receive data
	int bytesReceived = m_cClient.Receive(cBuff, sizeof(cBuff));
	if (bytesReceived <= 0) // No data received, or an error occurred
	{
		return;
	}
		
	// Determine if we should break on CRLF
	BOOL bChkCRLF = !PathFileExists(_T("D://NCRLF.txt"));

	// Process the received data
	CString csReceivedData;
	for (int i = 0; i < bytesReceived; ++i)
	{
		m_cBuff[i] = cBuff[i];
		m_iReceivedDataLength = i + 1;

		// Break if null character or CRLF is found
		if ((i > 0 && cBuff[i - 1] == 0x0D))
			break;

		csReceivedData += cBuff[i];
	}

	m_bDataReceived = TRUE;
	m_recvData = csReceivedData;

	// Optional: Display message box if MSG.txt exists
	if (PathFileExists(_T("D://MSG.txt")))
	{
		AfxMessageBox(csReceivedData);
	}

	// Log received data
	AddToLog(_T("TCPDATA=") + m_recvData);
}

void CAKGHWCDummy6Axis::resetBuffer()
{
	memset(m_cBuff, 0, sizeof(m_cBuff));  // Efficiently set the buffer to zero
	m_iReceivedDataLength = 0;  // Reset the data length
}

void CAKGHWCDummy6Axis::AddToLog(const CString& cs, ...)
{
	// Initialize static variable only once
	static ULONGLONG dTick = GetTickCount64();

	// Open the log file
	FILE* fp = nullptr;
	if (_wfopen_s(&fp, L"C:\\SLTCard\\TCPIPLog.txt", L"a") != 0 || !fp)
	{
		// If file opening fails, handle the error (optional)
		AfxMessageBox(_T("Failed to open log file."));
		return;
	}

	// Get the current time
	CTime cTime = CTime::GetCurrentTime();

	// Write the log entry
	fwprintf_s(fp, L"\n%ls Time=%02d-%02d-%04d %02d:%02d:%02d Tick=%llu",
		(LPCTSTR)cs,
		cTime.GetDay(), cTime.GetMonth(), cTime.GetYear(),
		cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(),
		GetTickCount64() - dTick);

	// Close the file
	fclose(fp);

	// Update the tick count
	dTick = GetTickCount64();
}

unsigned char CAKGHWCDummy6Axis::calculateChecksum(const std::vector<unsigned char>& packet) {
	unsigned char sum = 0;
	for (unsigned char byte : packet) {
		sum += byte;
	}
	return sum;
}

// Function to create a packet to send to the Laser
std::vector<unsigned char> CAKGHWCDummy6Axis::createPacket(unsigned char command, const std::vector<unsigned char>& arguments) {
	
	// Calculate the size of the packet upfront and reserve the required space
	size_t packetSize = 5 + arguments.size(); // 5: Start byte, N byte, Command Start byte, Command byte, Stop byte
	std::vector<unsigned char> packet;
	// Use reserve to allocate memory in advance for std::vector to avoid multiple reallocations.
	packet.reserve(packetSize + 1); // +1 for checksum

	packet.push_back(0x1B);  // Packet Start byte
	packet.push_back(static_cast<unsigned char>(arguments.size() + 2));  // N = 2 + number of argument bytes
	packet.push_back(0x09);  // Command Start byte
	packet.push_back(command);  // Laser Command number

	// Add argument bytes
	packet.insert(packet.end(), arguments.begin(), arguments.end());

	packet.push_back(0x0D);  // Packet Stop byte

	// Calculate and append checksum
	packet.push_back(calculateChecksum(packet));

	return packet;
	
}

void CAKGHWCDummy6Axis::DataToSend(const std::vector<unsigned char>& data) {
 
	m_bTimerPause = 1;

	while (m_bDataReceived == 0)
	{
		DoEvent(10);
	}

	m_bDataReceived = false;
	m_recvData.Empty();

	if (data.empty()) return;

	// Directly send the data vector
	m_cClient.Send(reinterpret_cast<const CHAR*>(data.data()), static_cast<int>(data.size()));

	m_bTimerPause = 0;

}

void CAKGHWCDummy6Axis::DoEvent(int iDelay)
{
	MSG msg;
	ULONGLONG dwStTime = GetTickCount64();
	ULONGLONG dwEndTime = dwStTime + iDelay;

	while (GetTickCount64() < dwEndTime)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void CAKGHWCDummy6Axis::OnSend()
{

}

void CAKGHWCDummy6Axis::OnClose()
{
	if (m_bConnect)
	{
		m_cClient.Close();
		AddToLog(_T("TCP IP Connection Closed."));
		m_bConnect = 0;
	}
}

void CAKGHWCDummy6Axis::DataBarcodeDataToSend(const CString& csSendData)
{
	m_recvData.Empty();  // Clear the receive data buffer
	const int length = csSendData.GetLength();

	// Create a buffer to hold the data
	CHAR cBuff[1024] = { 0 };
	memcpy(cBuff, csSendData, length);

	// Send the buffer over the client
	m_cClient.Send(cBuff, length);
}


// Send a command from the client to the server
void CAKGHWCDummy6Axis::SendCommandToServer(BYTE command)
{
	// Create a packet with the command byte
	std::vector<BYTE> packet = { command };

	// Send the packet to the server
	int result = m_cClient.Send(packet.data(), static_cast<int>(packet.size()));

	if (result == SOCKET_ERROR)
	{
		int errorCode = WSAGetLastError();
		CString errorMsg;
		errorMsg.Format(_T("Socket send error (Client): %d"), errorCode);
		AfxMessageBox(errorMsg);
	}
}

// Send a command from the server to client
void CAKGHWCDummy6Axis::SendCommandToClient(BYTE command)
{
	// Create a packet with the command byte
	std::vector<BYTE> packet = { command };

	// Send the packet to the client
	int result = m_cServer.Send(packet.data(), static_cast<int>(packet.size()));

	if (result == SOCKET_ERROR)
	{
		int errorCode = WSAGetLastError();
		CString errorMsg;
		errorMsg.Format(_T("Socket send error (Server): %d"), errorCode);
		AfxMessageBox(errorMsg);
	}
}

