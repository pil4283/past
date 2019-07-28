#include "stdafx.h"
#include "Block.h"
#include "fstream"
using namespace std;

Block::Block()
{
	
}

Block* Block::createLinkedList_h() {	//16개의 연결리스트를 만드는 함수, 임의의 노드 2개에 숫자 2를 넣는다.
	
	//헤더 = L 헤더를 기준으로 삽입,검색등등 실행.//
	Block* L;
	L = (Block*)malloc(sizeof(Block));
	L->m_number = 0;
	L->p_Up = NULL;
	L->p_Down = NULL;
	L->p_Left = NULL;
	L->p_Right = NULL;
	L->m_block = false;

	///////////////////////////////////////
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			addNode(L, x, y);	//4 X 4 사중 연결리스트 생성
		}
	}
	//모든 노드가 연결됬을때 랜덤한 노드 2개에 숫자2를 넣는다
	for (int i = 0 ; i < 2 ; i++)
	{
		addRandomNum(L);
	}
	return L;
}

// 헤더를 기준으로 노드를 추가, switch를 Y값 기준으로 맞춰서 노드를 연결시킴
void Block::addNode(Block* L, int x, int y)
{
	Block* newNode;
	newNode = (Block*)malloc(sizeof(Block));
	newNode->m_number = 0;
	newNode->m_block = false;
	newNode->p_Up = NULL;
	newNode->p_Down = NULL;
	newNode->p_Left = NULL;
	newNode->p_Right = NULL;

	switch (y){

	case 0:{	//첫번째줄
		if (x == 0)return; //예외처리

		//첫번째노드는 헤더 그러므로 두번째노드부터 시작

		if (x <= 2){
			while (L->p_Right != NULL) L = L->p_Right;
			//좌우로 연결시킴 아직 위아래에 노드가 없으므로 이중연결리스트처럼 연결시켜줌
			L->p_Right = newNode;
			newNode->p_Left = L;
		}
		
		else if (x == 3){
			//위처럼 while문으로 해도 되고 이것처럼 노가다코드로 만들어도 됨
			L->p_Right->p_Right->p_Right = newNode;
			newNode->p_Left = L->p_Right->p_Right;
		}
		break;
	}

	case 1: {	//두번째줄이므로 헤더에서 아래로 내려와야함

		if (x == 0){
			L->p_Down = newNode;   //헤더 아래의 노드를 연결
			newNode->p_Up = L;
		}
		else if (x <= 2){
			
			L = L->p_Down;	//편의를 위해 헤더를 아래로
			//L이 아래로 내려왔다는것만 빼면 위와 동일
			while (L->p_Right != NULL) L = L->p_Right;

			L->p_Right = newNode;
			newNode->p_Left = L;

			//이제 첫번째줄과 연결시켜줘야함

			L->p_Up->p_Right->p_Down = newNode;
			newNode->p_Up = L->p_Up->p_Right;
		}

		else if (x == 3) {	//두번째줄의 마지막노드 마찬가지로 첫번째줄 마지막노드와 연결시켜줘야함
			
			L = L->p_Down;	//편의를 위해 헤더를 아래로
			while (L->p_Right != NULL) L = L->p_Right;

			L->p_Right = newNode; //3번째노드와 연결
			newNode->p_Left = L;

			L->p_Up->p_Right->p_Down = newNode; //첫번째줄 마지막노드와 연결
			newNode->p_Up = L->p_Up->p_Right;
		}
		break;
	}

	case 2: { //세번째줄
		if (x == 0){
			L->p_Down->p_Down = newNode;
			newNode->p_Up = L->p_Down;
		}
		
		else if (x <= 2){
			L = L->p_Down->p_Down;	//편의를 위해 헤더를 세번째줄로
			while (L->p_Right != NULL) L = L->p_Right;

			L->p_Right = newNode;
			newNode->p_Left = L;

			//두번째줄과 연결
			L->p_Up->p_Right->p_Down = newNode;
			newNode->p_Up = L->p_Up->p_Right;
		}
		
		else if (x == 3){
			L = L->p_Down->p_Down;	//편의를 위해 헤더를 세번째줄로
			while (L->p_Right != NULL) L = L->p_Right;

			L->p_Right = newNode;
			newNode->p_Left = L;

			L->p_Up->p_Right->p_Down = newNode; //두번째줄 마지막노드와 연결
			newNode->p_Up = L->p_Up->p_Right;
		}
		break;
	}
	case 3: {//마지막줄
		if (x == 0) {
			L->p_Down->p_Down->p_Down = newNode;
			newNode->p_Up = L->p_Down->p_Down;
		}
		else if (x <= 2) {
			L = L->p_Down->p_Down->p_Down;	//편의를 위해 헤더를 네번째줄로
			while (L->p_Right != NULL) L = L->p_Right;

			L->p_Right = newNode;
			newNode->p_Left = L;

			L->p_Up->p_Right->p_Down = newNode;
			newNode->p_Up = L->p_Up->p_Right;
		}
		else if (x == 3) {
			L = L->p_Down->p_Down->p_Down;	//편의를 위해 헤더를 네번째줄로

			while (L->p_Right != NULL) L = L->p_Right;

			L->p_Right = newNode;
			newNode->p_Left = L;

			L->p_Up->p_Right->p_Down = newNode; //세번째줄 마지막노드와 연결
			newNode->p_Up = L->p_Up->p_Right;
		}
		break;
	}
	default:
		break;
	}
	//case 1: case 2: case 3: ~~~ break;
	//이렇게 3개를 한꺼번에 넣은 뒤 x값을 기준으로 L의 위치를 바꿔줘도 된다.
}

