// CMyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "SDIApp.h"
#include "CMyTreeView.h"

#include"SDIApp.h"
#include"SDIAppDoc.h"
#include"SDIAppView.h"


// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_OBJECT_Color, &CMyTreeView::OnObjectColor)
END_MESSAGE_MAP()


// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyTreeView


int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_CHECKBOXES;

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}

void  CMyTreeView::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();

	tree.DeleteAllItems();

	m_hRoot = tree.InsertItem(L"Объекты", -1, -1, NULL, TVI_FIRST);

	m_hLine = tree.InsertItem(L"Линия координат", -1, -1, m_hRoot, TVI_FIRST);
	m_hShtrix = tree.InsertItem(L"Штриховка", -1, -1, m_hRoot, TVI_FIRST);
	m_hSinus = tree.InsertItem(L"Синусоида", -1, -1, m_hRoot, TVI_FIRST);

	tree.SetCheck(m_hLine, m_pDoc->m_bLines);
	tree.SetCheck(m_hShtrix, m_pDoc->m_bShtrix);
	tree.SetCheck(m_hSinus, m_pDoc->m_bSinus);

	tree.Expand(m_hRoot, TVE_EXPAND);


}

void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CTreeView::OnLButtonDown(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();

	CRect rc;

	tree.GetItemRect(m_hRoot, &rc, false);
	if (rc.PtInRect(point))
		tree.SelectItem(m_hRoot);

	tree.GetItemRect(m_hLine, &rc, false);
	if (rc.PtInRect(point))
		tree.SelectItem(m_hLine);

	tree.GetItemRect(m_hSinus, &rc, false);
	if (rc.PtInRect(point))
		tree.SelectItem(m_hSinus);

	tree.GetItemRect(m_hShtrix, &rc, false);
	if (rc.PtInRect(point))
		tree.SelectItem(m_hShtrix);

	if (tree.GetSelectedItem() == m_hRoot)
	{
		bool check = tree.GetCheck(m_hRoot);

		tree.SetCheck(m_hLine, check);
		tree.SetCheck(m_hShtrix, check);
		tree.SetCheck(m_hSinus, check);
	}

	else
	{
		tree.SetCheck(m_hRoot, false);
	}

	m_pDoc->m_bLines = tree.GetCheck(m_hLine);
	m_pDoc->m_bShtrix = tree.GetCheck(m_hShtrix);
	m_pDoc->m_bSinus = tree.GetCheck(m_hSinus);

	m_pDoc->pView->Invalidate();

}


void CMyTreeView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	ClientToScreen(&point);

	CCmdUI state;

	CMenu* pMenu = AfxGetMainWnd()->GetMenu()->GetSubMenu(3);

	state.m_pMenu = pMenu;
	state.m_nIndexMax = pMenu->GetMenuItemCount();
	for (UINT i = 0; i < state.m_nIndexMax; i++)
	{
		state.m_nIndex = i;
		state.m_nID = pMenu->GetMenuItemID(i);
		state.DoUpdate(this, FALSE);
	}

	pMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

	CView::OnRButtonDown(nFlags, point);

	CTreeView::OnRButtonDown(nFlags, point);
}


void CMyTreeView::OnObjectColor()
{
	// TODO: добавьте свой код обработчика команд
	m_pDoc->pView->OnObjectColor();
}
