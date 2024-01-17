// CObjectsDlg.cpp: файл реализации
//

#include "pch.h"
#include "SDIApp.h"
#include "afxdialogex.h"
#include "CObjectsDlg.h"


// Диалоговое окно CObjectsDlg

IMPLEMENT_DYNAMIC(CObjectsDlg, CDialog)

CObjectsDlg::CObjectsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_bShtrix(FALSE)
	, m_bSinus(FALSE)
	, m_bLine(FALSE)
{

}

CObjectsDlg::~CObjectsDlg()
{
}

void CObjectsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_Shtrix, m_bShtrix);
	DDX_Check(pDX, IDC_CHECK_Sinus, m_bSinus);
	DDX_Check(pDX, IDC_CHECK_Line, m_bLine);
}


BEGIN_MESSAGE_MAP(CObjectsDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_Shtrix, &CObjectsDlg::OnBnClickedCheckShtrix)
END_MESSAGE_MAP()


// Обработчики сообщений CObjectsDlg


void CObjectsDlg::OnBnClickedCheckShtrix()
{
	// TODO: добавьте свой код обработчика уведомлений
}
