#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <WIndows.h>
#include "protocol.h"
#include "user.h"


#pragma comment(lib,"ws2_32.lib")

DWORD WINAPI RunGame(LPVOID para);

int main()
{
	WSADATA wsa;

	IniUser();

	if(WSAStartup(MAKEWORD(2,2),&wsa))
	{
		printf("wsaError");
		exit(1);
	}

	SOCKET sid = socket(AF_INET,SOCK_STREAM,0);

	if(INVALID_SOCKET == sid)
	{
		printf("socket error");
		exit(1);
	}
	
	SOCKADDR_IN saddr;
	
	memset(&saddr,0,sizeof(saddr));

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(2012);
	saddr.sin_addr.s_addr = INADDR_ANY;

	int re = bind(sid,(SOCKADDR*)&saddr,sizeof(saddr));
	if(SOCKET_ERROR == re)
	{
		printf("bind error");
		exit(1);
	}
	re = listen(sid,SOMAXCONN);
	if(SOCKET_ERROR == re)
	{
		printf("listen error");
		exit(1);
	}

	SOCKET cid;
	SOCKADDR_IN caddr;
	int len;
	
	HANDLE hThread;
	DWORD threadId;
	while(1)
	{
		len = sizeof(caddr);
		cid = accept(sid,(SOCKADDR*)&caddr,&len);
		if(SOCKET_ERROR == cid)
		{
			printf("accept error\n");
			continue;
		}

		printf("새 사용자가 접속함\n");

		hThread = CreateThread(NULL,0,RunGame,(LPVOID)cid,0,&threadId);
		if(INVALID_HANDLE_VALUE == hThread)
		{
			printf("Thread error\n");
			closesocket(cid);
			continue;
		}
	}

	
	closesocket(sid);
	WSACleanup();
	return 0;
}