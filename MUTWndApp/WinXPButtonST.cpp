#include "stdafx.h"
#include "WinXPButtonST.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CWinXPButtonST::CWinXPButtonST()
{
	// No rounded borders
	m_bIsRounded = FALSE;
}

CWinXPButtonST::~CWinXPButtonST()
{
}

// This function is called every time the button border needs to be painted.
// If the button is in standard (not flat) mode this function will NOT be called.
// This is a virtual function that can be rewritten in CButtonST-derived classes
// to produce a whole range of buttons not available by default.
//
// Parameters:
//		[IN]	pDC
//				Pointer to a CDC object that indicates the device context.
//		[IN]	pRect
//				Pointer to a CRect object that indicates the bounds of the
//				area to be painted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CWinXPButtonST::OnDrawBorder(CDC* pDC, LPCRECT pRect)
{

	// Create and select a solid brush for button background
// 	CBrush brushBK(RGB(0,0,0));//m_crColors[BTNST_COLOR_BK_IN]
// 	CBrush* pOldBrush = pDC->SelectObject(&brushBK);
// 
// 	// Create and select a thick black pen for button border
// 	CPen penBorder;
// 	penBorder.CreatePen(PS_SOLID, 1, RGB(240, 240, 240));
// 	CPen* pOldPen = pDC->SelectObject(&penBorder);
// 
// 	if (m_bIsRounded)
// 		pDC->RoundRect(pRect, CPoint(8, 8));
// 	else
// 		pDC->Rectangle(pRect);
// 
// 	// Put back the old objects
// 	pDC->SelectObject(pOldBrush);
// 	pDC->SelectObject(pOldPen);

	return BTNST_OK;
} // End of OnDrawBorder

// This function is called every time the button background needs to be painted.
// If the button is in transparent mode this function will NOT be called.
// This is a virtual function that can be rewritten in CButtonST-derived classes
// to produce a whole range of buttons not available by default.
//
// Parameters:
//		[IN]	pDC
//				Pointer to a CDC object that indicates the device context.
//		[IN]	pRect
//				Pointer to a CRect object that indicates the bounds of the
//				area to be painted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CWinXPButtonST::OnDrawBackground(CDC* pDC, LPCRECT pRect)
{
	CPoint  corPt;
	if(m_bIsNormal)
	{
		corPt.SetPoint(8,8);
		m_cr = RGB(240, 240, 240);
	}
	else
	{
		UINT height = pRect->bottom - pRect->top;
		corPt.SetPoint(height,height);
		m_cr = COLOR_BK_INOUT;
	}
	if (!m_bMouseOnButton && !m_bIsPressed)
	{	//return BASE_BUTTONST::OnDrawBackground(pDC, pRect);

		// Create and select a solid brush for button background
		CBrush brushBK(m_crColors[BTNST_COLOR_BK_OUT]);
		CBrush* pOldBrush = pDC->SelectObject(&brushBK);

		// Create and select a thick black pen for button border
		CPen penBorder;
		penBorder.CreatePen(PS_SOLID, 1,m_cr);
		CPen* pOldPen = pDC->SelectObject(&penBorder);
		
		if (m_bIsRounded)
			pDC->RoundRect(pRect, corPt);
		else
			pDC->Rectangle(pRect);

		// Put back the old objects
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
	}
	else
	{
		// Create and select a solid brush for button background
		CBrush brushBK(m_crColors[BTNST_COLOR_BK_IN]);
		CBrush* pOldBrush = pDC->SelectObject(&brushBK);

		// Create and select a thick black pen for button border
		CPen penBorder;
		penBorder.CreatePen(PS_SOLID, 1, m_cr);
		CPen* pOldPen = pDC->SelectObject(&penBorder);

		if (m_bIsRounded)
			pDC->RoundRect(pRect, corPt);
		else
			pDC->Rectangle(pRect);
	
		// Put back the old objects
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
	}

	return BTNST_OK;
} // End of OnDrawBackground

// This function enables or disables the rounded border for the button.
//
// Parameters:
//		[IN]	bRounded
//				If TRUE the button will have a round border.
//		[IN]	bRepaint
//				If TRUE the button will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CWinXPButtonST::SetRounded(BOOL bRounded,BOOL isNormal,BOOL bRepaint)
{
	m_bIsRounded = bRounded;
	m_bIsNormal = isNormal;
	if (bRepaint)	Invalidate();

	return BTNST_OK;
} // End of SetRounded

#undef	BASE_BUTTONST
