#pragma once

class JMainMenu
{
public:
	JMainMenu(void);
	~JMainMenu(void);
	void DrawMain(HDC hdc);
	void MainIni(HWND hWnd, HINSTANCE hInst);
	HBITMAP m_Main;
	HINSTANCE g_hInst;
	int MenuLife;
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	int e_x;
	int e_y;
	int e_w;
	int e_h;
	HBITMAP m_Help;
	int b_x;
	int b_y;
	int b_w;
	int b_h;
};
