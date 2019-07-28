#pragma once

class PPlayer
{
public:
	PPlayer(void);
	~PPlayer(void);
	bool PlayerLife(void);
	int PLife;
	void PlayerDraw(HDC hdc);
	char temp[80];
	int PGold;
};
