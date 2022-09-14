
// Assignment_1_Theory_1View.cpp: CAssignment1Theory1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Assignment_1_Theory_1.h"
#endif

#include "Assignment_1_Theory_1Doc.h"
#include "Assignment_1_Theory_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAssignment1Theory1View

IMPLEMENT_DYNCREATE(CAssignment1Theory1View, CView)

BEGIN_MESSAGE_MAP(CAssignment1Theory1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CAssignment1Theory1View 생성/소멸

CAssignment1Theory1View::CAssignment1Theory1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CAssignment1Theory1View::~CAssignment1Theory1View()
{
}

BOOL CAssignment1Theory1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CAssignment1Theory1View 그리기

void CAssignment1Theory1View::OnDraw(CDC* pDC)
{
	CAssignment1Theory1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CString str = _T("refracta 0123456789");
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < i % 6 + 1; j++)
		{
			pDC->TextOut(160 * j, 20 * i, str);
		}
	}
}


// CAssignment1Theory1View 인쇄

BOOL CAssignment1Theory1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CAssignment1Theory1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CAssignment1Theory1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CAssignment1Theory1View 진단

#ifdef _DEBUG
void CAssignment1Theory1View::AssertValid() const
{
	CView::AssertValid();
}

void CAssignment1Theory1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAssignment1Theory1Doc* CAssignment1Theory1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAssignment1Theory1Doc)));
	return (CAssignment1Theory1Doc*)m_pDocument;
}
#endif //_DEBUG


// CAssignment1Theory1View 메시지 처리기
