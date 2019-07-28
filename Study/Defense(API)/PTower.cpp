#include "StdAfx.h"
#include "PTower.h"
#include "resource.h"
#include "clccapilib/kdc.h"
#include <iostream>
#include <math.h>"
using namespace std;
extern HINSTANCE hInst;
PTower::PTower(void)
{
	////////////////////////////////
	//센트리건
	Life=0;
	m_x=1050; // left
	m_y=250; // top
	m_w=50; // right
	m_h=50; // bottom
	/////////////////////////////////
	//디스펜서
	DispenserLife=0;
	d_x=1150;
	d_y=250;
	d_w=50;
	d_h=50;
	////////////////////////////////
	//
	m_c=0;
	exp=0;
	Bullet=100;
	FBullet=100;
	Fexp=200;
	m_Info=0;
	Level=1;
	Missile=10;
	FMissile=10;
	Damage=16;
}

PTower::~PTower(void)
{

}

void PTower::TowerIni(HINSTANCE hInst)
{
	g_hinst = hInst;
	/*if(Level==1 || Level == 2)
	{
		Bullet=100;
	}
	if(Level==3)
	{
		Bullet=200;
	}*/
	m_Origin = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_BITMAP8));
	p_Sentry = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_LV1SENTRY));
	m_Bullet = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_BULLET));
	m_Upgrade = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_UPGRADE));
	m_Missile = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_MISSILE));
}

void PTower::TowerDraw(HDC hdc)
{
	/*Ellipse(hdc,m_x,m_y,m_x+m_w,m_y+m_h);

	HDC MemDC;
	HBITMAP MyBitmap,OldBitmap;

	MemDC=CreateCompatibleDC(hdc);
	MyBitmap=LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP8));
	OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
	BitBlt(hdc,m_x, m_y, m_x+m_w,m_y+m_h,MemDC,0,0,SRCCOPY);
	SelectObject(MemDC,OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);*/
	KDC::DrawBitmapTrans(hdc, m_x, m_y, 50, 50, m_Origin, 0, 0, 50, 50, RGB(255,0,255));
}

bool PTower::BulletCheck(void)
{
	if(Bullet <= 0)
	{
		return false;
	}
	return true;
}

void PTower::Dispenser(HDC hdc)
{
	KDC::DrawBitmapTrans(hdc, d_x, d_y, 50, 50, m_Origin, 0, 0, 50, 50, RGB(255,0,255));
}
void PTower::TeleporterDraw(HDC hdc)
{
	Rectangle(hdc,m_x,m_y,m_x+m_w,m_y+m_h);
}
void PTower::DrawInfo(HDC hdc)
{
	char temp[70];
	double bucheck;
	double upcheck;
	double micheck;

	if(m_Info==1)
	{
		HDC MemDC;
		HBITMAP OldBitmap,OldBitmap2,OldBitmap3;
		HBITMAP MyBitmap,MyBitmap2,MyBitmap3;

		MemDC=CreateCompatibleDC(hdc);
		MyBitmap=LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BULLET));
		MyBitmap2=LoadBitmap(hInst, MAKEINTRESOURCE(IDB_UPGRADE));
		MyBitmap3=LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MISSILE));
		
		bucheck = (double)Bullet/FBullet;
		bucheck = bucheck * 100;
		bucheck = bucheck / 2;

		bucheck = floor(bucheck);

		bucheck = 50 - bucheck;
		
		upcheck = (double)exp/Fexp;
		upcheck = upcheck * 100;
		upcheck = upcheck / 2;

		upcheck = floor(upcheck);

		upcheck = 50 - upcheck;

		micheck = (double)Missile/FMissile;
		micheck = micheck * 100;
		micheck = micheck / 2;

		micheck = floor(micheck);

		micheck = 50 - micheck;

		sprintf(temp,"총알 :");
		TextOut(hdc,1050,450,temp,strlen(temp));
		if(Level==3)
		{
			sprintf(temp,"미사일 :");
			TextOut(hdc,1050,500,temp,strlen(temp));
		}
		sprintf(temp,"업그레이드:");
		TextOut(hdc,1050,550,temp,strlen(temp));

		OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);
		BitBlt(hdc, 1100, 450, 100, 4, MemDC, bucheck, 0, SRCCOPY);
		OldBitmap2 = (HBITMAP)SelectObject(MemDC, MyBitmap2);
		BitBlt(hdc, 1150, 550, 50, 4, MemDC, upcheck, 0, SRCCOPY);
		if(Level==3)
		{
			OldBitmap3 = (HBITMAP)SelectObject(MemDC, MyBitmap3);
			BitBlt(hdc, 1125, 500, 50, 50, MemDC, micheck, 0, SRCCOPY);
		}
		SelectObject(MemDC,OldBitmap);
		DeleteObject(MyBitmap);
		SelectObject(MemDC,OldBitmap2);
		DeleteObject(MyBitmap2);
		SelectObject(MemDC,OldBitmap3);
		DeleteObject(MyBitmap3);
		DeleteDC(MemDC);

		//BitBlt(hdc, E_x, E_y-20, 50, 50, MemDC, hpPer, 0, SRCCOPY);
		//KDC::DrawBitmapTrans(hdc, 1100, 500, 50, 50, m_Bullet, 0, 0, 50, 50, RGB(255,0,255));
	}

}

void PTower::DrawSentry(HDC hdc)
{
	char tmp[80];
	int xpos,ypos;

	for(int y=0,x;y<YMAP;y++)
	{
		for(x=0;x<XMAP;x++)
		{
			xpos = x * SIZE;
			ypos = y * SIZE;
			if( x*SIZE == m_x && y*SIZE == m_y && Life == 2 && Level==1)
			{
				KDC::DrawBitmapTrans(hdc, xpos, ypos, 50, 50, p_Sentry, m_c, 0, 50, 50, RGB(255,0,255));
			}
			if( x*SIZE == m_x && y*SIZE == m_y && Life == 2 && Level==2)
			{
				KDC::DrawBitmapTrans(hdc, xpos, ypos, 50, 50, p_Sentry, m_c, 0, 50, 50, RGB(255,0,255));
			}
			if( x*SIZE == m_x && y*SIZE == m_y && Life == 2 && Level==3)
			{
				KDC::DrawBitmapTrans(hdc, xpos, ypos, 50, 50, p_Sentry, m_c, 0, 50, 50, RGB(255,0,255));
			}
		}
	}
}
