#include "StdAfx.h"
#include "PGameMenu.h"
#include "resource.h"
#include "clccapilib/kdc.h"
#include "clccapilib/KSound.h"

#define BG7 "À½¾Ç/7.mp3"
extern HINSTANCE hInst;

PGameMenu::PGameMenu(void)
{
	Life=1;
	
	m_x=1100;
	m_y=750;
	m_w=150;
	m_h=50;
	
}

PGameMenu::~PGameMenu(void)
{

}

void PGameMenu::GameMenuIni(HWND hWnd,HINSTANCE hInst)
{
	g_hinst = hInst;
	m_Menu = LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITMAP6));
}


void PGameMenu::MenuDraw(HDC hdc)
{
	
	HDC MemDC;
	HBITMAP MyBitmap,OldBitmap;

	MemDC=CreateCompatibleDC(hdc);
	MyBitmap=LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
	OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
	BitBlt(hdc,1000, 150, 300, 300,MemDC,0,0,SRCCOPY);
	SelectObject(MemDC,OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);

	KDC::DrawBitmapTrans(hdc, 1000, 150, 295, 284, m_Menu, 0, 0, 295, 284, RGB(255,0,255));

	if(Life==1)
	{
		Rectangle(hdc,m_x,m_y,m_x+m_w,m_y+m_h);
	}
}

