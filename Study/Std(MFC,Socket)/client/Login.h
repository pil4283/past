#pragma once

#include "DCDoc.h"
#include "DCView.h"

// Login 대화 상자입니다.

class Login : public CDialog
{
	DECLARE_DYNAMIC(Login)

public:
	Login(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Login();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_id;
	CFrameWnd* m_pWnd;
	CDCView* m_pView;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
