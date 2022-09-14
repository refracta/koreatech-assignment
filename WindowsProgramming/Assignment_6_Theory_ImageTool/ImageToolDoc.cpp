
// ImageToolDoc.cpp : CImageToolDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ImageTool.h"
#endif

#include "ImageToolDoc.h"
#include "FileNewDlg.h"
#include "CBrightnessContrastDlg.h"
#include "CArithmeticDlg.h"

#include <propkey.h>

#include "IppImage/IppImage.h"
#include "IppImage/IppConvert.h"
#include "IppImage/IppEnhance.h"

#define CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img) \
	IppByteImage img; \
	IppDibToImage(m_Dib, img);

#define CONVERT_IMAGE_TO_DIB(img, dib) \
	IppDib dib; \
	IppImageToDib(img, dib);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageToolDoc

IMPLEMENT_DYNCREATE(CImageToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageToolDoc, CDocument)
	ON_COMMAND(ID_WINDOW_DUPLICATE, &CImageToolDoc::OnWindowDuplicate)
	ON_COMMAND(ID_EDIT_COPY, &CImageToolDoc::OnEditCopy)
	ON_COMMAND(ID_IMAGE_INVERSE, &CImageToolDoc::OnImageInverse)
	ON_COMMAND(ID_BRIGHTNESS_CONTRAST_MENU, &CImageToolDoc::OnBrightnessContrast)
	ON_COMMAND(ID_ARITHMETIC, &CImageToolDoc::OnArithmetic)
END_MESSAGE_MAP()


// CImageToolDoc ����/�Ҹ�

CImageToolDoc::CImageToolDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CImageToolDoc::~CImageToolDoc()
{
}

BOOL CImageToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	BOOL ret = TRUE;

	if (theApp.m_pNewDib == NULL)
	{
		CFileNewDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			if (dlg.m_nType == 0) // �׷��̽����� ��Ʈ��
				ret = m_Dib.CreateGrayBitmap(dlg.m_nWidth, dlg.m_nHeight);
			else // Ʈ���÷� ��Ʈ��
				ret = m_Dib.CreateRgbBitmap(dlg.m_nWidth, dlg.m_nHeight);
		}
		else
		{
			ret = FALSE;
		}
	}
	else
	{
		m_Dib = *(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;
	}

	return ret;
}




// CImageToolDoc serialization

void CImageToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CImageToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CImageToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageToolDoc ����

#ifdef _DEBUG
void CImageToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageToolDoc ����


BOOL CImageToolDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	BOOL res = m_Dib.Load(CT2A(lpszPathName));
	if (res)
		AfxPrintInfo(_T("[���� ����] ���� ���: %s, ���� ũ��: %d�ȼ�, ���� ũ��: %d�ȼ�, �����: %d"),
			lpszPathName, m_Dib.GetWidth(), m_Dib.GetHeight(), 0x01 << m_Dib.GetBitCount());

	return res;
}


BOOL CImageToolDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return m_Dib.Save(CT2A(lpszPathName));
}


void CImageToolDoc::OnWindowDuplicate()
{
	AfxNewBitmap(m_Dib);
}


void CImageToolDoc::OnEditCopy()
{
	if (m_Dib.IsValid())
		m_Dib.CopyToClipboard();
}


void CImageToolDoc::OnImageInverse()
{
	IppDib dib;
	IppByteImage bImg;
	IppRgbImage rgbImg;

	switch (m_Dib.GetBitCount()) {
		case 8:
			IppDibToImage(m_Dib, bImg);
			IppInverse(bImg);
			IppImageToDib(bImg, dib);
			break;
		case 24:
			IppDibToImage(m_Dib, rgbImg);
			IppInverse(rgbImg);
			IppImageToDib(rgbImg, dib);
			break;
	}
	
	
	AfxPrintInfo(_T("[����] �Է� ����: %s"), GetTitle());
	AfxNewBitmap(dib);
}


void CImageToolDoc::OnBrightnessContrast()
{
	// TODO: ���⿡ ���� ó���� �ڵ带 �߰��մϴ�.
	CBrightnessContrastDlg dlg;

	IppDib dib;
	IppByteImage bImg;
	IppRgbImage rgbImg;

	if (dlg.DoModal() == IDOK) {
		switch (m_Dib.GetBitCount()) {
			case 8:
				IppDibToImage(m_Dib, bImg);
				IppBrightness(bImg, dlg.m_nBrightness);
				IppContrast(bImg, dlg.m_nContrast);
				IppImageToDib(bImg, dib);
				break;
			case 24:
				IppDibToImage(m_Dib, rgbImg);
				IppBrightness(rgbImg, dlg.m_nBrightness);
				IppContrast(rgbImg, dlg.m_nContrast);
				IppImageToDib(rgbImg, dib);
				break;
		}

		AfxPrintInfo(_T("[��� ����] �Է� ����: %s, ���: %d"), GetTitle(), dlg.m_nBrightness);
		AfxNewBitmap(dib);
	}
}


void CImageToolDoc::OnArithmetic()
{
	CArithmeticDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CImageToolDoc* pDoc1 = (CImageToolDoc*)dlg.m_pDoc1;
		CImageToolDoc* pDoc2 = (CImageToolDoc*)dlg.m_pDoc2;

		CONVERT_DIB_TO_BYTEIMAGE(pDoc1->m_Dib, img1)
		CONVERT_DIB_TO_BYTEIMAGE(pDoc2->m_Dib, img2)
		IppByteImage img3;

		bool ret = false;

		switch (dlg.m_nFunction)
		{
		case 0: ret = IppAdd(img1, img2, img3);  break;
		case 1: ret = IppSub(img1, img2, img3);  break;
		}

		if (ret)
		{
			CONVERT_IMAGE_TO_DIB(img3, dib)

				TCHAR* op[] = { _T("����"), _T("����")};
			AfxPrintInfo(_T("[��� �� ���� ����] [%s] �Է� ���� #1: %s, �Է� ���� #2: %s"),
				op[dlg.m_nFunction], pDoc1->GetTitle(), pDoc2->GetTitle());
			AfxNewBitmap(dib);
		}
		else
			AfxMessageBox(_T("������ ũ�Ⱑ �ٸ��ϴ�!"));
	}
}