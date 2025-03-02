//
//	Class:		CListBoxST
//
//	Compiler:	Visual C++
//	Tested on:	Visual C++ 6.0
//
//	Version:	See GetVersionC() or GetVersionI()
//
//	Created:	13/March/2002
//	Updated:	13/March/2002
//
//	Author:		Davide Calabro'		davide_calabro@yahoo.com
//									http://www.softechsoftware.it
//
//	Disclaimer
//	----------
//	THIS SOFTWARE AND THE ACCOMPANYING FILES ARE DISTRIBUTED "AS IS" AND WITHOUT
//	ANY WARRANTIES WHETHER EXPRESSED OR IMPLIED. NO REPONSIBILITIES FOR POSSIBLE
//	DAMAGES OR EVEN FUNCTIONALITY CAN BE TAKEN. THE USER MUST ASSUME THE ENTIRE
//	RISK OF USING THIS SOFTWARE.
//
//	Terms of use
//	------------
//	THIS SOFTWARE IS FREE FOR PERSONAL USE OR FREEWARE APPLICATIONS.
//	IF YOU USE THIS SOFTWARE IN COMMERCIAL OR SHAREWARE APPLICATIONS YOU
//	ARE GENTLY ASKED TO DONATE 1$ (ONE U.S. DOLLAR) TO THE AUTHOR:
//
//		Davide Calabro'
//		P.O. Box 65
//		21019 Somma Lombardo (VA)
//		Italy
//
#ifndef _LISTBOXST_
#define _LISTBOXST_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CListBoxST : public CListBox
{
public:
	CListBoxST();
	virtual	~CListBoxST();

    enum	{	ST_FULLROWSELECT	= 0,	// Hilight full list box item (Default)
				ST_FULLTEXTSELECT,			// Hilight half list box item (Part containing text)
				ST_TEXTSELECT				// Hilight only list box text
			};

	int AddString(LPCTSTR lpszItem, int nImage = -1L);
	int InsertString(int nIndex, LPCTSTR lpszString, int nImage = -1L);
	int DeleteString(int nIndex);
	int ReplaceString(int nIndex, LPCTSTR lpszString, int nImage = -1L);
	void ResetContent();

	int SetItemData(int nIndex, DWORD dwItemData);
	DWORD GetItemData(int nIndex);
	int SetItemDataPtr(int nIndex, void* pData);
	void* GetItemDataPtr(int nIndex);

	void EnableItem(int nIndex, BOOL bEnable = TRUE, BOOL bRepaint = TRUE);
	BOOL IsItemEnabled(int nIndex);

	void SetRowSelect(BYTE byRowSelect = ST_FULLROWSELECT, BOOL bRepaint = TRUE);
	void SetImageList(CImageList* pImageList);
	void SetImage(int nIndex, int nImage, BOOL bRepaint = TRUE);
	void GetImage(int nIndex, LPINT lpnImage);

	int MoveUp(int nIndex, BOOL bSetCurSel = TRUE);
	int MoveDown(int nIndex, BOOL bSetCurSel = TRUE);
	int MoveTop(int nIndex, BOOL bSetCurSel = TRUE);
	int MoveBottom(int nIndex, BOOL bSetCurSel = TRUE);

	static short GetVersionI()		{return 10;}
	static LPCTSTR GetVersionC()	{return (LPCTSTR)_T("1.0");}

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxST)
	//}}AFX_VIRTUAL
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

protected:
	virtual DWORD OnDrawTextBackground(int nIndex, CDC* pDC, CRect* prcItem, CRect* prcText, BOOL bIsDisabled, BOOL bIsSelected, COLORREF crSuggestedColor);
	//{{AFX_MSG(CListBoxST)
	afx_msg void OnDestroy();
	afx_msg BOOL OnReflectedDblclk();
	//afx_msg BOOL OnReflectedSelchange();
	//}}AFX_MSG

	virtual DWORD OnDrawIconBackground(int nIndex, CDC* pDC, CRect* prcItem, CRect* prcIcon, BOOL bIsDisabled, BOOL bIsSelected, COLORREF crSuggestedColor);
	virtual DWORD OnDrawIcon(int nIndex, CDC* pDC, CRect* prcItem, CRect* prcIcon, int nImage, BOOL bIsDisabled, BOOL bIsSelected);

	CFont		newFont1;			//add 8.2
	BYTE		m_byRowSelect;
	CImageList*	m_pImageList;
	SIZE		m_szImage;		// Size of each image in image list
	BOOL		m_bIsCheckBtnOk;
	BOOL		m_bIsDcmListUpdate;

private:
	
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	int Move(int nOldIndex, int nNewIndex, BOOL bSetCurSel);
	void FreeResources();
	int ReplaceItemData(int nIndex, DWORD dwItemData, LPVOID pData, int nImage, DWORD dwFlags, BYTE byMask);
	void DeleteItemData(int nIndex);

#pragma pack(1)
	typedef struct _STRUCT_LBDATA
	{
		DWORD		dwItemData;	// 32-bit value associated with an item in the list box
		LPVOID		pData;		// Pointer associated with an item in the list box
		int			nImage;		// Image associated with an item in the list box. -1 if no image.
		UINT		nFormat;	// Text alignment
		DWORD		dwFlags;	// Bit 0	- Item is disabled

		_STRUCT_LBDATA::_STRUCT_LBDATA()
		{::ZeroMemory(this, sizeof(_STRUCT_LBDATA));}
	} STRUCT_LBDATA;
#pragma pack()

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchange();
	//add 8.4
	bool ReplaceItemIcon(int nIndex,int nImage);
	void SetCheckBtnOk(BOOL bOk=TRUE){m_bIsCheckBtnOk = bOk;Invalidate();};
	//BOOL GetListState(){return m_bIsDcmListUpdate;};
	BOOL	IsDcmlistUpdate(){return m_bIsDcmListUpdate;};
	void	SetDcmlistUpdate(BOOL bUpdate=TRUE){m_bIsDcmListUpdate=bUpdate;};
	//BOOL	ChangeItemIcon(int nIndex,int nImage);
	afx_msg void OnLbnDblclk();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
