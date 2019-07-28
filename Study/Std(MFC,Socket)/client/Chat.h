#pragma once
#include "afxwin.h"



// Chat 폼 뷰입니다.

class Chat : public CFormView
{
	DECLARE_DYNCREATE(Chat)

public:
	Chat();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~Chat();

public:
	enum { IDD = IDD_CHAT };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list;
	CString m_msg;
	afx_msg void OnBnClickedButton1();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


