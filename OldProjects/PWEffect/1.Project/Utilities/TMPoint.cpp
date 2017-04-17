#include "stdafx.h"
#include <math.h>
#include "tmpoint.h"
#include <algorithm>
#include "DebugMacros.h"
/*
    操作符重载 建 议  

    1. 所有一元操作符重载为成员函数
    2. = () [] ->  必须为成员函数
    3. += -= /= *= ^= &= != %= >>= <<=  成员 
    4. 其它二元操作符  非成员函数（友元） 
*/

//////////////////////////////////////////////////////////////////////////

//Convenience inline method to compare floating point values based on a tolerance.
#define FLOAT_TOLERANCE 0.0001
inline BOOL IsEqual(DOUBLE f1, DOUBLE f2)
{
    return (fabs(f1 - f2)<=FLOAT_TOLERANCE);
}

// Rounding function.
inline TLcType Round(DOUBLE fValue)
{
    TLcType iX = TLcType(fValue);
    if (fabs(fValue-iX)>=0.5)
    {
        (fValue-iX>0) ? iX++ : iX--;
    }
    return iX;
}

//########################################################################
// class TMpoint implementation

TMPoint::TMPoint()
{
}

TMPoint::~TMPoint()
{
}

TMPoint::TMPoint(TLcType aX,TLcType aY)
{

    iX = aX;
    iY = aY;
}


TMPoint operator+(const TMPoint& ptStart,const TVector& aVector) 
{
    TMPoint endPoint;
    endPoint.iX = ptStart.iX + aVector.m_lHx;
    endPoint.iY = ptStart.iY + aVector.m_lVy;
    return endPoint;
}

TVector operator-(TMPoint ptEnd,TMPoint ptStart)
{
    TVector vPQ;
    vPQ.m_lHx = ptEnd.iX-ptStart.iX;
    vPQ.m_lVy = ptEnd.iY-ptStart.iY;
    return vPQ;
}

TMPoint TMPoint::operator-()
{
    return TMPoint(-iX,-iY);
}

TMPoint& TMPoint::operator +=(const TVector& aVector)
{
    iX += aVector.m_lHx;
    iY += aVector.m_lVy;
    return *this;
}

TMPoint& TMPoint::operator=(const TMPoint& aOther)
{
    if (this!=&aOther)
    {
        iX = aOther.iX;
        iY = aOther.iY;
    }
    return *this;
}

BOOL TMPoint::operator ==(const TMPoint& aOther) const
{
    return (iX==aOther.iX && iY==aOther.iY);
}

BOOL TMPoint::operator !=(const TMPoint& aOther) const
{
    return !(*this==aOther);
}

DOUBLE TMPoint::Distance(const TMPoint& aOtherPoint) const
{
    TLcType ndX = aOtherPoint.iX - iX;
    TLcType ndY = aOtherPoint.iY - iY;
    DOUBLE nReturn = sqrt(DOUBLE(ndX*ndX + ndY*ndY));

    return nReturn;
}

void TMPoint::Rotate(TMPoint aAxisPt,DOUBLE aRadian,BOOL aClosewise/*=ETrue*/)
{
    if (*this==aAxisPt)
    {
        return;
    }

    if (!aClosewise)
    {
        aRadian = -aRadian;
    }

    TLcType x = iX - aAxisPt.iX;
    TLcType y = iY - aAxisPt.iY;

    DOUBLE xTemp = (x*cos(aRadian) + y*sin(aRadian)) + aAxisPt.iX;
    DOUBLE yTemp = (-x*sin(aRadian) + y*cos(aRadian)) + aAxisPt.iY;

    iX = Round(xTemp);    
    iY = Round(yTemp);

}

POINT  TMPoint::TOPOINT() const
{
    POINT pt = {iX,iY};
    return pt;
}







//////////////////////////////////////////////////////////////////////////
//########################################################################
// class TMSize implementation
TMSize::TMSize()
{
}
TMSize::TMSize(TLcType aWith,TLcType aHeight)
{
    iWidth = aWith;
    iHeight = aHeight;
}
TMSize::~TMSize()
{

}





//////////////////////////////////////////////////////////////////////////
//########################################################################
// class TVector implementation
TVector::TVector()
{
    m_lHx = 0;
    m_lVy = 0;
}
TVector::~TVector()
{
}

TVector::TVector(TLcType x,TLcType y)
{
    m_lHx = x;
    m_lVy = y;
}

TVector::TVector(TMPoint ptStart,TMPoint ptEnd)
{
    *this = ptEnd-ptStart;
}

// 取反
TVector TVector::operator-()
{
    TVector vOther;
    vOther.m_lHx = -m_lHx;
    vOther.m_lVy = -m_lVy;
    return vOther;
}

// 
TVector& TVector::operator=(const TVector& aOther)
{
    if( this != &aOther )
    {
        m_lHx = aOther.m_lHx;
        m_lVy = aOther.m_lVy;
    }

    return *this;
}

TVector& TVector::operator=(const TSegmentVector& aLine)
{
    TVector v = aLine.GetVector();
    m_lHx = v.m_lHx;
    m_lVy = v.m_lVy;
    return *this;
}

// 加法运算
TVector  operator+(const TVector& V1,const TVector& V2)
{
    TVector result;
    result.m_lHx = V1.m_lHx + V2.m_lHx;
    result.m_lVy = V1.m_lVy + V2.m_lVy;
    return result;
}
TVector& TVector::operator+=(const TVector& aOther)
{
    m_lHx += aOther.m_lHx;
    m_lVy += aOther.m_lVy;
    return *this;
}

// 向量减法运算
TVector  operator-(const TVector& V1,const TVector& V2)
{
    TVector result;
    result.m_lHx = V1.m_lHx - V2.m_lHx;
    result.m_lVy = V1.m_lVy - V2.m_lVy;
    return result;
}
TVector& TVector::operator-=(const TVector& aOther) 
{
    m_lHx -= aOther.m_lHx;
    m_lVy -= aOther.m_lVy;
    return *this;
}

BOOL TVector::operator==(const TVector& aOther) const
{
    if (this==&aOther)
    {
        return TRUE;
    }

    return (m_lHx==aOther.m_lHx && m_lVy==aOther.m_lVy);
}

BOOL TVector::operator!=(const TVector& aOther) const
{
    return !(*this==aOther);
}


// 是否为零向量
BOOL TVector::IsZeroVector() const
{
    return (m_lHx==0 && m_lVy==0);
}


// 计算向量的斜率
TSlopeType TVector::GetSlope(DOUBLE& fSlope) const
{
    if (IsZeroVector())
    {
        fSlope = 0;
        return EST_INVALID;
    }

    if (m_lHx==0)
    {
        fSlope = m_lVy * 1E5;
        if(m_lVy>0)
        {
            return EST_POSITIVE_INF;
        }
        else
        {
            return EST_NEGATIVE_INF;
        }
    }
    else
    {
        fSlope = DOUBLE(m_lVy)/DOUBLE(m_lHx);
        return EST_NORMAL;
    }
}

// 两向量是否平行。向量平行（共线）的充要条件：X1*Y2-X2*Y1=0
BOOL  TVector::IsHorizontal(const TVector& aOther) const
{
    TLcType fRc = CrossProduct(aOther);
    return ( abs(fRc)<=1E-6 );
}

// 两向量是否垂直(内积为0)
BOOL  TVector::IsVertical(const TVector& aOther) const
{
    TLcType fRc = DotProduct(aOther);
    return ( abs(fRc)<=1E-6 );
}

// 计算向量的模

DOUBLE TVector::GetModule() const
{
    return sqrt(Square());
}

DOUBLE TVector::GetLength() const
{
    return sqrt(Square());
}

// 计算向量的平方
DOUBLE  TVector::Square() const
{
    return DOUBLE(m_lHx*m_lHx + m_lVy*m_lVy);
}

