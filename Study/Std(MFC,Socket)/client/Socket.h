#pragma once

// Socket 명령 대상입니다.
class CDCView;

class Socket : public CAsyncSocket
{
public:
	Socket();
	virtual ~Socket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	CDCView* m_pView;
};


