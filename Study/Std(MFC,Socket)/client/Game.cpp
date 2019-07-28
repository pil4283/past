#include "StdAfx.h"
#include "Game.h"

Game::Game(void)
: m_EndIndex(0)
{
	m_Player[1].m_x = 200;
	m_Player[1].m_y = 200;
	m_x = 700;
	m_w = 200;
	m_y = 500;
	m_h = 100;
	start = false;
}

Game::~Game(void)
{
}

void Game::Draw(CDC* pDC)
{
	if(start)
	{
		m_Picture.Draw(pDC);
	}
	for(int i=0;i<2;i++)
	{
		if(start)
		{
			m_Player[i].Draw(pDC);
		}
		else
		{
			GameLobby(pDC);
		}
	}

	CString msg;
	msg.Format("%d",m_Player[0].ready);
	pDC->TextOutA(0,50,msg);
}
BOOL Game::LButtonDown(CPoint point)
{
	if(m_x <= point.x && point.x <= m_x+m_w)
	{
		if(m_y <= point.y && point.y <= m_y+m_h)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void Game::GameLobby(CDC* pDC)
{
	pDC->Rectangle(0,0,1400,700);//로비 틀
	if(m_Player[MAX_USER-1].m_index != -1)
	{
		pDC->Rectangle(m_x,m_y,m_x+m_w,m_y+m_h);//준비버튼
	}
	pDC->Rectangle(1400,0,1600,100);//1p정보
	pDC->Rectangle(1400,100,1600,200);//2p정보

	/*pDC->Rectangle(1400,100,1600,200);  3,4p미구현
	pDC->Rectangle(1400,100,1600,200);*/

	int a;

	for(int i=0;i<MAX_USER;i++)
	{
		if(m_Player[i].m_index != -1)
		{
			a = ((i+1)*50);
			pDC->TextOut(1480,a,m_Player[i].m_id);
		}
		if(m_Player[i].ready == true)
		{
			a = ((i+1)*50)+10;
			pDC->TextOut(1480,a,"준비");
		}
		else
		{
			a = ((i+1)*50)+10;
			pDC->TextOut(1480,a,"대기중");			
		}
	}
}

void Game::Create(void)
{
	m_Picture.Create();
	m_Player[0].Create();
	m_Player[1].Create();
}