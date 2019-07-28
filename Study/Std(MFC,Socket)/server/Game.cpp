#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "User.h"
#include "protocol.h"
#include "sqlite3.h"
using namespace std;

int stage=0;
int Collect[5];
void NextStage(int count);

void RunEnd()
{
	if(g_aUser[0].count < g_aUser[1].count)
	{
		SendEnd(1);
	}
	else
	{
		SendEnd(0);
	}
}

void RunLogin(int index,char* id)
{
	printf("[%d번] %s님이 접속\n",index,id);
	strcpy(g_aUser[index].id,id);
	int ret=1;
	
	SendRlogin(index,id,ret);
	//모든 사용자에게 새로운 사용자 접속 알리기
	SendNuser(index,id);
	if(index != 0)
	{
		SendOldUser(g_aUser[0].id,g_aUser[0].index,index);
	}
}
void isCollect(int index,int x,int y)
{
	int count=0;
	printf("좌표 = %d %d",x,y);
	if(stage == 1)
	{
		if((495 <= x && x <= 555) || (1151 <= x && x <= 1211))
		{
			if(433 <= y&& y <= 493)
			{
				if(Collect[0] != 1)
				{
					Collect[0]=1;
					SendCollect(index,stage,0);
				}
			}
		}
		if((586 <= x && x <= 646) || (1242 <= x && x <= 1302))
		{
			if(495 <= y && y <= 555)
			{
				if(Collect[1] != 1)
				{
					Collect[1]=1;
					SendCollect(index,stage,1);
				}
			}
		}
		if((537 <= x && x <= 597) || (1193 <= x && x <= 1223))
		{
			if(123 <= y && y <= 183)
			{
				if(Collect[2] != 1)
				{
					Collect[2]=1;
					SendCollect(index,stage,2);
				}
			}
		}
		if((447 <= x && x <= 507) || (1103 <= x && x <= 1163))
		{
			if(242 <= y && y <= 272)
			{
				if(Collect[3] != 1)
				{
					Collect[3]=1;
					SendCollect(index,stage,3);
				}
			}
		}
		if((520 <= x && x <= 580) || (1176 <= x && x <= 1236))
		{
			if(496 <= y && y <= 556)
			{
				if(Collect[4] != 1)
				{
					Collect[4]=1;
					SendCollect(index,stage,4);
				}
			}
		}
	}
	////////////////////////////////
	else if(stage == 2)
	{
		if((470 <= x && x <= 530) || (1101 <= x && x <= 1161))
		{
			if(602 <= y && y <= 662)
			{
				if(Collect[0] != 1)
				{
					Collect[0]=1;
					SendCollect(index,stage,0);
				}
			}
		}
		if((472 <= x && x <= 532) || (1103 <= x && x <= 1163))
		{
			if(158 <= y && y <= 218)
			{
				if(Collect[1] != 1)
				{
					Collect[1]=1;
					SendCollect(index,stage,1);
				}
			}
		}
		if((458 <= x && x <= 518)||(1089 <= x && x <= 1149))
		{
			if(432 <= y && y <= 492)
			{
				if(Collect[2] != 1)
				{
					Collect[2]=1;
					SendCollect(index,stage,2);
				}
			}
		}
		if((367 <= x && x <= 427) || (998 <= x && x <= 1058))
		{
			if(40 <= y && y <= 100)
			{
				if(Collect[3] != 1)
				{
					Collect[3]=1;
					SendCollect(index,stage,3);
				}
			}
		}
		if((332 <= x && x <= 392) || (963 <= x && x <= 1023))
		{
			if(195 <= y && y <= 255)
			{
				if(Collect[4] != 1)
				{
					Collect[4]=1;
					SendCollect(index,stage,4);
				}
			}
		}
	}
	///////////////////////////////////
	else if(stage == 3)
	{
		if((240 <= x && x <= 300) || (901 <= x && x <= 961))
		{
			if(590 <= y && y <= 650)
			{
				if(Collect[0] != 1)
				{
					Collect[0]=1;
					SendCollect(index,stage,0);
				}
			}
		}
		if((14 <= x && x <= 74) || (675 <= x && x <= 735))
		{
			if(566 <= y && y <= 626)
			{
				if(Collect[1] != 1)
				{
					Collect[1]=1;
					SendCollect(index,stage,1);
				}
			}
		}
		if((159 <= x && x <= 219) || (820 <= x && x <= 880))
		{
			if(82 <= y && y <= 142)
			{
				if(Collect[2] != 1)
				{
					Collect[2]=1;
					SendCollect(index,stage,2);
				}
			}
		}
		if((284 <= x && x <= 344) || (945 <= x && x <= 1005))
		{
			if(238 <= y && y <= 298)
			{
				if(Collect[3] != 1)
				{
					Collect[3]=1;
					SendCollect(index,stage,3);
				}
			}
		}
		if((515 <= x && x <= 595) || ( 1176 <= x && x <= 1236))
		{
			if(485 <= y && y <= 545)
			{
				if(Collect[4] != 1)
				{
					Collect[4]=1;
					SendCollect(index,stage,4);
				}
			}
		}
	}
	///////////////////////////////////
	else if(stage ==4)
	{
		if((363 <= x && x <= 423) || (831 <= x && x <= 891))
		{
			if(641 <= y && y <= 701)
			{
				if(Collect[0] != 1)
				{
					Collect[0]=1;
					SendCollect(index,stage,0);
				}
			}
			if(472 <= y && y <= 532)
			{
				if(Collect[1] != 1)
				{
					Collect[1]=1;
					SendCollect(index,stage,1);
				}
			}
		}
		if((194 <= x && x <= 254) || (662 <= x && x <= 722))
		{
			if(144 <= y && y <= 204)
			{
				Collect[2] = 1;
				SendCollect(index,stage,2);
			}
		}
		if((305 <= x && x <= 365) || (773 <= x && x <= 833))
		{
			if(640 <= y && y <= 700)
			{
				if(Collect[3] != 1)
				{
					Collect[3]=1;
					SendCollect(index,stage,3);
				}
			}
		}
		if((204 <= x && x <= 264) || (672 <= x && x <= 732))
		{
			if(299 <= y  && y <= 359)
			{
				if(Collect[4] != 1)
				{
					Collect[4]=1;
					SendCollect(index,stage,4);
				}
			}
		}
	}
	///////////////////////////////////
	else if(stage == 5)
	{
		if((470 <= x && x <= 500) || (970 <= x && x <= 1000))
		{
			if(20 <= y && y <= 100)
			{
				if(Collect[0] != 1)
				{
					Collect[0]=1;
					SendCollect(index,stage,0);
				}
			}
		}
		if((460 <= x && x <= 480) || (960 <= x && x <= 980))
		{
			if(170 <= y && y <= 200)
			{
				if(Collect[1] != 1)
				{
					Collect[1]=1;
					SendCollect(index,stage,1);
				}
			}
		}
		if((240 <= x && x <= 270) || (740 <= x && x <= 770))
		{
			if(300 <= y && y <= 320)
			{
				if(Collect[2] != 1)
				{
					Collect[2]=1;
					SendCollect(index,stage,2);
				}
			}
		}
		if((290 <= x && x <= 330) || (790 <= x && x <=830))
		{
			if(440 <= y && y <= 480)
			{
				if(Collect[3] != 1)
				{
					Collect[3]=1;
					SendCollect(index,stage,3);
				}
			}
		}
		if((270 <= x && x <= 310) || (770 <= x && x <= 810))
		{
			if(490 <= y && y <= 530)
			{
				if(Collect[4] != 1)
				{
					Collect[4]=1;
					SendCollect(index,stage,4);
				}
			}
		}
	}
}
void NextStage(int count)
{
	/*if(count == 5)
	{
		if(stage == 5)
		{
			SendEnd();
		}
		else
		{
			SendNextStage(stage);
			count=0;
			for(int i=0;i<5;i++)
			{
				Collect[i]=-1;
			}
		}
	}*/
}

