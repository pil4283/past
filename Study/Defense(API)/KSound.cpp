#include "StdAfx.h"
#include "KSound.h"

#include <vfw.h>

extern HINSTANCE hInst;

KSound::KSound(void)
{
	m_Video=NULL;

	m_h1 = -1;
	m_h2 = -1;
}

KSound::~KSound(void)
{
}
BOOL KSound::PlayMp3(HWND hWnd,TCHAR* path)
{	
	if(NULL != m_Video)
		StopMp3();

	m_Video = MCIWndCreate(hWnd,
		  hInst,
		  WS_CHILD | MCIWNDF_NOMENU,path);
	MCIWndPlay(m_Video);
	return TRUE;
}

void KSound::StopMp3()
{
	MCIWndStop(m_Video);
	if(m_Video !=NULL)
	{
		MCIWndDestroy(m_Video);
		
	}
}

void KSound::PlayWave(TCHAR* filename, int ch)
{
	if( 0 == ch )
	{
		if( -1 != m_h1)
		{
			//0번채널 사운드 디바이스가 열려있다면 닫는다.
			mciSendCommand(m_h1, MCI_CLOSE, 0, (DWORD)NULL);
		}
	}
	else
	{
		if( -1 != m_h2)
		{
		//1번채널 사운드 디바이스가 열려있다면 닫는다.
		mciSendCommand(m_h2, MCI_CLOSE, 0, (DWORD)NULL);
		}
	}

	MCI_OPEN_PARMS a;
	MCI_PLAY_PARMS b;
	DWORD r;
	a.lpstrDeviceType = _T("WaveAudio");
	a.lpstrElementName = filename;
	// 사운드 카드를 열어 핸들을 확보
	r = mciSendCommand(ch, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&a);
	//if( r )
	//{
	//}
	UINT chid;
	chid = a.wDeviceID; //채널번호를 넘겨준다.
	//핸들을 이용해 플레이 명령을 내린다.
	mciSendCommand(chid, MCI_PLAY, 0, (DWORD)(LPVOID)&b);
	// 정지 명령도 여러가지가 있을수있으나 가장 확실한것은 디바이스를 닫는것이다.
	if( 0 == ch ) //0번 채널
	{
		m_h1 = chid;
	}
	else //1번 채널
	{
		m_h2 = chid;
	}
}