#pragma once
#define MAX_USER 2
typedef struct  _S_USER
{
	SOCKET cid; //소켓id
	char id[20]; //이름
	int index; //식별번호
	bool ready; //준비상태
	int count;  //맞은 갯수
	int stage;
	int check; // -1은 사용아님 1 은 사용중
}S_USER;

extern S_USER g_aUser[MAX_USER];
void IniUser();
int GetEmptyUser(SOCKET cid);