int Block::createBoard(Block* L,int x,int y)//게임판을 만든다. x,y값을이용해 노드의 숫자를 반환시킴
{
	int xnum = x, ynum = y; //x값,y값을받아 노드를 탐색하는 함수

	while (1 <= xnum) // x값이 1이상일때 오른쪽노드로 옮김 0이면 그냥 나옴
	{
		L = L->p_Right;
		xnum--;	//1씩 감소시켜서 0이될때까지
	}
	
	while (1 <= ynum) // y값이 1이상일때 아래쪽노드로 옮김 0이면 그냥 나옴
	{
		L = L->p_Down;
		ynum--;	//위랑 동일
	}

	//위의 계산으로 나온 노드의 숫자를 반환

	return L->m_number;
}


void Block::moveNode(Block* L, int key, int logNum, bool log)
{

	CString msg;

	Block* tempNode[4];//각 변마다 4개의 노드를 생성해 그 노드들을 기준으로 m_number를 제곱해나간다.

	int movecount = 0;//움직인 횟수를 저장해 키를 눌렀음에도 아무것도 변하지 않았을때에는(EX = 왼쪽변에 숫자4개가 꽉차고 제곱할 숫자가 없을경우) 숫자를 생성하지못하게 한다. 움직임이 있는 경우 +시켜준다.

	int comparecount = 3; //비교횟수 = (첫번째,두번째)노드 (1번)- > ((세번째,두번째),첫번째) (2번) -> (((네번째,세번째),두번째),첫번째) (3번)

	switch (key){
	case VK_DOWN://아래쪽 키를 눌렀을때 아래쪽변 4개를 기준으로 아래로 계산, 위에서부터 계산할경우 위부터 숫자가 2 2 2 4 일때 0 2 4 4 이래야 하지만 0 4 2 4 이렇게 되버림

		tempNode[0] = L->p_Down->p_Down->p_Down;
		tempNode[1] = L->p_Down->p_Down->p_Down->p_Right;
		tempNode[2] = L->p_Down->p_Down->p_Down->p_Right->p_Right;
		tempNode[3] = L->p_Down->p_Down->p_Down->p_Right->p_Right->p_Right;

		for (int i = 0; i < 4; i++)
		{
			while (comparecount != 0)
			{
				if (comparecount == 3) // 첫번째 노드와 두번째 노드 비교
				{
					if (tempNode[i]->p_Up->m_number != 0) //숫자가 0인지 검사, 0이면 계산할 필요가 없다.
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Up->m_number) //똑같은숫자면 거듭제곱시키고 숫자를 아래로 보냄
						{
							tempNode[i]->m_number *= 2;
							tempNode[i]->p_Up->m_number = 0;
							tempNode[i]->m_block = true;//더이상 제곱을 못하게 노드에 블락을건다.
							movecount++;
						}
						else if(tempNode[i]->m_number == 0)
						{//위는 0이아니지만 아래가 0일경우 위에숫자를 아래로 보낸다.
							tempNode[i]->m_number = tempNode[i]->p_Up->m_number;
							tempNode[i]->p_Up->m_number = 0;
							movecount++;
						}
						//둘다 다를경우 (EX 2, 4) 아무것도 하지않음 
					}
				}

				//세번째, 두번째를 비교한 뒤 그 결과를 첫번째노드와 비교
				else if (comparecount == 2)
				{
					if (tempNode[i]->p_Up->p_Up->m_number != 0)//세번째와 두번째를 비교한다.
					{
						if (tempNode[i]->p_Up->p_Up->m_number == tempNode[i]->p_Up->m_number)//숫자가 같을때 거듭제곱
						{
							tempNode[i]->p_Up->m_number *= 2;
							tempNode[i]->p_Up->p_Up->m_number = 0;
							tempNode[i]->p_Up->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Up->m_number == 0)
						{
							tempNode[i]->p_Up->m_number = tempNode[i]->p_Up->p_Up->m_number;
							tempNode[i]->p_Up->p_Up->m_number = 0;
							movecount++;
						}
					}

					//두번째와 첫번째를 비교한다.
					if (tempNode[i]->p_Up->m_number != 0) //숫자가 0인지 검사
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Up->m_number)
						{
							if (tempNode[i]->p_Up->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Up->m_number = 0;
								tempNode[i]->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//위는 0이아니지만 아래가 0일경우 위에숫자를 아래로 보낸다.
							tempNode[i]->m_number = tempNode[i]->p_Up->m_number;
							tempNode[i]->p_Up->m_number = 0;
							movecount++;
						}
					}
				}

				//네번째,세번째를 계산 후 그 결과값을 두번째와, 또 그결과를 첫번째와 계산
				else if (comparecount == 1)
				{
					//네번째와 세번째를 계산
					if (tempNode[i]->p_Up->p_Up->p_Up->m_number != 0)
					{
						if (tempNode[i]->p_Up->p_Up->p_Up->m_number == tempNode[i]->p_Up->p_Up->m_number)
						{
							tempNode[i]->p_Up->p_Up->m_number *= 2;
							tempNode[i]->p_Up->p_Up->p_Up->m_number = 0;
							tempNode[i]->p_Up->p_Up->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Up->p_Up->m_number == 0)
						{
							tempNode[i]->p_Up->p_Up->m_number = tempNode[i]->p_Up->p_Up->p_Up->m_number;
							tempNode[i]->p_Up->p_Up->p_Up->m_number = 0;
							movecount++;
						}
					}
					//세번째와 두번째를 계산한다.
					if (tempNode[i]->p_Up->p_Up->m_number != 0)
					{
						if (tempNode[i]->p_Up->p_Up->m_number == tempNode[i]->p_Up->m_number)
						{
							if (tempNode[i]->p_Up->p_Up->m_block == false && tempNode[i]->p_Up->m_block == false)
							{
								tempNode[i]->p_Up->m_number *= 2;
								tempNode[i]->p_Up->p_Up->m_number = 0;
								tempNode[i]->p_Up->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->p_Up->m_number == 0)
						{
							tempNode[i]->p_Up->m_number = tempNode[i]->p_Up->p_Up->m_number;
							tempNode[i]->p_Up->p_Up->m_number = 0;
							movecount++;
						}
					}

					//두번째와 첫번째를 계산한다.
					if (tempNode[i]->p_Up->m_number != 0) //숫자가 0인지 검사
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Up->m_number)
						{
							if ((tempNode[i]->p_Up->m_block == false) && (tempNode[i]->m_block == false))
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Up->m_number = 0;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//위는 0이아니지만 아래가 0일경우 위에숫자를 아래로 보낸다.
							tempNode[i]->m_number = tempNode[i]->p_Up->m_number;
							tempNode[i]->p_Up->m_number = 0;
							movecount++;
						}
					}
				}
				comparecount--;
			}
			comparecount = 3;//다음 노드의(오른쪽노드)계산을 위해 다시 3으로 바꿔준다.
		}

		//거듭제곱을 마치고 아래로 내렸으면 이제 랜덤한 노드에 숫자 2를 집어넣는다.
		if (movecount != 0)
		{
			addRandomNum(L);
		}
		break;

	case VK_LEFT://왼쪽 키를 눌렀을때 왼쪽변 4개를 기준으로 왼쪽으로 계산
		tempNode[0] = L;
		tempNode[1] = L->p_Down;
		tempNode[2] = L->p_Down->p_Down;
		tempNode[3] = L->p_Down->p_Down->p_Down;

		
		for (int i = 0; i < 4; i++)
		{
			while (comparecount != 0)
			{
				if (comparecount == 3) // 첫번째 노드와 두번째 노드 비교
				{
					if (tempNode[i]->p_Right->m_number != 0) //숫자가 0인지 검사, 0이면 계산할 필요가 없다.
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Right->m_number) //똑같은숫자면 거듭제곱시키고 숫자를 아래로 보냄
						{
							tempNode[i]->m_number *= 2;
							tempNode[i]->p_Right->m_number = 0;
							tempNode[i]->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->m_number == 0)
						{//위는 0이아니지만 아래가 0일경우 위에숫자를 아래로 보낸다.
							tempNode[i]->m_number = tempNode[i]->p_Right->m_number;
							tempNode[i]->p_Right->m_number = 0;
							movecount++;
						}
						//둘다 다를경우 (EX 2, 4) 아무것도 하지않음 
					}
				}

				//세번째, 두번째를 비교한 뒤 그 결과를 첫번째노드와 비교
				else if (comparecount == 2)
				{
					if (tempNode[i]->p_Right->p_Right->m_number != 0)//세번째와 두번째를 비교한다.
					{
						if (tempNode[i]->p_Right->p_Right->m_number == tempNode[i]->p_Right->m_number)//숫자가 같을때 거듭제곱
						{
							tempNode[i]->p_Right->m_number *= 2;
							tempNode[i]->p_Right->p_Right->m_number = 0;
							tempNode[i]->p_Right->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Right->m_number == 0)
						{
							tempNode[i]->p_Right->m_number = tempNode[i]->p_Right->p_Right->m_number;
							tempNode[i]->p_Right->p_Right->m_number = 0;
							movecount++;
						}
					}

					//두번째와 첫번째를 비교한다.
					if (tempNode[i]->p_Right->m_number != 0) //숫자가 0인지 검사
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Right->m_number)
						{
							if (tempNode[i]->p_Right->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Right->m_number = 0;
								tempNode[i]->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//위는 0이아니지만 아래가 0일경우 위에숫자를 아래로 보낸다.
							tempNode[i]->m_number = tempNode[i]->p_Right->m_number;
							tempNode[i]->p_Right->m_number = 0;
							movecount++;
						}
					}
				}

				//네번째,세번째를 계산 후 그 결과값을 두번째와, 또 그결과를 첫번째와 계산
				else if (comparecount == 1)
				{
					//네번째와 세번째를 계산
					if (tempNode[i]->p_Right->p_Right->p_Right->m_number != 0)
					{
						if (tempNode[i]->p_Right->p_Right->p_Right->m_number == tempNode[i]->p_Right->p_Right->m_number)
						{
							tempNode[i]->p_Right->p_Right->m_number *= 2;
							tempNode[i]->p_Right->p_Right->p_Right->m_number = 0;
							tempNode[i]->p_Right->p_Right->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Right->p_Right->m_number == 0)
						{
							tempNode[i]->p_Right->p_Right->m_number = tempNode[i]->p_Right->p_Right->p_Right->m_number;
							tempNode[i]->p_Right->p_Right->p_Right->m_number = 0;
							movecount++;
						}
					}
					if (tempNode[i]->p_Right->p_Right->m_number != 0)//세번째와 두번째를 계산한다.
					{
						if (tempNode[i]->p_Right->p_Right->m_number == tempNode[i]->p_Right->m_number)
						{
							if (tempNode[i]->p_Right->p_Right == false && tempNode[i]->p_Right->m_block == false)
							{
								tempNode[i]->p_Right->m_number *= 2;
								tempNode[i]->p_Right->p_Right->m_number = 0;
								tempNode[i]->p_Right->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->p_Right->m_number == 0)
						{
							tempNode[i]->p_Right->m_number = tempNode[i]->p_Right->p_Right->m_number;
							tempNode[i]->p_Right->p_Right->m_number = 0;
							movecount++;
						}
					}

					//두번째와 첫번째를 계산한다.
					if (tempNode[i]->p_Right->m_number != 0) //숫자가 0인지 검사
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Right->m_number)
						{
							if (tempNode[i]->p_Right->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Right->m_number = 0;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//위는 0이아니지만 아래가 0일경우 위에숫자를 아래로 보낸다.
							tempNode[i]->m_number = tempNode[i]->p_Right->m_number;
							tempNode[i]->p_Right->m_number = 0;
							movecount++;
						}
					}
				}
				comparecount--;
			}
			comparecount = 3;//다음 노드의(오른쪽노드)계산을 위해 다시 3으로 바꿔준다.
		}
		
		//거듭제곱을 마치고 아래로 내렸으면 이제 랜덤한 노드에 숫자 2를 집어넣는다.
		if (movecount != 0)
		{
			addRandomNum(L);
		}
		break;

	case VK_RIGHT:
		//오른쪽을 기준으로 계산한다.
		tempNode[0] = L->p_Right->p_Right->p_Right;
		tempNode[1] = L->p_Right->p_Right->p_Right->p_Down;
		tempNode[2] = L->p_Right->p_Right->p_Right->p_Down->p_Down;
		tempNode[3] = L->p_Right->p_Right->p_Right->p_Down->p_Down->p_Down;

		for (int i = 0; i < 4; i++)
		{
			while (comparecount != 0)
			{
				if (comparecount == 3) // 첫번째 노드와 두번째 노드 비교
				{
					if (tempNode[i]->p_Left->m_number != 0) //숫자가 0인지 검사, 0이면 계산할 필요가 없다.
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Left->m_number) //똑같은숫자면 거듭제곱시키고 숫자를 아래로 보냄
						{
							tempNode[i]->m_number *= 2;
							tempNode[i]->p_Left->m_number = 0;
							tempNode[i]->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->m_number == 0)
						{//위는 0이아니지만 아래가 0일경우 위에숫자를 아래로 보낸다.
							tempNode[i]->m_number = tempNode[i]->p_Left->m_number;
							tempNode[i]->p_Left->m_number = 0;
							movecount++;
						}
						//둘다 다를경우 (EX 2, 4) 아무것도 하지않음 
					}
				}

				//세번째, 두번째를 비교한 뒤 그 결과를 첫번째노드와 비교
				else if (comparecount == 2)
				{
					if (tempNode[i]->p_Left->p_Left->m_number != 0)//세번째와 두번째를 비교한다.
					{
						if (tempNode[i]->p_Left->p_Left->m_number == tempNode[i]->p_Left->m_number)//숫자가 같을때 거듭제곱
						{
							tempNode[i]->p_Left->m_number *= 2;
							tempNode[i]->p_Left->p_Left->m_number = 0;
							tempNode[i]->p_Left->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Left->m_number == 0)
						{
							tempNode[i]->p_Left->m_number = tempNode[i]->p_Left->p_Left->m_number;
							tempNode[i]->p_Left->p_Left->m_number = 0;
							movecount++;
						}
					}

					//두번째와 첫번째를 비교한다.
					if (tempNode[i]->p_Left->m_number != 0) //숫자가 0인지 검사
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Left->m_number)
						{
							if (tempNode[i]->p_Left->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Left->m_number = 0;
								tempNode[i]->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//위는 0이아니지만 아래가 0일경우 위에숫자를 아래로 보낸다.
							tempNode[i]->m_number = tempNode[i]->p_Left->m_number;
							tempNode[i]->p_Left->m_number = 0;
							movecount++;
						}
					}
				}

				//네번째,세번째를 계산 후 그 결과값을 두번째와, 또 그결과를 첫번째와 계산
				else if (comparecount == 1)
				{
					//네번째와 세번째를 계산
					if (tempNode[i]->p_Left->p_Left->p_Left->m_number != 0)
					{
						if (tempNode[i]->p_Left->p_Left->p_Left->m_number == tempNode[i]->p_Left->p_Left->m_number)
						{
							tempNode[i]->p_Left->p_Left->m_number *= 2;
							tempNode[i]->p_Left->p_Left->p_Left->m_number = 0;
							tempNode[i]->p_Left->p_Left->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Left->p_Left->m_number == 0)
						{
							tempNode[i]->p_Left->p_Left->m_number = tempNode[i]->p_Left->p_Left->p_Left->m_number;
							tempNode[i]->p_Left->p_Left->p_Left->m_number = 0;
							movecount++;
						}
					}
					if (tempNode[i]->p_Left->p_Left->m_number != 0)//세번째와 두번째를 계산한다.
					{
						if (tempNode[i]->p_Left->p_Left->m_number == tempNode[i]->p_Left->m_number)
						{
							if (tempNode[i]->p_Left->p_Left->m_block == false && tempNode[i]->p_Left->m_block == false)
							{
								tempNode[i]->p_Left->m_number *= 2;
								tempNode[i]->p_Left->p_Left->m_number = 0;
								tempNode[i]->p_Left->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->p_Left->m_number == 0)
						{
							tempNode[i]->p_Left->m_number = tempNode[i]->p_Left->p_Left->m_number;
							tempNode[i]->p_Left->p_Left->m_number = 0;
							movecount++;
						}
					}

					//두번째와 첫번째를 계산한다.
					if (tempNode[i]->p_Left->m_number != 0) //숫자가 0인지 검사
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Left->m_number)
						{
							if (tempNode[i]->p_Left->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Left->m_number = 0;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//위는 0이아니지만 아래가 0일경우 위에숫자를 아래로 보낸다.
							tempNode[i]->m_number = tempNode[i]->p_Left->m_number;
							tempNode[i]->p_Left->m_number = 0;
							movecount++;
						}
					}
				}
				comparecount--;
			}
			comparecount = 3;//다음 노드의(오른쪽노드)계산을 위해 다시 3으로 바꿔준다.
		}

		//거듭제곱을 마치고 아래로 내렸으면 이제 랜덤한 노드에 숫자 2를 집어넣는다.
		if (movecount != 0)
		{
			addRandomNum(L);
		}
		break;
		
	case VK_UP://위변을 기준으로 계산
		tempNode[0] = L;
		tempNode[1] = L->p_Right;
		tempNode[2] = L->p_Right->p_Right;
		tempNode[3] = L->p_Right->p_Right->p_Right;

		for (int i = 0; i < 4; i++)
		{
			while (comparecount != 0)
			{
				if (comparecount == 3) // 첫번째 노드와 두번째 노드 비교
				{
					if (tempNode[i]->p_Down->m_number != 0) //숫자가 0인지 검사, 0이면 계산할 필요가 없다.
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Down->m_number) //똑같은숫자면 거듭제곱시키고 숫자를 아래로 보냄
						{
							tempNode[i]->m_number *= 2;
							tempNode[i]->p_Down->m_number = 0;
							tempNode[i]->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->m_number == 0)
						{//위는 0이아니지만 아래가 0일경우 위에숫자를 아래로 보낸다.
							tempNode[i]->m_number = tempNode[i]->p_Down->m_number;
							tempNode[i]->p_Down->m_number = 0;
							movecount++;
						}
						//둘다 다를경우 (EX 2, 4) 아무것도 하지않음 
					}
				}

				//세번째, 두번째를 비교한 뒤 그 결과를 첫번째노드와 비교
				else if (comparecount == 2)
				{
					if (tempNode[i]->p_Down->p_Down->m_number != 0)//세번째와 두번째를 비교한다.
					{
						if (tempNode[i]->p_Down->p_Down->m_number == tempNode[i]->p_Down->m_number)//숫자가 같을때 거듭제곱
						{
							tempNode[i]->p_Down->m_number *= 2;
							tempNode[i]->p_Down->p_Down->m_number = 0;
							tempNode[i]->p_Down->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Down->m_number == 0)
						{
							tempNode[i]->p_Down->m_number = tempNode[i]->p_Down->p_Down->m_number;
							tempNode[i]->p_Down->p_Down->m_number = 0;
							movecount++;
						}
					}

					//두번째와 첫번째를 비교한다.
					if (tempNode[i]->p_Down->m_number != 0) //숫자가 0인지 검사
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Down->m_number)
						{
							if (tempNode[i]->p_Down->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Down->m_number = 0;
								tempNode[i]->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//위는 0이아니지만 아래가 0일경우 위에숫자를 아래로 보낸다.
							tempNode[i]->m_number = tempNode[i]->p_Down->m_number;
							tempNode[i]->p_Down->m_number = 0;
							movecount++;
						}
					}
				}

				//네번째,세번째를 계산 후 그 결과값을 두번째와, 또 그결과를 첫번째와 계산
				else if (comparecount == 1)
				{
					//네번째와 세번째를 계산
					if (tempNode[i]->p_Down->p_Down->p_Down->m_number != 0)
					{
						if (tempNode[i]->p_Down->p_Down->p_Down->m_number == tempNode[i]->p_Down->p_Down->m_number)
						{
							tempNode[i]->p_Down->p_Down->m_number *= 2;
							tempNode[i]->p_Down->p_Down->p_Down->m_number = 0;
							tempNode[i]->p_Down->p_Down->m_block = true;
							movecount++;
						}
						else if (tempNode[i]->p_Down->p_Down->m_number == 0)
						{
							tempNode[i]->p_Down->p_Down->m_number = tempNode[i]->p_Down->p_Down->p_Down->m_number;
							tempNode[i]->p_Down->p_Down->p_Down->m_number = 0;
							movecount++;
						}
					}
					if (tempNode[i]->p_Down->p_Down->m_number != 0)//세번째와 두번째를 계산한다.
					{
						if (tempNode[i]->p_Down->p_Down->m_number == tempNode[i]->p_Down->m_number)
						{
							if (tempNode[i]->p_Down->p_Down->m_block == false && tempNode[i]->p_Down->m_block == false)
							{
								tempNode[i]->p_Down->m_number *= 2;
								tempNode[i]->p_Down->p_Down->m_number = 0;
								tempNode[i]->p_Down->m_block = true;
								movecount++;
							}
						}
						else if (tempNode[i]->p_Down->m_number == 0)
						{
							tempNode[i]->p_Down->m_number = tempNode[i]->p_Down->p_Down->m_number;
							tempNode[i]->p_Down->p_Down->m_number = 0;
							movecount++;
						}
					}

					//두번째와 첫번째를 계산한다.
					if (tempNode[i]->p_Down->m_number != 0) //숫자가 0인지 검사
					{
						if (tempNode[i]->m_number == tempNode[i]->p_Down->m_number)
						{
							if (tempNode[i]->p_Down->m_block == false && tempNode[i]->m_block == false)
							{
								tempNode[i]->m_number *= 2;
								tempNode[i]->p_Down->m_number = 0;
								movecount++;
							}
						}
						else if (tempNode[i]->m_number == 0)
						{//위는 0이아니지만 아래가 0일경우 위에숫자를 아래로 보낸다.
							tempNode[i]->m_number = tempNode[i]->p_Down->m_number;
							tempNode[i]->p_Down->m_number = 0;
							movecount++;
						}
					}
				}
				comparecount--;
			}
			comparecount = 3;//다음 노드의(오른쪽노드)계산을 위해 다시 3으로 바꿔준다.
		}

		//거듭제곱을 마치고 아래로 내렸으면 이제 랜덤한 노드에 숫자 2를 집어넣는다.
		if (movecount != 0)
		{
			addRandomNum(L);
		}
		break;
	}

	if (log == true)//로그메뉴가 체크되어있으면 로그파일을 만들어준다.
	{
		Block* storeNode = L;
		ofstream fcout;
		
		fcout.open("log.txt", ios::ate | ios::app);

		if (key == VK_LEFT)
		{
			fcout << logNum << ". KEY_LEFT\n[result]\n";
		}
		else if (key == VK_RIGHT)
		{
			fcout << logNum << ". KEY_RIFHT\n[result]\n";
		}
		else if (key == VK_DOWN)
		{
			fcout << logNum << ". KEY_DOWN\n[result]\n";
		}
		else if (key == VK_UP)
		{
			fcout << logNum << ". KEY_UP\n[result]\n";
		}

		for (int i = 0; i < 4; i++)
		{
			while (storeNode->p_Right != NULL)
			{
				if (storeNode->m_number == 0)	//숫자가 0이면 공백만 넣는다.
				{
					fcout << "\t";
				}
				else
				{
					fcout << storeNode->m_number << "\t";
				}

				storeNode = storeNode->p_Right;	//입력을 완료하면 다음노드로 간다.

				if (storeNode->p_Right == NULL)	//만약 마지막 노드라면 숫자를 입력하고 한칸 아래로 내려준다
				{
					if (storeNode->m_number == 0)
					{
						fcout << "\t\n";
					}
					else
					{
						fcout << storeNode->m_number << "\t\n";
					}
				}
			}
			storeNode = storeNode->p_Left->p_Left->p_Left;
			storeNode = storeNode->p_Down;
		}
		fcout.close();
	}
}

