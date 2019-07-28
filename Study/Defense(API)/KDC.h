#pragma once

class KDC
{
public:
	KDC(void);
	~KDC(void);

	static void DrawBitmap(HDC hdc,int x,int y,HBITMAP myBitmap);
	static void DrawBitmap(HDC hdc,int x,int y,int w,int h,HBITMAP myBitmap,int sx,int sy);
	static void DrawBitmap(HDC hdc,int x,int y,int w,int h,HBITMAP myBitmap,int sx,int sy,int sw,int sh);

	static void DrawBitmapTrans(HDC hdc,int x,int y,HBITMAP myBitmap,COLORREF color);
	static void DrawBitmapTrans(HDC hdc,int x,int y,int w,int h,HBITMAP myBitmap,int sx,int sy,COLORREF color);
	static void DrawBitmapTrans(HDC hdc,int x,int y,int w,int h,HBITMAP myBitmap,int sx,int sy,int sw,int sh,COLORREF color);
};
