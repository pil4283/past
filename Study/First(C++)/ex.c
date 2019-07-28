#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mtg.h"
#include "mtgsound.h"

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define BG1 "1.mp3"
#define BG2 "2.mp3"
#define BG3 "3.mp3"
#define EP1 "1.wav"

#define MapX 45
#define MapY 25
////////////////////////////////
//구조체

struct Enemy //별들
{
	int x;
	int y;
	int life;
	int type;
	int speed;
};
struct Enemy g_Enemy[100];

struct Player //플레이어 
{
	int x;
	int y;
	int life;
};
struct Player g_Player;
////////////////////////////////////////
// 전역 변수 
char g_Debug[80]="DEBUG";
int g_Stage=0; //엔터누를때마다+1
int g_RunManX=0;
int g_RunManY=21;
int g_RunManXX=70;
int g_RunManYY=16;
int g_Color=1;
int g_cho;
int g_bun;
int g_si;
int g_RainBowX=15;//유도별x
int g_RainBowY=0;//유도별y
int g_RainBow=1;
int g_EnemyColor=1; 
int g_WallX=4; //모서리에있는 동그라미
int g_WallXR=27; //모서리에있는 동그라미
int g_WallY=1; //모서리에있는 동그라미
int Slug=200; //적내려오는시간 1초마다-1
int Speed;
int RainBowSlug=400;
int g_Score=0;
int g_Time_Score=0;
int StillAlive;
////////////////////////////////////////
//맵
char g_Map[MapY][MapX+3]=
{
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │",
	"│                         │"
};
////////////////////////////////////////
// 화면 처리

