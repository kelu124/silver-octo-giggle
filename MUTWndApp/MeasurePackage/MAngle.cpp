// MAngle.cpp: implementation of the CMDistance class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MAngle.h"
#define  PI  3.14159f
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "math.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMAngle::CMAngle(const CComputeMethod &computer):CMeasureObject(computer)
{
	m_nStep = 0;
}

CMAngle::~CMAngle()
{
	
}

CMeasureObject *CMAngle::Clone()
{
	CMAngle *pAngle = new CMAngle(m_computer);
	pAngle->m_nStep = this->m_nStep;
	pAngle->m_pointStart = this->m_pointStart;
	pAngle->m_pointEnd = this->m_pointEnd;
	pAngle->m_pointLast = this->m_pointLast;
	pAngle->m_pointMiddle = this->m_pointMiddle;
	pAngle->m_angle = this->m_angle;
	return pAngle;
}

void CMAngle::GetLineAndPointRatio(CPoint m_pointBtwStartToMid,CPoint &c_p, 
								   CPoint m_pointMiddle,float fDisStarToMid,
								   float fDisBtwLine,int ddx_MidToStart,
								   int ddy_MidToStart,CPoint m_pointVec)
{

	if ( ddy_MidToStart!=0 && ddx_MidToStart!=0 )
	{
		m_pointBtwStartToMid.x = (int)(fDisBtwLine * (m_pointMiddle.x - m_pointStart.x) / fDisStarToMid  +m_pointMiddle.x) ;
		m_pointBtwStartToMid.y = (int)(fDisBtwLine * (m_pointMiddle.y - m_pointStart.y) / fDisStarToMid  +m_pointMiddle.y) ;
		//四种结果
		if ( ddx_MidToStart>0 && ddy_MidToStart>0 )			//直线从左向右画且向上倾斜
		{
			m_pointVec.x = m_pointMiddle.x + m_pointBtwStartToMid.y - m_pointMiddle.y;
			m_pointVec.y = m_pointMiddle.y - m_pointBtwStartToMid.x + m_pointMiddle.x;
		} 
		else if(ddx_MidToStart>0 && ddy_MidToStart<0)			//直线从左向右画且向下倾斜
		{
			m_pointVec.x = m_pointMiddle.x - m_pointBtwStartToMid.y + m_pointMiddle.y;
			m_pointVec.y = m_pointMiddle.y + m_pointBtwStartToMid.x - m_pointMiddle.x;
		}
		else if(ddx_MidToStart<0 && ddy_MidToStart>0)			//直线从右向左画且向上倾斜
		{
			m_pointVec.x = m_pointMiddle.x - m_pointBtwStartToMid.y + m_pointMiddle.y;
			m_pointVec.y = m_pointMiddle.y + m_pointBtwStartToMid.x - m_pointMiddle.x;
		}
		else if(ddx_MidToStart<0 && ddy_MidToStart<0)			//直线从右向左画且向下倾斜
		{
			m_pointVec.x = m_pointMiddle.x + m_pointBtwStartToMid.y - m_pointMiddle.y;
			m_pointVec.y = m_pointMiddle.y - m_pointBtwStartToMid.x + m_pointMiddle.x;
		}
		c_p.x = m_pointVec.x;
		c_p.y = m_pointVec.y;
	}
}

