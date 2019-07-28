#pragma once
//////////////////////////////////
//								\\
//								\\
//	   조필상,이석 게임서버		\\
//								\\
//								\\
//////////////////////////////////
//로그인
#define CS_LOGIN 0	//클라이언트 ->서버
#define SC_RLOGIN 1 // 서버 -> 클라이언트
#define SCA_NEWUSER 2 //서버가 모든 클라이언트
#define CS_SENDME 3
#define CS_SENDONE 4
#define SC_OLDUSER 5
//게임
#define CS_XY 11 //좌표 넘김
#define SCA_XY 12 //좌표 뿌림
#define CS_SPACE 13  //틀린곳 찍음
#define SCA_COLLECT 14 //정답
#define SCA_INCOLLECT 15 //오답
#define CS_NEXTSTAGE 16 // 다음스테이지로
#define SCA_END 17 //게임종료
//로비
#define CS_READY 21 //준비누름
#define SCA_READY 22 //다른사용자가 준비누름
#define SCA_START 23 //유저 전원이 준비누르면 시작
//채팅
#define CS_MSG 31
#define SCA_MSG 32
////////////////////////////////////////////////
//-----------------------------------------------------------------------
typedef struct _S_H
{
	int cmd;
	int len;

}S_H;

typedef struct _S_LOGIN
{
	char id[20];

}S_LOGIN;

typedef struct _S_RLOGIN
{
	char id[20];
	int index;
	int ret; //-1 은 접속안됨 1은 접속 됨
	
}S_RLOGIN;

typedef struct _S_NEWUSER
{
	char id[20];
	int index;

}S_NEWUSER;

typedef struct _S_ME
{
	char id[20];
	int index;
	int newindex;
}S_ME;

typedef struct _S_ONE
{
	int index;
}S_ONE;

typedef struct _S_OLDUSER
{
	char id[20];
	int index;
}S_OLDUSER;

typedef struct _S_XY
{
	int index;
	int x;
	int y;
}S_XY;

typedef struct _S_READY
{
	int index;
	bool ready;
}S_READY;

typedef struct _S_START
{
	bool start;
	int stage;
}S_START;

typedef struct _S_SPACE
{
	int stage;
	int x;
	int y;
}S_SPACE;

typedef struct _S_COLLECT
{
	int index;
	int stage;
	int i;
	int count;
}S_COLLECT;

typedef struct _S_INCOLLECT
{
	int stage;
	int index;
}S_INCOLLECT;

typedef struct _S_NEXTSTAGE
{
	int stage;
}S_NEXTSTAGE;

typedef struct _S_END//점수 표시
{
	int count;
	int index;
	char id[20];
}S_END;

////////////////////////////////////

typedef struct _S_MSG
{
	char msg[80];

}S_MSG;

typedef struct _S_RMSG
{
	char id[20];
	char msg[80];

}S_RMSG;

typedef struct _S_LOGOUT
{
	
}S_LOGOUT;

typedef struct _S_RLOGOUT
{
	char id[20];
}S_RLOGOUT;