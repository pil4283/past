#pragma once
#include "PEnemy.h"
//#include "PTower.h"
#define ENEMY_COUNT 30
#define XMAP 20
#define YMAP 16
#define SIZE 50


class PMap
{
public:
	PMap(void);
	~PMap(void);
	void DrawMap(HDC hdc);
	int p_Map[YMAP][XMAP];
	void DrawSentryGun(HDC hdc);
	void DrawDispenser(HDC hdc);
	void DrawEnemyMap(HDC hdc);
	void DrawTeleporterIN(HDC hdc);
	HBITMAP m_Map;
	HINSTANCE g_hinst;
	HBITMAP p_Sentry;
	void IniMap(HWND hWnd, HINSTANCE hInst);
	HBITMAP p_Dispenser;
	HBITMAP p_Teleporter;
//	PEnemy m_Enemy[10];
//	PTower m_Tower[SENTRY_COUNT];
	void CheckEnemy(HDC hdc);
};
