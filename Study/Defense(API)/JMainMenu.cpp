#include "StdAfx.h"
#include "JMainMenu.h"
#include "clccapilib/KDC.h"
#include "resource.h"
#include <iostream>
using namespace std;

extern HINSTANCE hInst;

JMainMenu::JMainMenu(void)
{
	MenuLife=1;
	m_x=500;
	m_y=550;
	m_w=150;
	m_h=50;
	e_x=500;
	e_y=650;
	e_w=150;
	e_h=50;
	b_x=50;
	b_y=50;
	b_w=150;
	b_h=50;
}

JMainMenu::~JMainMenu(void)
{
}

void JMainMenu::MainIni(HWND hWnd, HINSTANCE hInst)
{
	g_hInst = hInst;
	m_Main = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_MainMenu));
	m_Help = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_HELP));
}


void JMainMenu::DrawMain(HDC hdc)
{
	if(MenuLife==1)
	{
	KDC::DrawBitmapTrans(hdc, 0, 0, 1280, 900, m_Main, 0, 0, 1280, 900, RGB(255,0,255));
	char temp[80];
	Rectangle(hdc,m_x,m_y,m_x+m_w,m_y+m_h);
	sprintf(temp,"게임시작");
	TextOut(hdc,m_x+45,m_y+20,temp,strlen(temp));
	Rectangle(hdc,e_x,e_y,e_x+e_w,e_y+e_h);
	sprintf(temp,"도움말");
	TextOut(hdc,e_x+50,e_y+20,temp,strlen(temp));
	}
	////////////////////////////////////////////////
	//도움말클릭시
	if(MenuLife==2)
	{
		KDC::DrawBitmapTrans(hdc,0,0,1280,900, m_Help, 0, 0, 1280, 900, RGB(255,0,255));
		//Rectangle(hdc,b_x,b_y,b_x+b_w,b_y+b_h);
	}
	////////////////////////////////////////////////
	//게임시작 클릭시
	if(MenuLife==0)
	{

	}
}