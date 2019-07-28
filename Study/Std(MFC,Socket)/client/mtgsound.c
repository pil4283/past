#pragma once

#include <windows.h>
#include <mmsystem.h>
 
#pragma comment(lib,"winmm.lib")

#define     MCI_SETAUDIO              0x0873 
#define     MCI_DGV_SETAUDIO_VOLUME    0x4002 
#define     MCI_DGV_SETAUDIO_ITEM      0x00800000 
#define     MCI_DGV_SETAUDIO_VALUE     0x01000000 
#define     MCI_DGV_STATUS_VOLUME  0x4019


typedef struct 
{ 
	DWORD dwCallback; 
	DWORD dwItem; 
	DWORD dwValue; 
	DWORD dwOver; 
	LPSTR lpstrAlgorithm; 
	LPSTR lpstrQuality; 
} MCI_DGV_SETAUDIO_PARMS; 
/////////////////////////////////////////
MCI_OPEN_PARMS mciOpenParms;
DWORD wDeviceID;
LONG m_nTotalTime;
MCI_PLAY_PARMS  mciPlayParms;

UINT m_h1=-1;
UINT m_h2=-1;
/////////////////////////////////////



/////////////////////////////////////////
void MTGOpen(LPSTR filename)
{
    MCI_STATUS_PARMS mciStatusParms;

    mciOpenParms.lpstrElementName = filename;                           //화일 설정
    mciOpenParms.lpstrDeviceType = "MPEGVideo";                     //디바이스 를 waveaudio로
    mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT|MCI_OPEN_TYPE,
                    (DWORD)(LPVOID)&mciOpenParms);          //MCI_OPEN 명령을 준다.
    wDeviceID = mciOpenParms.wDeviceID;                     //열린 디바이스 아이디를 받느다.
    mciStatusParms.dwItem = MCI_STATUS_LENGTH;
    mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);
    m_nTotalTime = (LONG)mciStatusParms.dwReturn;
}
BOOL MTGPause()
{

    mciSendCommand(wDeviceID,MCI_PAUSE,MCI_NOTIFY,
                    (DWORD)(LPVOID) &mciPlayParms);
    return TRUE;
}
BOOL MTGPlay()
{
    mciSendCommand(wDeviceID,MCI_PLAY,MCI_NOTIFY,
                    (DWORD)(LPVOID) &mciPlayParms);
    return TRUE;
}

BOOL MTGStop()
{
    mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
    return TRUE;
}

void MTGSetPosition(DWORD dwPos)
{

    MCI_SEEK_PARMS mciSeekParms;
    mciSeekParms.dwTo = dwPos;
    mciSendCommand(wDeviceID, MCI_SEEK, MCI_TO, (DWORD)(LPVOID)&mciSeekParms);
    MTGPlay();
}

DWORD MTGGetMode()
{

    DWORD dwMode;
    MCI_STATUS_PARMS mciStatusParms;

    mciStatusParms.dwItem = MCI_STATUS_MODE;
    mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);
    dwMode = (LONG)mciStatusParms.dwReturn;

    return dwMode;
}
 

DWORD MTGGetPosition()
{

    DWORD nTime;

    MCI_STATUS_PARMS mciStatusParms;
    mciStatusParms.dwItem = MCI_STATUS_POSITION;
    mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);

    nTime = (LONG)mciStatusParms.dwReturn;
    return nTime;
}

DWORD MTGGetLength()
{

    DWORD nTime;
    MCI_STATUS_PARMS mciStatusParms;

    mciStatusParms.dwItem = MCI_STATUS_LENGTH;
    mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);
    nTime = (LONG)mciStatusParms.dwReturn;

    return nTime;
}
void MTGSetVolume( DWORD volume ) 
{    //Volume: 0 - 1000 
	MCI_DGV_SETAUDIO_PARMS  p;

	if( volume>100 ) volume=100; 
	if( volume<0   ) volume=0; 

	volume *= 10; 

	p.dwCallback = 0; 
	p.dwItem     = MCI_DGV_SETAUDIO_VOLUME; 
	p.dwValue    = volume; 
	p.dwOver     = 0; 
	p.lpstrAlgorithm = NULL; 
	p.lpstrQuality   = NULL; 

	mciSendCommand( wDeviceID, MCI_SETAUDIO,MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&p ); 
} 

int MTGGetVolume() 
{ 
  MCI_STATUS_PARMS p; 

  p.dwCallback = 0; 
  p.dwItem     = MCI_DGV_STATUS_VOLUME; 
  mciSendCommand( wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&p ); 

  return (int)(p.dwReturn/10);  // Volume: 0 - 1000  
} 

void MTGPlayWave(char* filename, int ch)
{
	MCI_OPEN_PARMS a;
	MCI_PLAY_PARMS b;
	DWORD r;
	UINT chid;
	

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

	
	a.lpstrDeviceType = "WaveAudio";
	a.lpstrElementName = filename;
	// 사운드 카드를 열어 핸들을 확보
	r = mciSendCommand(ch, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&a);
	//if( r )
	//{
	//}
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


