
// Assignment_1_Theory_1View.h: CAssignment1Theory1View 클래스의 인터페이스
//

#pragma once


class CAssignment1Theory1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CAssignment1Theory1View() noexcept;
	DECLARE_DYNCREATE(CAssignment1Theory1View)

// 특성입니다.
public:
	CAssignment1Theory1Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CAssignment1Theory1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Assignment_1_Theory_1View.cpp의 디버그 버전
inline CAssignment1Theory1Doc* CAssignment1Theory1View::GetDocument() const
   { return reinterpret_cast<CAssignment1Theory1Doc*>(m_pDocument); }
#endif

