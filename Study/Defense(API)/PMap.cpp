#include "StdAfx.h"
#include "PMap.h"
#include <iostream>
#include "resource.h"
#include "clccapilib/kdc.h"

using namespace std;
extern HINSTANCE hInst;
	int xpos,ypos;

int p_Map2[YMAP][XMAP]={
	{0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0},
	{0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0},
	{0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,0,1,1,0},
	{0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0},
	{0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,1,0,1,0,0},
	{0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,0},
	{0,0,1,0,0,0,1,0,1,1,1,1,1,0,0,1,0,1,0,0},
	{0,0,1,1,1,1,1,0,1,0,0,0,0,0,0,1,0,1,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,1,0,0},
	{0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,1,0,1,0,0},
	{0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,1,0,1,0,0},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0}
};

//PaintMap 
// if(g_Map[y][x] == 3)
//{
//  	PaintTower(hdc,y,x);
//}
//

PMap::PMap(void)
{
	memcpy(p_Map, p_Map2, sizeof(p_Map));
}

PMap::~PMap(void)
{
}

void PMap::IniMap(HWND hWnd, HINSTANCE hInst)
{
	g_hinst = hInst;
	m_Map = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_BITMAP9));
	p_Dispenser = LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITMAP4));
	p_Sentry = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_LV1SENTRY));
	p_Teleporter = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_BITMAP7));
}

void PMap::DrawMap(HDC hdc)
{
	Rectangle(hdc,0,0,1280,900);

	/*HDC MemDC;
	HBITMAP MyBitmap,OldBitmap;
	MemDC=CreateCompatibleDC(hdc);
	MyBitmap=LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP9)); //여기다가 맵리소스넣어서 불러오면됨
	OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);

	BitBlt(hdc,0,0,1280,900,MemDC,0,0,SRCCOPY);
	SelectObject(MemDC,OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);*/
	KDC::DrawBitmapTrans(hdc, 0, 0, 1280, 900, m_Map, 0, 0, 1280, 900, RGB(255,0,255));
}
void PMap::DrawSentryGun(HDC hdc)
{
	/*for(int y=0,x;y<YMAP;y++)
	{
		for(x=0;x<XMAP;x++)
		{
			xpos = x * SIZE;
			ypos = y * SIZE;
			if(2 == p_Map[y][x])
			{
				CheckEnemy(hdc);
				//KDC::DrawBitmapTrans(hdc, xpos, ypos, 50, 50, p_Sentry, 50, 0, 50, 50, RGB(255,0,255));
				char tmp[80];
				sprintf(tmp, "xpos: %d, ypos: %d", xpos, ypos);
				TextOut(hdc, 0, 0, tmp, strlen(tmp));
			}
		}
	}*/
}

void PMap::DrawDispenser(HDC hdc)
{
	for(int y=0;y<YMAP;y++)
	{
		for(int x=0;x<XMAP;x++)
		{
			xpos = x * SIZE;
			ypos = y * SIZE;
			if(3 == p_Map[y][x])
			{
				KDC::DrawBitmapTrans(hdc, xpos, ypos, 50, 50, p_Dispenser, 0, 0, 50, 50, RGB(255,0,255));

				char tmp[80];

				sprintf(tmp, "xpos: %d, ypos: %d", xpos, ypos);
				TextOut(hdc, 0, 0, tmp, strlen(tmp));
			}
		}
	}
}

void PMap::DrawEnemyMap(HDC hdc)
{
/*	for(int y=0;y<YMAP;y++)
	{
		for(int x=0;x<XMAP;x++)
		{
			xpos = x * SIZE;
			ypos = y * SIZE;
			if(1 == p_Map[y][x])
			{
				KDC::DrawBitmapTrans(hdc, xpos, ypos, 50, 50, p_Dispenser, 0, 0, 50, 50, RGB(255,0,255));

				char tmp[80];

				sprintf(tmp, "xpos: %d, ypos: %d", xpos, ypos);
				TextOut(hdc, 0, 0, tmp, strlen(tmp));
			}
		}
	}*/
}

void PMap::DrawTeleporterIN(HDC hdc)
{
	for(int y=0,x;y<YMAP;y++)
	{
		for(x=0;x<XMAP;x++)
		{
			xpos = x * SIZE;
			ypos = y * SIZE;
			if(4 == p_Map[y][x] || 5 == p_Map[y][x])
			{
				KDC::DrawBitmapTrans(hdc, xpos, ypos, 50, 50, p_Teleporter, 0, 0, 50, 50, RGB(255,0,255));

				char tmp[80];

				sprintf(tmp, "xpos: %d, ypos: %d", xpos, ypos);
				TextOut(hdc, 0, 0, tmp, strlen(tmp));
			}
		}
	}
}

/*void PMap::CheckEnemy(HDC hdc)
{
	for(int i=0,j;i<SENTRY_COUNT;i++)
	{
		for(j=0;j<ENEMY_COUNT;j++)
		{
			if(m_Tower[i].m_x <= m_Enemy[j].E_x)
			{
				KDC::DrawBitmapTrans(hdc, xpos, ypos, 50, 50, p_Sentry, 50, 0, 50, 50, RGB(255,0,255));
			}
			else if(m_Enemy[j].E_x <= m_Tower[i].m_x)
			{
				KDC::DrawBitmapTrans(hdc, xpos, ypos, 50, 50, p_Sentry, 50, 0, 50, 50, RGB(255,0,255));
			}
			else if(m_Tower[i].m_y <= m_Enemy[j].E_y)
			{
				KDC::DrawBitmapTrans(hdc, xpos, ypos, 50, 50, p_Sentry, 50, 0, 50, 50, RGB(255,0,255));
			}
			else if(m_Enemy[j].E_y <= m_Tower[i].m_y)
			{
				KDC::DrawBitmapTrans(hdc, xpos, ypos, 50, 50, p_Sentry, 50, 0, 50, 50, RGB(255,0,255));
			}
		}
	}
}*/