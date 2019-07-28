#include "StdAfx.h"
#include "KDBuffer.h"

KDBuffer::KDBuffer(void)
{
}

KDBuffer::~KDBuffer(void)
{
}

HDC KDBuffer::InitDBuffer(HDC hdc,int w,int h)
{
	m_w=w;
	m_h=h;
	m_hdc=hdc;

	m_hMemDC=CreateCompatibleDC(hdc);
	m_hBackBit=CreateCompatibleBitmap(hdc,w,h);
	m_hOldBitmap=(HBITMAP)SelectObject(m_hMemDC,m_hBackBit);


	return m_hMemDC;
}

void KDBuffer::Draw()
{
	BitBlt(m_hdc,0,0,m_w,m_h,m_hMemDC,0,0,SRCCOPY);	
	SelectObject(m_hMemDC,m_hOldBitmap);
	DeleteObject(m_hBackBit);
	DeleteDC(m_hMemDC);
}
