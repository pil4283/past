#include "StdAfx.h"
#include "PPlayer.h"
#include <iostream>
using namespace std;

PPlayer::PPlayer(void)
{
	PGold=1000;
	PLife=10;
}

PPlayer::~PPlayer(void)
{
}

bool PPlayer::PlayerLife(void)
{
	if(1 <= PLife)
	{
		return true;
	}
	if(PLife == 0)
	{
		return false;
	}
	return false;
}

void PPlayer::PlayerDraw(HDC hdc)
{
	sprintf(temp,"gold : %d",PGold);
	TextOut(hdc,1200,100,temp,strlen(temp));
}