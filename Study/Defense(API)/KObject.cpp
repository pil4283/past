#include "StdAfx.h"
#include "KObject.h"
#include "KDC.h"

KObject::KObject(void)
{
	m_dx=0;
	m_dy=0;
}

KObject::~KObject(void)
{
}

void KObject::Draw(HDC hdc)
{
	int w=m_vAction[m_aindex].w;
	int h=m_vAction[m_aindex].h;
	int sx=0;
	int sy=h*m_findex;
	COLORREF color=m_vAction[m_aindex].color;
	HBITMAP hBitmap=m_vAction[m_aindex].hBitmap;

	if(0==m_vAction[m_aindex].type)
	{ //0:세로 
		KDC::DrawBitmapTrans(hdc,m_xpos,m_ypos,w,h,hBitmap,sx,sy,color);
	}
	else
	{
		//1:가로
		sx=w*m_findex;
		sy=0;
		KDC::DrawBitmapTrans(hdc,m_xpos,m_ypos,w,h,hBitmap,sx,sy,color);
	}
}

BOOL KObject::NextFrame()
{
	static long oldT=0;

	long newT=GetTickCount();

	if(abs(newT - oldT) < m_interval)
	{
		return FALSE;
	}
	else
	{
		oldT=newT;
	}

	int f_size=m_vAction[m_aindex].f_size;
	if(-1==m_loop)
	{
		//무한 루프 
		m_xpos += m_dx;
		m_ypos += m_dy;
		m_findex++;
		if(f_size <= m_findex)
		{
			m_findex=0;
		}
	
		return TRUE;
	}
	else
	{
		if(0 < m_loop)
		{
			m_xpos += m_dx;
			m_ypos += m_dy;
			m_findex++;
			if(f_size <= m_findex)
			{
				m_findex=0;
				m_loop--;
			}
			return TRUE;
		}
	}

	return FALSE;
}
int KObject::AddAction(HBITMAP hBitmap,COLORREF color,int w,int h,int f_size,int type) //0:세로 리소스, 1:가로 리소스
{

	S_ACTION action;

	action.w=w;
	action.h=h;
	action.color=color;

	action.f_size=f_size;
	action.hBitmap=hBitmap;
	action.type=type;

	m_vAction.push_back(action);

	return m_vAction.size()-1;
}
BOOL KObject::SetActiveAction(int aindex,int loop,int dx,int dy,int interval)
{
	if(0 < m_loop ) return FALSE;
 
	m_aindex=aindex;
	m_findex=0;
	m_loop=loop;
	m_dx=dx;
	m_dy=dy;
	m_interval=interval;

	return TRUE;
}
void KObject::StopAction()
{
	m_findex=0;
	m_loop=0;
}