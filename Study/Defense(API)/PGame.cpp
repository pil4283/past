#include "StdAfx.h"
#include "PGame.h"
#include <time.h>
#include <iostream>
#include "resource.h"
#include "clccapilib/KDBuffer.h"
#include "clccapilib/KSound.h"

#define BG1 "음악/1.mp3"
#define BG2 "음악/2.mp3"
#define BG3 "음악/3.mp3"
#define BG4 "음악/4.mp3"
#define BG5 "음악/5.mp3"
#define BG6 "음악/6.mp3"
#define BG7 "음악/7.mp3"
#define BG8 "음악/win.mp3"
#define WAV1 "음악/LV1B.WAV"
#define WAV2 "효과음/BS1.WAV"
#define WAV3 "효과음/BS2.WAV"
#define WAV4 "효과음/BD1.WAV"
#define WAV5 "효과음/BD2.WAV"
#define WAV6 "효과음/BT1.WAV"
#define WAV7 "효과음/BT2.WAV"

using namespace std;

static BOOL TELEPORTERINCLICK=FALSE;
static BOOL TELEPORTEROUTCLICK=FALSE;
static BOOL SENTRYCLICK=FALSE;
static BOOL DISPENSERCLICK=FALSE;
static int a;
static int x;
static int y;
static int RanMP; 
extern HINSTANCE hInst;
char tmp[20];
KSound g_Sound;


PGame::PGame(void)
{
	srand(time(NULL));
	stage=1;
	CheckStage=0;
}

PGame::~PGame(void)
{
}
void onRButtonDown(WPARAM wParam, LPARAM lParam);
void PGame::Ini(HWND hWnd)//초기화
{
	m_MainMenu.MainIni(hWnd,hInst);
	g_Sound.PlayMp3(hWnd,BG1);
	CheckStageOver();
	m_GameMenu.GameMenuIni(hWnd,hInst);
	m_Map.IniMap(m_hWnd,hInst);
	CheckStageOver();
	for(int i=0;i<10;i++)
	{
		m_Enemy[i].EnemyIni(hWnd,hInst);
		m_Enemy[i].EnemyLife=0;
	}
	for(int i=10;i<20;i++)
	{
		m_Enemy[i].EnemyIni(hWnd,hInst);
		m_Enemy[i].EnemyLife=0;
		m_Enemy[i].EnemyFHP=400;
		m_Enemy[i].EnemyHP=400;
	}
	for(int i=20;i<30;i++)
	{
		m_Enemy[i].EnemyIni(hWnd,hInst);
		m_Enemy[i].EnemyLife=0;
		m_Enemy[i].EnemyFHP=1000;
		m_Enemy[i].EnemyHP=1000;
	}
	for(int i=0;i<SENTRY_COUNT;i++)
	{
		m_Tower[i].TowerIni(hInst);
		m_Tower[i].Life=0;
		m_Tower[i].Bullet=100;
		if(100 <= m_Tower[i].Bullet)
		{
			m_Tower[i].Bullet=100;
		}
	}
	for(int i=0;i<DISPENSER_COUNT;i++)
	{
		m_Dispenser[i].TowerIni(hInst);
		m_Dispenser[i].DispenserLife=0;
	}
	GameOverCheck();
	m_TeleporterIN.TowerIni(hInst);
	m_TeleporterIN.m_x=1050;
	m_TeleporterIN.m_y=350;
	m_TeleporterIN.m_w=50;
	m_TeleporterIN.m_h=50;
	m_TeleporterOUT.TowerIni(hInst);
	m_TeleporterOUT.m_x=1150;
	m_TeleporterOUT.m_y=350;
	m_TeleporterOUT.m_w=50;
	m_TeleporterOUT.m_h=50;
	m_Tower[0].Life=1;
	m_Dispenser[0].DispenserLife=1;
	m_TeleporterIN.Life=1;
	m_TeleporterOUT.Life=1;
}

void PGame::Draw(HDC hdc)//그리기
{
	m_MainMenu.DrawMain(hdc);
	if(m_MainMenu.MenuLife==0)
	{
		m_Map.DrawMap(hdc);
		for(int i=0;i<DISPENSER_COUNT;i++)
		{
			//Ellipse(hdc,m_Dispenser[i].d_rx,m_Dispenser[i].d_ry,m_Dispenser[i].d_rw,m_Dispenser[i].d_rh);
			if(m_Dispenser[i].DispenserLife==1)
			{
				m_Dispenser[i].Dispenser(hdc);
			}
		}
		//m_Map.DrawSentryGun(hdc);
		m_Map.DrawDispenser(hdc);
		m_Map.DrawEnemyMap(hdc);
		m_Map.DrawTeleporterIN(hdc);
		m_Player.PlayerDraw(hdc);

		char temp[80];
		/*sprintf(temp,"%d",a);
		TextOut(hdc,1150,500,temp,strlen(temp));
		sprintf(temp,"%d",m_Enemy[10].EnemyLife);
		TextOut(hdc,1150,550,temp,strlen(temp));
		sprintf(temp,"%d",x);
		TextOut(hdc,1150,600,temp,strlen(temp));
		*/

		for(int i=0;i<SENTRY_COUNT;i++)
		{
			m_Tower[i].DrawSentry(hdc);
			m_Tower[i].DrawInfo(hdc);
			sprintf(temp,"%d",m_Tower[i].Bullet);
			TextOut(hdc,m_Tower[i].m_x,m_Tower[i].m_y-20,temp,strlen(temp));
			sprintf(temp,"%d",m_Tower[i].Level);
			TextOut(hdc,m_Tower[i].m_x,m_Tower[i].m_y-30,temp,strlen(temp));
			if(m_Tower[i].Life==1)
			{
				m_Tower[i].TowerDraw(hdc);
			}
			//Ellipse(hdc,m_Tower[i].m_rx,m_Tower[i].m_ry,m_Tower[i].m_rw,m_Tower[i].m_rh);
		}
		if(m_TeleporterIN.Life==1)
		{
			m_TeleporterIN.TowerDraw(hdc);
		}
		if(m_TeleporterOUT.Life==1)
		{
			m_TeleporterOUT.TowerDraw(hdc);
		}

		for(int i=0;i<ENEMY_COUNT;i++)
		{
			if(1 == m_Enemy[i].EnemyLife && m_GameMenu.Life==0)
			{
				m_Enemy[i].DrawEnemy(hdc);
			}
		}
		m_GameMenu.MenuDraw(hdc);
	}
}

