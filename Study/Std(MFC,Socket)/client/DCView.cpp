// DCView.cpp : CDCView 클래스의 구현
//

#include "stdafx.h"
#include "DC.h"

#include "DCDoc.h"
#include "DCView.h"
#include "Protocol.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDCView

IMPLEMENT_DYNCREATE(CDCView, CView)

BEGIN_MESSAGE_MAP(CDCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CDCView 생성/소멸

CDCView::CDCView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	PlayerIndex = -1;
	end = false;
}

CDCView::~CDCView()
{
}

int CDCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	//SetTimer(1,1000,NULL);

	CClientDC dc(this);

	onep.LoadBitmapA(IDB_BITMAP2);
	twop.LoadBitmapA(IDB_BITMAP5);

	onedc.CreateCompatibleDC(&dc);
	twodc.CreateCompatibleDC(&dc);

	onedc.SelectObject(&onep);
	twodc.SelectObject(&twop);


	CDCApp* pApp = (CDCApp*)AfxGetApp();
	pApp->m_pView = this;
	m_Game.m_Picture.m_pView = this;
	m_Game.m_Player[0].m_pView = this;
	m_Game.m_Player[1].m_pView = this;

	m_Game.Create();

	return 0;
}

BOOL CDCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}
///////////////////////////////////////////////////////////////////////
// CDCView 그리기

void CDCView::OnDraw(CDC* pDC)
{
	CDCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	m_Game.Draw(pDC);
	CString msg;
	//msg.Format("Player count : %d",m_Game.m_Player[PlayerIndex].m_CCount);
	//pDC->TextOutA(10,10,msg);

	if(end==true)
	{
		msg.Format("%s님이 승리했습니다 점수:%d",m_Game.m_Player[m_Game.m_EndIndex].m_id,m_Game.m_Player[m_Game.m_EndIndex].m_CCount);
		pDC->TextOut(300,300,msg);
		if(m_Game.m_EndIndex==0)
		{
			pDC->BitBlt(300,350,259,210,&onedc,0,0,SRCCOPY);
		}
		else if(m_Game.m_EndIndex == 1)
		{
			pDC->BitBlt(300,350,267,207,&twodc,0,0,SRCCOPY);
		}
	}
}
/////////////////////////////////////////////////////////////////////////
// CDCView 인쇄

BOOL CDCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CDCView 진단

#ifdef _DEBUG
void CDCView::AssertValid() const
{
	CView::AssertValid();
}

void CDCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDCDoc* CDCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDCDoc)));
	return (CDCDoc*)m_pDocument;
}
#endif //_DEBUG

void CDCView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CView::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////
// CDCView 메시지 처리기

void CDCView::RunConnect(int error)
{
	if(0 == error)
	{
		AfxMessageBox("접속됨");
		SendLogin();
	}
	else
	{
		AfxMessageBox("서버가 닫혀있음");
	}
}

