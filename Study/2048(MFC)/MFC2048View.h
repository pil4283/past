
// MFC2048View.h : CMFC2048View 클래스의 인터페이스
//

#pragma once
#include "Board.h"

class CMFC2048View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFC2048View();
	DECLARE_DYNCREATE(CMFC2048View)

// 특성입니다.
public:
	CMFC2048Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMFC2048View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

// 클래스 정의
public:
	Board m_Board;
	CPoint pt;
	bool m_drag;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMoveLog();
	afx_msg void OnOnlyNum();
	afx_msg void OnNumCol();
	afx_msg void OnTurnLog();
	afx_msg void OnUpdateMoveLog(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNumCol(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOnlyNum(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTurnLog(CCmdUI *pCmdUI);
	bool m_bOnlyChecked;
	bool m_bNCChecked;
	bool m_bMLogChecked;
	bool m_bTLogChecked;
};

#ifndef _DEBUG  // MFC2048View.cpp의 디버그 버전
inline CMFC2048Doc* CMFC2048View::GetDocument() const
   { return reinterpret_cast<CMFC2048Doc*>(m_pDocument); }
#endif

