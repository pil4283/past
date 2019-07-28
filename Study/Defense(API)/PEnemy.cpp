#include "StdAfx.h"
#include "PEnemy.h"
#include <iostream>
#include "resource.h"
#include "clccapilib/kdc.h"
#include <math.h>
extern HINSTANCE hInst;
using namespace std;



PEnemy::PEnemy(void)
{
	SPEED=5;
	EnemyFHP=200;
	EnemyLife=0;
	EnemyHP=200;
	E_x=250;
	E_y=0;
	E_h=50;
	E_w=50;

	LEFT=false;
	RIGHT=false;
	UP=false;
	DOWN=false;
}

PEnemy::~PEnemy(void)
{

}
 
void PEnemy::EnemyIni(HWND hWnd, HINSTANCE hinst)
{
	g_hinst = hinst;
	m_Enemy1 = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_S1));
}

void PEnemy::DrawEnemy(HDC hdc)
{
	double hpPer;
	
	//Rectangle(hdc,E_x,E_y,E_x+E_w,E_y+E_h);
	if(DOWN==true)
	{
		KDC::DrawBitmapTrans(hdc, E_x, E_y, 50, 50, m_Enemy1, s_x, 0, 50, 50, RGB(255,0,255));
	}
	else if(LEFT==true)
	{
		KDC::DrawBitmapTrans(hdc, E_x, E_y, 50, 50, m_Enemy1, s_x, 50, 50, 50, RGB(255,0,255));
	}
	else if(RIGHT==true)
	{
		KDC::DrawBitmapTrans(hdc, E_x, E_y, 50, 50, m_Enemy1, s_x, 100, 50, 50, RGB(255,0,255));
	}
	else if(UP==true)
	{
		KDC::DrawBitmapTrans(hdc, E_x, E_y, 50, 50, m_Enemy1, s_x, 150, 50, 50, RGB(255,0,255));
	}
	HDC MemDC;
	HBITMAP OldBitmap2;
	HBITMAP MyBitmap2;

	MemDC=CreateCompatibleDC(hdc);
	MyBitmap2=LoadBitmap(hInst, MAKEINTRESOURCE(IDB_HP1));
	//OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
	//BitBlt(hdc,E_x, E_y,E_x+E_w,E_y+E_h,MemDC,0,0,SRCCOPY);

	hpPer = (double)EnemyHP/EnemyFHP;
	hpPer = hpPer * 100;
	hpPer = hpPer / 2;

	hpPer = floor(hpPer);

	hpPer = 50 - hpPer;

	OldBitmap2 = (HBITMAP)SelectObject(MemDC, MyBitmap2);
	BitBlt(hdc, E_x, E_y-20, 50, 50, MemDC, hpPer, 0, SRCCOPY);

	SelectObject(MemDC,OldBitmap2);
	DeleteObject(MyBitmap2);
	DeleteDC(MemDC);
}



void PEnemy::MoveEnemy()
{
	if(E_x==250 && E_y < 200)
	{
		E_y+=SPEED;
		DOWN=true;
		LEFT=false;
		RIGHT=false;
		UP=false;
	}
	else if( 100 < E_x  && E_x < 625 && E_y == 200)
	{
		E_x-=SPEED;
		LEFT=true;
		DOWN=false;
		RIGHT=false;
		UP=false;
	}
	else if(E_x==100 && E_y < 450)
	{
		E_y+=SPEED;
		DOWN=true;
		LEFT=false;
		RIGHT=false;
		UP=false;
	}
	else if(E_x < 300 && E_y == 450)
	{
		E_x+=SPEED;
		RIGHT=true;
		LEFT=false;
		UP=false;
		DOWN=false;
	}
	else if(E_x == 300 && 300 < E_y && E_y < 500)
	{
		E_y-=SPEED;
		UP=true;
		LEFT=false;
		RIGHT=false;
		DOWN=false;
	}
	else if(E_x < 600 && E_y==300)
	{
		E_x+=SPEED;
		RIGHT=true;
		LEFT=false;
		UP=false;
		DOWN=false;
	}
	else if(E_x == 600 &&E_y < 400 && 250 < E_y )
	{
		E_y+=SPEED;
		DOWN=true;
		LEFT=false;
		RIGHT=false;
		UP=false;
	}
	else if(400 < E_x && E_y==400 && E_x < 650)
	{
		E_x-=SPEED;
		LEFT=true;
		RIGHT=false;
		UP=false;
		DOWN=false;
	}
	else if(400==E_x && E_y<500 && 350 <= E_y)
	{
		E_y+=SPEED;
		DOWN=true;
		LEFT=false;
		RIGHT=false;
		UP=false;
	}
	else if(E_x < 600 && E_y==500)
	{
		E_x+=SPEED;
		RIGHT=true;
		LEFT=false;
		UP=false;
		DOWN=false;
	}
	else if(E_x==600 && E_y < 600 && 450 < E_y)
	{
		E_y+=SPEED;
		DOWN=true;
		LEFT=false;
		RIGHT=false;
		UP=false;
	}
	else if(300 < E_x && E_y==600 && E_x < 650)
	{
		E_x-=SPEED;
		LEFT=true;
		RIGHT=false;
		UP=false;
		DOWN=false;
	}
	else if(300 == E_x && 550 < E_y &&  E_y < 650)
	{
		E_y-=SPEED;
		UP=true;
		LEFT=false;
		RIGHT=false;
		DOWN=false;
	}
	else if(50 < E_x && E_y==550 && E_x < 350)
	{
		E_x-=SPEED;
		LEFT=true;
		RIGHT=false;
		UP=false;
		DOWN=false;
	}
	else if(50 == E_x && E_y < 700)
	{
		E_y+=SPEED;
		DOWN=true;
		LEFT=false;
		RIGHT=false;
		UP=false;
	}
	else if(E_x < 750 && E_y==700)
	{
		E_x+=SPEED;
		RIGHT=true;
		LEFT=false;
		UP=false;
		DOWN=false;
	}
	else if(E_x==750 && 150 < E_y)
	{
		E_y-=SPEED;
		UP=true;
		LEFT=false;
		RIGHT=false;
		DOWN=false;
	}
	else if(400 < E_x && E_y==150 && E_x <=750)
	{
		E_x-=SPEED;
		LEFT=true;
		RIGHT=false;
		UP=false;
		DOWN=false;
	}
	else if(400 == E_x && 0 < E_y)
	{
		E_y-=SPEED;
		UP=true;
		LEFT=false;
		RIGHT=false;
		DOWN=false;
	}
	else if(E_x < 900 && E_y==0)
	{
		E_x+=SPEED;
		RIGHT=true;
		LEFT=false;
		UP=false;
		DOWN=false;
	}
	else if(E_x==900 && E_y<150)
	{
		E_y+=SPEED;
		DOWN=true;
		LEFT=false;
		RIGHT=false;
		UP=false;
	}
	else if(850 < E_x && E_y==150)
	{
		E_x-=SPEED;
		LEFT=true;
		RIGHT=false;
		UP=false;
		DOWN=false;
	}
	else if(850 == E_x && E_y < 800)
	{
		E_y+=SPEED;
		LEFT=false;
		RIGHT=false;
		UP=false;
		DOWN=true;
	}
		////////////////////////////////////////
		//이경우 플레이어의 라이프를 1감소시킴
		if(E_y==800)
		{
			EnemyLife=0;
			Player.PLife--;
		}
}