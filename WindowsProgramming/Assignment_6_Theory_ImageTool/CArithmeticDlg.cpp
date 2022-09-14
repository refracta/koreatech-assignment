// CArithmeticDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ImageTool.h"
#include "CArithmeticDlg.h"
#include "afxdialogex.h"
#include "ImageToolDoc.h"


// CArithmeticDlg 대화 상자

IMPLEMENT_DYNAMIC(CArithmeticDlg, CDialogEx)

CArithmeticDlg::CArithmeticDlg(CWnd* pParent /*=nullptr*/)
   : CDialogEx(IDD_ARITHMETIC, pParent)
   , m_nFunction(0), m_pDoc1(NULL), m_pDoc2(NULL)
{

}

CArithmeticDlg::~CArithmeticDlg()
{
}

void CArithmeticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_IMAGE1, m_comboImage1);
	DDX_Control(pDX, IDC_COMBO_IMAGE2, m_comboImage2);
	DDX_Radio(pDX, IDC_FUNCTION1, m_nFunction);
}


BEGIN_MESSAGE_MAP(CArithmeticDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CArithmeticDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CArithmeticDlg 메시지 처리기


BOOL CArithmeticDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 콤보 박스에 차일드윈도우 창의 이름을 삽입
	int nIndex = 0;
	CString strTitle;

	CImageToolApp* pApp = (CImageToolApp*)AfxGetApp();
	POSITION pos = pApp->m_pImageDocTemplate->GetFirstDocPosition();
	while (pos != NULL) {
		CImageToolDoc* pDoc = (CImageToolDoc*)pApp->m_pImageDocTemplate->GetNextDoc(pos);
		if (pDoc->m_Dib.GetBitCount() != 8)
			continue;

		strTitle = pDoc->GetTitle();

		m_comboImage1.InsertString(nIndex, strTitle);
		m_comboImage2.InsertString(nIndex, strTitle);

		m_comboImage1.SetItemDataPtr(nIndex, (void*)pDoc);
		m_comboImage2.SetItemDataPtr(nIndex, (void*)pDoc);
		
		nIndex++;
	}
	m_comboImage1.SetCurSel(0);
	m_comboImage1.SetCurSel(0);

	if (nIndex > 1) m_comboImage2.SetCurSel(1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CArithmeticDlg::OnBnClickedOk()
{
	m_pDoc1 = (CImageToolDoc*)m_comboImage1.GetItemDataPtr(m_comboImage1.GetCurSel());
	m_pDoc2 = (CImageToolDoc*)m_comboImage2.GetItemDataPtr(m_comboImage2.GetCurSel());

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
