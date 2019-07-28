#pragma once
#include "Block.h"
#include "stdafx.h"
#include "afxwin.h"
#include "afx.h"

class Board
{
private:
	Block* Block_Header;//노드헤더
	CBrush newBrush;
public:
	Board();
	virtual ~Board();

	void TurnBoard(int direction);
	void PushKey(int key);
	void Paint(CDC* pDC);

	bool drawOption;
	bool moveLog;
	bool turnLog;

	int logNum;
	bool isGameOver;
};