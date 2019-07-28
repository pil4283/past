#pragma once

#include <vector>
using namespace std;

#define LOOP_INFINITE -1



typedef struct _S_ACTION
{
	int w;
	int h;
	COLORREF color;
	HBITMAP hBitmap;
	int f_size;
	int type; // 0:세로, 1:가로 
}S_ACTION;


class KObject
{
public:
	KObject(void);
	~KObject(void);
private:
	vector<S_ACTION> m_vAction;
	
public:	
	int m_xpos;
	int m_ypos;
	int m_findex;
	int m_aindex;
	int m_loop;

	int m_dx;
	int m_dy;
	int m_interval;
 
	BOOL SetActiveAction(int aindex,int loop,int dx,int dy,int interval);
	void Draw(HDC hdc);
	int AddAction(HBITMAP hBitmap,COLORREF color,int w,int h,int f_size,int type);
	BOOL NextFrame();
	void StopAction(void);
};
