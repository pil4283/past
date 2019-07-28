#pragma once
#include "afxwin.h"



// State 폼 뷰입니다.

class State : public CFormView
{
	DECLARE_DYNCREATE(State)

protected:
	State();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~State();

public:
	enum { IDD = IDD_STATE };
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