void PGame::MoveEnemy(void)//적이동
{
	for(int i=0;i<10;i++)
	{
		if(m_GameMenu.Life==0 && stage == 1 && m_Enemy[i].EnemyLife==1)
		{
			m_Enemy[i].MoveEnemy();
			GameOverCheck();
		}
	}
	for(int i=10;i<20;i++)
	{
		if(m_GameMenu.Life==0 && stage == 2 && m_Enemy[i].EnemyLife==1)
		{
			m_Enemy[i].MoveEnemy();
			GameOverCheck();
		}
	}
	for(int i=20;i<30;i++)
	{
		if(m_GameMenu.Life==0 && stage == 3 && m_Enemy[i].EnemyLife==1)
		{
			m_Enemy[i].MoveEnemy();
			GameOverCheck();
		}
	}
	//AttackCheck();
}

void PGame::CheckEnemy(void)//적생존체크
{
	for(int j=0;j<SENTRY_COUNT;j++)
	{
		for(int i=0;i<10;i++)
		{
			if(m_Enemy[i].EnemyHP <= 0 && 1==m_Enemy[i].EnemyLife)
			{
				m_Enemy[i].EnemyLife=0;
				a++;
				m_Player.PGold+=50;
				if(a == 10)
				{
					m_GameMenu.Life=1;
					stage++;
					break;
				}
			}
		}

		for(int i=10;i<20;i++)
		{
			if(m_Enemy[i].EnemyHP <= 0 && 1==m_Enemy[i].EnemyLife)
			{
				m_Enemy[i].EnemyLife=0;
				a++;
				m_Player.PGold+=200;
				if(a == 20)
				{
					m_GameMenu.Life=1;
					stage++;
					break;
				}
			}
		}



		for(int i=20;i<30;i++)
		{
			if(m_Enemy[i].EnemyHP <= 0 && 1==m_Enemy[i].EnemyLife)
			{
				m_Enemy[i].EnemyLife=0;
				a++;
				m_Player.PGold+=400;
				if(a == 30)
				{
					m_GameMenu.Life=1;
					stage++;
					break;
				}
			}
		}
	}
	/*if(stage == 4 && m_GameMenu.Life==0 && CheckStage==4 )
	{
		if(m_Enemy[30].EnemyHP <= 0 && 1==m_Enemy[30].EnemyLife)
		{
			MessageBox(m_hWnd,"YOU WIN!","ㅊㅊ",MB_OK);
		}
	}*/
}