void EnemyLife()// 적이 이동불가지역에 갈시 라이프-1
{
	int i;

	for(i=0;i<100;i++)
	{
		if(27<=g_Enemy[i].x || 3>=g_Enemy[i].x ||  24<=g_Enemy[i].y)
		{
			g_Enemy[i].life=-1;
		}
	}
}
void TimeMap()//시간출력
{
	char tmp[50];
	sprintf(tmp,"플레이시간 : %d시 %d분 %d초",g_si,g_bun,g_cho);
	_DrawText(45,19,tmp);
	sprintf(tmp,"별 속도 : %d%%  (최대200%%)",Speed);
	_DrawText(45,20,tmp);
}
int PlayerMove(int sx, int sy, int dx, int dy) //플레이어이동조건
{
	if(sx<4 || sx>27)
	{
		return -1;
	}
	else
	{
		return 1;
	}
	return -1;
}
void Move()//플레이어이동
{
	char k;
	k=_GetKey();

	if(k==KEY_LEFT)
	{
		if(1==PlayerMove(g_Player.x-1,g_Player.y,g_Player.x,g_Player.y))
		{
			g_Player.x--;
		}
	}
	else if(k==KEY_RIGHT)
	{
		if(1==PlayerMove(g_Player.x+1,g_Player.y,g_Player.x,g_Player.y))
		{
			g_Player.x++;
		}
	}
}
void Creater()//제작자출력겸 도움말
{
	_DrawTextColor(60,22,"제작자 조필상",3);

	_DrawTextColor(60,24,"게임종료:q",3);
}
void RunMan()//미사일을 피해 도망치는사람
{
	char msg[20];

	sprintf(msg,"─☆★☆옷");

	_DrawTextColor(g_RunManX,g_RunManY,msg,g_Color);
}
void MoveRunMan()//미사일을 피해 도망치는사람의 이동경로
{
	static long oldT=0;
	long newT;

	newT=_GetTickCount();

	if(50 <= newT-oldT)
	{
		if(g_Stage==1)
		{
		g_RunManX++;
		oldT=newT;
		g_Color++;
		}
		if(16 <=g_Color)
		{
			g_Color=1;
		}
		if(70 <= g_RunManX)
		{
			g_RunManX=0;
		}
		_Invalidate();
	}
}
void GameOverYo() // 겜오버
{
	char tmp[30];
	int TimeScore;
	int Score;
	int FinalScore;
	char k;
	StillAlive=-1;

	
		k=_GetKey();
			_cls();
			TimeScore=g_Time_Score*87;
			FinalScore=TimeScore;
			_DrawText(40,11,"GameOver");
			sprintf(tmp,"점수는? : %d",FinalScore);
			_DrawText(40,12,tmp);
			_DrawText(50,5,"게임종료↗");
			_BitBlt();
			_Delay(1000);
	
	MTGStop();
	MTGOpen(BG3);
	MTGSetVolume(100);
	MTGPlay();
}
void GameOver()//겜오버조건
{
	int i;
	if(g_Stage==2)
	{
		if(g_WallX==g_Player.x && g_WallY==g_Player.y)
		{
			GameOverYo();
		}
		if(g_RainBowX==g_Player.x && g_RainBowY==g_Player.y)
		{
			GameOverYo();
		}
		for(i=0;i<100;i++)
		{
			if(1==g_Enemy[i].life)
			{
				if(g_Player.x==g_Enemy[i].x && g_Player.y==g_Enemy[i].y)
				{
					GameOverYo();
				}
			}
		}
	}
}
void Check()//다음단계로 넘어가기위한 단계
{
	_DrawText(30,12,"Enter키를 눌러주세요");
}
void Main()//허접한 메인, 땜빵으로 도망치는사람 넣음
{
	_DrawTextColor(1,1,"  ●●●    ●     ●           ●●   ● ●     ●     ●",7);
	_DrawTextColor(1,2,"●●●●●  ●     ●          ●  ●●● ●    ●    ●●",7);
	_DrawTextColor(1,3,"   ●●     ● ●  ●           ●●   ● ●   ● ●    ●",7);
	_DrawTextColor(1,4,"  ●  ●    ●     ●●●●●          ● ●  ●    ●  ●",7);
	_DrawTextColor(1,5,"   ●●     ●                         ● ●            ●",7);
	_DrawTextColor(1,6,"                 ●●●●●●●",7);                           
	_DrawTextColor(1,7,"                                                          ",7);
	_DrawTextColor(1,8,"                    ●●●●",7);                      
	_DrawTextColor(1,9,"                        ●",7);                       
	_DrawTextColor(1,10,"                      ●",7);                         
	_DrawTextColor(1,11,"                     ●●●●",7);                    
	_DrawTextColor(1,12,"      ●      ●  ●   ●●●●   ●  ●",7);            
	_DrawTextColor(1,13,"      ●      ●  ●        ●    ●  ●",7);         
	_DrawTextColor(1,14,"      ●      ●●●      ●      ●  ●",7);           
	_DrawTextColor(1,15,"      ●●●●●  ●    ●●●●  ●  ●●●●●",7);    
	_DrawTextColor(1,16,"              ●  ●              ●",7);                  
	_DrawTextColor(1,17,"                                    ●●●●●●",7);
	_DrawTextColor(1,18,"                                      ●",7);
	_DrawTextColor(1,19,"                                      ●",7);
	_DrawTextColor(1,20,"                                      ●●●●●",7);
	_DrawTextColor(59,1,"     ●●●●●  ●",10);
	_DrawTextColor(59,2,"        ● ●    ●",10);
	_DrawTextColor(59,3,"      ●●●●● ●",10);
	_DrawTextColor(59,4,"                 ●",10);
	_DrawTextColor(59,5,"       ●●●     ",10);
	_DrawTextColor(59,6,"     ●●●●● ●",10);
	_DrawTextColor(59,7,"        ●●    ●",10);
	_DrawTextColor(59,8,"       ●  ●   ●●",10);
	_DrawTextColor(59,9,"        ●●    ●",10);
	_DrawTextColor(59,10,"                ●",10);
	_DrawTextColor(59,12,"      ●●●●  ●",10); 
	_DrawTextColor(59,13,"            ●  ●",10);
	_DrawTextColor(59,14,"            ●  ●",10);
	_DrawTextColor(59,15,"            ●  ●",10);
	_DrawTextColor(59,16,"                ●",10);
	_DrawTextColor(50,8,"★    ★  ★",14);
	_DrawTextColor(50,9,"★    ★  ★",14);
	_DrawTextColor(50,10,"★★★★★★",14);
	_DrawTextColor(50,11,"★    ★  ★",14);
	_DrawTextColor(50,12,"★★★★★★",14);
	_DrawTextColor(50,13,"          ★",14);
	_DrawTextColor(50,14,"  ★★★★",14);
	_DrawTextColor(50,15,"      ★",14);
	_DrawTextColor(50,16,"    ★",14);
	_DrawTextColor(50,17,"   ★★★★",14);
	_DrawTextColor(20,23,"Enter : 게임시작, 'q' : 게임종료",5);
	RunMan();
}
void EnemySpot(int i) //적 생성 위치
{
	int a;
	
	
	a=rand()%4;
	if(0==a)
	{
		a=rand()%8+3;
		g_Enemy[i].x=a;
		g_Enemy[i].y=1;

		a=rand()%5+1;
		g_Enemy[i].type=a;
	}
	else if(1==a)
	{
		a=rand()%16+3;
		g_Enemy[i].x=a;
		g_Enemy[i].y=1;

		a=rand()%10+1;
		g_Enemy[i].type=a;
	}
	else if(2==a)
	{
		a=rand()%24+3;
		g_Enemy[i].x=a;
		g_Enemy[i].y=1;

		a=rand()%9+1;
		g_Enemy[i].type=a;
	}
	else if(3==a)
	{
		a=rand()%30+3;
		g_Enemy[i].x=a;
		g_Enemy[i].y=1;

		a=rand()%8+1;
		g_Enemy[i].type=a;
	}
}
void EnemyStart() //적에게 라이프 부여
{
	int i;
	int a;

	for(i=0;i<50;i++)
	{
		if(-1==g_Enemy[i].life)
		{
			a=rand()%5;

			if(0==a)
			{
				g_Enemy[i].life=1;
				EnemySpot(i);
			}
		}
	}
}
void ShowWall() //적 모양내기
{
	int i;
	char tmp[40];
	for(i=0;i<50;i++)
	{
		if(1==g_Enemy[i].life)
		{
			_DrawTextColor(g_Enemy[i].x,g_Enemy[i].y,"☆",14);
		}
	}
	_DrawTextColor(g_RainBowX,g_RainBowY,"★",g_RainBow);
	sprintf(tmp,"o");
	_DrawText(g_WallX,g_WallY,tmp);
	sprintf(tmp,"o");
	_DrawText(g_WallXR,g_WallY,tmp);
}
void DownWall() //모서리에있는 동그라미 이동
{
	static long OLD=0;
	long NEW;

	NEW=_GetTickCount();
	if(100<= NEW-OLD)
	{
		OLD=NEW;
		g_WallY++;
		if(26 <= g_WallY)
		{
			g_WallY=0;

			_Invalidate();
		}
	}
	if(g_WallX==g_Player.x && g_WallY==g_Player.y)
	{
		GameOverYo();
	}
	if(g_WallXR==g_Player.x && g_WallY==g_Player.y)
	{
		GameOverYo();
	}
}
void RainBow()//유도별
{
	static long oldR=0;
	long newR;

	newR=_GetTickCount();
	if(RainBowSlug <= newR-oldR)
	{
		if(g_Stage==2)
		{
			g_RainBowY++;
			oldR=newR;
			g_RainBow++;

			_Invalidate();
		}
		if(24 <= g_RainBowY)
		{
			g_RainBowY=0;
		}
		if(g_RainBowX < g_Player.x)
		{
			g_RainBowX++;
		}
		if(g_Player.x < g_RainBowX)
		{
			g_RainBowX--;
		}
		if(16 <= g_RainBow)
		{
			g_RainBow=1;
		}
	}

}
void ShowPlayer()//플레이어 출력
{
	_DrawText(g_Player.x,g_Player.y,"옷");
}
void RandomMove() //적 움직임
{
	int i;

	for(i=0;i<100;i++)
	{
		if(1==g_Enemy[i].life)
		{
			switch(g_Enemy[i].type)
			{
			case 1:
				g_Enemy[i].y++;
				break;
			case 2:
				g_Enemy[i].y++;
				break;
			case 3:
				g_Enemy[i].x++;
				g_Enemy[i].y++;
				break;
			case 4:
				g_Enemy[i].y++;
				break;
			case 6:
				g_Enemy[i].y++;
				break;
			case 7:
				g_Enemy[i].x--;
				g_Enemy[i].y++;
				break;
			default:
				g_Enemy[i].life=-1;
				break;
			}
		}
	}
}
void Game()//실제 게임
{

	int y;
	//맵출력
	//Map();
	for(y=0; y<MapY; y++)
	{
		_DrawText(1,y,g_Map[y]);
	}
	//플레이어출력
	ShowPlayer();
	//적출력
	ShowWall();
	//시간출력
	TimeMap();
	GameOver();
	
	
}