void Block::addRandomNum(Block* L)//랜덤한곳에 2를 입력한다.
{
	//x,y를 이용해 임의의 노드를 선택한다.
	int ranx = 1;
	int rany = 1;
	srand((unsigned int)time(NULL));

	/////////////////////////////////////////////////
	Block* tempNode = L;
	//x만큼 오른쪽노드로,y만큼 아래쪽노드로 이동한다.
	
	while (ranx != 0 || rany != 0) //   (ex) x == 0 y == 1이면 x는 무시, L->p_Down을 실행한다.
	{
		ranx = rand() % 4;
		rany = rand() % 4;

		while (ranx != 0) {
			tempNode = tempNode->p_Right;
			ranx--;
		}
		while (rany != 0) {
			tempNode = tempNode->p_Down;
			rany--;
		}

		if (tempNode->m_number != 0)//만약 선택한 노드에 숫자가 들어있으면 다시 랜덤한값을넣어 숫자가없는 노드가 나올때까지 계산한다.
		{
			ranx = 1;
			tempNode = L;	//노드는 다시 헤더쪽으로 돌려놓는다.
		}
	}
	tempNode->m_number = 2;	//계산이 완료되면 임의의 노드m_number에 2를 넣는다
}

int Block::CheckGameOver(Block* L)//2048을 완성하거나 모든노드에 숫자가 있지만 2048이 없을경우 게임오버 메세지를 출력 후 프로그램을 종료시킨다.
{
	int numcount = 0; //각 노드의 m_number에 숫자가 있는지 검사하는 변수, 16이되면 게임종료, 하지만 움직일수 있는 경우의 수가 있을때는 계속 진행
	int gameover = 0; //0이면 계속 진행, 1이면 2048완성, 2면숫자가 꽉차서 게임오버
	Block* tempNode = L;

	//검사하는김에 노드에m_block을 전부 false로 초기화시킨다.

	for (int y = 0 ; y < 4 ; y++)
	{
		if (y == 0)//첫번째 줄
		{
			while (tempNode!=NULL)
			{
				tempNode->m_block = false;
				if (tempNode->m_number == 2048)//m_number가 2048인지 검사
				{
					gameover = 1;
					return gameover;	//2048이면 바로 게임오버신호를 보냄
				}
				if (tempNode->m_number != 0)//숫자 16개가 꽉찼는지 numcount로 확인한다.
				{
					numcount += 1;
				}
				tempNode = tempNode->p_Right;
			}
			tempNode = L; //확인했으면 다시 헤더로 돌아간다.
		}
		else if (y == 1)
		{
			tempNode = tempNode->p_Down;
			while (tempNode != NULL)
			{
				tempNode->m_block = false;
				if (tempNode->m_number == 2048)
				{
					gameover = 1;
					return gameover;
				}
				if (tempNode->m_number != 0)
				{
					numcount += 1;
				}
				tempNode = tempNode->p_Right;
			}
			tempNode = L;
		}
		else if (y == 2)
		{
			tempNode = tempNode->p_Down->p_Down;
			while (tempNode != NULL)
			{
				tempNode->m_block = false;
				if (tempNode->m_number == 2048)
				{
					gameover = 1;
					return gameover;
				}
				if (tempNode->m_number != 0)
				{
					numcount += 1;
				}
				tempNode = tempNode->p_Right;
			}
			tempNode = L;
		}
		else if (y == 3)
		{
			tempNode = tempNode->p_Down->p_Down->p_Down;
			while (tempNode != NULL)
			{
				tempNode->m_block = false;
				if (tempNode->m_number == 2048)
				{
					gameover = 1;
					return gameover;
				}
				if (tempNode->m_number != 0)
				{
					numcount += 1;
				}
				tempNode = tempNode->p_Right;
			}
			tempNode = L;
		}
	}

	Block* lastCheck = L;
	int checknum = 0;

	if (numcount == 16)//모든 노드에 숫자가 들어있으나 아직 이동가능한 노드가 있을경우(EX-2,2가 붙어있을경우)게임오버가 되지않는다.
	{
		for (int y = 0 ; y < 4 ; y++)//왼쪽,오른쪽의 숫자중 같은게 있는지 검사
		{
			while (lastCheck != NULL)
			{
				if (lastCheck->m_number == lastCheck->p_Right->m_number)
				{
					checknum++;
				}
				if (lastCheck->p_Right->p_Right != NULL)//3번만 검사한다. 12 , 23,  34 따라서 4번째노드까지 갈 필요가 없음.
				{
					lastCheck = lastCheck->p_Right;
				}
				else
				{
					break;
				}
			}
			lastCheck = lastCheck->p_Left->p_Left->p_Down;//다시 원상복귀하고 한칸 아래로 내려감
		}
		
		lastCheck = L;

		for (int x = 0 ; x < 4 ; x++)//이제 위쪽,아래쪽 숫자를 검사한다.
		{
			while (lastCheck != NULL)
			{
				if (lastCheck->m_number == lastCheck->p_Down->m_number)
				{
					checknum++;
				}
				if (lastCheck->p_Down->p_Down != NULL)
				{
					lastCheck = lastCheck->p_Down;
				}
				else
				{
					break;
				}
			}
			lastCheck = lastCheck->p_Up->p_Up->p_Right;
		}

		if (checknum == 0)//checknum에 아무것도 들어오지 않았을경우(모든 이웃한 노드의 숫자가 다를경우)게임오버가된다.
		{
			gameover = 2;
		}
	}
	return gameover;
}

