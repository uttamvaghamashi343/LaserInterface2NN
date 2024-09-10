#pragma once

#include <afxsock.h>

class CAKGHWCDummy6Axis; 
class CAKGDummyInterface : public CAsyncSocket
{
public:
	CAKGDummyInterface();
	virtual ~CAKGDummyInterface();

	// Override CAsyncSocket virtual functions
	virtual void OnAccept(int nErrorCode) override;
	virtual void OnReceive(int nErrorCode) override;
	virtual void OnSend(int nErrorCode) override;
	virtual void OnClose(int nErrorCode) override;
	virtual void OnConnect(int nErrorCode) override;
	virtual void OnOutOfBandData(int nErrorCode) override;

	// Set parent dialog
	void SetParentDlg(CAKGHWCDummy6Axis* pDlg);

private:
	char m_rbuf[40];
	CAKGHWCDummy6Axis* m_pDlg = nullptr;
};
