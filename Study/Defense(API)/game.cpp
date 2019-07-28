#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "resource.h"
#include "clccapilib/KDC.h"
#include "clccapilib/KDBuffer.h"
#include "clccapilib/KSound.h"
#include <iostream>
using namespace std;
//////////////////////////////
//헤더
#include "PGame.h"
//////////////////////////////
//
#define EMT 1
#define ERT 2
#define ONEAttackTime 3
#define ONESupplyTime 4
#define TWOAttackTime 5
#define TWOSupplyTime 6
#define THREEAttackTime	7
#define THREESupplyTime 8
#define MISSLEAttackTime 9
#define ENEMYMOVE 10
//////////////////////////////
//
char temp[80];
PGame g_Game;
HWND g_hWnd=NULL;
extern HINSTANCE hInst;
//////////////////////////////
//전역변수

static int e=0;
static int k=0;

void onCreate(HWND hWnd,WPARAM wParam, LPARAM lParam)
{
	g_hWnd=hWnd;
	SetTimer(hWnd,EMT,150,NULL);
	SetTimer(hWnd,ERT,1500,NULL);
	SetTimer(hWnd,ONEAttackTime,350,NULL);
	SetTimer(hWnd,ONESupplyTime,5000,NULL);
	SetTimer(hWnd,TWOAttackTime,150,NULL);
	SetTimer(hWnd,ENEMYMOVE,500,NULL);
	g_Game.Ini(hWnd);
	if(g_Game.stage == 1 && g_Game.CheckStage == 1 && g_Game.m_GameMenu.Life==0)
	{
		g_Game.m_Enemy[0].E_x=250;
		g_Game.m_Enemy[0].E_y=50;
		g_Game.m_Enemy[0].EnemyLife=1;
	}

}

void onPaint(HDC hdc,WPARAM wParam, LPARAM lParam)
{
	/*HDC MemDC = CreateCompatibleDC(hdc);
	HBITMAP hBit,OldBit;

	hBit = CreateCompatibleBitmap(hdc,1280,900);

	OldBit = (HBITMAP)SelectObject(MemDC,hBit);

	g_Game.Draw(MemDC);
	//sprintf(temp,"%d %d %d",g_Game.m_Tower[0].Life,g_Game.m_Tower[1].Life,g_Game.m_Tower[2].Life);
	//TextOut(MemDC,1,1,temp,strlen(temp));

	BitBlt(hdc,0,0,1280,900,MemDC,0,0,SRCCOPY);

	SelectObject(MemDC,OldBit);
	DeleteDC(MemDC);
	DeleteObject(hBit);*/



	KDBuffer buffer;
	//HDC MemDC = CreateCompatibleDC(hdc);
	HDC MemDC = buffer.InitDBuffer(hdc,1280,900);
	//HBITMAP hBit,OldBit;

	//hBit = CreateCompatibleBitmap(hdc,1280,900);

	//OldBit = (HBITMAP)SelectObject(MemDC,hBit);

	g_Game.Draw(MemDC);
	sprintf(temp,"%d",k);
	TextOut(MemDC,1,1,temp,strlen(temp));
	sprintf(temp,"%d",g_Game.m_Enemy[0].EnemyLife);
	TextOut(MemDC,1,25,temp,strlen(temp));
	sprintf(temp,"%d",g_Game.m_Enemy[10].EnemyLife);
	TextOut(MemDC,1,50,temp,strlen(temp));
	sprintf(temp,"%d",g_Game.m_Enemy[20].EnemyLife);
	TextOut(MemDC,1,75,temp,strlen(temp));

	//BitBlt(hdc,0,0,1280,900,MemDC,0,0,SRCCOPY);
	buffer.Draw();
	/*
	SelectObject(MemDC,OldBit);
	DeleteDC(MemDC);
	DeleteObject(hBit);*/

}

void onLButtonDown(WPARAM wParam, LPARAM lParam,HWND hWnd)
{
	g_Game.ButtonDown(wParam,lParam,hWnd);
}

void onMouseMove(WPARAM wParam, LPARAM lParam,HWND hWnd )
{
	g_Game.Drag(wParam,lParam,hWnd);
}