/***************************************************************************************************
内积 a·b = |a|·|b|·cos<a, b> = Xa*Ya+Xb+Yb
两向量 a,b 的内积，记为 a·b，规定为一个实数：a·b = |a|·|b|·cos<a, b>

*/
TLcType TVector::DotProduct(const TVector& aOther) const
{
    return (m_lHx*aOther.m_lHx+m_lVy*aOther.m_lVy);
}
TLcType operator&(TVector aV1,TVector aV2)
{
    return aV1.DotProduct(aV2);
}


/***************************************************************************************************
// 外积 a × b = |a|·|b|·Sin<a, b> ; 方向：适用右手定律
矢量叉积：
设矢量P = （x1,y1） ，Q = (x2,y2)，则矢量叉积定义为由(0,0)、p1、p2和p1+p2所组成的
平行四边形的带符号的面积，即：P × Q = x1*y2 - x2*y1，其结果是一个标量。显然有性
质 P × Q = - ( Q × P ) 和 P × ( - Q ) = - ( P × Q)。

叉积的一个非常重要性质是可以通过它的符号判断两矢量相互之间的顺逆时针关系：
1. 若 P × Q > 0 , 则P在Q的顺时针方向。 
2. 若 P × Q < 0 , 则P在Q的逆时针方向。 
3. 若 P × Q = 0 , 则P与Q共线，但可能同向也可能反向。

*/
TLcType TVector::CrossProduct(const TVector& aOther) const
{
    return (m_lHx*aOther.m_lVy-aOther.m_lHx*m_lVy);
}
TLcType operator*(TVector aV1,TVector aV2)
{
    return aV1.CrossProduct(aV2);
}

/************************************************************************************************

1、n个数值组成的行(x1, x2, x3,…… Xn)称为n维向量简记为大写字母X 

|X| = √x1^2+x2^2+...+xn2 定义为向量X的模，向量X与Y的内积为： X·Y=x1*y1+x2*y2+..Xn*Yn


2、向量X及Y的向量夹角余弦按照下式计算：

cos(θ) = X·Y/(|X|×|Y|) = (X1×Y1+X2×Y2) / (|X|×|Y|) 。     [ PI=>θ>=0]

*/
DOUBLE TVector::Angle(const TVector& aOther) const
{
    if (IsZeroVector() || aOther.IsZeroVector())
    {
        return -1;
    }

    if (IsVertical(aOther))
    {
        return PIRADIAN/2;
    }

    DOUBLE vp = GetLength()*aOther.GetLength();

    if(vp==0) 
    {
        return -1;
    }

    DOUBLE angle = acos((DotProduct(aOther))/vp);

    return angle;
}

// 与X正轴的夹角
DOUBLE TVector::Angle() const
{
    TVector vTemp(10,0);

    DOUBLE fAngle = Angle(vTemp);

    if (m_lVy<0)
    {
        fAngle = 2*PIRADIAN - fAngle;
    }
    else if (m_lVy==0)
    {
        if (m_lHx<0)
        {
            fAngle = PIRADIAN;
        }
    }
    

    return fAngle;
}

// 向量以aAxisPt点顺时针旋转aRadian弧度
void  TVector::Rotate(TMPoint aAxisPt,DOUBLE aRadian)
{
    TMPoint pt1(0,0);
    TMPoint pt2(m_lHx,m_lVy);

    pt1.Rotate(aAxisPt,aRadian,TRUE);
    pt2.Rotate(aAxisPt,aRadian,TRUE);

    m_lHx = pt2.iX - pt1.iX;
    m_lVy = pt2.iY - pt1.iY;
}


// 判断两向量的位置关系
// Return Value: aOther与当前向量的位置关系
/*
1. 若 P × Q > 0 , 则P在Q的顺时针方向。 
2. 若 P × Q < 0 , 则P在Q的逆时针方向。 
3. 若 P × Q = 0 , 则P与Q共线，但可能同向也可能反向。*/

TVPType TVector::GetPositionType(const TVector& aOther) const
{
    if (*this==aOther)
    {
        return ETVP_EQUAL;
    }

    TVector P = *this;
    TVector Q = aOther;
    TLcType result = P*Q;

    if (result>0)
    {
        return ETVP_CLOCKWISE;
    }
    else if (result<0)
    {
        return ETVP_COUNTERCLOCKWISE;
    }
    else
    {
        if (P.Angle(Q)>PIRADIAN/2)
        {
            return ETVP_COLLINEAR_REVERSE;
        }
        else
        {
            return ETVP_COLLINEAR_OBVERSE;
        }
    }
}



//////////////////////////////////////////////////////////////////////////
//########################################################################
// class TLineVector implementation
TSegmentVector::TSegmentVector()
{
    iStartPoint.iX = 0;
    iStartPoint.iY = 0;
    iEndPoint.iX = 0;
    iEndPoint.iY = 0;
}
TSegmentVector::TSegmentVector(const TMPoint& ptEnd)
{
    iStartPoint.iX = 0;
    iStartPoint.iY = 0;
    iEndPoint.iX = ptEnd.iX;
    iEndPoint.iY = ptEnd.iY;
}
TSegmentVector::TSegmentVector(POINT aStart,POINT aEnd)
{
    iStartPoint.iX = aStart.x;
    iStartPoint.iY = aStart.y;
    iEndPoint.iX = aEnd.x;
    iEndPoint.iY = aEnd.y;
}
TSegmentVector::TSegmentVector(TMPoint aStartPt,TMPoint aEndPt)
{
    iStartPoint = aStartPt;
    iEndPoint = aEndPt;
}
TSegmentVector::~TSegmentVector()
{

}


void TSegmentVector::Move(TVector aVector)
{
    iStartPoint += aVector;
    iEndPoint += aVector;
}

TSegmentVector& TSegmentVector::operator=(const TSegmentVector& aOther)
{
    if (this!=&aOther)
    {
        iStartPoint = aOther.iStartPoint;
        iEndPoint = aOther.iEndPoint;
    }
    return *this;
}
TLcType TSegmentVector::Vx() const
{
    return iEndPoint.iX - iStartPoint.iX;
}
TLcType TSegmentVector::Vy() const
{
    return iEndPoint.iY - iStartPoint.iY;
}
DOUBLE TSegmentVector::GetLength() const
{
    return iStartPoint.Distance(iEndPoint);
}

TMPoint TSegmentVector::GetCenterPt() const
{
    TMPoint pt;
    pt.iX = iStartPoint.iX+Vx()/2;
    pt.iY = iStartPoint.iY+Vy()/2;
    return pt;
}

TVector TSegmentVector::GetVector() const
{
    return TVector(iEndPoint.iX-iStartPoint.iX,iEndPoint.iY-iStartPoint.iY);
}

