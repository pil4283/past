#pragma once
#include "PPlayer.h"

class PEnemy
{
public:
	PEnemy(void);
	~PEnemy(void);
	void DrawEnemy(HDC hdc);
	void MoveEnemy();
	int E_x;
	int E_y;
	int E_h;
	int E_w;
	int EnemyLife;
	int EnemyHP;
	char temp[80];
	PPlayer Player;
	int EnemyFHP;
	int SPEED;
	HBITMAP m_Enemy1;
	HINSTANCE g_hinst;
	void EnemyIni(HWND hWnd, HINSTANCE hinst);
	bool LEFT;
	bool RIGHT;
	bool UP;
	bool DOWN;
	int s_x;
	int s_y;
};