void CDCView::RunReceive(int error)
{
	int count=0;
	S_H h;
	char buffer[1024*3];
	memset(buffer,0,sizeof(buffer));
	memset(&h,0,sizeof(h));
	m_Socket.Receive(&buffer,sizeof(buffer));
	memcpy(&h,buffer,sizeof(h));
	CString msg;
	switch(h.cmd)
	{
	case SC_RLOGIN:
		{
			S_RLOGIN rlogin;
			//m_Socket.Receive(&rlogin,sizeof(rlogin));
			memcpy(&rlogin,buffer+sizeof(h),sizeof(rlogin));
			strcpy(m_Game.m_Player[rlogin.index].m_id,PlayerID);
			m_Game.m_Player[rlogin.index].m_index = rlogin.index;
			PlayerIndex = rlogin.index;
			if(PlayerIndex != 0)
			{
				SendOne(PlayerID,PlayerIndex);
			}
			CDCApp* pApp = (CDCApp*)AfxGetApp();
			if(PlayerIndex==0)
			{
				msg.Format("1P-[%s]님",rlogin.id);
			}
			else
			{
				msg.Format("2P-[%s]님",rlogin.id);
			}
			pApp->m_pState->m_list.AddString(msg);
			InvalidateRect(NULL,FALSE);
		}
		break;
	case SCA_NEWUSER:
		{
			S_NEWUSER newuser;
			//m_Socket.Receive(&newuser,sizeof(newuser));
			memcpy(&newuser,buffer+sizeof(h),sizeof(newuser));
			if(PlayerIndex==newuser.index)
			{
				return;
			}
			else
			{
				strcpy(m_Game.m_Player[newuser.index].m_id,newuser.id);
				m_Game.m_Player[newuser.index].m_index = newuser.index;
				SendMe(newuser.index);
				CDCApp* pApp = (CDCApp*)AfxGetApp();
				msg.Format("2P-[%s]님",newuser.id);
				pApp->m_pState->m_list.AddString(msg);
				InvalidateRect(NULL,FALSE);
				//msg.Format("접속함 : %d - %s",m_Game.m_Player[newuser.index].m_index,m_Game.m_Player[newuser.index].m_id);
				//AfxMessageBox(msg);
			}
		}
		break;
	case SC_OLDUSER:
		{
			S_OLDUSER olduser;
			//m_Socket.Receive(&olduser,sizeof(olduser));
			memcpy(&olduser,buffer+sizeof(h),sizeof(olduser));
			strcpy(m_Game.m_Player[olduser.index].m_id,olduser.id);
			m_Game.m_Player[olduser.index].m_index = olduser.index;
			CDCApp* pApp = (CDCApp*)AfxGetApp();
			msg.Format("1P-[%s]님",olduser.id);
			pApp->m_pState->m_list.AddString(msg);
			InvalidateRect(NULL,FALSE);
			//msg.Format("%d - %s",m_Game.m_Player[olduser.index].m_index,m_Game.m_Player[olduser.index].m_id);
			//AfxMessageBox(msg);
		}
		break;
	case SCA_XY:
		{
			S_XY xy;
			//m_Socket.Receive(&xy,sizeof(xy));
			memcpy(&xy,buffer+sizeof(h),sizeof(xy));
			m_Game.m_Player[xy.index].m_x = xy.x;
			m_Game.m_Player[xy.index].m_y = xy.y;
			InvalidateRect(NULL,FALSE);
		}
		break;
	case SCA_READY:
		{
			S_READY ready;
			//m_Socket.Receive(&ready,sizeof(ready));
			memcpy(&ready,buffer+sizeof(h),sizeof(ready));
			m_Game.m_Player[ready.index].ready = ready.ready;
			InvalidateRect(NULL,FALSE);
		}
		break;
	case SCA_START:
		{
			S_START start;
			//m_Socket.Receive(&start,sizeof(start));
			memcpy(&start,buffer+sizeof(h),sizeof(start));
			m_Game.start = start.start;
			m_Game.m_Picture.stage = start.stage;
			InvalidateRect(NULL,FALSE);
		}
		break;
	case SCA_COLLECT:
		{
			S_COLLECT collect;
			//m_Socket.Receive(&collect,sizeof(collect));
 			memcpy(&collect,buffer+sizeof(h),sizeof(collect));
			m_Game.m_Picture.CheckCollect(collect.i);
			m_Game.m_Player[collect.index].m_CCount = collect.count;

			for(int i=0;i<5;i++)
			{
				if(m_Game.m_Picture.isCollect[i]==1)
				{
					count++;
				}
				else
				{
					count =0;
					break;
				}
			}
			if(count==5)
			{
				m_Game.m_Picture.stage++;
				SendStage(m_Game.m_Picture.stage);
				m_Game.m_Picture.IniCollect();
			}
			InvalidateRect(NULL,FALSE);
		}
		break;
	case SCA_INCOLLECT:
		{
			S_INCOLLECT incollect;
			//m_Socket.Receive(&incollect,sizeof(incollect));
			memcpy(&incollect,buffer+sizeof(h),sizeof(incollect));
			msg.Format("%d님이 틀림",incollect.index);
			AfxMessageBox(msg);
		}
		break;
/*	case SCA_NEXTSTAGE:
		{
			S_NEXTSTAGE next;
			//m_Socket.Receive(&next,sizeof(next));
			memcpy(&next,buffer+sizeof(h),sizeof(next));
			m_Game.m_Picture.stage = next.stage;
			m_Game.m_Picture.IniCollect();
			InvalidateRect(NULL,FALSE);
		}
		break;*/
	case SCA_END:
		{
			S_END l_end;
			//m_Socket.Receive(&end,sizeof(end));
			memcpy(&l_end,buffer+sizeof(h),sizeof(l_end));
			end = true;
			m_Game.m_EndIndex = l_end.index;
			//msg.Format("%s님이 승리하셨습니다.점수:%d",end.id,end.count);
			//AfxMessageBox(msg);

		}
		break;
	case SCA_MSG:
		{
			S_RMSG rmsg;
			memcpy(&rmsg,buffer+sizeof(h),sizeof(rmsg));
			msg.Format("[%s]:%s",rmsg.id,rmsg.msg);
			CDCApp* pApp = (CDCApp*)AfxGetApp();
			pApp->m_pChat->m_list.AddString(msg);
		}
		break;
	default:
		break;
	}	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//입력처리
void CDCView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	/*if(nChar == VK_LEFT)
	{
		m_Game.m_Player[PlayerIndex].KeyDown(LEFT);
		SendXY();
	}
	else if(nChar == VK_RIGHT)
	{
		m_Game.m_Player[PlayerIndex].KeyDown(RIGHT);
		SendXY();
	}
	else if(nChar == VK_UP)
	{
		m_Game.m_Player[PlayerIndex].KeyDown(UP);
		SendXY();
	}
	else if(nChar == VK_DOWN)
	{
		m_Game.m_Player[PlayerIndex].KeyDown(DOWN);
		SendXY();
	}*/
	switch(nChar)
	{
	case VK_LEFT:
		m_Game.m_Player[PlayerIndex].m_x-=10;
		break;
	case VK_RIGHT:
		m_Game.m_Player[PlayerIndex].m_x +=10;
		break;
	case VK_UP:
		m_Game.m_Player[PlayerIndex].m_y-=10;
		break;
	case VK_DOWN:
		m_Game.m_Player[PlayerIndex].m_y+=10;
		break;
	}
	SendXY();
	if(nChar == VK_SPACE)
	{
		SendSpace();
		return;
	}
	InvalidateRect(NULL,FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(m_Game.LButtonDown(point)==TRUE)
	{
		m_Game.m_Player[PlayerIndex].ready = true;
		InvalidateRect(NULL,FALSE);
		SendReady(m_Game.m_Player[PlayerIndex].ready);
	}
	CView::OnLButtonDown(nFlags, point);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//통신관련(SEND)
void CDCView::Connect(void)
{
	m_Socket.m_pView = this;
	m_Socket.Create();
	m_Socket.Connect("127.0.0.1",2012);
}

void CDCView::SendLogin()
{
	S_H h;
	S_LOGIN login;

	h.cmd = CS_LOGIN;
	strcpy(login.id,PlayerID);

	char temp[1024*3];

	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&login,sizeof(login));

	m_Socket.Send(temp,sizeof(h)+sizeof(login));
}
void CDCView::SendXY(void)
{
	S_H h;
	S_XY xy;

	h.cmd = CS_XY;
	xy.index = PlayerIndex;
	xy.x = m_Game.m_Player[PlayerIndex].m_x;
	xy.y = m_Game.m_Player[PlayerIndex].m_y;
	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&xy,sizeof(xy));

	m_Socket.Send(temp,sizeof(h)+sizeof(xy));
}
void CDCView::SendReady(bool ready)
{
	S_H h;
	S_READY m_ready;

	h.cmd = CS_READY;
	m_ready.index = PlayerIndex;
	m_ready.ready = ready;

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&m_ready,sizeof(m_ready));

	m_Socket.Send(temp,sizeof(h)+sizeof(m_ready));
}
void CDCView::SendSpace(void)
{
	S_H h;
	S_SPACE space;

	h.cmd = CS_SPACE;
	space.stage = m_Game.m_Picture.stage;
	space.x = m_Game.m_Player[PlayerIndex].m_x;
	space.y = m_Game.m_Player[PlayerIndex].m_y;

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&space,sizeof(space));

	m_Socket.Send(temp,sizeof(h)+sizeof(space));
}
void CDCView::SendMe(int newindex)
{
	S_H h;
	S_ME me;

	h.cmd = CS_SENDME;
	h.len = sizeof(me);

	strcpy(me.id,PlayerID);
	me.index = PlayerIndex;
	me.newindex = newindex;

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&me,sizeof(me));

	m_Socket.Send(temp,sizeof(h)+sizeof(me));
}
void CDCView::SendOne(char* id, int index)
{
	S_H h;
	S_ONE one;

	h.cmd = CS_SENDONE;
	h.len = sizeof(one);

	one.index = index;

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&one,sizeof(one));

	m_Socket.Send(temp,sizeof(h)+sizeof(one));
}
void CDCView::SendMsg(char* msg)
{
	S_H h;
	S_MSG m_msg;

	h.cmd = CS_MSG;
	h.len = sizeof(m_msg);

	strcpy(m_msg.msg,msg);

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&m_msg,sizeof(m_msg));

	m_Socket.Send(temp,sizeof(h)+sizeof(m_msg));
}
void CDCView::SendStage(int stage)
{
	S_H h;
	S_NEXTSTAGE next;

	h.cmd = CS_NEXTSTAGE;
	h.len = sizeof(next);

	next.stage = stage;

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&next,sizeof(next));

	m_Socket.Send(temp,sizeof(h)+sizeof(next));	
}

///////////////////////////////////////////////////////////////////////////////
//통신관련(RECV)
void CDCView::GetInfo(char* id, int index)
{
	//m_Game.m_Player[PlayerIndex].m_index = PlayerIndex;
	//strcpy(m_Game.m_Player[PlayerIndex].m_id,PlayerID);
}


