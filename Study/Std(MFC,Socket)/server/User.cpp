#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include "User.h"

S_USER g_aUser[MAX_USER];

void IniUser()
{
	for(int i=0;i<MAX_USER;i++)
	{
		g_aUser[i].check = -1;
	}
}

int GetEmptyUser(SOCKET cid)
{
	for(int i=0;i<MAX_USER;i++)
	{
		if(-1 == g_aUser[i].check)
		{
			g_aUser[i].check = 1;
			g_aUser[i].cid = cid;
			g_aUser[i].ready = false;
			return i;
		}
	}
	return -1;
}
