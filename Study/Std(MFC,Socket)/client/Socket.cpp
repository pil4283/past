// Socket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DC.h"
#include "Socket.h"
#include "DCDoc.h"
#include "DCView.h"


// Socket

Socket::Socket()
{
}

Socket::~Socket()
{
}


// Socket 멤버 함수

void Socket::OnConnect(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pView->RunConnect(nErrorCode);
	CAsyncSocket::OnConnect(nErrorCode);
}

void Socket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pView->RunReceive(nErrorCode);
	CAsyncSocket::OnReceive(nErrorCode);
}

void Socket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	AfxMessageBox("종료됨");
	CAsyncSocket::OnClose(nErrorCode);
}
