
// SDIAppView.cpp: реализация класса CSDIAppView
//

#include "pch.h"
#include "framework.h"
#include "cmath"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SDIApp.h"
#endif
#include <vector>
#include <iostream>
#include "SDIAppDoc.h"
#include "SDIAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
constexpr double M_PI = 3.14159265358979323846;
#endif



// CSDIAppView

IMPLEMENT_DYNCREATE(CSDIAppView, CView)

BEGIN_MESSAGE_MAP(CSDIAppView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_MOUSEHWHEEL()
ON_WM_MOUSEWHEEL()
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_WM_RBUTTONDOWN()
ON_COMMAND(ID_OBJECT_Color, &CSDIAppView::OnObjectColor)
END_MESSAGE_MAP()

// Создание или уничтожение CSDIAppView

CSDIAppView::CSDIAppView() noexcept
{
	// TODO: добавьте код создания

}

CSDIAppView::~CSDIAppView()
{
}

BOOL CSDIAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CSDIAppView

void CSDIAppView::OnDraw(CDC* pDC)
{
	CSDIAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	std::vector<CPoint> pointVector = {};

	CRect rect;
	GetClientRect(&rect);






	CBrush brush(HS_BDIAGONAL, m_Color1); // Чёрная кисть
	CBrush* pOldBrush = pDC->SelectObject(&brush);



	double scaleX = pDoc->m_scaleX; 
	double scaleY = pDoc->m_scaleY; 
	int yOffset = rect.Height() / 2;
	pDC->MoveTo(0, yOffset);
	for (int i = 0; i < rect.Width(); i++)
	{
		int step = 5; // Интервал между вертикальными линиями
		double x = i / scaleX;
		double y = sin(x) * scaleY * 0.5;
		int screenX = i;
		int screenY = yOffset - static_cast<int>(y * yOffset);
		
		//Отрисовка синуса 
		CPen pen2;
		pen2.CreatePen(PS_SOLID, 2, m_Color2);
		CPen* oldPen2 = pDC->SelectObject(&pen2);

		if (pDoc->m_bSinus)
			pDC->LineTo(screenX, screenY); // Рисуем линию к следующей точке

		pDC->SelectObject(oldPen2);

		//отрисовка штриховки
		if (pDoc->m_bShtrix)
		{
			CPen pen;
			pen.CreatePen(PS_SOLID, 2, m_Color1);
			CPen* oldPen1 = pDC->SelectObject(&pen);
			// Рисуем вертикальную штриховку
			if (i % step == 0 && screenY > yOffset)
			{
				pDC->MoveTo(screenX, yOffset);// Начало вертикальной линии
				pDC->LineTo(screenX, screenY);
			}

			else if (screenY < yOffset)
			{
				pointVector.emplace_back(screenX, screenY);
			}
			pDC->SelectObject(oldPen1);
		}
	}
	

	
	pointVector.push_back(CPoint(rect.Width(), rect.Height() / 2));
	pDC->SelectObject(pOldBrush);
	CRgn rg;
	rg.CreatePolygonRgn(pointVector.data(), pointVector.size(), ALTERNATE);
	pDC->FillRgn(&rg, &brush);
	pointVector.clear();
	
	//Отрисовка координатной прямой
	if (pDoc->m_bLines)
	{
		CPen pen3;
		pen3.CreatePen(PS_SOLID, 2, m_Color3);
		CPen* oldPen3 = pDC->SelectObject(&pen3);
		pDC->MoveTo(0, yOffset);
		pDC->LineTo(rect.Width(), yOffset);
		pDC->SelectObject(oldPen3);
	}
}

// Печать CSDIAppView

BOOL CSDIAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CSDIAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CSDIAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CSDIAppView
#ifdef _DEBUG
void CSDIAppView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIAppDoc* CSDIAppView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIAppDoc)));
	return (CSDIAppDoc*)m_pDocument;
}
#endif //_DEBUG


void CSDIAppView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CSDIAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (nChar == VK_CONTROL)
	{
		pDoc->m_bCtrlPressed = FALSE;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSDIAppView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	CSDIAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (nChar == VK_CONTROL)
	{
		pDoc->m_bCtrlPressed = TRUE;
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}



BOOL CSDIAppView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CSDIAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->m_bCtrlPressed)
	{
		// Если левая кнопка мыши нажата, измените m_myValue1
		if (zDelta > 0)
		{
			// Прокрутка вперед
			pDoc->m_scaleX += 1; // Измените первую переменную
		}
		if (zDelta < 0)
		{
			// Прокрутка назад
			pDoc->m_scaleX -= 1; // Измените первую переменную
		}
	}
	if(pDoc->m_bCtrlPressed == FALSE)
	{
		// Если левая кнопка мыши не нажата, измените m_myValue2
		if (zDelta > 0)
		{
			// Прокрутка вперед
			pDoc->m_scaleY += 0.05; // Измените вторую переменную
		}
		if (zDelta < 0)
		{
			// Прокрутка назад
			pDoc->m_scaleY -= 0.05; // Измените вторую переменную
		}
	}

	//Ограничение величины синусоиды границами экрана
	if (pDoc->m_scaleY > 2)
	{
		pDoc->m_scaleY = 2;
	}
	 
	if (pDoc->m_scaleY < 0)
	{
		pDoc->m_scaleY = 0;
	}

	Invalidate();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}




void CSDIAppView::OnRButtonDown(UINT nFlags, CPoint point)
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
}


void CSDIAppView::OnObjectColor()
{
	// TODO: добавьте свой код обработчика команд
	if(!m_ColorDlg)
		m_ColorDlg.Create(IDD_DIALOG2, this);

	m_ColorDlg.pView = this;

	m_ColorDlg.ShowWindow(SW_SHOW);
}
