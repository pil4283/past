
// MFC2048View.cpp : CMFC2048View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC2048.h"
#endif

#include "MFC2048Doc.h"
#include "MFC2048View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC2048View

IMPLEMENT_DYNCREATE(CMFC2048View, CView)

BEGIN_MESSAGE_MAP(CMFC2048View, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_MOVE_LOG, &CMFC2048View::OnMoveLog)
	ON_COMMAND(ID_ONLY_NUM, &CMFC2048View::OnOnlyNum)
	ON_COMMAND(ID_NUM_COL, &CMFC2048View::OnNumCol)
	ON_COMMAND(ID_TURN_LOG, &CMFC2048View::OnTurnLog)
	ON_UPDATE_COMMAND_UI(ID_MOVE_LOG, &CMFC2048View::OnUpdateMoveLog)
	ON_UPDATE_COMMAND_UI(ID_NUM_COL, &CMFC2048View::OnUpdateNumCol)
	ON_UPDATE_COMMAND_UI(ID_ONLY_NUM, &CMFC2048View::OnUpdateOnlyNum)
	ON_UPDATE_COMMAND_UI(ID_TURN_LOG, &CMFC2048View::OnUpdateTurnLog)
END_MESSAGE_MAP()

// CMFC2048View 생성/소멸

CMFC2048View::CMFC2048View()
	: m_bOnlyChecked(false)
	, m_bNCChecked(true)
	, m_bMLogChecked(true)
	, m_bTLogChecked(true)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFC2048View::~CMFC2048View()
{
}

BOOL CMFC2048View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFC2048View 그리기

void CMFC2048View::OnDraw(CDC* pDC)
{
	CMFC2048Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	m_Board.Paint(pDC);	

	ReleaseDC(pDC);
}


// CMFC2048View 진단

#ifdef _DEBUG
void CMFC2048View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC2048View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC2048Doc* CMFC2048View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC2048Doc)));
	return (CMFC2048Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC2048View 메시지 처리기


BOOL CMFC2048View::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)		//키보드입력을 받아 각 노드의 숫자를 움직인다.
	{
		m_Board.PushKey(pMsg->wParam);
		Invalidate();
	}


	
	
	return CView::PreTranslateMessage(pMsg);
}


void CMFC2048View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//마우스 클릭 시와 뗄 시의 x좌표를 비교해 보드를 돌린다.
	pt.x = point.x;
	pt.y = point.y;
	m_drag = true;	//드래그상태인지 확인하는 변수

	CView::OnLButtonDown(nFlags, point);
}


void CMFC2048View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_drag == true)
	{
		m_drag = false;

		if (pt.y <= 256 && point.y <= 256)//보드밖에서의 드래그는 무시하라 하셨으니 블록 안에서 드래그한것만 체크한다.
		{
			if (pt.x < point.x) //오른쪽 드래그 시 보드를 오른쪽으로 돌림.
			{
				m_Board.TurnBoard(1);
				Invalidate();
			}
			else if (point.x < pt.x)//왼쪽으로 드래그 시 보드를 왼쪽으로 돌림.
			{
				m_Board.TurnBoard(2);
				Invalidate();
			}
		}
	}
	CView::OnLButtonUp(nFlags, point);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//숫자만 보일건지 숫자,색깔 둘다 보일건지 결정. 한개가 체크상태가되면 다른하나는 언체크된다.
void CMFC2048View::OnNumCol()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	//기본적으로 true상태이다. 언체크된 상태일때 누르면 체크상태가됨.
	m_bNCChecked = true;
	m_bOnlyChecked = false;//숫자만 보이게하는 메뉴를 언체크한다.
	m_Board.drawOption = true;
	Invalidate();
}

void CMFC2048View::OnUpdateNumCol(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_bNCChecked == true)
	{
		pCmdUI->SetCheck(TRUE);//체크상태는 TRUE로 만들고 숫자와 색상을 동시에 출력하게 함.

	}
	else
	{
		pCmdUI->SetCheck(FALSE);//체크상태가 false면 언체크됨.
	}
}

void CMFC2048View::OnOnlyNum()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Board.drawOption = false;
	m_bOnlyChecked = true;
	m_bNCChecked = false;
	Invalidate();
}


void CMFC2048View::OnUpdateOnlyNum(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_bOnlyChecked == true)
	{
		pCmdUI->SetCheck(TRUE);

	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//로그파일생성은 하나만 체크상태가될수도있고 두개다 체크상태가 될수도있다.


void CMFC2048View::OnMoveLog()	//키보드 이동 결과를 기록함. 기본적으로 체크되어있음.
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_bMLogChecked == false)
	{
		m_bMLogChecked = true;
		m_Board.moveLog = true;	//체크되어있으면 이동할때마다 로그파일이 갱신된다.
	}
	else
	{
		m_bMLogChecked = false;
		m_Board.moveLog = false;
	}
}

void CMFC2048View::OnUpdateMoveLog(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_bMLogChecked == true)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMFC2048View::OnTurnLog()	//마우스 드래그 이동 결과를 기록함, 체크되어있으면 기록됨, 키보드,마우스 두개다 기록할수도있고 하나만 할수도 있음.
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_bTLogChecked == false)
	{
		m_bTLogChecked = true;
		m_Board.turnLog = true;//체크되어있으면 보드를 돌릴때마다 로그파일이 갱신된다.
	}
	else
	{
		m_bTLogChecked = false;
		m_Board.turnLog = false;
	}
	
}

void CMFC2048View::OnUpdateTurnLog(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_bTLogChecked == true)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}
