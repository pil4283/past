#pragma once
#include "afxwin.h"

class CDCView;

#define MAX_USER 2

class Player
{
public:
	Player(void);
	~Player(void);

	int m_x;
	int m_y;
	int m_w;
	int m_h;
	int m_index;
	char m_id[20];
	bool ready;

	CDCView* m_pView;
	
	void Draw(CDC* pDC);
	int m_CCount;
	CBitmap m_Pb;
	CBitmap m_bB;
	CDC m_PbDC;
	CDC m_bBDC;
	void Create(void);
};
