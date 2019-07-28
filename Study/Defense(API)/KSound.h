#pragma once

#include <mmsystem.h>

#pragma comment(lib,"VFW32.lib")
#pragma comment(lib,"winmm.lib")

class KSound
{
public:
	KSound(void);
	~KSound(void);

public:
	void StopMp3();
	BOOL PlayMp3(HWND hWnd,TCHAR* path);
	
	void PlayWave(TCHAR* filename, int ch);


private:
	HWND m_Video;
	UINT m_h1;
	UINT m_h2;
};
