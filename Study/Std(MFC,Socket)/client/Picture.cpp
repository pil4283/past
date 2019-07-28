#include "StdAfx.h"
#include "Picture.h"
#include "resource.h"

CDC m_backDC;
CBitmap m_backBit;

Picture::Picture(void)
{
	stage = -1;
	for(int i=0;i<5;i++)
	{
		isCollect[i] = -1;
	}
}

Picture::~Picture(void)
{
}

void Picture::Create(void)
{
	CClientDC dc((CWnd*)m_pView);
	

	m_backBit.LoadBitmapA(IDB_BACK);
	m_backDC.CreateCompatibleDC(&dc);
	m_backDC.SelectObject(&m_backBit);



	//m_bBuffer.LoadBitmapA(IDB_BACK);
	m_bBuffer.CreateCompatibleBitmap(&dc,1600,1950);
	m_bBufferDC.CreateCompatibleDC(&dc);
	m_bBufferDC.SelectObject(&m_bBuffer);

	m_bitmap.LoadBitmapA(IDB_STAGE1);
	m_dc.CreateCompatibleDC(&dc);
	m_dc.SelectObject(&m_bitmap);

	m_bitmap2.LoadBitmapA(IDB_STAGE2);
	m_dc2.CreateCompatibleDC(&dc);
	m_dc2.SelectObject(&m_bitmap2);


	m_bitmap3.LoadBitmapA(IDB_STAGE3);
	m_dc3.CreateCompatibleDC(&dc);
	m_dc3.SelectObject(&m_bitmap3);


	m_bitmap4.LoadBitmapA(IDB_STAGE4);
	m_dc4.CreateCompatibleDC(&dc);
	m_dc4.SelectObject(&m_bitmap4);


	m_bitmap5.LoadBitmapA(IDB_STAGE5);
	m_dc5.CreateCompatibleDC(&dc);
	m_dc5.SelectObject(&m_bitmap5);

	m_bitmap6.LoadBitmapA(IDB_ONE);
	m_dc6.CreateCompatibleDC(&dc);
	m_dc6.SelectObject(&m_bitmap6);


}

void Picture::Draw(CDC* pDC)
{
	BITMAP the;
	
	m_backBit.GetBitmap(&the);
	m_bBufferDC.BitBlt(0,0,the.bmWidth,the.bmHeight,&m_backDC,0,0,SRCCOPY);
	if(1 == stage)
	{
		m_bitmap.GetBitmap(&the);
		m_bBufferDC.BitBlt(0,0,the.bmWidth,the.bmHeight,&m_dc,0,0,SRCCOPY);
	}
	else if(2 == stage)
	{
		m_bitmap2.GetBitmap(&the);
		m_bBufferDC.BitBlt(0,0,the.bmWidth,the.bmHeight,&m_dc2,0,0,SRCCOPY);
	}
	else if(3 == stage)
	{
		m_bitmap3.GetBitmap(&the);
		m_bBufferDC.BitBlt(0,0,the.bmWidth,the.bmHeight,&m_dc3,0,0,SRCCOPY);
	}
	else if(4 == stage)
	{
		m_bitmap4.GetBitmap(&the);
		m_bBufferDC.BitBlt(0,0,the.bmWidth,the.bmHeight,&m_dc4,0,0,SRCCOPY);
	}
	else if(5 == stage)
	{
		m_bitmap5.GetBitmap(&the);
		m_bBufferDC.BitBlt(0,0,the.bmWidth,the.bmHeight,&m_dc5,0,0,SRCCOPY);
	}
	Collect(&m_bBufferDC);
	
	pDC->BitBlt(0,0,1600,1950,&m_bBufferDC,0,0,SRCCOPY);
}