TVectorDirect TSegmentVector::GetDirection(TDirectCategory aType/* =EDT_FOURE */) const
{
    if (iStartPoint.iX==iEndPoint.iX && iStartPoint.iY==iEndPoint.iY)
    {
        return EVD_INVALID;
    }
    else 
    {
        TLcType h = Vy();
        TLcType l = Vx();

        TMRect newRect;
        if (h<0&&l==0)
        {
            return EVD_BOTTOM;
        }
        else if(h<0&&l>0)
        {
            if (aType==EDT_FOURE)
            {
                if (-h>l)
                {
                    return EVD_BOTTOM;
                }
                else
                {
                    return EVD_RIGHT;
                }
            }
            else
            {
                if (-h>2.36*l)
                {
                    return EVD_BOTTOM;
                }
                else if (-h<0.4*l)
                {
                    return EVD_RIGHT;
                }
                else
                {
                    return EVD_BOTTOM_RIGHT;
                }

            }

        }
        else if (h==0&&l>0)
        {
            return EVD_RIGHT;
        }
        else if (h>0&&l>0)
        {
            if (aType==EDT_FOURE)
            {
                if (h>l)
                {
                    return EVD_TOP;
                } 
                else
                {
                    return EVD_RIGHT;
                }
            }
            else
            {
                if (h<0.4*l)
                {
                    return EVD_RIGHT;
                }
                else if (h>2.36*l)
                {
                    return EVD_TOP;
                }
                else
                {
                    return EVD_TOP_RIGHT;
                }

            }
        }
        else if (h>0&&l==0)
        {
            return EVD_TOP;
        }
        else if (h>0&&l<0)
        {
            if (aType==EDT_FOURE)
            {
                if (h>-l)
                {
                    return EVD_TOP;
                } 
                else
                {
                    return EVD_LEFT;
                }
            }
            else
            {
                if (h>-l*2.36)
                {
                    return EVD_TOP;
                } 
                else if (h<-l*0.4)
                {
                    return EVD_LEFT;
                }
                else
                {
                    return EVD_TOP_LEFT;
                }
            }
        }
        else if (h==0&&l<0)
        {
            return EVD_LEFT;
        }
        else// (l<0,h<0)
        {

            if (aType==EDT_FOURE)
            {
                if (-h>-l)
                {
                    return EVD_BOTTOM;
                }
                else
                {
                    return EVD_LEFT;
                }
            }
            else
            {
                if (-h>-l*2.36)
                {
                    return EVD_BOTTOM;
                } 
                else if (-h<0.4*-l)
                {
                    return EVD_LEFT;
                }
                else
                {
                    return EVD_BOTTOM_LEFT;
                }

            }
        }
    }
}

DOUBLE TSegmentVector::GetAzimuth() const
{

    TLcType detalX = iEndPoint.iX - iStartPoint.iX;
    TLcType detalY = iEndPoint.iY - iStartPoint.iY;

    if (detalX==0 && detalY!=0)
    {
        if (detalY>0)
        {
            return 0;
        }
        else
        {
            return PIRADIAN;   
        }
    }
    else if (detalY==0 && detalX!=0)
    {
        if (detalX>0)
        {
            return PIRADIAN/2;
        }
        else
        {
            return PIRADIAN*3/2;
        }
    }
    else if (detalX==0 && detalY==0)
    {
        return -1;
    }

    // detaX!=0 && detalY!=0
    else
    {

        //DOUBLE azimuth = 0;
        DOUBLE azimuth = atanl( abs(DOUBLE(detalY)/detalX) );


        // 第一象限
        if (detalX>0 && detalY>0)
        {
            //azimuth = (float)atanl(float(detalY)/float(detalX));
            return PIRADIAN/2-azimuth;
        }

        // 第二象限
        else if (detalX<0 && detalY>0)
        {
            //azimuth = (float)atanl(float(detalY)/float(-detalX));
            return 3*PIRADIAN/2+azimuth;
        }

        // 第三象限
        else if (detalX<0 && detalY<0)
        {
            //azimuth = (float)atanl(float(-detalY)/float(-detalX));
            return PIRADIAN*3/2-azimuth;
        }

        // 第四象限
        else 
        {
            //azimuth = (float)atanl(float(-detalY)/float(detalX));
            return PIRADIAN/2+azimuth;
        }

    }
}

BOOL TSegmentVector::GetRemotePoint(TMPoint& ptArg, DOUBLE fRemoteLen) const
{
    DOUBLE fSegLen = GetLength();
    if (fRemoteLen>fSegLen)
    {
        return FALSE;
    }
    else if (IsEqual(fRemoteLen,fSegLen))
    {
        ptArg = iEndPoint;
    }
    else
    {
        DOUBLE fAngleX = GetVector().Angle();
        DOUBLE fDeltaX = fRemoteLen*cos(fAngleX);
        DOUBLE fDeltaY = fRemoteLen*sin(fAngleX);
        
        ptArg.iX = Round(iStartPoint.iX + fDeltaX);
        ptArg.iY = Round(iStartPoint.iY + fDeltaY);
    }

    //
    return TRUE;
}

void TSegmentVector::Rotate( TMPoint aAxisPt,float aRadian)
{
    iStartPoint.Rotate(aAxisPt,aRadian);
    iEndPoint.Rotate(aAxisPt,aRadian);
}

/************************************************************************

设点为Q，线段为P1P2 。 判断点Q在该线段上的依据是：
( Q - P1 ) × ( P2 - P1 ) = 0 且 Q 在以 P1，P2为对角顶点的矩形内。

前者保证Q点在直线P1P2上，后者是保证Q点不在线段P1P2的延长线或反向延长线上

******************************************************************************/
BOOL TSegmentVector::PointInSegment(const TMPoint& aPoint,BOOL bExtendLine /*=EFalse*/) const
{
    TLcType x,y,x0,y0,x1,y1;
    x = aPoint.iX;
    y = aPoint.iY;
    x0 = iStartPoint.iX;
    y0 = iStartPoint.iY;
    x1 = iEndPoint.iX;
    y1= iEndPoint.iY;

    TLcType aResult = abs((y-y0)*(x1-x0)-(y1-y0)*(x-x0));

    // 点不在直线上
    if (aResult!=0)
    {
        return FALSE;
    }
    else
    {
        // 点在直线上
        if (bExtendLine)
        {
            return TRUE;
        }
        else
        {
            TMRect rect(iStartPoint,iEndPoint);
            return rect.Contains(aPoint);
        }
    }        
}

TSegmentVector TSegmentVector::BuildSegment(TMPoint aStartPt,float aAzimuth,LONG aLogicLen/* =1000 */)
{
    float sinA,cosA;
    sinA = sin(aAzimuth);
    cosA = cos(aAzimuth);

    TMPoint endPt;
    endPt.iX = Round(aLogicLen*sinA + aStartPt.iX);
    endPt.iY = Round(aLogicLen*cosA + aStartPt.iY);

    TSegmentVector newVector(aStartPt,endPt);

    return newVector;
}

// 点的投影在线段上的位置。根据内积计算
int TSegmentVector::ProjectionPosition(TMPoint aPt) const
{
    TVector AO(iStartPoint,aPt);
    TVector AB = GetVector();
    TLcType product = AO.DotProduct(AB);
    if (product<0)
    {
        return EPP_OFFSETSTART;
    }
    else if (product==0)
    {
        return EPP_INSEGMENT; // 投影点与起点重合
    }

    TVector BO(iEndPoint,aPt);
    TVector BA(iEndPoint,iStartPoint);
    product = BO.DotProduct(BA);
    if (product<0)
    {
        return EPP_OFFSETEND;
    }
    else if (product==0)
    {
        return EPP_INSEGMENT; // 投影点与终点重合
    }

    return EPP_INSEGMENT;
}

// 点到线段的距离
DOUBLE  TSegmentVector::Distance(TMPoint aPoint) const
{
    DOUBLE AB,AC,BC;
    AB = iStartPoint.Distance(iEndPoint);
    AC = iStartPoint.Distance(aPoint);
    BC = iEndPoint.Distance(aPoint);

    DOUBLE	L_ab2 = AB * AB;
    DOUBLE  L_ac2 = AC * AC;
    DOUBLE  L_bc2 = BC * BC;


    if (L_ac2 + L_ab2 <= L_bc2)
    {
        return AC;
    }
    else if (L_bc2 + L_ab2 <= L_ac2)
    {
        return BC;
    }
    else
    {
        DOUBLE pp,hh,ss;
        pp = (AB + AC + BC) / 2;
        ss = sqrt(pp * (pp - AB) * (pp - AC) * (pp - BC));
        hh = 2 * ss / AB;

        return hh;
    }
}

