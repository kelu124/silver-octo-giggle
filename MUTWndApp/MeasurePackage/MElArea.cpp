// MAxArea.cpp: implementation of the CMElArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MElArea.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMElArea::CMElArea(const CComputeMethod &computer):CMeasureObject(computer)
{
	m_nStep = 0;
	m_pointFirst.SetPoint(0,0);
	m_pointSecond.SetPoint(0,0);
	m_pointThird.SetPoint(0,0);
	m_nAInPix = 0;
	m_nBInPix = 0;
	cr = 0x00ffff;
	dr = 0x005555;	
}
CMElArea::CMElArea(const CComputeMethod &computer,UINT index=0)
:CMeasureObject(computer)
,m_uIndex(index)
{
	m_nStep = 0;
	m_pointFirst.SetPoint(0,0);
	m_pointSecond.SetPoint(0,0);
	m_pointThird.SetPoint(0,0);
	m_nAInPix = 0;
	m_nBInPix = 0;
	cr = 0x00ffff;
	dr = 0x005555;	
}
CMElArea::~CMElArea()
{
	//释放资源
}
void CMElArea::BackUpObj(CMElArea &rt)
{
	rt.m_nStep = this->m_nStep;
	rt.m_pointFirst = this->m_pointFirst;
	rt.m_pointSecond = this->m_pointSecond;
	rt.m_nAInPix = this->m_nAInPix;
	rt.m_nBInPix = this->m_nBInPix;
}
float CMElArea::ReturnGetEllipseAreaFromPixel()
{
	return m_computer.GetEllipseAreaFromPixel(m_nAInPix, m_nBInPix);
}

