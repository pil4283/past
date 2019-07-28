// Chat.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DC.h"
#include "Chat.h"


// Chat

IMPLEMENT_DYNCREATE(Chat, CFormView)

Chat::Chat()
	: CFormView(Chat::IDD)
	, m_msg(_T(""))
{

}

Chat::~Chat()
{
}

void Chat::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_msg);
}

BEGIN_MESSAGE_MAP(Chat, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &Chat::OnBnClickedButton1)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// Chat 진단입니다.

#ifdef _DEBUG
void Chat::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Chat::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// Chat 메시지 처리기입니다.

void Chat::OnBnClickedButton1()
{
	char msg[80];
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	strcpy(msg,m_msg);
	CDCApp* pApp = (CDCApp*)AfxGetApp();
	pApp->m_pView->SendMsg(msg);
}

int Chat::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CDCApp* pApp = (CDCApp*)AfxGetApp();
	pApp->m_pChat = this;

	return 0;
}