// 设线段为AB，从点Q做垂线，垂足为点O。
DOUBLE TSegmentVector::Plumbline(TMPoint aPointQ,TMPoint& aCrossedPt/*垂足O*/) const
{
    // 是否为零向量
    if (GetVector().IsZeroVector())
    {
        return -1;
    }

    // 点的投影是否在线段上
    if (ProjectionPosition(aPointQ)!=EPP_INSEGMENT)
    {
        return -1;
    }

    // 点是否在线上
    if (PointInSegment(aPointQ))
    {
        aCrossedPt = aPointQ;
        return 0;
    }

#ifdef _NEW_PLUMBINE


    TLcType dx = Vx();
    TLcType dy = Vy();

    TLcType aa = GetVector() & TVector(aPointQ,iStartPoint); // 外积： aa = AB*PA
    TLcType bb = dx*dx + dy*dy;

    DOUBLE fDistance = fabs(aa/sqrt(DOUBLE(bb)));

    aCrossedPt.iX = Round(aPointQ.iX - DOUBLE(dy*aa)/bb);
    aCrossedPt.iY = Round(aPointQ.iY + DOUBLE(dx*aa)/bb);

    return fDistance;

#else   

    /************************************************************************/
    /* 此算法效率较低,但可以得到垂足                                        */
    /************************************************************************/
    DOUBLE nUpX,nUpY;  //点与直线垂直相交的交点
    DOUBLE nMinDist;
    DOUBLE nMinX,nMaxX,nMinY,nMaxY;

    // 
    if(iStartPoint.iX == iEndPoint.iX) // 
    {
        nUpX = iStartPoint.iX;
        nUpY = aPointQ.iY;
    }
    else
    {
        if(iStartPoint.iY == iEndPoint.iY)
        {
            nUpX = aPointQ.iX;
            nUpY = iStartPoint.iY;
        }
        else
        {
            // 计算p1p2的斜率
            double k1 = (double)(iEndPoint.iY - iStartPoint.iY) / (double)(iEndPoint.iX - iStartPoint.iX);
            // 垂线的斜率
            double k2 = (double)-1 / k1;
            // 利用直线公式计算垂足
            nUpX = (k1 * iStartPoint.iX - k2 * aPointQ.iX - iStartPoint.iY + aPointQ.iY) / (k1 - k2);
            nUpY = (k1 * aPointQ.iY - k2 * iStartPoint.iY - iStartPoint.iX + aPointQ.iX) / (k1 - k2);
        }
    }

    //
    if(iStartPoint.iX > iEndPoint.iX)
    {
        nMinX = iEndPoint.iX;
        nMaxX = iStartPoint.iX;
    }
    else
    {
        nMinX = iStartPoint.iX;
        nMaxX = iEndPoint.iX;
    }

    //
    if(iStartPoint.iY > iEndPoint.iY)
    {
        nMinY = iEndPoint.iY;
        nMaxY = iStartPoint.iY;
    }
    else
    {
        nMinY = iStartPoint.iY;
        nMaxY = iEndPoint.iY;
    }

    //
    if(nUpX < nMinX || nUpX >nMaxX ||nUpY <nMinY||nUpY>nMaxY)  // 垂足未落在线段上
    {
        if((abs(iEndPoint.iX-aPointQ.iX)+abs(iEndPoint.iY-aPointQ.iY))>(abs(iStartPoint.iX-aPointQ.iX)+abs(iStartPoint.iY-aPointQ.iY)))
        {
            nUpX = iStartPoint.iX;
            nUpY = iStartPoint.iY;
        }
        else
        {
            nUpX = iEndPoint.iX;
            nUpY = iEndPoint.iY;
        }

        nMinDist= aPointQ.Distance(TMPoint(Round(nUpX),Round(nUpY)));
    }
    else
    {
        nMinDist= aPointQ.Distance(TMPoint(Round(nUpX),Round(nUpY)));
    }

    aCrossedPt.iX = Round(nUpX);
    aCrossedPt.iY = Round(nUpY);

    return nMinDist;
#endif
}

BOOL  TSegmentVector::IsHorizontal(const TSegmentVector& aOther) const
{
    TVector unitV1 = GetVector();
    TVector unitV2 = aOther.GetVector();

    return unitV1.IsHorizontal(unitV2);
}

BOOL  TSegmentVector::IsVertical(const TSegmentVector& aOther) const
{
    TVector unitV1 = GetVector();
    TVector unitV2 = aOther.GetVector();

    return unitV1.IsVertical(unitV2);

}

DOUBLE TSegmentVector::Angle(const TSegmentVector& aOther) const
{
    TVector unitV1 = GetVector();
    TVector unitV2 = aOther.GetVector();

    DOUBLE angle = unitV1.Angle(unitV2);

    return angle;
}