void PGame::CheckStageOver(void)//스테이지체크
{
	sprintf(tmp,"WAVE %d CLEAR!",stage);

	if(10<=a)
	{
		MessageBox(m_hWnd,tmp,"Next Wave!",MB_OK);
		g_Sound.PlayMp3(m_hWnd,BG8);
	}

	if(20<=a && CheckStage == 2)
	{
		MessageBox(m_hWnd,tmp,"Next Wave!",MB_OK);
	}

	if(30<=a && CheckStage == 3)
	{
		MessageBox(m_hWnd,tmp,"Next Wave!",MB_OK);
	}
	
}
/////////////////////////////////////////////////////////////////////////////////////////////
//충돌체크
void PGame::AttackCheck()//공격체크
{
	RECT r1,r2,r3;

	for(int i=0;i<SENTRY_COUNT;i++)
	{
		if(2 == m_Tower[i].Life && true == m_Tower[i].BulletCheck() && 1 == m_Tower[i].Level)
		{
			r1.left = m_Tower[i].m_rx;
			r1.top = m_Tower[i].m_ry;
			r1.right = m_Tower[i].m_rw;
			r1.bottom = m_Tower[i].m_rh;
		}

		else
		{
			continue;
		}
	
		for(int j=0	;j<ENEMY_COUNT;j++)
		{
			if(1 == m_Enemy[j].EnemyLife)
			{
				r2.left = m_Enemy[j].E_x;
				r2.top = m_Enemy[j].E_y;
				r2.right = m_Enemy[j].E_x+m_Enemy[j].E_w;
				r2.bottom = m_Enemy[j].E_y+m_Enemy[j].E_h;

				if(TRUE == IntersectRect(&r3,&r1,&r2))
				{
					//g_Sound.PlayWave(WAV1,1);

					
					if(m_Tower[i].m_y < m_Enemy[j].E_y&& m_Enemy[j].E_y < m_Tower[i].m_y+300 && m_Tower[i].m_x-100 < m_Enemy[j].E_x && m_Enemy[j].E_x < m_Tower[i].m_x+100) //아래
					{
						m_Tower[i].m_c=0;
					}
					else if(m_Enemy[j].E_x < m_Tower[i].m_x+300 && m_Tower[i].m_x+10 < m_Enemy[j].E_x && m_Tower[i].m_y-100 < m_Enemy[j].E_y && m_Enemy[j].E_y < m_Tower[i].m_y+100)//오른쪽
					{
						m_Tower[i].m_c=100;
					}
					else if(m_Tower[i].m_x-300 < m_Enemy[j].E_x && m_Tower[i].m_y-100 < m_Enemy[j].E_y && m_Enemy[j].E_y < m_Tower[i].m_y+100) //왼쪽
					{
						m_Tower[i].m_c=50;
					}
					else if(m_Tower[i].m_y-300 < m_Enemy[j].E_y && m_Enemy[j].E_y < m_Tower[i].m_y && m_Tower[i].m_x-100 < m_Enemy[j].E_x && m_Enemy[j].E_x < m_Tower[i].m_x+100) //위
					{
						m_Tower[i].m_c=150;
					}
					/*else if(m_Tower[i].m_x-150 < m_Enemy[j].E_x && m_Enemy[j].E_x < m_Tower[i].m_x-10 && m_Tower[i].m_y+150 < m_Enemy[j].E_y && m_Enemy[j].E_y < m_Tower[i].m_y+10)//왼쪽 아래
					{
						m_Tower[i].m_c=300;
					}
					else if(m_Enemy[j].E_x < m_Tower[i].m_x+150 && m_Tower[i].m_x+10 < m_Enemy[j].E_x && m_Tower[i].m_y+150 < m_Enemy[j].E_y && m_Enemy[j].E_y < m_Tower[i].m_y+10)//오른쪽 아래
					{
						m_Tower[i].m_c=350;
					}
					else if(m_Tower[i].m_x-150 < m_Enemy[j].E_x && m_Enemy[j].E_x < m_Tower[i].m_x-10 && m_Enemy[j].E_y < m_Tower[i].m_y-150 && m_Tower[i].m_y-10 < m_Enemy[j].E_y)//왼쪽 위
					{
						m_Tower[i].m_c=200;
					}
					else if(m_Enemy[j].E_x < m_Tower[i].m_x+150 && m_Tower[i].m_x+10 < m_Enemy[j].E_x && m_Enemy[j].E_y < m_Tower[i].m_y-150 && m_Tower[i].m_y-10 < m_Enemy[j].E_y)//오른쪽 위
					{
						m_Tower[i].m_c=250;
					}*/

					m_Enemy[j].EnemyHP-=m_Tower[i].Damage;
					m_Tower[i].Bullet--;
					CheckEnemy();
					break;
				}
			}
		}
	}
}

void PGame::TWOAttackCheck(void)
{
	RECT r1,r2,r3;

	for(int i=0;i<SENTRY_COUNT;i++)
	{
		if(2 == m_Tower[i].Life && true == m_Tower[i].BulletCheck() && 2 == m_Tower[i].Level)
		{
			r1.left = m_Tower[i].m_rx;
			r1.top = m_Tower[i].m_ry;
			r1.right = m_Tower[i].m_rw;
			r1.bottom = m_Tower[i].m_rh;
		}
		else
		{
			continue;
		}
	
		for(int j=0	;j<ENEMY_COUNT;j++)
		{
			if(1 == m_Enemy[j].EnemyLife)
			{
				r2.left = m_Enemy[j].E_x;
				r2.top = m_Enemy[j].E_y;
				r2.right = m_Enemy[j].E_x+m_Enemy[j].E_w;
				r2.bottom = m_Enemy[j].E_y+m_Enemy[j].E_h;

				if(TRUE == IntersectRect(&r3,&r1,&r2))
				{
					//g_Sound.PlayWave(WAV1,0);
					if(m_Tower[i].m_y-10 < m_Enemy[j].E_y && m_Tower[i].m_x-75 < m_Enemy[j].E_x && m_Enemy[j].E_x < m_Tower[i].m_x+75) //위
					{
						m_Tower[i].m_c=0;
					}
					else if(m_Enemy[j].E_x < m_Tower[i].m_x-10 && m_Tower[i].m_y-75 < m_Enemy[j].E_y && m_Enemy[j].E_y < m_Tower[i].m_y+75) //왼쪽
					{
						m_Tower[i].m_c=50;
					}
					else if(m_Enemy[j].E_x < m_Tower[i].m_x-10 && m_Tower[i].m_x-150 < m_Enemy[j].E_x && m_Enemy[j].E_y < m_Tower[i].m_y+150)//왼쪽 위
					{
						m_Tower[i].m_c=200;
					}
					else if(m_Tower[i].m_x+10 < m_Enemy[j].E_x && m_Enemy[j].E_x < m_Tower[i].m_x+150 && m_Enemy[j].E_y < m_Tower[i].m_y+150)//오른쪽 위
					{
						m_Tower[i].m_c=250;
					}
					else if(m_Tower[i].m_x+10 < m_Enemy[j].E_x && m_Tower[i].m_y-75 < m_Enemy[j].E_y && m_Enemy[j].E_y < m_Tower[i].m_y+75)//오른쪽
					{
						m_Tower[i].m_c=100;
					}
					else if(m_Enemy[j].E_y < m_Tower[i].m_y+10 && m_Tower[i].m_x-75 < m_Enemy[j].E_x && m_Enemy[j].E_x < m_Tower[i].m_x+75) //아래
					{
						m_Tower[i].m_c=150;
					}
					else if(m_Enemy[j].E_x < m_Tower[i].m_x-10 && m_Tower[i].m_x-150 < m_Enemy[j].E_x && m_Tower[i].m_y+150 < m_Enemy[j].E_y )//왼쪽 아래
					{
						m_Tower[i].m_c=300;
					}
					else if(m_Tower[i].m_x+10 < m_Enemy[j].E_x && m_Enemy[j].E_x < m_Tower[i].m_x+150 && m_Tower[i].m_y+150 < m_Enemy[j].E_y)//오른쪽 아래
					{
						m_Tower[i].m_c=350;
					}
					m_Enemy[j].EnemyHP-=m_Tower[i].Damage;
					m_Tower[i].Bullet--;
					CheckEnemy();
					break;
				}
			}
		}
	}
}

