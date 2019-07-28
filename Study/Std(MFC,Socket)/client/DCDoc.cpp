// DCDoc.cpp : CDCDoc 클래스의 구현
//

#include "stdafx.h"
#include "DC.h"

#include "DCDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDCDoc

IMPLEMENT_DYNCREATE(CDCDoc, CDocument)

BEGIN_MESSAGE_MAP(CDCDoc, CDocument)
END_MESSAGE_MAP()


// CDCDoc 생성/소멸

CDCDoc::CDCDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
}

CDCDoc::~CDCDoc()
{
}

BOOL CDCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CDCDoc serialization

void CDCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CDCDoc 진단

#ifdef _DEBUG
void CDCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDCDoc 명령
