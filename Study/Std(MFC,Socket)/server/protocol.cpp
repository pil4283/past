#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "User.h"
#include "protocol.h"

int SendRlogin(int index,char* id,int ret)
{
	S_H h;
	S_RLOGIN rlogin;

	h.cmd = SC_RLOGIN;
	h.len = sizeof(rlogin);

	rlogin.ret = ret;
	rlogin.index = index;
	sprintf(rlogin.id,id);

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&rlogin,sizeof(rlogin));

	send(g_aUser[index].cid,temp,sizeof(h)+sizeof(rlogin),0);

	return 0;
}

int SendNuser(int index,char* id)
{
	S_H h;
	S_NEWUSER newuser;

	h.cmd = SCA_NEWUSER;
	h.len = sizeof(newuser);

	strcpy(newuser.id,id);
	newuser.index = index;
	
	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&newuser,sizeof(newuser));
	for(int i=0;i<MAX_USER;i++)
	{
		if(-1 == g_aUser[i].check)
		{
			continue;
		}
		send(g_aUser[i].cid,temp,sizeof(h)+sizeof(newuser),0);
	}
	return 0;
}

int SendOldUser(char* id,int oldindex,int index)
{
	printf("index = %d",index);
	S_H h;
	S_OLDUSER olduser;

	h.cmd = SC_OLDUSER;
	h.len = sizeof(olduser);

	strcpy(olduser.id,id);
	olduser.index = oldindex;

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&olduser,sizeof(olduser));

	send(g_aUser[index].cid,temp,sizeof(h)+sizeof(olduser),0);
	printf("%d´Ô¿¡°Ô %d-%s¸¦º¸³¿",index,olduser.index,olduser.id);

	return 0;
}
int SendMove(int index,int x,int y)
{
	S_H h;
	S_XY xy;

	h.cmd = SCA_XY;
	h.len = sizeof(xy);

	xy.index = index;
	xy.x = x;
	xy.y = y;

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&xy,sizeof(xy));

	for(int i=0;i<MAX_USER;i++)
	{
		if(index == i)
		{
			continue;
		}
		send(g_aUser[i].cid,temp,sizeof(h)+sizeof(xy),0);
		printf("%d´ÔÀÌ %d´Ô¿¡°Ô %d,%d¸¦º¸³¿",index,i,xy.x,xy.y);
	}
	return 0;
}
int SendReady(int index,bool ready)
{
	int allready = 0;
	S_H h;
	S_READY m_ready;

	h.cmd = SCA_READY;
	h.len = sizeof(m_ready);

	m_ready.index = index;
	m_ready.ready = ready;
	g_aUser[index].ready = ready;

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&m_ready,sizeof(m_ready));

	for(int i=0;i<MAX_USER;i++)
	{
		send(g_aUser[i].cid,temp,sizeof(h)+sizeof(m_ready),0);
		printf("%d´Ô¿¡°Ô %d,%dº¸³¿",i,m_ready.index,m_ready.ready);
	}


	for(int i=0;i<MAX_USER;i++)
	{
		if(g_aUser[i].ready==true)
		{
			allready++;
		}else
		{
			allready = 0;
			break;
		}
		if(allready == 2)
		{
			SendStart(index);
		}
	}

	return 0;
}
int SendStart(int index)
{
	S_H h;
	S_START start;

	h.cmd = SCA_START;
	h.len = sizeof(start);

	start.start = true;
	start.stage = 1;
	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&start,sizeof(start));

	for(int i=0;i<MAX_USER;i++)
	{
		send(g_aUser[i].cid,temp,sizeof(h)+sizeof(start),0);
		printf("%d´Ô¿¡°Ô startº¸³¿",i,start.start);
	}

	return 0;
}
int SendCollect(int index,int stage,int Cindex)
{
	S_H h;
	S_COLLECT collect;

	h.cmd = SCA_COLLECT;
	h.len = sizeof(collect);

	g_aUser[index].count++;

	collect.index = index;
	collect.stage = stage;
	collect.i = Cindex;
	collect.count = g_aUser[index].count;

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&collect,sizeof(collect));

	for(int i=0;i<MAX_USER;i++)
	{
		send(g_aUser[i].cid,temp,sizeof(h)+sizeof(collect),0);
		printf("%d´Ô¿¡°Ô %d %dº¸³¿",i,collect.stage,collect.i);
	}
	
	return 0;
}
int SendInCollect(int index,int stage)
{
	S_H h;
	S_INCOLLECT incollect;

	h.cmd = SCA_INCOLLECT;
	h.len = sizeof(incollect);

	incollect.index = index;
	incollect.stage = stage;
	
	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&incollect,sizeof(incollect));

	for(int i=0;i<MAX_USER;i++)
	{
		send(g_aUser[i].cid,temp,sizeof(h)+sizeof(incollect),0);
		printf("%d´Ô¿¡°Ô %d , %dº¸³¿",i,incollect.index,incollect.stage);
	}
	return 0;
}
/*int SendNextStage(int stage)
{
	S_H h;
	S_NEXTSTAGE next;

	h.cmd = SCA_NEXTSTAGE;
	h.len = sizeof(next);

	next.stage = stage+1;

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&next,sizeof(next));

	for(int i=0;i<MAX_USER;i++)
	{
		send(g_aUser[i].cid,temp,sizeof(h)+sizeof(next),0);
		printf("%d´Ô¿¡°Ô stage%dº¸³¿",i,next.stage);
	}

	return 0;
}*/
int SendEnd(int index)
{
	S_H h;
	S_END end;

	h.cmd = SCA_END;
	h.len = sizeof(end);

	strcpy(end.id,g_aUser[index].id);
	end.count = g_aUser[index].count;
	end.index = g_aUser[index].index;

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&end,sizeof(end));

	for(int i=0;i<MAX_USER;i++)
	{
		send(g_aUser[i].cid,temp,sizeof(h)+sizeof(end),0);
		printf("%d´Ô¿¡°Ô %s-%d-%dº¸³¿",i,end.id,end.count,end.index);
	}

	return 0;
}
int SendMSG(int index,char* msg)
{
	S_H h;
	S_RMSG rmsg;

	h.cmd = SCA_MSG;
	h.len = sizeof(rmsg);

	strcpy(rmsg.id,g_aUser[index].id);
	strcpy(rmsg.msg,msg);

	char temp[1024*3];
	memcpy(temp,&h,sizeof(h));
	memcpy(temp+sizeof(h),&rmsg,sizeof(rmsg));

	for(int i=0;i<MAX_USER;i++)
	{
		send(g_aUser[i].cid,temp,sizeof(h)+sizeof(rmsg),0);
		printf("%d´Ô¿¡°Ô %s-%sº¸³¿",i,rmsg.id,rmsg.msg);
	}

	return 0;
}