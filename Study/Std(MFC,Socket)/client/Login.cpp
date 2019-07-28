// Login.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DC.h"
#include "Login.h"
#include "MTGSOUND.h"

#define MP1 "1.mp3"


// Login 대화 상자입니다.

IMPLEMENT_DYNAMIC(Login, CDialog)

Login::Login(CWnd* pParent /*=NULL*/)
	: CDialog(Login::IDD, pParent)
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_id);
}


BEGIN_MESSAGE_MAP(Login, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &Login::OnBnClickedButton1)
END_MESSAGE_MAP()

BOOL Login::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_pWnd = (CFrameWnd*)AfxGetMainWnd();
	m_pView = (CDCView*)(m_pWnd->GetActiveView());

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


// Login 메시지 처리기입니다.

void Login::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if(m_id.GetLength()==0)
	{
		AfxMessageBox("한글자라도 입력해주세요");
		return;
	}
	strcpy(m_pView->PlayerID,m_id);

	UpdateData(FALSE);
	
	m_pView->Connect();

	OnOK();
}

