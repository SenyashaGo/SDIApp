// CColorDlg.cpp: файл реализации
//

#include "pch.h"
#include "SDIApp.h"
#include "afxdialogex.h"
#include "CColorDlg.h"
#include "SDIAppView.h" 

// Диалоговое окно CColorDlg

IMPLEMENT_DYNAMIC(CColorDlg, CDialogEx)

CColorDlg::CColorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_ColorCtrl1);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON2, m_ColorCtrl2);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON3, m_ColorCtrl3);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CColorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CColorDlg::OnBnClickedMfccolorbutton1)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON2, &CColorDlg::OnBnClickedMfccolorbutton2)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON3, &CColorDlg::OnBnClickedMfccolorbutton3)
END_MESSAGE_MAP()


// Обработчики сообщений CColorDlg


void CColorDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CColorDlg::OnBnClickedMfccolorbutton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	pView->m_Color1 = m_ColorCtrl1.GetColor();

	pView->m_Color2 = m_ColorCtrl2.GetColor();

	pView->Invalidate();
}


void CColorDlg::OnBnClickedMfccolorbutton2()
{
	// TODO: добавьте свой код обработчика уведомлений
	pView->m_Color2 = m_ColorCtrl2.GetColor();

	pView->Invalidate();
}


void CColorDlg::OnBnClickedMfccolorbutton3()
{
	// TODO: добавьте свой код обработчика уведомлений
	pView->m_Color3 = m_ColorCtrl3.GetColor();

	pView->Invalidate();
}
