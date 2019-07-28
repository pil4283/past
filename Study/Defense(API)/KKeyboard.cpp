#include "StdAfx.h"
#include "KKeyboard.h"

KKeyboard::KKeyboard(void)
{
	Clear();
}

KKeyboard::~KKeyboard(void)
{

}

void KKeyboard::OnKeyDown(int key)
{
	if(-1==FindKey(key))
	{
		for(int i=0;i<MAX_KEYBUFF_SIZE;i++)
		{
			if(-1==m_aKeyBuff[i])
			{
				m_aKeyBuff[i]=key;
				return;
			}
		}
	}
}

void KKeyboard::OnKeyUp(int key)
{
	int index;

	index=FindKey(key);
	if( -1 != index)
	{
		m_aKeyBuff[index]=-1;
	}
}

void KKeyboard::Clear(void)
{
	for(int i=0;i<MAX_KEYBUFF_SIZE;i++)
	{
		m_aKeyBuff[i]=-1;
	}
}
// -1: ¾øÀ½. 
int KKeyboard::FindKey(int key)
{
	for(int i=0;i<MAX_KEYBUFF_SIZE;i++)
	{
		if(key==m_aKeyBuff[i])
		{
			return i;
		}
	}

	return -1;
}