float CMElArea::ReturnGetEllipsePerimeterFromPixel()
{
	return m_computer.GetEllipsePerimeterFromPixel(m_nAInPix, m_nBInPix);
}
void CMElArea::DrawResult(CDC *dc)
{
	CString strResult;
	dc->SetTextColor(m_TextColor);
	if(0 == m_uIndex)
	strResult.Format(_T("%8.2f cm^2"),m_computer.GetEllipseAreaFromPixel(m_nAInPix, m_nBInPix));
	else
	strResult.Format(_T("%8.2f cm"),m_computer.GetEllipsePerimeterFromPixel(m_nAInPix, m_nBInPix));

	DrawResultText(dc,strResult,CPoint(m_pointFirst.x,m_pointFirst.y));
}
void CMElArea::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	CString strP;
	CString strA;

	strA.Format(_T("A:   %8.2f cm^2"), m_computer.GetEllipseAreaFromPixel(m_nAInPix, m_nBInPix));
	strP.Format(_T("P:   %8.2f cm"),  m_computer.GetEllipsePerimeterFromPixel(m_nAInPix, m_nBInPix));
	dc->SetBkMode(TRANSPARENT);
	dc->TextOut(x,y,strA);
	y += szLine.cy;
	dc->TextOut(x,y,strP);
	y += szLine.cy;

}
void CMElArea::CountBInPix(const double beta,const CPoint& pointCenter)
{
	int x1 =  m_pointThird.x-pointCenter.x;
	int y1 =  m_pointThird.y-pointCenter.y;
	int y   = (int)(x1*sin(beta) - y1*cos(beta));   
	int x   = (int)(x1*cos(beta) + y1*sin(beta));
	float a2y2 = m_nAInPix*m_nAInPix*y*y;
	float a2x2 = m_nAInPix*m_nAInPix - x*x;
	m_nBInPix = sqrt(fabs(a2y2/a2x2));

}
void CMElArea::DrawObject(CDC *dc, int nIndex)
{
	//DrawNumber(dc, nIndex, m_pointFirst);	
	if(m_nStep < 1) return;
	dc->SetBkMode(TRANSPARENT);
	//dc->SetTextColor(m_TextColor);
	CPen pen(PS_SOLID,1,m_TextColor);
	CPen *old = dc->SelectObject(&pen);
	DrawCrossFlag(dc, m_pointFirst.x, m_pointFirst.y);
	DrawCrossFlag(dc, m_pointSecond.x, m_pointSecond.y);
// 	CPoint temp = m_pointFirst - m_pointSecond;
// 	if(temp.x < 0)           //之前
// 	{
// 		if(m_pointThird.x >= m_pointSecond.x 
// 			|| m_pointThird.x <= m_pointFirst.x)
// 			return;
// 	}
// 	else if(temp.x > 0)		//之后
// 	{
// 		if(m_pointThird.x >= m_pointFirst.x 
// 			|| m_pointThird.x <= m_pointSecond.x)
// 			return;
// 	}
// 	else
// 	{
// 		return;
// 	}
// 	m_nStep = 3;
	//dc->SelectObject(old);
	pen.DeleteObject();

	if(m_nStep < 3) return;
	DrawCrossFlag(dc, m_pointThird.x, m_pointThird.y);
	cr = m_TextColor;
	//椭圆旋转角度+
	double beta = atan(double(m_pointFirst.y-m_pointSecond.y)/(m_pointFirst.x-m_pointSecond.x));
	CPoint pointCenter;//求中点
	pointCenter.x = (m_pointFirst.x+m_pointSecond.x)/2;
	pointCenter.y = (m_pointFirst.y+m_pointSecond.y)/2;

	CountBInPix(beta,pointCenter);

	float nA = m_nAInPix;
	float nB = m_nBInPix;
	//画椭圆
	for(int Angle=0; Angle<=90; Angle+=10)
	{		
		double x = 0.5+nA*cos(Angle/180.0*3.1416);
		double y = 0.5+nB*sin(Angle/180.0*3.1416);
		//画对称点
		CirPot(dc,  x,  y, beta, pointCenter);
		CirPot(dc, -x, -y, beta, pointCenter);
		CirPot(dc,  x, -y, beta, pointCenter);
		CirPot(dc, -x,  y, beta, pointCenter);		
	}
		
}
 void CMElArea::CirPot(CDC *dc, const double x1, const double y1, const double beta, const CPoint& pointCenter)
{	
	 int y   = (int)(x1*sin(beta) - y1*cos(beta));   
	 int x   = (int)(x1*cos(beta) + y1*sin(beta));
	
	 //绘制点, 4*4矩阵描点
	dc->SetPixel(pointCenter.x+x,   pointCenter.y+y,   cr);
	dc->SetPixel(pointCenter.x+x+1, pointCenter.y+y+1, cr);
	dc->SetPixel(pointCenter.x+x+1, pointCenter.y+y,   cr);
	dc->SetPixel(pointCenter.x+x  , pointCenter.y+y+1, cr);
	
/*	dc->SetPixel(pointCenter.x+x-1, pointCenter.y+y  , dr);
	dc->SetPixel(pointCenter.x+x-1, pointCenter.y+y+1, dr);
	dc->SetPixel(pointCenter.x+x  , pointCenter.y+y-1, dr);
	dc->SetPixel(pointCenter.x+x+1, pointCenter.y+y-1, dr);
	dc->SetPixel(pointCenter.x+x+2, pointCenter.y+y  , dr);
	dc->SetPixel(pointCenter.x+x+2, pointCenter.y+y+1, dr);
	dc->SetPixel(pointCenter.x+x  , pointCenter.y+y+2, dr);
	dc->SetPixel(pointCenter.x+x+1, pointCenter.y+y+2, dr);
	*/

}
BOOL CMElArea::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep==1)//鼠标移动改变短轴
	{
		//m_pointSecond = point; 
		//CPoint temp = m_pointFirst-m_pointSecond;
		//m_nAInPix = m_computer.GetDistanceInPixes(m_pointSecond, m_pointFirst)/2;//半短轴长
		//m_nBInPix = m_nAInPix;		 
		//return TRUE;
	}
	else if(m_nStep==2)//鼠标移动改变椭圆长轴
	{			
// 		CPoint temp=m_pointFirst-m_pointSecond;
// 		double lc = sqrt( float(temp.x*temp.x + temp.y*temp.y)); 
// 		temp = point-m_pointFirst;
// 		double la = sqrt(float(temp.x*temp.x + temp.y*temp.y));
// 		temp = point - m_pointSecond;
// 		double lb = sqrt(float(temp.x*temp.x + temp.y*temp.y));
// 		double p = (la+lb+lc)/2;
// 		double h = sqrt(p*(p-la)*(p-lb)*(p-lc))*2/lc;//求高
// 		m_nBInPix = (float) h;//半长轴长		
		return TRUE;
	}
	return FALSE;
}
BOOL CMElArea::OnLButtonDown(UINT nFlags, CPoint point)
{
	switch(m_nStep)
	{
	case 0://测量开始,初始化
		{
			m_pointFirst = point;
			//m_pointSecond = point;
			m_nStep = 1;
			return TRUE;
			break;
		}
	case 1://改变第二个点,确定短轴
		{
			m_pointSecond = point;	
			//m_pointThird = point;
			m_nAInPix = m_computer.GetDistanceInPixes(point,m_pointFirst)/2;//半短轴长	
			//计算周长			
			m_nStep = 2;
			//ShowCursor(false);
			return TRUE;
			break;
		}
	case 2://结束
		{	
			//计算周长	
			ShowCursor(true);
			m_pointThird = point;
			
			m_nStep = 3;
			return TRUE;
			break;			
		}		
	}
	return FALSE;
}
bool CMElArea::HasEnded()
{
	return m_nStep>2;
	
}
CMeasureObject *CMElArea::Clone()
{
	CMElArea *pElArea = new CMElArea(m_computer,m_uIndex);
	pElArea->m_nStep = this->m_nStep;
	pElArea->m_pointFirst=this->m_pointFirst;
	pElArea->m_pointSecond=this->m_pointSecond;
	pElArea->m_pointThird=this->m_pointThird;
	pElArea->m_nAInPix = this->m_nAInPix;
	pElArea->m_nBInPix = this->m_nBInPix;
	pElArea->m_uIndex = this->m_uIndex;
	

	return pElArea;
}

int CMElArea::GetResultCount()
{
	return 2;
}

bool CMElArea::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back(m_computer.GetEllipsePerimeterFromPixel(m_nAInPix, m_nBInPix));
	return true;
}

bool CMElArea::SetResultValue(vector<CString> strResult)
{
	if( strResult.empty() )return false;
	if ( !m_result.empty() )m_result.clear();
	for (int i=0; i<strResult.size(); i++)
	{
		m_result.push_back(strResult.at(i));
	}
	return true;
}

bool CMElArea::GetResultValue(vector<CString> &strResult)const
{
	if( !strResult.empty() )strResult.clear();
	if ( m_result.empty() )return false;
	for (int i=0; i<m_result.size(); i++)
	{
		strResult.push_back(m_result.at(i));
	}
	return true;
}

void CMElArea::Restart()
{
	m_pointFirst.SetPoint(0,0);
	m_pointSecond.SetPoint(0,0);
	m_pointThird.SetPoint(0,0);
	//m_uIndex = 0;
	m_nStep = 0;
	m_nAInPix = 0;
	m_nBInPix = 0;
}