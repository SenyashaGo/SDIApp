
// SDIAppDoc.h: интерфейс класса CSDIAppDoc 
//


#pragma once
class CMyTreeView;
class CSDIAppView;
class CRect;

class CSDIAppDoc : public CDocument
{
protected: // создать только из сериализации
	CSDIAppDoc() noexcept;
	DECLARE_DYNCREATE(CSDIAppDoc)

// Атрибуты
public:
	double m_scaleX = 123;
	double m_scaleY = 2;

	BOOL m_bCtrlPressed;

	bool m_bLines, m_bShtrix, m_bSinus;
	
	CSDIAppView* pView;
	CMyTreeView* pTree;
	
// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CSDIAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnObjectColor();
	afx_msg void OnObjectDialog();
	afx_msg void OnObjectLine();
	afx_msg void OnObjectMenu();
	afx_msg void OnObjectShtrix();
	afx_msg void OnObjectSinus();
	afx_msg void OnUpdateObjectColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjectDialog(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjectLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjectShtrix(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjectSinus(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjectMenu(CCmdUI* pCmdUI);
};
