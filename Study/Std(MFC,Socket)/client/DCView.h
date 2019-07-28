// DCView.h : CDCView 클래스의 인터페이스
//

#pragma once
#include "socket.h"
#include "game.h"
#include "Chat.h"
#include "afxwin.h"

class CMainFrame;
class CDCView : public CView
{
protected: // serialization에서만 만들어집니다.
	CDCView();
	DECLARE_DYNCREATE(CDCView)

// 특성입니다.
public:
	CDCDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CDCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	Socket m_Socket;
	void RunConnect(int error);
	void RunReceive(int error);
	void RunClose(int error);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	Game m_Game;
	char PlayerID[20];
	int PlayerIndex;
	void Connect(void);
	void SendLogin();
	void GetInfo(char* id, int index);
	void SendXY(void);
	void SendReady(bool ready);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SendSpace(void);
	void SendMe(int newindex);
	void SendOne(char* id, int index);
	CDC m_backDC;
	CBitmap m_backBit;
	CDC m_backBufferDC;
	CBitmap m_backBuffer;
	bool end;
	
	void SendMsg(char* msg);
	void SendStage(int stage);
	CDC onedc;
	CDC twodc;
	CBitmap onep;
	CBitmap twop;
};

#ifndef _DEBUG  // DCView.cpp의 디버그 버전
inline CDCDoc* CDCView::GetDocument() const
   { return reinterpret_cast<CDCDoc*>(m_pDocument); }
#endif

