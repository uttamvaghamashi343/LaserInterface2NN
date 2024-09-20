#pragma once
#include "AKGDummyInterface.h"
#include <vector>
#include <map>

class CLaserInterface2NNDlg;
class CAKGHWCDummy6Axis
{
public:
	CAKGHWCDummy6Axis(void);
	~CAKGHWCDummy6Axis(void);

public:

    CLaserInterface2NNDlg* m_cLaserInterface2NNDlg;
	CAKGDummyInterface m_cClient;
	CAKGDummyInterface m_cServer;

    void ConnectToServer(const CString& csIpAddress, int iPortNum, BOOL bIsServer);
    void OnAccept();
    void OnReceive();
    void OnSend();
    void OnClose();
	void DataToSend(const std::vector<unsigned char>& data);
    void DataBarcodeDataToSend(const CString& csSendData);
    void SendCommandToServer(BYTE command);
    void SendCommandToClient(BYTE command);
    BOOL InitSocketConnection(BOOL bIsServer, int iPort);
    void DisconnectFromServer();
    void resetBuffer();
    void setServerListenForClient(int port);
    void AddToLog(const CString& cs, ...);
    unsigned char calculateChecksum(const std::vector<unsigned char>& packet);
    std::vector<unsigned char> createPacket(unsigned char command, const std::vector<unsigned char>& arguments);
    void DoEvent(int iDelay);

    CString m_csIpAdd;
    int m_iPort;
    CString m_recvData;
    BOOL m_bConnect;
    BOOL m_bDataReceived;
    BYTE m_cBuff[1024];
    UINT m_iReceivedDataLength;
    BOOL m_bTimerPause;

};