/************************************************************************

1、判断两线段是否相交：

分两步确定两条线段是否相交：

(1) 快速排斥试验
设以线段 P1P2 为对角线的矩形为R， 设以线段 Q1Q2 为对角线的矩形为T，
如果R和T不相交，显然两线段不会相交。

(2) 跨立试验 如果两线段相交，则两线段必然相互跨立对方。若P1P2跨立Q1Q2 ，
则矢量 (P1 - Q1) 和(P2 - Q1)位于矢量( Q2 - Q1 ) 的两侧，
即( P1 - Q1 ) × ( Q2 - Q1 ) * ( P2 - Q1 ) × ( Q2 - Q1 ) < 0。
上式可改写成( P1 - Q1 ) × ( Q2 - Q1 ) * ( Q2 - Q1 ) × ( P2 - Q1 ) > 0。
当 ( P1 - Q1 ) × ( Q2 - Q1 ) = 0 时，说明 ( P1 - Q1 ) 和 ( Q2 - Q1)共线，
但是因为已经通过快速排斥试验，所以 P1 一定在线段 Q1Q2上；同理，
( Q2 - Q1 ) ×(P2 - Q1 ) = 0 说明 P2 一定在线段 Q1Q2上。

所以判断P1P2跨立Q1Q2的依据是：
( P1 - Q1 ) × ( Q2 - Q1 ) * ( Q2 - Q1 ) × ( P2 - Q1 ) >= 0。

同理判断Q1Q2跨立P1P2的依据是：
( Q1 - P1 ) × ( P2 - P1 ) * ( P2 - P1 ) × ( Q2 - P1 ) >= 0。


2、判断线段和直线是否相交


如果线段 P1P2和直线Q1Q2相交，则P1P2跨立Q1Q2，即：

( P1 - Q1 ) × ( Q2 - Q1 )  *  ( Q2 - Q1 ) × ( P2 - Q1 )  >=  0

  
如果线段 Q1Q2和直线P1P2相交，则Q1Q2跨立P1P2，即：
    
( Q1 - P1 ) × ( P2 - P1 ) * ( P2 - P1 ) × ( Q2 - P1 ) >= 0。


/************************************************************************/
// 功能：判断两线段是否相交（包括共线）
BOOL TSegmentVector::IsIntersects(const TSegmentVector& aOther,BOOL bLine) const
{
    TMPoint P1 = iStartPoint;
    TMPoint P2 = iEndPoint;
    TMPoint Q1 = aOther.iStartPoint;
    TMPoint Q2 = aOther.iEndPoint;

    if (!bLine)
    {
        TMRect rect1(iStartPoint,iEndPoint);
        TMRect rect2(aOther.iStartPoint,aOther.iEndPoint);

        // (1) 快速排斥试验
        if (!rect1.IsIntersects(rect2))
        {
            return FALSE;
        }

        // (2) 跨立试验

        // 判断P1P2跨立Q1Q2
        TLcType r1 = ((P1-Q1)*(Q2-Q1));
        TLcType r2 = ((Q2-Q1)*(P2-Q1));
        if (r1<0 && r2>0 || r1>0 && r2<0)
        {
            return FALSE;
        }

        // 判断Q1Q2跨立P1P2
        r1 = ((Q1-P1)*(P2-P1));
        r2 = ((P2-P1)*(Q2-P1));
        if (r1<0 && r2>0 || r1>0 && r2<0)
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
    else
    {        
        TLcType r1 = ((P1-Q1)*(Q2-Q1));
        TLcType r2 = ((Q2-Q1)*(P2-Q1));
        if (r1<0 && r2>0 || r1>0 && r2<0)
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
}

// 两线段的相交点
BOOL  TSegmentVector::CalcIntersection(const TSegmentVector& aOther,
                                       TMPoint& ptCross,
                                       BOOL bLine/*=FALSE*/) const
{  
    // 若平行，返回FASLE
    if (IsHorizontal(aOther))
    {
        return FALSE;
    }

    // 如果两线段不相交，返回FALSE 
    if (!IsIntersects(aOther,bLine))
    {
        return FALSE;
    }

    // 相交，则计算相交点
    TLcType X1 = iStartPoint.iX;
    TLcType Y1 = iStartPoint.iY;
    TLcType X2 = iEndPoint.iX;
    TLcType Y2 = iEndPoint.iY;
    TLcType X3 = aOther.iStartPoint.iX;
    TLcType Y3 = aOther.iStartPoint.iY;
    TLcType X4 = aOther.iEndPoint.iX;
    TLcType Y4 = aOther.iEndPoint.iY;

    DOUBLE X0,Y0;
    DOUBLE K1,K2;

    if(X2==X1 && X3!=X4)
    {
        X0 = X1;
        K2 = (Y4-Y3) / (DOUBLE)(X4-X3);
        Y0 = K2*(X0-X3) + Y3;
    }
    else if (X2!=X1 && X4==X3)
    {
        X0 = X3;
        K1 = (Y2-Y1) / (DOUBLE)(X2-X1);
        Y0 = K1*(X0-X1) + Y1;
    }
    else  if (X2!=X1 && X4!=X3)
    {
        K1 = (Y2-Y1) / (DOUBLE)(X2-X1);
        K2 = (Y4-Y3) / (DOUBLE)(X4-X3);
        X0 = (K1*X1-Y1+Y3-K2*X3) / (K1-K2);
        Y0 = K1*(X0-X1) + Y1;
    }
    else 
    {
        return FALSE;
    }

    ptCross.iX = Round(X0);
    ptCross.iY = Round(Y0);
    
    // 
    return TRUE;
}





//////////////////////////////////////////////////////////////////////////
//########################################################################
// class TMRect implementation
TMRect::TMRect(TCoordinateType iType)
{
    m_iType = iType;

    iTl.iX = 0;
    iTl.iY = 1;

    iBr.iX = 1;
    iBr.iY = 0;

}

TMRect::TMRect(TLcType aAx,TLcType aAy,TLcType aBx,TLcType aBy,
               TCoordinateType iType)
{
    m_iType = iType;

    iTl.iX = aAx;
    iTl.iY = aAy;

    iBr.iX = aBx;
    iBr.iY = aBy;

    NormalizeRect( );
}

TMRect::TMRect(const TMPoint& aPointA,const TMPoint& aPointB,
               TCoordinateType iType)
{
    m_iType = iType;

    iTl = aPointA;
    iBr = aPointB;

    NormalizeRect( );
    
}

TMRect::TMRect(const TMPoint& aLt,TMSize aSize,
               TCoordinateType iType)
{
    m_iType = iType;

    // 
    iTl = aLt;
    iBr.iX = aLt.iX + aSize.iWidth;

    if(iType==ECartesian)
    {
        iBr.iY = aLt.iY - aSize.iHeight;
    }
    else if(iType==EPCScreen)
    {
        iBr.iY = aLt.iY + aSize.iHeight;
    }
    else
    {
        ASSERT(0);
    }

    NormalizeRect( );
}

TMRect::TMRect(const TMPoint& aCenter,TLcType aWidth,TLcType aHeight,
               TCoordinateType iType)
{
    m_iType = iType;

    iTl.iX = aCenter.iX - aWidth/2;
    iBr.iX = aCenter.iX + aWidth/2;

    if(iType==ECartesian)
    {
        iTl.iY = aCenter.iY + aHeight/2;
        iBr.iY = aCenter.iY - aHeight/2;
    }
    else if(iType==EPCScreen)
    {
        iTl.iY = aCenter.iY - aHeight/2;
        iBr.iY = aCenter.iY + aHeight/2;
    }
    else
    {
        ASSERT(0);
    }

    NormalizeRect( );
}

TMRect::TMRect(const CMPointVector& aPloygon,
               TCoordinateType iType)
{
    m_iType = iType;

    //
    INT_PTR number = aPloygon.size();
    if (number<2)
    {
        return;
    }

    TMPoint element = aPloygon[0];
    TLcType minX,maxX,minY,maxY;
    minX = maxX = element.iX;
    minY = maxY = element.iY;

    for (INT_PTR i=1; i<number; i++)
    {
        element = aPloygon[i];
        if (element.iX<minX)
        {
            minX = element.iX;
        }
        else if (element.iX>maxX)
        {
            maxX = element.iX;
        }

        if (element.iY<minY)
        {
            minY = element.iY;
        }
        else if (element.iY>maxY)
        {
            maxY = element.iY;
        }
    }

    
    NormalizeRect( );
}

TMRect::~TMRect()
{
}


void TMRect::NormalizeRect( )
{
    TLcType tlX,tlY,brX,brY;
    
    if (m_iType==ECartesian)
    {
        tlX = min(iTl.iX,iBr.iX);
        tlY = max(iTl.iY,iBr.iY);
        brX = max(iTl.iX,iBr.iX);
        brY = min(iTl.iY,iBr.iY);
    } 
    else if (m_iType==EPCScreen)
    {
        tlX = min(iTl.iX,iBr.iX);
        tlY = min(iTl.iY,iBr.iY);
        brX = max(iTl.iX,iBr.iX);
        brY = max(iTl.iY,iBr.iY);
    }
    else
    {
        ASSERT(ERROR);
    }

    iTl = TMPoint(tlX,tlY);
    iBr = TMPoint(brX,brY);
}

//
TLcType TMRect::Top() const
{
    return iTl.iY;
}

TLcType TMRect::Bottom() const
{
    return iBr.iY;
}

TLcType TMRect::Left() const
{
    return iTl.iX;
}

TLcType TMRect::Right() const
{
    return iBr.iX;
}

TMPoint TMRect::TopRight() const
{
    return TMPoint(iBr.iX,iTl.iY);
}

TMPoint TMRect::BottomLeft() const
{
    return TMPoint(iTl.iX,iBr.iY);
}

TMPoint TMRect::Center() const
{
    TLcType x = iTl.iX + (iBr.iX - iTl.iX)/2;
    TLcType y = iBr.iY + (iTl.iY - iBr.iY)/2;
    return TMPoint(x,y);
}

TLcType TMRect::Width() const
{
    return abs(iBr.iX-iTl.iX);
}

TLcType TMRect::Height() const
{
    return abs(iTl.iY-iBr.iY);
}

void TMRect::GetLocation(TMPoint* aPt) const
{
    if (aPt!=NULL)
    {
        *aPt = iTl;
    }
}

void TMRect::MoveAlongVector(const TVector& aVector)
{
    TLcType x = aVector.m_lHx;
    TLcType y = aVector.m_lVy;

    iTl.iX += x;
    iTl.iY += y;

    iBr.iX += x;
    iBr.iY += y;
}

// 赋值号重载
TMRect& TMRect::operator=(const TMRect& aOther)
{
    if (this != &aOther)
    {
        m_iType = aOther.m_iType;

        // 
        iTl.iX = aOther.iTl.iX;
        iTl.iY = aOther.iTl.iY;
        iBr.iX = aOther.iBr.iX;
        iBr.iY = aOther.iBr.iY;
    }
    return *this;
}

TMRect operator+(TMRect aRect1,TMRect aRect2)
{
    if (aRect2.m_iType!=aRect1.m_iType)
    {
        return TMRect(0,0,0,0);        
    }

    // 
    TCoordinateType iType = aRect1.m_iType;

    if (aRect1.IsNull())
    {
        return aRect2;
    }
    else if (aRect2.IsNull())
    {
        return aRect1;
    }
    else
    {
        TLcType lpX = min(aRect1.iTl.iX,aRect2.iTl.iX);
        TLcType brX = max(aRect1.iBr.iX,aRect2.iBr.iX);
        TLcType lpY;
        TLcType brY;
        
        if (iType==ECartesian)
        {
            lpY = max(aRect1.iTl.iY,aRect2.iTl.iY);
            brY = min(aRect1.iBr.iY,aRect2.iBr.iY);
        }
        else if (iType==EPCScreen)
        {
            lpY = min(aRect1.iTl.iY,aRect2.iTl.iY);
            brY = max(aRect1.iBr.iY,aRect2.iBr.iY);
        } 
        else
        {
            ASSERT(0);
        }
        
        return TMRect(lpX,lpY,brX,brY);
    }

}
void TMRect::operator+=(const TMRect& aRect)
{
    *this = *this + aRect;
}

void TMRect::operator-=(TMSize size)
{
    iTl.iX -= size.iWidth;
    iBr.iX -= size.iWidth;

    iTl.iY -= size.iHeight;
    iBr.iY -= size.iHeight;


    if (!IsValid())
    {
        SetNull();
    }
}


// 
BOOL TMRect::IsValid() const
{
    if (m_iType==ECartesian)
    {
        if (Left()>Right() || Top()<Bottom())
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
    else if (m_iType==EPCScreen)
    {
        if (Left()>Right() || Top()>Bottom())
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    } 
    else
    {
        return TRUE;
    }
}

BOOL TMRect::IsEmpty() const
{
    return (Width()==0 || Height()==0);
}

void TMRect::SetNull()
{
    iTl.iX = iTl.iY = 0;
    iBr.iX = iBr.iY = 0;
}

BOOL TMRect::IsNull() const
{
    return (Left()==0 && Right()==0 && Top()==0 && Bottom()==0);
}

// 
// void TMRect::Copy(CRect aOther)
// {
//     iTl.iX = aOther.left;
//     iTl.iY = aOther.top;
//     iBr.iX = aOther.right;
//     iBr.iY = aOther.bottom;
//     NormalizeRect();
// }
// 

RECT TMRect::ToRECT() const
{
    RECT aNewRect;
    aNewRect.left   = min(LONG(iTl.iX),LONG(iBr.iX));
    aNewRect.top    = min(LONG(iTl.iY),LONG(iBr.iY));
    aNewRect.right  = max(LONG(iTl.iX),LONG(iBr.iX));
    aNewRect.bottom = max(LONG(iTl.iY),LONG(iBr.iY));

    return aNewRect;
}

void TMRect::MoveLeft(TLcType aLen)
{
    iTl.iX -= aLen;
    iBr.iX -= aLen;
}

void TMRect::MoveRight(TLcType aLen)
{
    iTl.iX += aLen;
    iBr.iX += aLen;
}
void TMRect::MoveTop(TLcType aLen)
{
    if (m_iType==ECartesian)
    {
        iTl.iY += aLen;
        iBr.iY += aLen;
    } 
    else if(m_iType==EPCScreen)
    {
        iTl.iY -= aLen;
        iBr.iY -= aLen;
    }
}
void TMRect::MoveBottom(TLcType aLen)
{
    if (m_iType==ECartesian)
    {
        iTl.iY -= aLen ;
        iBr.iY -= aLen ;
    } 
    else if(m_iType==EPCScreen)
    {
        iTl.iY += aLen;
        iBr.iY += aLen;
    }
}
void TMRect::Offset(TMPoint aPt)
{
    iTl.iX += aPt.iX;
    iBr.iX += aPt.iX;

    iTl.iY += aPt.iY;
    iBr.iY += aPt.iY;
}

/************************************************************************

判断矩形是否包含点

只要判断该点的横坐标和纵坐标是否夹在矩形的左右边和上下边之间。

************************************************************************/

BOOL TMRect::Contains(const TMPoint& aPoint) const
{
    BOOL x = (aPoint.iX>=iTl.iX) && (aPoint.iX<=iBr.iX);

    if (!x)
    {
        return FALSE;
    }

    BOOL y = FALSE;
    if (m_iType==ECartesian)
    {
        y = (aPoint.iY>=iBr.iY) && (aPoint.iY<=iTl.iY);
    }
    else if(m_iType==EPCScreen)
    {
        y = (aPoint.iY<=iBr.iY) && (aPoint.iY>=iTl.iY);
    }
    
    return y;
}

BOOL TMRect::Contains(const TSegmentVector& aSegment) const
{
    if (!Contains(aSegment.iStartPoint))
    {
        return FALSE;
    }

    if (!Contains(aSegment.iEndPoint))
    {
        return FALSE;
    }

    return TRUE;
}

/************************************************************************/
/* 
    判断线段、折线、多边形是否在矩形中

    因为矩形是个凸集，所以只要判断所有端点是否都在矩形中就可以了。

/************************************************************************/
BOOL TMRect::Contains(const TMRect& aRect) const
{
    BOOL rc = Contains(aRect.iTl);
    if (!rc)
    {
        return FALSE;
    }
    
    return Contains(aRect.iBr);   
}

// 两矩形是否相交
BOOL TMRect::IsIntersects(const TMRect& aRect) const
{
    BOOL rc = FALSE;

    if (m_iType==ECartesian)
    {
        rc = !(iTl.iY < aRect.iBr.iY || iBr.iX < aRect.iTl.iX ||
            iBr.iY > aRect.iTl.iY || iTl.iX > aRect.iBr.iX );
    }
    else
    {
        rc = !(iTl.iY > aRect.iBr.iY || iBr.iX < aRect.iTl.iX ||
            iBr.iY < aRect.iTl.iY || iTl.iX > aRect.iBr.iX );
    }

    return rc;

}

/************************************************************************

    In Decartesian  co-ordinates:

    假定矩形是用一对点表达的(minx,miny)(maxx,maxy)   
    那么两个矩形rect1{(minx1,miny1)(maxx1,   maxy1)},   rect2{(minx2,miny2)(maxx2,   maxy2)}   

    相交的结果一定是个矩形，构成这个相交矩形rect{(minx,miny)(maxx,   maxy)}的点对坐标是：   
    minx   =   max(minx1,   minx2)   
    miny   =   max(miny1,   miny2)   
    maxx   =   min(maxx1,   maxx2)   
    maxy   =   min(maxy1,   maxy2)   

    如果两个矩形不相交，那么计算得到的点对坐标必然满足   
    minx   >   maxx   
    或者   
    miny   >   maxy

/************************************************************************/
TMRect TMRect::Intersersects(const TMRect& aRect) const
{
    if (!IsIntersects(aRect))
    {
        // 不相交，返回空矩形
        return TMRect(0,0,0,0);
    }

    TMRect rect;

    rect.iTl.iX = max( Left(), aRect.Left() );
    rect.iBr.iX = min( Right(), aRect.Right() );

    if(m_iType==ECartesian)
    {
        rect.iBr.iY = max( Bottom(), aRect.Bottom() );
        rect.iTl.iY = min( Top(), aRect.Top() );
    }
    else if(m_iType==EPCScreen)
    {
        rect.iBr.iY = min( Bottom(), aRect.Bottom() );
        rect.iTl.iY = max( Top(), aRect.Top() );
    }

    return rect;
}


// 矩形与线段是否相交：分别判断矩形四个线段和目标线段是否相交
BOOL TMRect::IsIntersects(const TSegmentVector& aSegment) const
{    
    // 如果线段在矩形内，则相交
    if ( Contains(aSegment) )
    {
        return TRUE;
    }

    // TopLeft -> BottomLeft 
    TSegmentVector svTl2Bl(iTl,BottomLeft());
    if ( aSegment.IsIntersects(svTl2Bl) )
    {
        return TRUE;
    }

    // BottomLeft -> BottomRight
    TSegmentVector svBl2Br(BottomLeft(),iBr);
    if ( aSegment.IsIntersects(svBl2Br) )
    {
        return TRUE;
    }

    // BottomRight -> TopRight
    TSegmentVector svBr2Tr(iBr,TopRight());
    if ( aSegment.IsIntersects(svBr2Tr) )
    {
        return TRUE;
    }

    // TopRight -> TopLeft
    TSegmentVector svTr2Tl(TopRight(),iTl);
    if ( aSegment.IsIntersects(svTr2Tl) )
    {
        return TRUE;
    }

    return FALSE;
}

TMRect TMRect::UnionRect(const TMRect& aRect) const
{
    return (*this) + aRect;
}


void TMRect::Shrink(const TMSize& aSize)
{
    iTl.iX += aSize.iWidth;
    iBr.iX -= aSize.iWidth;

    if (m_iType==ECartesian)
    {
        iTl.iY -= aSize.iHeight;
        iBr.iY += aSize.iHeight;
    }
    else if(m_iType==EPCScreen)
    {
        iTl.iY += aSize.iHeight;
        iBr.iY -= aSize.iHeight;
    }
}
void TMRect::Shrink(float aMultiple)
{
    iTl.iX += Round(Width()*aMultiple);
    iBr.iX -= Round(Width()*aMultiple);

    if (m_iType==ECartesian)
    {
        iTl.iY -= Round(Height()*aMultiple);
        iBr.iY += Round(Height()*aMultiple);
    } 
    else if(m_iType==EPCScreen)
    {
        iTl.iY += Round(Height()*aMultiple);
        iBr.iY -= Round(Height()*aMultiple);
    }
}
void TMRect::Grow(const TMSize& aSize)
{
    iTl.iX -= aSize.iWidth;
    iBr.iX += aSize.iWidth;

    if (m_iType==ECartesian)
    {
        iTl.iY += aSize.iHeight;
        iBr.iY -= aSize.iHeight;
    }
    else if (m_iType==EPCScreen)
    {
        iTl.iY -= aSize.iHeight;
        iBr.iY += aSize.iHeight;
    }
}
void TMRect::Grow(float aMultiple)
{
    iTl.iX -= Round(Width()*aMultiple);
    iBr.iX += Round(Width()*aMultiple);

    if (m_iType==ECartesian)
    {
        iTl.iY += Round(Height()*aMultiple);
        iBr.iY -= Round(Height()*aMultiple);
    }
    else if (m_iType==EPCScreen)
    {
        iTl.iY -= Round(Height()*aMultiple);
        iBr.iY += Round(Height()*aMultiple);
    }
}
void TMRect::Rotate(TMPoint aAxisPt,float aRadian)
{
    TMPoint topRight = TopRight();
    TMPoint leftBottom = BottomLeft();

    topRight.Rotate(aAxisPt,aRadian);
    leftBottom.Rotate(aAxisPt,aRadian);
    iTl.Rotate(aAxisPt,aRadian);
    iBr.Rotate(aAxisPt,aRadian);

    CMPointVector ptArray;
    ptArray.push_back(topRight);
    ptArray.push_back(leftBottom);
    ptArray.push_back(iTl);
    ptArray.push_back(iBr);

    TMRect newRect(ptArray);
    iTl = newRect.iTl;
    iBr = newRect.iBr;

}
//////////////////////////////////////////////////////////////////////////
// TMPolygon
/*////////////////////////////////////////////////////////////////////////
1. 所谓凸多边形，就是把一个多边形任意一边向两方无限延长成为一条直线，如果多
   边形的其他各边均在此直线的同旁，那么这个多边形就叫做凸多边形，也可以理解为
   通过凸多边形的任意一条边作平面，并与此多边形所在的平面相异，那么凸多边形的
   其他所有部分都在所作平面的同一侧。

2. 凸多边形包含三角形和平面四边形。
*/////////////////////////////////////////////////////////////////////////
TMPolygon::TMPolygon()
{

}

TMPolygon::TMPolygon(const std::vector<TMPoint>& vertexes)
{
    m_Vertex = vertexes;
}

VOID TMPolygon::AddVertex(const TMPoint& aVertex)
{
    if (!IsVertex(aVertex))
    {
        m_Vertex.push_back(aVertex);
    }
}

// Add a edge.
VOID TMPolygon::AddEdge(const TSegmentVector& edge)
{
    AddVertex(edge.iStartPoint);
    AddVertex(edge.iEndPoint);
}

// Is this a polygon?
BOOL TMPolygon::IsValid() const
{
    return (m_Vertex.size()>=3);
}

/*/////////////////////////////////////////////////////////
1．凸多边形的内角均小于180°，边数为n（n为整数且n大于2）的
   凸多边形内角和为（n－2）×180°，但任意凸多边形外角和均
   为360°，并可通过反证法证明凸多边形内角中锐角的个数不能
   多于3个。

2．凸多边形所有对角线都在内部，边数为n的凸多边形对角线条数
   为n（n－3）／2，其中通过任一顶点可与其余n－3个顶点连对角
   线。
*///////////////////////////////////////////////////////////
// Is this a convex polygon?
BOOL  TMPolygon::IsConvex() const
{
    size_t iNum = m_Vertex.size();
    if (!IsValid())
    {
        return FALSE;
    }

    //
    DOUBLE fExceptSum = PIRADIAN*2;
    DOUBLE fActualSum = GetSumOfAngle(FALSE); // sum of outer angles.
    if (IsEqual(fActualSum,fExceptSum))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

// normalize to convex polygon.
BOOL TMPolygon::Normalize2Convex()
{
    size_t iNum = m_Vertex.size();
    if (iNum==3) // triangle
    {
        return TRUE;
    }

    // 中心点
    TMPoint ptCenter = Center();

    // 中心点与各顶点形成的向量与X正轴的夹角
    std::vector<DOUBLE> arrAngle;
    for (size_t i=0; i<iNum; i++)
    {
        TVector vTemp(ptCenter,m_Vertex[i]);
        DOUBLE fAngle = vTemp.Angle();
        arrAngle.push_back(fAngle);
    }

    // 比较夹角，重排序顶点
    std::vector<INT> arrIndex;
    Sort(arrAngle,arrIndex);
    std::vector<TMPoint> vertexTemp = m_Vertex;
    for (size_t j=0; j<iNum; j++)
    {
        TMPoint ptTemp = vertexTemp[arrIndex[j]];
        m_Vertex[j] = ptTemp;
    }

    // 
    return IsConvex();
}

// operations overrides
TMPolygon& TMPolygon::operator=(const TMPolygon& aOther)
{
    if (this!=&aOther)
    {
        this->m_Vertex = aOther.m_Vertex;
    }
    return *this;
}

// 质量中心
TMPoint TMPolygon::Center() const
{
    DOUBLE xSum = 0, ySum = 0;
    size_t iNum = m_Vertex.size();
    for (size_t i=0; i<iNum; i++)
    {
        xSum += m_Vertex[i].iX;
        ySum += m_Vertex[i].iY;
    }

    TLcType x = Round(xSum / iNum);
    TLcType y = Round(ySum / iNum);
    return TMPoint(x,y);
}

// 得到顶点个数
BYTE TMPolygon::GetNumVertex() const
{
    return (BYTE)(m_Vertex.size());
}


// Get the sum of angles.
DOUBLE TMPolygon::GetSumOfAngle(BOOL bInner /*= FALSE*/) const
{
    DOUBLE fSum = 0;

    // get all edges.
    std::vector<TSegmentVector> edges;
    GetEdges(edges);

    // 
    size_t iNum = edges.size();
    if (iNum>=2)
    {
        TSegmentVector edgeStart = edges[0];

        // 
        BOOL bClockwise = IsClockwise();

        DOUBLE fAngle = 0; // angle made with neighboring edge.
        TLcType crossProduct = 0; // cross product
        
        for (size_t iIndex = 1; iIndex<iNum; iIndex++)
        {
            fAngle = edgeStart.Angle(edges[iIndex]);
            if (bInner)
            {
                crossProduct = edgeStart.GetVector() * edges[iIndex].GetVector();
                if ( (!bClockwise && crossProduct>0)
                    || (bClockwise && crossProduct<0) )
                {
                    fSum += (PIRADIAN-fAngle);
                }
                else if ( (!bClockwise && crossProduct<0) ||
                           (bClockwise && crossProduct>0) )
                {
                    fSum += (PIRADIAN+fAngle);
                }
                else
                {
                    // do nothing
                }
            }
            else
            {
                fSum += fAngle;
            }

            edgeStart = edges[iIndex];
        }

        fSum += edgeStart.Angle(edges[0]);
    }

    return fSum;
}

// Get all edges.
VOID TMPolygon::GetEdges(std::vector<TSegmentVector>& edges) const
{
    if (!IsValid())
    {
        return;
    }

    size_t iNum = m_Vertex.size();

    // 
    TMPoint ptStart = m_Vertex[0];
    size_t i = 1;
    for (; i<iNum; i++)
    {
        TSegmentVector edgeItem(ptStart,m_Vertex[i]);
        edges.push_back(edgeItem);
        ptStart = m_Vertex[i];
    }

    edges.push_back(TSegmentVector(ptStart,m_Vertex[0]));
}

// get the external rectangular.
BOOL TMPolygon::GetExternalRect(TMRect& rectExternal) const
{
    if (!IsValid())
    {
        return FALSE;
    }

    size_t number = m_Vertex.size();

    TMPoint element = m_Vertex[0];
    TLcType minX,maxX,minY,maxY;
    minX = maxX = element.iX;
    minY = maxY = element.iY;

    for (size_t i=1; i<number; i++)
    {
        element = m_Vertex[i];
        if (element.iX<minX)
        {
            minX = element.iX;
        }
        else if (element.iX>maxX)
        {
            maxX = element.iX;
        }

        if (element.iY<minY)
        {
            minY = element.iY;
        }
        else if (element.iY>maxY)
        {
            maxY = element.iY;
        }
    }

    rectExternal.iTl.iX = minX;
    rectExternal.iTl.iY = maxY;
    rectExternal.iBr.iX = maxX;
    rectExternal.iBr.iY = minY;

    return TRUE;
}

// to HRGN
HRGN TMPolygon::ToHRGN() const
{
    INT iNum = GetNumVertex();
    if (iNum<=0)
    {
        return NULL;
    }

    //
    return ::CreatePolygonRgn((POINT*)(&(m_Vertex[0])),iNum,ALTERNATE);
}

// Is the given Point a vertex?
BOOL  TMPolygon::IsVertex(const TMPoint& aPoint) const
{
    size_t iNum = m_Vertex.size();

    for (size_t i=0; i<iNum; i++)
    {
        if (m_Vertex[i]==aPoint)
        {
            return TRUE;
        }
    }

    return FALSE;
}


// Determines whether the specified point lies within the polygon.
BOOL TMPolygon::Contains(const TMPoint& aPoint) const
{
    TMRect rectExternal;
    if (!GetExternalRect(rectExternal))
    {
        return FALSE;
    }

    // 首先计算多边形的外包矩形，判断点是否落在外包矩形内，只有满足落在
    // 外包矩形内的条件的点，才进入下一步的计算。
    if (!rectExternal.Contains(aPoint))
    {
        return FALSE;
    }

    // 当点满足落在多边形外包矩形内的条件，要进一步判断点(O)是否在多边形(POLYGON)内。
    // 采用射线法，由待测试点(O)引出一条水平射线R，计算R与多边线的交点数目，记为N，根
    // 据奇内偶外原则(N为奇数说明O在P内，否则O不在P内)判断点是否在多边形内。 
    // 特殊情况1: 点在边上（TRUE）。
    // 特殊情况2: 射线与边平行（不作判断）。
    // 特殊情况3: 边的一个顶点在射线上。

    // build rays
    TLcType raysLen = rectExternal.Width() + rectExternal.Height();
    TMPoint raysEnd(aPoint.iX+raysLen,aPoint.iY);
    TSegmentVector rays(aPoint,raysEnd);
    //rays.Rotate(aPoint,PIRADIAN/4);

    // get all edges.
    std::vector<TSegmentVector> edges;
    GetEdges(edges);

    // the number of intersection point.
    INT nNumPoint = 0;

    // 
    size_t iNum = edges.size();
    for (size_t i=0; i<iNum; i++)
    {
        // 特殊情况1
        if (edges[i].PointInSegment(aPoint,FALSE))
        {
            return TRUE;
        }

        // 特殊情况2
        if(edges[i].IsHorizontal(rays))
        {
            continue;
        }
        
        // 特殊情况3
        if (rays.PointInSegment(edges[i].iStartPoint))
        {
            if (edges[i].iStartPoint.iY>edges[i].iEndPoint.iY)
            {
                nNumPoint ++;
            }
        }
        else if (rays.PointInSegment(edges[i].iEndPoint)) // 特殊情况3
        {
            if (edges[i].iEndPoint.iY>edges[i].iStartPoint.iY)
            {
                nNumPoint ++;
            }
        }
        else // 通常情况
        {
            if (rays.IsIntersects(edges[i]))
            {
                nNumPoint ++;
            }
        }        
    }
    return (nNumPoint%2);
}

//////////////////////////////////////////////////////////////////////////
// is the circle clockwise?
BOOL TMPolygon::IsClockwise() const
{
    // get all edges.
    std::vector<TSegmentVector> edges;
    GetEdges(edges); 

    //
    TMPoint ptCenter = Center();

    size_t iNum = edges.size();
    for (size_t iIndex = 0; iIndex<iNum; iIndex++)
    {
        TSegmentVector V1(ptCenter,edges[iIndex].iStartPoint);
        TSegmentVector V2(edges[iIndex].iEndPoint,ptCenter);
        TLcType product = V1.GetVector()*V2.GetVector();
        if (product>0)
        {
            return TRUE;
        }
        else if (product<0)
        {
            return FALSE;
        }
        else
        {
            continue;
        }
    }

    return FALSE;
}

//////////////////////////////////////////////////////////////////////////
struct TAngleValue
{
    DOUBLE  fAngle;
    INT     iIndex;
};
VOID TMPolygon::Sort( const std::vector<DOUBLE>& arrValue,
                      std::vector<INT>& arrIndex) const
{

    std::vector<TAngleValue> arrAngleValue;

    // 
    INT i = 0;
    INT iNum = (INT)arrValue.size();
    for (i=0; i<iNum; i++)
    {
        TAngleValue value = {arrValue[i],i};
        arrAngleValue.push_back(value);
    }
    
    // Sort
    for (i=0; i<iNum-1; i++)
    {
        for (INT j=i+1; j<iNum; j++)
        {
            if (arrAngleValue[j].fAngle<arrAngleValue[i].fAngle)
            {
                TAngleValue value = arrAngleValue[j];
                arrAngleValue[j] = arrAngleValue[i];
                arrAngleValue[i] = value;
            }
        }
    }

    // 
    for (i=0; i<iNum; i++)
    {
        arrIndex.push_back(arrAngleValue[i].iIndex);
    }
}