void PGame::THRAttackCheck(void)
{
	RECT r1,r2,r3;

	for(int i=0;i<SENTRY_COUNT;i++)
	{
		if(2 == m_Tower[i].Life && true == m_Tower[i].BulletCheck() && 3 == m_Tower[i].Level)
		{
			r1.left = m_Tower[i].m_rx;
			r1.top = m_Tower[i].m_ry;
			r1.right = m_Tower[i].m_rw;
			r1.bottom = m_Tower[i].m_rh;
		}

		else
		{
			continue;
		}
	
		for(int j=0	;j<ENEMY_COUNT;j++)
		{
			if(1 == m_Enemy[j].EnemyLife)
			{
				r2.left = m_Enemy[j].E_x;
				r2.top = m_Enemy[j].E_y;
				r2.right = m_Enemy[j].E_x+m_Enemy[j].E_w;
				r2.bottom = m_Enemy[j].E_y+m_Enemy[j].E_h;

				if(TRUE == IntersectRect(&r3,&r1,&r2))
				{
					//g_Sound.PlayWave(WAV1,0);
					if(m_Tower[i].m_y-10 < m_Enemy[j].E_y && m_Tower[i].m_x-75 < m_Enemy[j].E_x && m_Enemy[j].E_x < m_Tower[i].m_x+75) //위
					{
						m_Tower[i].m_c=0;
					}
					else if(m_Enemy[j].E_x < m_Tower[i].m_x-10 && m_Tower[i].m_y-75 < m_Enemy[j].E_y && m_Enemy[j].E_y < m_Tower[i].m_y+75) //왼쪽
					{
						m_Tower[i].m_c=50;
					}
					else if(m_Enemy[j].E_x < m_Tower[i].m_x-10 && m_Tower[i].m_x-150 < m_Enemy[j].E_x && m_Enemy[j].E_y < m_Tower[i].m_y+150)//왼쪽 위
					{
						m_Tower[i].m_c=200;
					}
					else if(m_Tower[i].m_x+10 < m_Enemy[j].E_x && m_Enemy[j].E_x < m_Tower[i].m_x+150 && m_Enemy[j].E_y < m_Tower[i].m_y+150)//오른쪽 위
					{
						m_Tower[i].m_c=250;
					}
					else if(m_Tower[i].m_x+10 < m_Enemy[j].E_x && m_Tower[i].m_y-75 < m_Enemy[j].E_y && m_Enemy[j].E_y < m_Tower[i].m_y+75)//오른쪽
					{
						m_Tower[i].m_c=100;
					}
					else if(m_Enemy[j].E_y < m_Tower[i].m_y+10 && m_Tower[i].m_x-75 < m_Enemy[j].E_x && m_Enemy[j].E_x < m_Tower[i].m_x+75) //아래
					{
						m_Tower[i].m_c=150;
					}
					else if(m_Enemy[j].E_x < m_Tower[i].m_x-10 && m_Tower[i].m_x-150 < m_Enemy[j].E_x && m_Tower[i].m_y+150 < m_Enemy[j].E_y )//왼쪽 아래
					{
						m_Tower[i].m_c=300;
					}
					else if(m_Tower[i].m_x+10 < m_Enemy[j].E_x && m_Enemy[j].E_x < m_Tower[i].m_x+150 && m_Tower[i].m_y+150 < m_Enemy[j].E_y)//오른쪽 아래
					{
						m_Tower[i].m_c=350;
					}
					m_Enemy[j].EnemyHP-=m_Tower[i].Damage;
					m_Tower[i].Bullet--;
					CheckEnemy();
					break;
				}
			}
		}
	}
}

void PGame::MissileCheck(void)
{
	RECT r1,r2,r3;

	for(int i=0;i<SENTRY_COUNT;i++)
	{
		if(2 == m_Tower[i].Life && 0 < m_Tower[i].Missile  && 3 == m_Tower[i].Level)
		{
			r1.left = m_Tower[i].m_rx-200;
			r1.top = m_Tower[i].m_ry-200;
			r1.right = m_Tower[i].m_rw+400;
			r1.bottom = m_Tower[i].m_rh+400;
		}

		else
		{
			continue;
		}
	
		for(int j=0	;j<ENEMY_COUNT;j++)
		{
			if(1 == m_Enemy[j].EnemyLife)
			{
				r2.left = m_Enemy[j].E_x;
				r2.top = m_Enemy[j].E_y;
				r2.right = m_Enemy[j].E_x+m_Enemy[j].E_w;
				r2.bottom = m_Enemy[j].E_y+m_Enemy[j].E_h;

				if(TRUE == IntersectRect(&r3,&r1,&r2))
				{
					//g_Sound.PlayWave(WAV1,0);
					if(m_Tower[i].m_x < m_Enemy[j].E_x && m_Tower[i].m_y+20 < m_Enemy[j].E_y)
					{
						m_Tower[i].m_c=100;
					}
					else if(m_Enemy[j].E_x < m_Tower[i].m_x)
					{
						m_Tower[i].m_c=50;
					}
					else if(m_Tower[i].m_y < m_Enemy[j].E_y)
					{
						m_Tower[i].m_c=0;
					}
					else if( m_Enemy[j].E_y < m_Tower[i].m_y )
					{
						m_Tower[i].m_c=150;
					}
					m_Enemy[j].EnemyHP-=78;
					m_Tower[i].Missile--;
					CheckEnemy();
					break;
				}
			}
		}
	}
}