void onLButtonUP(WPARAM wParam, LPARAM lParam)
{
	g_Game.ButtonUp(wParam,lParam);
}
void onRButtonDown(WPARAM wParam , LPARAM lParam)
{
	g_Game.RButtonDown(wParam,lParam);
}
void onRButtonOn(WPARAM wParam , LPARAM lParam)
{
	g_Game.RButtonUp(wParam,lParam);
}
void onTimer( WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case 1:
		if(g_Game.m_GameMenu.Life==0)
		{
			
			g_Game.MoveEnemy();
		}
		break;
	case 2:
		g_Game.MissileCheck();
		if(g_Game.m_GameMenu.Life==0)
		{
			if(g_Game.stage==1 && g_Game.CheckStage == 1)
			{
				if(g_Game.m_Enemy[0].EnemyLife==0)
				{
					g_Game.m_Enemy[0].EnemyLife=1;
					g_Game.m_Enemy[0].E_x=250;
					g_Game.m_Enemy[0].E_y=0;
					if(g_Game.m_Enemy[0].EnemyHP <= 0)
					{
						g_Game.m_Enemy[0].EnemyLife=-1;
					}
				}
					g_Game.m_Enemy[k].E_x=250;
					g_Game.m_Enemy[k].E_y=0;
					g_Game.m_Enemy[k].EnemyLife=1;

					g_Game.m_Enemy[10].EnemyLife=0;
				if(10>k)
				{
					k++;
					g_Game.m_Enemy[10].EnemyLife=0;
				}
			}
			if(g_Game.stage==2 && g_Game.CheckStage == 2)
			{
				if(g_Game.m_Enemy[10].EnemyLife==0)
				{
					g_Game.m_Enemy[10].E_x=250;
					g_Game.m_Enemy[10].E_y=0;
					g_Game.m_Enemy[10].EnemyLife=1;
					if(g_Game.m_Enemy[10].EnemyHP <= 0)
					{
						g_Game.m_Enemy[10].EnemyLife=-1;
					}
				}
				g_Game.m_Enemy[k].E_x=250;
				g_Game.m_Enemy[k].E_y=0;
				g_Game.m_Enemy[k].EnemyLife=1;
				g_Game.m_Enemy[20].EnemyLife=0;
				if(20>k)
				{
					k++;
					g_Game.m_Enemy[20].EnemyLife=0;
				}

			}
			if(g_Game.stage==3 && g_Game.CheckStage == 3)
			{
				if(g_Game.m_Enemy[20].EnemyLife==0)
				{
					g_Game.m_Enemy[20].E_x=250;
					g_Game.m_Enemy[20].E_y=0;
					g_Game.m_Enemy[20].EnemyLife=1;
					if(g_Game.m_Enemy[20].EnemyHP <= 0)
					{
						g_Game.m_Enemy[20].EnemyLife=-1;
					}
				}
				g_Game.m_Enemy[k].E_x=250;
				g_Game.m_Enemy[k].E_y=0;
				g_Game.m_Enemy[k].EnemyLife=1;
				if(30>k)
				{
					k++;
				}
			}
		}
		break;
	case 3:
		if(2 == g_Game.m_Tower->Life)
		{
			g_Game.AttackCheck();
		}
		break;
	case 4:
		if(2 == g_Game.m_Dispenser->DispenserLife)
		{
			g_Game.SupplyCheck();
			g_Game.TWOSupplyCheck();
			g_Game.THRSupplyCheck();
			g_Game.TeleporterCheck();
		}
		break;
	case 5:
		g_Game.TWOAttackCheck();
		g_Game.THRAttackCheck();
		break;
	case 10:
		for(int i=0;i<ENEMY_COUNT;i++)
		{
			if(g_Game.m_Enemy[i].RIGHT==true || g_Game.m_Enemy[i].LEFT==true)
			{
				g_Game.m_Enemy[i].s_x+=50;
				if(200 <= g_Game.m_Enemy[i].s_x)
				{
					g_Game.m_Enemy[i].s_x=0;
				}
			}
			else if(g_Game.m_Enemy[i].UP==true || g_Game.m_Enemy[i].DOWN==true)
			{	
				g_Game.m_Enemy[i].s_x+=50;
				if(200 <= g_Game.m_Enemy[i].s_x)
				{
					g_Game.m_Enemy[i].s_x=0;
				}
			}
		}
		break;
	}
	InvalidateRect(g_hWnd,NULL,FALSE);
}