#pragma once
#include "afxdialogex.h"
class CSDIAppView;

// Диалоговое окно CColorDlg

class CColorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	CColorDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CColorDlg();

	CSDIAppView* pView;


// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CMFCColorButton m_ColorCtrl1;
	afx_msg void OnBnClickedMfccolorbutton1();
	CMFCColorButton m_ColorCtrl2;
	afx_msg void OnBnClickedMfccolorbutton2();
	afx_msg void OnBnClickedMfccolorbutton3();
	CMFCColorButton m_ColorCtrl3;
};
