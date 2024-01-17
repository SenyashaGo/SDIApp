
// SDIAppDoc.cpp: реализация класса CSDIAppDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SDIApp.h"
#endif

#include"SDIAppView.h"
#include "SDIAppDoc.h"
#include "CObjectsDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include"CMyTreeView.h"

// CSDIAppDoc

IMPLEMENT_DYNCREATE(CSDIAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CSDIAppDoc, CDocument)
	ON_COMMAND(ID_OBJECT_Color, &CSDIAppDoc::OnObjectColor)
	ON_COMMAND(ID_OBJECT_Dialog, &CSDIAppDoc::OnObjectDialog)
	ON_COMMAND(ID_OBJECT_Line, &CSDIAppDoc::OnObjectLine)
	ON_COMMAND(ID_OBJECT_Menu, &CSDIAppDoc::OnObjectMenu)
	ON_COMMAND(ID_OBJECT_Shtrix, &CSDIAppDoc::OnObjectShtrix)
	ON_COMMAND(ID_OBJECT_Sinus, &CSDIAppDoc::OnObjectSinus)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_Color, &CSDIAppDoc::OnUpdateObjectColor)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_Dialog, &CSDIAppDoc::OnUpdateObjectDialog)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_Line, &CSDIAppDoc::OnUpdateObjectLine)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_Shtrix, &CSDIAppDoc::OnUpdateObjectShtrix)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_Sinus, &CSDIAppDoc::OnUpdateObjectSinus)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_Menu, &CSDIAppDoc::OnUpdateObjectMenu)
END_MESSAGE_MAP()


// Создание или уничтожение CSDIAppDoc

CSDIAppDoc::CSDIAppDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CSDIAppDoc::~CSDIAppDoc()
{
}

BOOL CSDIAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)
	
	m_bLines = m_bShtrix = m_bSinus = true;
	
	pTree->FillTree();


	return TRUE;
}




// Сериализация CSDIAppDoc

void CSDIAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CSDIAppDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
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

// Поддержка обработчиков поиска
void CSDIAppDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CSDIAppDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CSDIAppDoc

#ifdef _DEBUG
void CSDIAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDIAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CSDIAppDoc


void CSDIAppDoc::OnObjectColor()
{
	// TODO: добавьте свой код обработчика команд
}


void CSDIAppDoc::OnObjectDialog()
{
	// TODO: добавьте свой код обработчика команд
	CObjectsDlg dlg;
	 
	dlg.m_bSinus = m_bSinus;
	dlg.m_bShtrix = m_bShtrix;
	dlg.m_bLine = m_bLines;

	if (dlg.DoModal() == IDOK)
	{
		m_bSinus = dlg.m_bSinus;
		m_bShtrix = dlg.m_bShtrix;
		m_bLines = dlg.m_bLine;

		pView->Invalidate();
		pTree->FillTree();
	}	
}


void CSDIAppDoc::OnObjectLine()
{
	// TODO: добавьте свой код обработчика команд
	m_bLines = !m_bLines;
	pView->Invalidate();

	pTree->FillTree();
}


void CSDIAppDoc::OnObjectMenu()
{
	// TODO: добавьте свой код обработчика команд
}


void CSDIAppDoc::OnObjectShtrix()
{
	// TODO: добавьте свой код обработчика команд
	m_bShtrix = !m_bShtrix;
	pView->Invalidate();
	pTree->FillTree();
}


void CSDIAppDoc::OnObjectSinus()
{
	// TODO: добавьте свой код обработчика команд
	m_bSinus = !m_bSinus;
	pView->Invalidate();
	pTree->FillTree();
}


void CSDIAppDoc::OnUpdateObjectColor(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
}


void CSDIAppDoc::OnUpdateObjectDialog(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
}


void CSDIAppDoc::OnUpdateObjectLine(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	pCmdUI->SetCheck(m_bLines);
}


void CSDIAppDoc::OnUpdateObjectShtrix(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	pCmdUI->SetCheck(m_bShtrix);
}


void CSDIAppDoc::OnUpdateObjectSinus(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	pCmdUI->SetCheck(m_bSinus);
}


void CSDIAppDoc::OnUpdateObjectMenu(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
}
