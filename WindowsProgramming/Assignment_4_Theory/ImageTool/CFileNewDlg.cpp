// CFileNewDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "CFileNewDlg.h"
#include "afxdialogex.h"


// CFileNewDlg 대화 상자

IMPLEMENT_DYNAMIC(CFileNewDlg, CDialogEx)

CFileNewDlg::CFileNewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILE_NEW, pParent)
	, m_nWidth(256)
	, m_nHeight(256)
	, m_nType(0)
{

}

CFileNewDlg::~CFileNewDlg()
{
}

void CFileNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDX_CBIndex(pDX, IDC_IMAGE_TYPE, m_nType);
}


BEGIN_MESSAGE_MAP(CFileNewDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_IMAGE_TYPE, &CFileNewDlg::OnCbnSelchangeImageType)
END_MESSAGE_MAP()


// CFileNewDlg 메시지 처리기


void CFileNewDlg::OnCbnSelchangeImageType()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
