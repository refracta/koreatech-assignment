#pragma once


// CArithmeticDlg 대화 상자

class CArithmeticDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CArithmeticDlg)

public:
	CArithmeticDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CArithmeticDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARITHMETIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboImage1;
	CComboBox m_comboImage2;
	int m_nFunction;
	void* m_pDoc1;
	void* m_pDoc2;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
