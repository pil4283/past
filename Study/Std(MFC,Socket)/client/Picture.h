#pragma once
#include "afxwin.h"

class CDCView;

class Picture
{
public:
	Picture(void);
	~Picture(void);

	CBitmap m_bitmap;
	CBitmap m_bitmap2;
	CBitmap m_bitmap3;
	CBitmap m_bitmap4;
	CBitmap m_bitmap5;
	CBitmap m_bitmap6;
	CDC m_dc;
	CDC m_dc2;
	CDC m_dc3;
	CDC m_dc4;
	CDC m_dc5;
	CDC m_dc6;

	CDC m_bBufferDC;
	CBitmap m_bBuffer;
	//int a;


	CDCView* m_pView;

	int stage;
	int isCollect[5];

	void Create(void);
	void Draw(CDC* pDC);
	void CheckCollect(int index);
	void Collect(CDC* pDC);
	void IniCollect(void);

};