void Block::TurnNode(Block* L, int direction, int logNum, bool log)
{
	//오른쪽으로 돌릴 시 case 1:
	/*1 2 3 4				13 9 5 1
	5 6 7 8		->			14 10 6 2
	9 10 11 12				15 11 7 3
	13 14 15 16				16 12 8 4
	*///왼쪽은 반대로 case2:
	Block* tempNode[4];

	int tempcount = 0;	//tempnum에 저장을하면 +1씩시켜 모든 숫자를 저장시키게한다.
	int tempnum[16];	//숫자를 모두 저장해 재배치한다.

	//노드를 돌려주기위해 임시저장노드를 만든다. 
	tempNode[0] = L;
	tempNode[1] = L->p_Down;
	tempNode[2] = L->p_Down->p_Down;
	tempNode[3] = L->p_Down->p_Down->p_Down;

	switch (direction)
	{
	case 1://오른쪽으로 돌린다.

		for (int i = 0 ;i < 4 ;i++)
		{
			while (tempNode[i]->p_Right != NULL)//왼쪽에서 오른쪽으로 가면서 숫자를 tempnum에저장한다
			{
				tempnum[tempcount] = tempNode[i]->m_number;
				tempcount++;
				tempNode[i] = tempNode[i]->p_Right;
				if (tempNode[i]->p_Right == NULL)//마지막 노드는 while문 조건에 막혀 저장이 안되므로 따로 조건을 만들어 준다.
				{
					tempnum[tempcount] = tempNode[i]->m_number;
					tempcount++;
				}
			}
		}

		//모든 노드를 오른쪽부터 차례로 다시 재지정한다.
		tempNode[0] = L->p_Right->p_Right->p_Right;
		tempNode[1] = L->p_Right->p_Right;
		tempNode[2] = L->p_Right;
		tempNode[3] = L;
		//tempnum 배열에 접근하기위해 tempcount를 다시 0으로 바꾼다.
		tempcount = 0;
		//이제 tempnum에 저장된 숫자를 다시 재배치한다.
		for (int i = 0 ; i < 4 ; i++)
		{
			while (tempNode[i]->p_Down != NULL)
			{
				tempNode[i]->m_number = tempnum[tempcount];
				tempcount++;
				tempNode[i] = tempNode[i]->p_Down;
				if (tempNode[i]->p_Down == NULL)//위와 마찬가지로 따로 조건을 만들어준다.
				{
					tempNode[i]->m_number = tempnum[tempcount];
					tempcount++;
				}
			}
		}
		break;

	case 2://왼쪽으로 돌린다.
		/*		1 2 3 4		->		4 8 12 16
				5 6 7 8				3 7 11 15
				9 10 11 12			2 6 10 14
		*///	13 14 15 16			1 5 9 13

		//숫자를 뽑는것은 같다.
		for (int i = 0; i < 4; i++)
		{
			while (tempNode[i]->p_Right != NULL)//왼쪽에서 오른쪽으로 가면서 숫자를 tempnum에저장한다
			{
				tempnum[tempcount] = tempNode[i]->m_number;
				tempcount++;
				tempNode[i] = tempNode[i]->p_Right;
				if (tempNode[i]->p_Right == NULL)//마지막 노드는 while문 조건에 막혀 저장이 안되므로 따로 조건을 만들어 준다.
				{
					tempnum[tempcount] = tempNode[i]->m_number;
					tempcount++;
				}
			}
		}

		//모든 노드를 아래쪽부터 차례로 다시 재지정한다.
		tempNode[0] = L->p_Down->p_Down->p_Down;
		tempNode[1] = L->p_Down->p_Down->p_Down->p_Right;
		tempNode[2] = L->p_Down->p_Down->p_Down->p_Right->p_Right;
		tempNode[3] = L->p_Down->p_Down->p_Down->p_Right->p_Right->p_Right;

		//tempnum 배열에 접근하기위해 tempcount를 다시 0으로 바꾼다.
		tempcount = 0;

		//이제 tempnum에 저장된 숫자를 다시 재배치한다.
		for (int i = 0; i < 4; i++)
		{
			while (tempNode[i]->p_Up != NULL)
			{
				tempNode[i]->m_number = tempnum[tempcount];
				tempcount++;
				tempNode[i] = tempNode[i]->p_Up;
				if (tempNode[i]->p_Up == NULL)//위와 마찬가지로 따로 조건을 만들어준다.
				{
					tempNode[i]->m_number = tempnum[tempcount];
					tempcount++;
				}
			}
		}
		break;

	default:

		break;
	}

	if (log == true)//회전로그메뉴가 체크되어있을때 log파일에 저장시켜준다
	{
		Block* storeNode = L;
		ofstream f;
		
		f.open("log.txt",ios::ate | ios::app);

		if (direction == 1) //오른쪽
		{
			f << logNum << ". Mouse_Left_to_Right\n[result]\n";
		}
		else if (direction == 2)//왼쪽
		{
			f << logNum << ". Mouse_Right_to_Left\n[result]\n";
		}

		for (int i = 0; i < 4; i++)//숫자입력은 키보드입력때와 같다.
		{
			while (storeNode->p_Right != NULL)
			{
				if (storeNode->m_number == 0)	//숫자가 0이면 공백만 넣는다.
				{
					f << "\t";
				}
				else
				{
					f << storeNode->m_number << "\t";
				}

				storeNode = storeNode->p_Right;	//입력을 완료하면 다음노드로 간다.

				if (storeNode->p_Right == NULL)	//만약 마지막 노드라면 숫자를 입력하고 한칸 아래로 내려준다
				{
					if (storeNode->m_number == 0)
					{
						f << "\t\n";
					}
					else
					{
						f << storeNode->m_number << "\t\n";
					}
				}
			}
			storeNode = storeNode->p_Left->p_Left->p_Left;
			storeNode = storeNode->p_Down;
		}

		f.close();
	}
}

Block::~Block()
{

}