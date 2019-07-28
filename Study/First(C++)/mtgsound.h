/* -----------------------------------------
   Copyright(C) by clccclcc 2011.6
	For Windows Only
 --------------------------------------------*/
#pragma once

#include <windows.h>
#include <mmsystem.h>

int  MTGGetVolume();
void MTGSetVolume( DWORD volume );
DWORD MTGGetLength();
DWORD MTGGetPosition();
DWORD MTGGetMode();
void MTGSetPosition(DWORD dwPos);
BOOL MTGStop();
BOOL MTGPlay();
BOOL MTGPause();
void MTGOpen(LPSTR filename);

void MTGPlayWave(char* filename, int ch);
