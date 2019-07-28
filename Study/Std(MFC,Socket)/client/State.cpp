// State.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DC.h"
#include "State.h"


// State

IMPLEMENT_DYNCREATE(State, CFormView)

State::State()
	: CFormView(State::IDD)
{

}

State::~State()
{
}

void State::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(State, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// State 진단입니다.

#ifdef _DEBUG
void State::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void State::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// State 메시지 처리기입니다.

int State::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	
	CDCApp* pApp = (CDCApp*)AfxGetApp();
	pApp->m_pState = this;
	
	return 0;
}