void PGame::SupplyCheck(void)//보급체크
{
	RECT r1,r2,r3;

	for(int i=0;i<DISPENSER_COUNT;i++)
	{
		if(2 == m_Dispenser[i].DispenserLife && 1 == m_Dispenser[i].Level)
		{
			r1.left = m_Dispenser[i].d_rx;
			r1.top = m_Dispenser[i].d_ry;
			r1.right = m_Dispenser[i].d_rw;
			r1.bottom = m_Dispenser[i].d_rh;
		}
		else
		{
			continue;
		}
		for(int j=0	;j<SENTRY_COUNT;j++)
		{
			if(2 == m_Tower[j].Life)
			{
				r2.left = m_Tower[j].m_x;
				r2.top = m_Tower[j].m_y;
				r2.right = m_Tower[j].m_x+m_Tower[j].m_w;
				r2.bottom = m_Tower[j].m_y+m_Tower[j].m_h;

				if(TRUE == IntersectRect(&r3,&r1,&r2))
				{
					if(m_Tower[j].Missile <= 9)
					{
						m_Tower[j].Missile+=2;
						if(10 <=m_Tower[j].Missile)
						{
							m_Tower[j].Missile=10;
						}
					}
					if(m_Tower[j].Bullet <= 99)
					{
						m_Tower[j].Bullet+=10;
						if(100 <=m_Tower[j].Bullet)
						{
							m_Tower[j].Bullet=100;
						}
						break;
					}
				}
			}
		}
	}
}

void PGame::TWOSupplyCheck(void)
{
	RECT r1,r2,r3;

	for(int i=0;i<DISPENSER_COUNT;i++)
	{
		if(2 == m_Dispenser[i].DispenserLife && m_Dispenser[i].Level == 2)
		{
			r1.left = m_Dispenser[i].d_rx;
			r1.top = m_Dispenser[i].d_ry;
			r1.right = m_Dispenser[i].d_rw;
			r1.bottom = m_Dispenser[i].d_rh;
		}
		else
		{
			continue;
		}
		for(int j=0	;j<SENTRY_COUNT;j++)
		{
			if(2 == m_Tower[j].Life)
			{
				r2.left = m_Tower[j].m_x;
				r2.top = m_Tower[j].m_y;
				r2.right = m_Tower[j].m_x+m_Tower[j].m_w;
				r2.bottom = m_Tower[j].m_y+m_Tower[j].m_h;

				if(TRUE == IntersectRect(&r3,&r1,&r2))
				{
					if(m_Tower[j].Missile <= 9)
					{
						m_Tower[j].Missile+=4;
						if(10 <=m_Tower[j].Missile)
						{
							m_Tower[j].Missile=10;
						}
					}
					if(m_Tower[j].Bullet <= 99)
					{
						m_Tower[j].Bullet+=30;
						if(100 <=m_Tower[j].Bullet)
						{
							m_Tower[j].Bullet=100;
						}
						break;
					}
				}
			}
		}
	}
}

void PGame::THRSupplyCheck(void)
{
	RECT r1,r2,r3;

	for(int i=0;i<DISPENSER_COUNT;i++)
	{
		if(2 == m_Dispenser[i].DispenserLife && m_Dispenser[i].Level == 3)
		{
			r1.left = m_Dispenser[i].d_rx;
			r1.top = m_Dispenser[i].d_ry;
			r1.right = m_Dispenser[i].d_rw;
			r1.bottom = m_Dispenser[i].d_rh;
		}
		else
		{
			continue;
		}
		for(int j=0	;j<SENTRY_COUNT;j++)
		{
			if(2 == m_Tower[j].Life)
			{
				r2.left = m_Tower[j].m_x;
				r2.top = m_Tower[j].m_y;
				r2.right = m_Tower[j].m_x+m_Tower[j].m_w;
				r2.bottom = m_Tower[j].m_y+m_Tower[j].m_h;

				if(TRUE == IntersectRect(&r3,&r1,&r2))
				{
					m_Player.PGold+=25;
					m_Tower[j].Damage=24;
					if(m_Tower[j].Missile <= 9)
					{
						m_Tower[j].Missile+=2;
						if(10 <=m_Tower[j].Missile)
						{
							m_Tower[j].Missile=10;
						}
					}
					if(m_Tower[j].Bullet <= 99)
					{
						m_Tower[j].Bullet+=10;
						if(100 <=m_Tower[j].Bullet)
						{
							m_Tower[j].Bullet=100;
						}
					}
				}
			}
		}
	}
}


