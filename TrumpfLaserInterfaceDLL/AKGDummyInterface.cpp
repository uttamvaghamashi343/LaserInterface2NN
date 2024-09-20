
#include "pch.h"
#include "framework.h"
#include "AKGDummyInterface.h"
#include "AKGHWCDummy6Axis.h"


// CAKGDummyInterface

CAKGDummyInterface::CAKGDummyInterface()
{
	// Initialize buffer to zero using std::fill
	std::fill(std::begin(m_rbuf), std::end(m_rbuf), 0);
}

CAKGDummyInterface::~CAKGDummyInterface() = default;

void CAKGDummyInterface::SetParentDlg(CAKGHWCDummy6Axis * pDlg)
{
	m_pDlg = pDlg;
}

void CAKGDummyInterface::OnAccept(int nErrorCode)
{
	if (m_pDlg)
		m_pDlg->OnAccept();
}

void CAKGDummyInterface::OnReceive(int nErrorCode)
{
	if (m_pDlg)
		m_pDlg->OnReceive();
}

void CAKGDummyInterface::OnSend(int nErrorCode)
{
	if (m_pDlg)
		m_pDlg->OnSend();
}

void CAKGDummyInterface::OnClose(int nErrorCode)
{
	if (m_pDlg)
		m_pDlg->OnClose();
}

void CAKGDummyInterface::OnConnect(int nErrorCode)
{
	CAsyncSocket::OnConnect(nErrorCode);
}

void CAKGDummyInterface::OnOutOfBandData(int nErrorCode)
{
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}
