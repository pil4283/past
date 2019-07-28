#pragma once

class KDBuffer
{
public:
	KDBuffer(void);
	~KDBuffer(void);
	HDC InitDBuffer(HDC hdc,int w,int h);
	void Draw();

private:
	HBITMAP m_hOldBitmap;
	HDC m_hMemDC;
	int m_w;
	int m_h;
	HDC m_hdc;
	HBITMAP m_hBackBit;


};
