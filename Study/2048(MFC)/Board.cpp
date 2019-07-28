#include "stdafx.h"
#include "Board.h"
#include "Block.h"


Board::Board()
	: drawOption(true)//숫자만 출력할지, 숫자 색깔 둘다 출력할지 정한다.
	, moveLog(true)
	, turnLog(true)
	, logNum(1)
	, isGameOver(false)
{
	Block_Header = Block_Header->createLinkedList_h();
}

void Board::Paint(CDC* pDC)
{
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = RGB(255, 255, 255);

	CString msg;
	CBrush* pOldBrush = pDC->SelectObject(&newBrush);


	for (int y = 0 ; y < 4 ; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			int num = Block_Header->createBoard(Block_Header, x, y);// 각 블록의 값을 가져온다 가져온 값에따라 색깔이 바뀌는 구조.
			msg.Format("%d ", num);

			switch (num)
			{
			case 0:
				logBrush.lbColor = RGB(255, 255, 255);//0하얀색
				break;
			case 2:
				logBrush.lbColor = RGB(255, 255, 0);//2 노란색
				if(drawOption == true)pDC->SetBkColor(RGB(255, 255, 0));//글자뒷배경에도 색을입혀준다. 숫자와색깔 메뉴가 체크되어있어야함.
				break;
			case 4:
				logBrush.lbColor = RGB(255, 127, 0);//4오렌지색
				if (drawOption == true)pDC->SetBkColor(RGB(255, 127, 0));
				break;
			case 8:
				logBrush.lbColor = RGB(0, 255, 0);//8녹색
				if (drawOption == true)pDC->SetBkColor(RGB(0, 255, 0));
				break;
			case 16:
				logBrush.lbColor = RGB(0, 0, 255);//16파란색
				if (drawOption == true)pDC->SetBkColor(RGB(0, 0, 255));
				break;
			case 32:
				logBrush.lbColor = RGB(166, 166, 166);//32회색
				if (drawOption == true)pDC->SetBkColor(RGB(166, 166, 166));
				break;
			case 64:
				logBrush.lbColor = RGB(255, 0, 255);//64핑크색
				if (drawOption == true)pDC->SetBkColor(RGB(255, 0, 255));
				break;
			case 128:
				logBrush.lbColor = RGB(0, 255, 255);//128하늘색
				if (drawOption == true)pDC->SetBkColor(RGB(0, 255, 255));
				break;
			case 256:
				logBrush.lbColor = RGB(128, 0, 128);//256분홍색
				if (drawOption == true)pDC->SetBkColor(RGB(128, 0, 128));
				break;
			case 512:
				logBrush.lbColor = RGB(112, 48, 160);//512바이올렛
				if (drawOption == true)pDC->SetBkColor(RGB(112, 48, 160));
				break;
			case 1024:
				logBrush.lbColor = RGB(255, 255, 255);//1024하얀색
				if (drawOption == true)pDC->SetBkColor(RGB(255, 255, 255));
				break;
			case 2048:
				logBrush.lbColor = RGB(255, 0, 0);//2048빨간색
				if (drawOption == true)pDC->SetBkColor(RGB(255, 0, 0));
				break;
			default:
				logBrush.lbColor = RGB(255, 255, 255);//그외 나머지
				if (drawOption == true)pDC->SetBkColor(RGB(255, 255, 255));
				break;
			}

			if (drawOption == true)//숫자랑색깔 메뉴가 체크되어있을때만 사각형에 색을 입혀준다
			{
				newBrush.CreateBrushIndirect(&logBrush);	//브러쉬에 지정된 색을 넣어준다
				pOldBrush = pDC->SelectObject(&newBrush);	//pDC에 넣어줌
			}

			pDC->Rectangle(x * 64, y * 64, x * 64 + 64, y * 64 + 64);//64x64픽셀로 사각형생성
			
			if (num != 0)//0이 아닐경우에만  숫자를 출력
			{
				pDC->TextOutA(x * 64 + 30, y * 64 + 30, msg);
			}
			
			pDC->SelectObject(pOldBrush);	// 색칠
			
			newBrush.DeleteObject();		//CBrush의 색을 바꾸려면 한번 지운 뒤 다시 만들어줘야함.
		}
	}
}
void Board::PushKey(int key)
{
	if (isGameOver == false)
	{
		Block_Header->moveNode(Block_Header, key, logNum, moveLog);
		if (moveLog == true)
		{
			logNum++;
		}
	}
	int gameOver = Block_Header->CheckGameOver(Block_Header);//게임오버인지 체크하는 변수 게임오버면 isGameOver불변수를 true로바꿔서 게임진행이 안되게 한다.

	switch (gameOver)
	{
	case 1://1이면 2048완성
		AfxMessageBox("2048완성");
		isGameOver = true;
		break;
	case 2://2이면 게임오버
		AfxMessageBox("게임오버...");
		isGameOver = true;
		break;
	default://0일때는 무시
		break;
	}
}
void Board::TurnBoard(int direction)//보드를 돌리는 함수 1은 오른쪽 2는 왼쪽으로 보드를 돌린다.
{
	if (isGameOver == false)//게임오버면 더이상 진행불가.
	{
		Block_Header->TurnNode(Block_Header, direction, logNum, turnLog);
		if (turnLog == true)
		{
			logNum++;
		}
	}
}

Board::~Board()
{
	//모든 리스트를 삭제함
	delete Block_Header;
}