DWORD WINAPI RunGame(LPVOID para)
{
	SOCKET cid = (SOCKET)para;
	
	int Uindex = GetEmptyUser(cid);

	if(-1 == Uindex)
	{
		printf("close Socket\n");
		closesocket(cid);
	}
	printf("Uindex=%d 접속함\n",Uindex);
	g_aUser[Uindex].index = Uindex;
	g_aUser[Uindex].count = 0;
	printf("Uindex=%d\n",Uindex);
	while(1)
	{
		S_H h;
		memset(&h,0,sizeof(h));
		//ZeroMemory(&h,sizeof(h));
		int re = recv(cid,(char*)&h,sizeof(h),0);
		if(SOCKET_ERROR == re)
		{
			closesocket(cid);
			break;
		}
		printf("h.cmd = %d\n",h.cmd);

		switch(h.cmd)
		{
		case CS_LOGIN:
			{
				printf("CS_LOGIN받음\n");
				S_LOGIN login;
				recv(cid,(char*)&login,sizeof(login),0);
				RunLogin(Uindex,login.id);
			}
			break;
		case CS_XY:
			{
				S_XY xy;
				recv(cid,(char*)&xy,sizeof(xy),0);
				SendMove(Uindex,xy.x,xy.y);
			}
			break;
		case CS_READY:
			{
				S_READY ready;
				recv(cid,(char*)&ready,sizeof(ready),0);
				SendReady(ready.index,ready.ready);
			}
			break;
		case CS_SPACE:
			{
				S_SPACE space;
				recv(cid,(char*)&space,sizeof(space),0);
				stage = space.stage;
				isCollect(Uindex,space.x,space.y);
			}
			break;
		case CS_SENDME:
			{
				printf("me");
				S_ME me;
				recv(cid,(char*)&me,sizeof(me),0);
				//SendOldUser(me.id,me.index,me.newindex);
			}
			break;
		case CS_SENDONE:
			{
				S_ONE one;
				recv(cid,(char*)&one,sizeof(one),0);
				SendOldUser(g_aUser[0].id,g_aUser[0].index,one.index);
			}
			break;
		case CS_MSG:
			{
				S_MSG msg;
				recv(cid,(char*)&msg,sizeof(msg),0);
				SendMSG(Uindex,msg.msg);
			}
			break;
		case CS_NEXTSTAGE:
			{
				S_NEXTSTAGE next;
				recv(cid,(char*)&next,sizeof(next),0);
				stage = next.stage;
				for(int i=0;i<5;i++)
				{
					Collect[i]=-1;
				}
				if(stage == 6)
				{
					RunEnd();
				}
			}
			break;
		default:
			break;
		}
	}
	closesocket(cid);
	return 0;
}