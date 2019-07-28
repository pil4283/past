#pragma once
#include <fstream>
class Block
{
private:
	int m_number;
	Block *p_Up;
	Block *p_Down;
	Block *p_Left;
	Block *p_Right;
	bool m_block;
public:
	Block();
	virtual ~Block();
	Block* createLinkedList_h();
	// 헤더에 노드를 추가, 총 9가지로 나뉨
	void addNode(Block*, int, int);
	int createBoard(Block*,int,int);
	void addRandomNum(Block*);
	int CheckGameOver(Block*);
	void moveNode(Block*, int,int, bool);
	void TurnNode(Block*, int,int, bool);
};