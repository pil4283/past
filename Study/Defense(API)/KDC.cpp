#include "StdAfx.h"
#include "KDC.h"

#pragma comment(lib,"Msimg32.lib")

KDC::KDC(void)
{
}

KDC::~KDC(void)
{
}
void KDC::DrawBitmap(HDC hdc,int x,int y,HBITMAP myBitmap)
{
	HDC memDC;
	HBITMAP  oldBitmap;
	BITMAP bit;

	GetObject(myBitmap,sizeof(BITMAP),&bit);
	memDC=CreateCompatibleDC(hdc);
	oldBitmap=(HBITMAP)SelectObject(memDC,myBitmap);
	
	BitBlt(hdc,x,y,bit.bmWidth,bit.bmHeight,memDC,0,0,SRCCOPY);

	SelectObject(memDC,oldBitmap);
	DeleteObject(memDC);
}

void KDC::DrawBitmap(HDC hdc,int x,int y,int w,int h,HBITMAP myBitmap,int sx,int sy)
{
	HDC memDC;
	HBITMAP  oldBitmap;
	BITMAP bit;

	GetObject(myBitmap,sizeof(BITMAP),&bit);
	memDC=CreateCompatibleDC(hdc);
	oldBitmap=(HBITMAP)SelectObject(memDC,myBitmap);
	
	BitBlt(hdc,x,y,w,h,memDC,sx,sy,SRCCOPY);
 

	SelectObject(memDC,oldBitmap);
	DeleteObject(memDC);
}
void KDC::DrawBitmap(HDC hdc,int x,int y,int w,int h,HBITMAP myBitmap,int sx,int sy,int sw,int sh)
{
	HDC memDC;
	HBITMAP  oldBitmap;
	BITMAP bit;

	GetObject(myBitmap,sizeof(BITMAP),&bit);
	memDC=CreateCompatibleDC(hdc);
	oldBitmap=(HBITMAP)SelectObject(memDC,myBitmap);
	
	 
	StretchBlt(hdc,x,y,w,h,memDC,sx,sy,sw,sh,SRCCOPY);

	SelectObject(memDC,oldBitmap);
	DeleteObject(memDC);
}
///////////////////////////////////////////////
// Trans 
void KDC::DrawBitmapTrans(HDC hdc,int x,int y,HBITMAP myBitmap,COLORREF color)
{
	HDC memDC;
	HBITMAP  oldBitmap;
	BITMAP bit;

	GetObject(myBitmap,sizeof(BITMAP),&bit);
	memDC=CreateCompatibleDC(hdc);
	oldBitmap=(HBITMAP)SelectObject(memDC,myBitmap);
	
	TransparentBlt(hdc,x, y, bit.bmWidth,bit.bmHeight,memDC,0, 0, bit.bmWidth, bit.bmHeight, color);

	SelectObject(memDC,oldBitmap);
	DeleteObject(memDC);
}
void KDC::DrawBitmapTrans(HDC hdc,int x,int y,int w,int h,HBITMAP myBitmap,int sx,int sy,COLORREF color)
{
	HDC memDC;
	HBITMAP  oldBitmap;
	BITMAP bit;

	GetObject(myBitmap,sizeof(BITMAP),&bit);
	memDC=CreateCompatibleDC(hdc);
	oldBitmap=(HBITMAP)SelectObject(memDC,myBitmap);
	
	TransparentBlt(hdc,x, y, w,h,memDC,sx, sy,w,h, color);
 

	SelectObject(memDC,oldBitmap);
	DeleteObject(memDC);
}
void KDC::DrawBitmapTrans(HDC hdc,int x,int y,int w,int h,HBITMAP myBitmap,int sx,int sy,int sw,int sh,COLORREF color)
{
	HDC memDC;
	HBITMAP  oldBitmap;
	BITMAP bit;

	GetObject(myBitmap,sizeof(BITMAP),&bit);
	memDC=CreateCompatibleDC(hdc);
	oldBitmap=(HBITMAP)SelectObject(memDC,myBitmap);
	
	 
	TransparentBlt(hdc,x, y, w,h,memDC,sx, sy,sw,sh, color);

	SelectObject(memDC,oldBitmap);
	DeleteObject(memDC);
}