void Draw()
{	
	switch(g_Stage)
	{
	case 0:
		Check();
		break;
	case 1:
		Main();
		break;
	case 2:
		Game();
		break;
	}
	Creater();

	_DrawText(50,0,g_Debug);
}
/////////////////////////////////////////
// 이벤트 
void RunStart()//처음화면 스타탱크소리넣음
{
	int x=0;
	char msg[30]="○Now Loading●";

	MTGOpen(EP1); 
	MTGSetVolume(100);
	MTGPlay();

	while(1)
	{
		_DrawTextOrg(x,12,msg);
		x++;
		if(x > 65)
		{
			break;
		}
		_Delay(45);
	}
	_Invalidate();
}
void RunTime() //시간창
{
	static long old1=0; 
	long new1;

	new1=_GetTickCount();

	if(1000<=new1-old1)
	{
		if(g_Stage==2)
		{
			old1=new1;
			Slug--;
			RainBowSlug--;
			g_cho++;
			g_Time_Score++;
			Speed++;
			_Invalidate();
		}
		if(Slug<=50)
		{
			Slug++;
		}
		if(200<=Speed)
		{
			Speed--;
		}
		if(g_cho == 60)
		{
			g_cho=0;
			g_bun++;
			_Invalidate();
		}
		if(g_bun == 60)
		{
			g_bun=0;
			g_si++;
			_Invalidate();
		}

	}
	_Invalidate();
}
	void EnemyTimeA() //적 라이프 부여 시간
{
	static long old=0;
	long time;

	time=_GetTickCount();

	if(g_Stage==2)
	{
		if(Slug<=time-old)
		{
			old=time;
			EnemyStart();
		}
	}
}
void EnemyTimeB()//적 내려오는 시간
{
	int i=100;
	static long old=0;
	long time;

	time=_GetTickCount();

	if(Slug<=time-old)
	{
		old=time;
		RandomMove();
	}
}
int RunKey(char k)// 키보드 제어
{
	Move();
	if(k==13)
	{
		g_Stage++;
		if(1 < g_Stage)
		{
			g_Stage=2;
		}
		if(g_Stage==0)
		{

		}
		else if(g_Stage==1)
		{  
			MTGStop();
			MTGOpen(BG1);
			MTGSetVolume(100);
			MTGPlay();

		}else if(g_Stage==2)
		{
			g_Player.x=18;
			g_Player.y=24;
			MTGStop();
			MTGOpen(BG2);
			MTGSetVolume(100);
			MTGPlay();
		}
	}
	if('q'==k)
	{
		exit(1);
	}
	sprintf(g_Debug,"key:%d Press 'q' key to Quit!",k);

	return 0;
}
void StageTime()
{
	
	EnemyLife();
	EnemyTimeA();
	EnemyTimeB();
	RunTime();

	_Invalidate();
}
/////////////////////////////////////////
// GameMain
void GameMain() 
{
	char k;
	
	RunStart();

	while(1)
	{
		MoveRunMan();
		RainBow();
		GameOver();
		StageTime();
		DownWall();
		k=_GetKey();
		if(-1==k) continue;		
		if(-1==RunKey(k))
		{
			break;
		}
		_Invalidate();
	}

}
///////////////////////////////////////////
// main
int main(void) 
{
	_BeginWindow();

	GameMain();

	_EndWindow();

	return 0;
}