void PGame::TeleporterCheck(void)//텔레포터체크
{
	RECT r1,r2,r3;

	for(int i=0;i<ENEMY_COUNT;i++)
	{
		if(1 == m_Enemy[i].EnemyLife)
		{
			r1.left = m_Enemy[i].E_x;
			r1.top = m_Enemy[i].E_y;
			r1.right = m_Enemy[i].E_x+m_Enemy[i].E_w;
			r1.bottom = m_Enemy[i].E_y+m_Enemy[i].E_h;
		}
		else
		{
			continue;
		}
		if(2 == m_TeleporterIN.Life)
		{
			r2.left = m_TeleporterIN.m_x;
			r2.top = m_TeleporterIN.m_y;
			r2.right = m_TeleporterIN.m_x+m_TeleporterIN.m_w;
			r2.bottom = m_TeleporterIN.m_y+m_TeleporterIN.m_h;

			if(TRUE == IntersectRect(&r3,&r1,&r2))
			{
				m_Enemy[i].E_x=m_TeleporterOUT.m_x;
				m_Enemy[i].E_y=m_TeleporterOUT.m_y;
				break;

			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//인터페이스
/*void PGame::GameMenu(HDC hdc)//게임메뉴 건물설치,돈등등
{
	HDC MemDC;
	HBITMAP MyBitmap,OldBitmap;

	MemDC=CreateCompatibleDC(hdc);
	MyBitmap=LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
	BitBlt(hdc,1050, 250, 50, 50,MemDC,0,0,SRCCOPY);
	SelectObject(MemDC,OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);


	MemDC=CreateCompatibleDC(hdc);
	MyBitmap=LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
	BitBlt(hdc,1150, 250, 50, 50,MemDC,0,0,SRCCOPY);
	SelectObject(MemDC,OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
}*/
/////////////////////////////////////////////////////////////////////////////////////////////////////
//마우스 클릭시 건물설치,게임시작등등
void PGame::ButtonDown(WPARAM wParam, LPARAM lParam , HWND hWnd)
{
	x=(LOWORD(lParam)/50)*50;
	y=(HIWORD(lParam)/50)*50;
	///////////////////////////////////////////////////////////////
	//게임시작 OR 도움말
	if(m_MainMenu.MenuLife==1)
	{
		if(m_MainMenu.m_x <= x && x <= m_MainMenu.m_x+m_MainMenu.m_w)
		{
			if(m_MainMenu.m_y <= y && y <= m_MainMenu.m_y+m_MainMenu.m_h)
			{
				m_MainMenu.MenuLife=0;
				g_Sound.StopMp3();
				g_Sound.PlayMp3(hWnd,BG7);
			}
		}
		if(m_MainMenu.e_x <= x && x <= m_MainMenu.e_x+m_MainMenu.e_w)
		{
			if(m_MainMenu.e_y <= y && y <= m_MainMenu.e_y+m_MainMenu.e_h)
			{
				m_MainMenu.MenuLife=2;
				g_Sound.StopMp3();
				RanMP=rand()%7+1;
				switch(RanMP)
				{
				case 1:
					g_Sound.PlayMp3(hWnd,BG1);
					break;
				case 2:
					g_Sound.PlayMp3(hWnd,BG2);
					break;
				case 3:
					g_Sound.PlayMp3(hWnd,BG3);
					break;
				case 4:
					g_Sound.PlayMp3(hWnd,BG4);
					break;
				case 5:
					g_Sound.PlayMp3(hWnd,BG5);
					break;
				case 6:
					g_Sound.PlayMp3(hWnd,BG6);
					break;
				case 7:
					g_Sound.PlayMp3(hWnd,BG7);
					break;
				}
				
			}

		}
	}
	if(m_MainMenu.MenuLife==2)
	{
		if(50 <= x && x <= 200)
		{
			if(50 <= y && y <= 100)
			{
				m_MainMenu.MenuLife=1;				
				g_Sound.StopMp3();
				g_Sound.PlayMp3(hWnd,BG1);
			}
		}
	}
	/////////////////////////////////////////////////////////////////
	//설치
	if(m_MainMenu.MenuLife==0)
	{
		for(int i=0;i<SENTRY_COUNT;i++)
		{
			if(m_Tower[i].m_x <= x && x <= m_Tower[i].m_x)
			{
				if(m_Tower[i].m_y <= y && y <= m_Tower[i].m_y)
				{
					if(m_Tower[i].Life==1 && 130 <= m_Player.PGold )
					{
						m_Player.PGold-=130;
						SENTRYCLICK=TRUE;
						SetCapture(hWnd);
					}
					/////////////////////////////////////////////////////
					//센트리건 업그레이드
					if(m_Tower[i].Life==2)
					{
						if(m_Tower[i].Level < 3)
						{
							m_Tower[i].exp+=25;
							m_Player.PGold-=25;
						}
						if(m_Tower[i].exp==200)
						{
							m_Tower[i].Level+=1;
							m_Tower[i].exp=0;
						}
					}
				}
			}
		}

		for(int i=0;i<DISPENSER_COUNT;i++)
		{
			if(m_Dispenser[i].d_x <= x && x <= m_Dispenser[i].d_x)
			{
				if(m_Dispenser[i].d_y <= y && y <= m_Dispenser[i].d_y)
				{
					if(m_Dispenser[i].DispenserLife==1 && 100 <= m_Player.PGold )
					{
						m_Player.PGold-=100;
						DISPENSERCLICK=TRUE;
						SetCapture(hWnd);
					}
					//////////////////////////////////////////////////////////////
					//디스펜서 업그레이드
					if(m_Dispenser[i].DispenserLife==2)
					{
						if(m_Dispenser[i].Level < 3)
						{
							m_Dispenser[i].exp+=25;
							m_Player.PGold-=25;
						}
						if(m_Dispenser[i].exp==200)
						{
							m_Dispenser[i].Level+=1;
							m_Dispenser[i].exp=0;
						}						
					}
				}
			}
		}
		if(m_TeleporterIN.m_x <= x && x <= m_TeleporterIN.m_x+m_TeleporterIN.m_w)
		{
			if(m_TeleporterIN.m_y <= y && y <= m_TeleporterIN.m_y+m_TeleporterIN.m_h)
			{
				if(m_TeleporterIN.Life==1 && 1250 <= m_Player.PGold )
				{
					m_Player.PGold-=1250;
					TELEPORTERINCLICK=TRUE;
					SetCapture(hWnd);
				}
			}
		}
		if(m_TeleporterOUT.m_x <= x && x <= m_TeleporterOUT.m_x+m_TeleporterOUT.m_w)
		{
			if(m_TeleporterOUT.m_y <= y && y <= m_TeleporterOUT.m_y+m_TeleporterOUT.m_h)
			{
				if(m_TeleporterOUT.Life==1 && 1250 <= m_Player.PGold )
				{
					m_Player.PGold-=1250;
					TELEPORTEROUTCLICK=TRUE;
					SetCapture(hWnd);
				}
			}
		}
		////////////////////////////////////////////////////////////////
		//게임시작
		if(m_GameMenu.m_x <= x && x <= m_GameMenu.m_x+m_GameMenu.m_w)
		{
			if(m_GameMenu.m_y <= y && y <= m_GameMenu.m_y+m_GameMenu.m_h)
			{
				if(m_GameMenu.Life == 1)
				{
					m_GameMenu.Life=0;
					CheckStage++;
					g_Sound.StopMp3();
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////
//드래그 설치
void PGame::Drag(WPARAM wParam, LPARAM lParam,HWND hWnd)
{
	if(SENTRYCLICK==TRUE)
	{
		for(int i=0;i<SENTRY_COUNT;i++)
		{
			if(m_Tower[i].Life == 1)
			{
				m_Tower[i].m_x=(LOWORD(lParam)/50)*50;
				m_Tower[i].m_y=(HIWORD(lParam)/50)*50;
			}
		}
	}

	if(DISPENSERCLICK==TRUE)
	{
		for(int i=0;i<DISPENSER_COUNT;i++)
		{
			if(m_Dispenser[i].DispenserLife == 1)
			{
				m_Dispenser[i].d_x=(LOWORD(lParam)/50)*50;
				m_Dispenser[i].d_y=(HIWORD(lParam)/50)*50;
			}
		}
	}

	if(TELEPORTERINCLICK==TRUE)
	{
		if(m_TeleporterIN.Life==1)
		{
			m_TeleporterIN.m_x=(LOWORD(lParam)/50)*50;
			m_TeleporterIN.m_y=(HIWORD(lParam)/50)*50;
		}
	}
	if(TELEPORTEROUTCLICK==TRUE)
	{
		if(m_TeleporterOUT.Life==1)
		{
			m_TeleporterOUT.m_x=(LOWORD(lParam)/50)*50;
			m_TeleporterOUT.m_y=(HIWORD(lParam)/50)*50;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//설치
void PGame::ButtonUp(WPARAM wParam, LPARAM lParam)
{
	RanMP=rand()%2+1;
	if(TRUE==SENTRYCLICK)
	{
		for(int i=0;i<SENTRY_COUNT;i++)
		{
			if(m_Tower[i].Life == 1 && SENTRYCLICK==TRUE && true==SentryMap())
			{
				SENTRYCLICK=FALSE;
				ReleaseCapture();
				switch(RanMP)
				{
				case 1:
					g_Sound.PlayWave(WAV2,0);
				break;
				case 2:
					g_Sound.PlayWave(WAV3,0);
					break;
				}
				m_Tower[i].m_rx = m_Tower[i].m_x - 150;
				m_Tower[i].m_ry = m_Tower[i].m_y - 150;
				m_Tower[i].m_rw = m_Tower[i].m_rx + 300;
				m_Tower[i].m_rh = m_Tower[i].m_ry + 300;
				m_Tower[i].Life=2;
				m_Tower[i+1].Life=1;
				break;
			}
			if(m_Tower[i].Life == 1 && SENTRYCLICK==TRUE && false == SentryMap())
			{
				SENTRYCLICK=FALSE;
				ReleaseCapture();
				m_Player.PGold+=130;
				m_Tower[i].m_x = 1050;
				m_Tower[i].m_y = 250;
				break;
			}
		}
	}
	else if(TRUE==DISPENSERCLICK)
	{
		for(int i=0;i<DISPENSER_COUNT;i++)
		{
			if(m_Dispenser[i].DispenserLife == 1 && DISPENSERCLICK==TRUE && true==DispenserMap())
			{
				switch(RanMP)
				{
				case 1:
					g_Sound.PlayWave(WAV4,0);
				break;
				case 2:
					g_Sound.PlayWave(WAV5,0);
					break;
				}
				DISPENSERCLICK=FALSE;
				ReleaseCapture();
				m_Dispenser[i].d_rx = m_Dispenser[i].d_x - 200;
				m_Dispenser[i].d_ry = m_Dispenser[i].d_y - 200;
				m_Dispenser[i].d_rw = m_Dispenser[i].d_rx + 400;
				m_Dispenser[i].d_rh = m_Dispenser[i].d_ry + 400;
				m_Dispenser[i].DispenserLife=2;
				m_Dispenser[i+1].DispenserLife=1;
				break;
			}
			if(m_Dispenser[i].DispenserLife == 1 && DISPENSERCLICK==TRUE && false==DispenserMap())
			{
				DISPENSERCLICK=FALSE;
				ReleaseCapture();
				m_Player.PGold+=100;
				m_Dispenser[i].d_x = 1150;
				m_Dispenser[i].d_y = 250;

				break;
			}
		}
	}
	else if(TRUE==TELEPORTERINCLICK)
	{
		if(m_TeleporterIN.Life == 1 && TELEPORTERINCLICK==TRUE && true==TeleporterINMap())
		{
			TELEPORTERINCLICK=FALSE;
			ReleaseCapture();
			switch(RanMP)
			{
			case 1:
				g_Sound.PlayWave(WAV6,0);
				break;
			case 2:
				g_Sound.PlayWave(WAV7,0);
				break;
			}
			m_TeleporterIN.Life=2;
		}
		if(m_TeleporterIN.Life == 1 && TELEPORTERINCLICK==TRUE && false == TeleporterINMap())
		{
			TELEPORTERINCLICK=FALSE;
			ReleaseCapture();
			m_Player.PGold+=1250;
			m_TeleporterIN.m_x = 1050;
			m_TeleporterIN.m_y = 350;
		}
	}
	else if(TRUE==TELEPORTEROUTCLICK)
	{
		if(m_TeleporterOUT.Life == 1 && TELEPORTEROUTCLICK==TRUE && true==TeleporterOUTMap())
		{
			TELEPORTEROUTCLICK=FALSE;
			ReleaseCapture();
			switch(RanMP)
			{
			case 1:
				g_Sound.PlayWave(WAV6,0);
				break;
			case 2:
				g_Sound.PlayWave(WAV7,0);
				break;
			}
			m_TeleporterOUT.Life=2;
		}
		if(m_TeleporterOUT.Life == 1 && TELEPORTEROUTCLICK==TRUE && false == TeleporterOUTMap())
		{
			TELEPORTEROUTCLICK=FALSE;
			ReleaseCapture();
			m_Player.PGold+=1250;
			m_TeleporterOUT.m_x = 1150;
			m_TeleporterOUT.m_y = 350;
		}
	}
}

void PGame::RButtonDown(WPARAM wParam, LPARAM lParam)
{
	x=(LOWORD(lParam)/50)*50;
	y=(HIWORD(lParam)/50)*50;
	/////////////////////////////////////////////////////////
	//
	for(int i=0;i<SENTRY_COUNT;i++)
	{
		if(m_Tower[i].m_x <= x && x <= m_Tower[i].m_x)
		{
			if(m_Tower[i].m_y <= y && y <= m_Tower[i].m_y)
			{
				if(m_Tower[i].Life==2)
				{
					m_Tower[i].m_Info=1;
				}
			}
		}
	}
}
void PGame::RButtonUp(WPARAM wParam, LPARAM lParam)
{
	for(int i=0;i<SENTRY_COUNT;i++)
	{
		m_Tower[i].m_Info=0;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//센트리 건설체크
bool PGame::SentryMap(void)
{
	for(int s=0;s<SENTRY_COUNT;s++)
	{
		for(int i=0;i<YMAP;i++)
		{
			for(int j=0;j<XMAP;j++)
			{
				if(m_Map.p_Map[i][j]==0 && j*SIZE == m_Tower[s].m_x && i*SIZE == m_Tower[s].m_y && m_Tower[s].Life == 1)
				{
					m_Map.p_Map[i][j]=2;
					return true;
					break;
				}
			}
		}
	}
	return false;
}
//////////////////////////////////////////
//디스펜서 건설체크
bool PGame::DispenserMap(void)
{
	for(int s=0;s<DISPENSER_COUNT;s++)
	{
		for(int i=0;i<YMAP;i++)
		{
			for(int j=0;j<XMAP;j++)
			{
				if(m_Map.p_Map[i][j]==0 && j*SIZE == m_Dispenser[s].d_x && i*SIZE == m_Dispenser[s].d_y && m_Dispenser[s].DispenserLife == 1)
				{
					m_Map.p_Map[i][j]=3;
					return true;
					break;
				}
			}
		}
	}
	return false;
}

bool PGame::TeleporterINMap(void)
{

	for(int i=0;i<YMAP;i++)
	{
		for(int j=0;j<XMAP;j++)
		{
			if(m_Map.p_Map[i][j]==1 && j*SIZE == m_TeleporterIN.m_x && i*SIZE == m_TeleporterIN.m_y && m_TeleporterIN.Life == 1)
			{
				m_Map.p_Map[i][j]=4;
				return true;
				break;
			}
		}
	}

	return false;
}

bool PGame::TeleporterOUTMap(void)
{
	for(int i=0;i<YMAP;i++)
	{
		for(int j=0;j<XMAP;j++)
		{
			if(m_Map.p_Map[i][j]==1 && j*SIZE == m_TeleporterOUT.m_x && i*SIZE == m_TeleporterOUT.m_y && m_TeleporterOUT.Life == 1)
			{
				m_Map.p_Map[i][j]=5;
				return true;
				break;
			}
		}
	}
	return false;
}

void PGame::GameOverCheck(void)
{
	for(int i=0;i<ENEMY_COUNT;i++)
	{
		if(800 <= m_Enemy[i].E_y)
		{
			m_Player.PLife--;
		}
	}
	if(false == m_Player.PlayerLife())
	{
		exit(1);
	}
}
