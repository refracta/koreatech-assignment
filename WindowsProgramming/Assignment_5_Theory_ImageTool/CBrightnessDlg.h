#pragma once


// CBrightnessDlg 대화 상자

class CBrightnessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBrightnessDlg)

public:
	CBrightnessDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBrightnessDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BRIGHTNESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderBrightness;
	virtual BOOL OnInitDialog();
	int m_nBrightness;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeBrightnessEdit();
};