void CMAngle::GetDrawCircle(int ddx_MidToStart,int ddy_MidToStart,
							int ddx_MidToEnd,int ddy_MidToEnd,
							float cos_an,int &draw_flag)
{
	/************************************************************************/
	/* 确定应该是顺时针画弧还是逆时针画弧									*/
	/*cos_an垂线上的点与鼠标确定的第二点和最后一点构成的角的余弦值          */
	/************************************************************************/
	if ( ddx_MidToStart>0 && ddy_MidToStart>0)
	{
		draw_flag  =2;
		if ( cos_an<0 )			//角度90~180度
		{
			draw_flag = 1;
		} 
		else if(cos_an>0)		//角度0~90度
		{
			draw_flag = 2;
		}
	} 
	else if ( ddx_MidToStart>0 && ddy_MidToStart<0)
	{
		draw_flag  =2;	
		if ( cos_an<0 )		//角度90~180度
		{
			draw_flag = 2;
		} 
		else if(cos_an>0)	//角度0~90度
		{
			draw_flag = 1;
		}
	}
	else if( ddx_MidToStart<0 && ddy_MidToStart>0 )
	{
		draw_flag = 1;
		if ( cos_an<0 )		//下面同理
		{
			draw_flag = 2;
		} 
		else if(cos_an>1)
		{
			draw_flag = 1;
		}
	}
	else if( ddx_MidToStart<0 && ddy_MidToStart<0 )
	{
		draw_flag = 2;
		if ( cos_an<0 )
		{
			draw_flag = 1;
		} 
		else if(cos_an>1)
		{
			draw_flag = 2;
		}
	}
	else if( ddx_MidToStart==0 && ddy_MidToStart!=0 )
	{
		if ( ddy_MidToStart>0 )
		{
			if ( ddx_MidToEnd>0 )
			{
				draw_flag = 1;
			} 
			else
			{
				draw_flag = 2;
			}
		} 
		else
		{	
			if ( ddx_MidToEnd>0 )
			{
				draw_flag = 2;
			} 
			else
			{
				draw_flag = 1;
			}
		}
	}
	else if( ddx_MidToStart!=0 && ddy_MidToStart==0 )
	{
		if ( ddx_MidToStart>0 )
		{
			if ( ddy_MidToEnd>0 )
			{
				draw_flag = 2;
			} 
			else
			{
				draw_flag = 1;
			}
		} 
		else
		{
			if ( ddy_MidToEnd>0 )
			{
				draw_flag = 1;
			} 
			else
			{
				draw_flag = 2;
			}
		}
	}
}


void CMAngle::DrawAngle(CDC *dc,int nIndex,CPoint &m_pointStart,
						CPoint &m_pointMiddle,CPoint &m_pointEnd,
						float fDisBtwLine,float &m_angle)
{
	if ( m_nStep<1 ) return;
	//DrawNumber(dc,nIndex,CPoint(m_pointStart.x,m_pointStart.y));
	//计算该画的点数
	CPen pen(PS_SOLID, 1, m_TextColor);
	CPen *oldpen = dc->SelectObject(&pen);
	DrawCrossFlag(dc, m_pointStart.x, m_pointStart.y);
	DrawCrossFlag(dc, m_pointMiddle.x, m_pointMiddle.y);
	DrawCrossFlag(dc, m_pointEnd.x, m_pointEnd.y);

	dc->MoveTo(m_pointStart);
	dc->LineTo(m_pointMiddle);
// 	if ( m_nStep>=2 )
// 	{
// 		//DrawCrossFlag(dc, m_pointMiddle.x, m_pointMiddle.y);
// 		m_pointLast.x = 2 * m_pointMiddle.x - m_pointStart.x;
// 		m_pointLast.y = 2 * m_pointMiddle.y - m_pointStart.y;
// 		dc->MoveTo(m_pointMiddle);
// 		dc->LineTo(m_pointLast);
// 	}
	dc->MoveTo(m_pointStart);
	dc->LineTo(m_pointEnd);
	//起点和中点的直线长
//	float fDisStarToMid = m_computer.GetDistanceInPixes(m_pointStart,m_pointMiddle);
	//画圈圈
// 	//有了三点坐标，求角度用余弦定理
	float cos_angle = m_computer.Get1Angle(m_pointMiddle,m_pointStart,m_pointEnd);		//点击第1个点为中间点
	m_angle =  (acos(cos_angle) * 180) / PI;			//返回角度
// 
// 	int ddx_MidToStart,ddy_MidToStart;			//中点和起点的x,y差值
// 	int ddx_MidToEnd,ddy_MidToEnd;			//中点和尾点的x,y差值
// 	int draw_flag=0;			//规定如何画圆(顺时针还是逆时针)
// 	ddx_MidToStart = m_pointMiddle.x - m_pointStart.x;
// 	ddy_MidToStart = m_pointMiddle.y - m_pointStart.y;
// 	ddx_MidToEnd = m_pointMiddle.x - m_pointEnd.x;
// 	ddy_MidToEnd = m_pointMiddle.y - m_pointEnd.y;
// 	// 角度范围只在1，2象限内，求第一条直线的垂线上的一点
// 	CPoint m_pointBtwStartToMid;	//从中点向起点的直线截距为fDisStarToMid的点坐标
// 	m_pointBtwStartToMid.x = 0;
// 	m_pointBtwStartToMid.y = 0;
// 	CPoint m_pointVec;			//垂线上的一点
// 	m_pointVec.x = 0;
// 	m_pointVec.y = 0;
// 	CPoint c_p;			//垂线上的点
// 	//先得到第一条直线的另外一点和变化率		第一条直线x的变化率是垂直直线y的变化率，y->x
// 	GetLineAndPointRatio(m_pointBtwStartToMid, c_p, m_pointMiddle, fDisStarToMid ,
// 						 fDisBtwLine, ddx_MidToStart, ddy_MidToStart, m_pointVec);
// 
// 	float cos_an = 0.0;
// 	if ( c_p.x != 0 && c_p.y!=0 )
// 	{
// 		cos_an = m_computer.Get1Angle(c_p, m_pointMiddle, m_pointEnd);		//得到余弦值
// 	}
	//如果第一条直线的垂线上的点与m_pointMiddle,m_pointEnd这3个点组成的三角形且由m_pointMiddle
	//为定点的角大于90度，说明圆弧已经超过了180度，应该反向画圆弧
// 	if ( m_nStep>2 )			//规定是从起点开始画圆弧还是从尾点开始画圆弧
// 	{
// 		DrawCrossFlag(dc, m_pointEnd.x, m_pointEnd.y);
// 		//GetDrawCircle(ddx_MidToStart, ddy_MidToStart, ddx_MidToEnd, ddy_MidToEnd, cos_an, draw_flag);
// 	}

// 	switch( draw_flag )
// 	{
// 	case 1:
// 		dc->Arc(m_pointMiddle.x-(int)fDisBtwLine,	m_pointMiddle.y-(int)fDisBtwLine,
// 				m_pointMiddle.x+(int)fDisBtwLine,	m_pointMiddle.y+(int)fDisBtwLine,
// 				m_pointStart.x,						m_pointStart.y,
// 				m_pointEnd.x,						m_pointEnd.y);	
// 		break;
// 	case 2:
// 		dc->Arc(m_pointMiddle.x-(int)fDisBtwLine,	m_pointMiddle.y-(int)fDisBtwLine,
// 				m_pointMiddle.x+(int)fDisBtwLine,	m_pointMiddle.y+(int)fDisBtwLine,
// 				m_pointEnd.x,						m_pointEnd.y,
// 				m_pointStart.x,						m_pointStart.y);	
// 		break;
// 	}
}

