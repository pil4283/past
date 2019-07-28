#pragma once
#include "clccapilib\ksound.h"

class PGameMenu
{
public:
	PGameMenu(void);
	~PGameMenu(void);
	void MenuDraw(HDC hdc);
	int Life;
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	HINSTANCE g_hinst;
	HBITMAP m_Menu;
	void GameMenuIni(HWND hWnd,HINSTANCE hInst);
	KSound g_Sound;
};
