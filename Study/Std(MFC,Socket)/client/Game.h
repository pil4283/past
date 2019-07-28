#pragma once
#include "player.h"
#include "picture.h"

class Game
{
public:
	Game(void);
	~Game(void);
	
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	bool start;

	Player m_Player[2];


	void Draw(CDC* pDC);
	BOOL LButtonDown(CPoint point);
	void GameLobby(CDC* pDC);
	
	void Create(void);
	Picture m_Picture;
	int m_EndIndex;
};