void CMAngle::DrawObject(CDC *dc, int nIndex)
{
	DrawAngle(dc,nIndex,m_pointStart,m_pointMiddle,m_pointEnd,25.0,m_angle);
}


BOOL CMAngle::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_nStep == 0)//点第一下,确定开始点
	{
		m_pointStart = point;
		m_pointMiddle = point;
		m_pointEnd = point;
		m_nStep=1;	
		return TRUE;
	}
	else if(m_nStep==1)//点第二下,确定结束点
	{
		//计算两点间距离				
		m_pointMiddle = point;
		m_pointEnd = point;
		m_nStep = 2;
		return TRUE;
	}
	else if (m_nStep==2)
	{
		//第三点
		m_pointEnd = point;
		m_nStep = 3;
		return TRUE;
	}
	return FALSE;

}

BOOL CMAngle::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep ==1)
	{
		//m_pointMiddle = point;		
		return TRUE;
	}
	if (m_nStep==2)
	{
		//m_pointEnd = point;
		return TRUE;
	}
	return FALSE;
}
bool CMAngle::HasEnded()
{	
	return m_nStep==3;
}
void CMAngle::DrawResult(CDC *dc)
{
	CString strResult;
	dc->SetTextColor(m_TextColor);
	strResult.Format(_T("%8.2f°"),m_angle);
	DrawResultText(dc,strResult,CPoint(m_pointStart.x,m_pointStart.y));
}
void CMAngle::DrawResult(CDC *dc,int &x,int &y)
{
	CString strResult;
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	float disInpixel = m_computer.GetDistanceInPixes(m_pointEnd, m_pointStart);
	if(disInpixel < 5)
		strResult.Format(_T("∠α: --------"));
	else
		strResult.Format(_T("∠α: %8.2f°"),m_angle);	
	dc->TextOut(x,y,strResult);
	y+=szLine.cy;
}

void CMAngle::Restart()
{
	m_pointStart.SetPoint(0,0);
	m_pointMiddle.SetPoint(0,0);
	m_pointEnd.SetPoint(0,0);
	m_pointLast.SetPoint(0,0);
	m_nStep = 0;
	m_angle = 0.0;
}