void Picture::CheckCollect(int index)
{
	isCollect[index] = 1;
}
void Picture::Collect(CDC* pDC)
{
	BITMAP the1;
	if(stage == 1)
	{
		if(isCollect[0] == 1)
		{
			//pDC->Ellipse(495,433,495+50,433+50);
			//pDC->Ellipse(1151,433,1151+50,433+50);
			//m_bBufferDC.BitBlt(495,433,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,SRCCOPY);
			//m_bBufferDC.BitBlt(1151,433,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,SRCCOPY);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(495,433,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(1151,433,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[1]==1)
		{
			//pDC->Ellipse(586,495,586+50,495+50);
			//pDC->Ellipse(1242,495,1242+50,495+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(586,495,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(1242,495,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[2]==1)
		{
			//pDC->Ellipse(537,123,537+50,123+50);
			//pDC->Ellipse(1193,123,1193+50,123+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(537,123,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(1193,123,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[3]==1)
		{
			//pDC->Ellipse(447,242,447+50,242+50);
			//pDC->Ellipse(1103,242,1103+50,242+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(447,242,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(1103,242,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[4]==1)
		{
			//pDC->Ellipse(520,496,520+50,496+50);
			//pDC->Ellipse(1176,496,1176+50,496+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(520,496,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(1176,496,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
	}
	else if(stage == 2)
	{
		if(isCollect[0]==1)
		{
			//pDC->Ellipse(470,602,470+50,602+50);
			//pDC->Ellipse(1101,602,1101+50,602+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(470,602,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(1101,602,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[1]==1)
		{
			//pDC->Ellipse(472,158,472+50,158+50);
			//pDC->Ellipse(1103,158,1103+50,158+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(472,158,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(1103,158,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[2]==1)
		{
			//pDC->Ellipse(458,432,458+50,432+50);
			//pDC->Ellipse(1089,432,1089+50,432+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(458,432,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(1089,432,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[3]==1)
		{
			//pDC->Ellipse(367,40,367+50,40+50);
			//pDC->Ellipse(998,40,998+50,40+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(367,40,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(998,40,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[4]==1)
		{
			//pDC->Ellipse(332,195,332+50,195+50);
			//pDC->Ellipse(963,195,963+50,195+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(332,195,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(963,195,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
	}
	else if(stage==3)
	{
		if(isCollect[0]==1)
		{
			//pDC->Ellipse(240,590,240+50,590+50);
			//pDC->Ellipse(901,590,901+50,590+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(240,590,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(901,590,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[1]==1)
		{
			//pDC->Ellipse(14,566,14+50,566+50);
			//pDC->Ellipse(675,566,675+50,566+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(14,566,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(675,566,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[2]==1)
		{
			//pDC->Ellipse(159,82,159+50,82+50);
			//pDC->Ellipse(820,82,820+50,82+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(159,82,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(820,182,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[3]==1)
		{
			//pDC->Ellipse(284,238,284+50,238+50);
			//pDC->Ellipse(945,238,945+50,238+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(284,238,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(945,238,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[4]==1)
		{
			//pDC->Ellipse(515,485,515+50,485+50);
			//pDC->Ellipse(1176,485,1176+50,485+50);
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(515,485,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(1176,485,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
	}
	else if(stage == 4)
	{
		if(isCollect[0]==1)
		{
	
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(363,641,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(831,641,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[1]==1)
		{
			
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(363,472,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(831,472,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[2]==1)
		{
			
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(194,144,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(662,144,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[3]==1)
		{
			
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(305,640,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(773,640,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[4]==1)
		{
			
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(204,299,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(672,299,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
	}
	else if(stage == 5)
	{
		if(isCollect[0]==1)
		{
	
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(470,20,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(970,20,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[1]==1)
		{
			
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(460,170,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(960,170,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[2]==1)
		{
			
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(240,300,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(740,300,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[3]==1)
		{
			
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(290,440,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(790,440,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
		if(isCollect[4]==1)
		{
			
			m_bitmap6.GetBitmap(&the1);
			m_bBufferDC.TransparentBlt(270,490,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
			m_bBufferDC.TransparentBlt(770,490,the1.bmWidth,the1.bmHeight,&m_dc6,0,0,the1.bmWidth,the1.bmHeight,RGB(255,255,255));
		}
	}
}

void Picture::IniCollect(void)
{
	for(int i=0;i<5;i++)
	{
		isCollect[i]=-1;
	}
}
