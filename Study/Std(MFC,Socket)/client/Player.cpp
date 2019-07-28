#include "StdAfx.h"
#include "Player.h"
#include "resource.h"

Player::Player(void)
: m_CCount(0)
{
	m_x = 100;
	m_y = 100;
	m_w = 50;
	m_h = 50;
	m_index = -1;
	ready = false;
}

Player::~Player(void)
{
}


void Player::Draw(CDC* pDC)
{

	//pDC->Rectangle(m_x,m_y,m_x+m_w,m_y+m_h);
	//pDC->TextOut(m_x,m_y-30,m_id);
	BITMAP the;
	m_Pb.GetBitmap(&the);
	pDC->BitBlt(m_x,m_y,the.bmWidth,the.bmHeight,&m_PbDC,0,0,SRCCOPY);

	//pDC->BitBlt(0,0,1600,800,&m_bBDC,0,0,SRCCOPY);
}
void Player::Create(void)
{
	CClientDC dc((CWnd*)m_pView);

	m_Pb.LoadBitmapA(IDB_PLAYER);
	m_PbDC.CreateCompatibleDC(&dc);
	m_PbDC.SelectObject(&m_Pb);

	/*m_bB.CreateCompatibleBitmap(&dc,1600,800);
	m_bBDC.CreateCompatibleDC(&dc);
	m_bBDC.SelectObject(&m_bB);	*/

}
