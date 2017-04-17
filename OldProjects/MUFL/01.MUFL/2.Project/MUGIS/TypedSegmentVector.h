

#ifndef _TYPED_SEGMENT_VECTOR_H_
#define _TYPED_SEGMENT_VECTOR_H_




namespace Mugis
{

/////////////////////// Template CTypedSegmentVector ///////////////////////////////////

template<class T>
class CTypedSegmentVector
{

public:

	typedef T value_type;

	CTypedSegmentVector()
	{
		iStartPoint.iX = 0;
		iStartPoint.iY = 0;
		iEndPoint.iX = 0;
		iEndPoint.iY = 0;
	}

	CTypedSegmentVector(const CTypedPoint<T>& ptEnd)
	{
		iStartPoint.iX = 0;
		iStartPoint.iY = 0;
		iEndPoint.iX = ptEnd.iX;
		iEndPoint.iY = ptEnd.iY;
	}
	CTypedSegmentVector(POINT aStart,POINT aEnd)
	{
		iStartPoint.iX = aStart.x;
		iStartPoint.iY = aStart.y;
		iEndPoint.iX = aEnd.x;
		iEndPoint.iY = aEnd.y;
	}
	CTypedSegmentVector(CTypedPoint<T> aStartPt,CTypedPoint<T> aEndPt)
	{
		iStartPoint = aStartPt;
		iEndPoint = aEndPt;
	}
	~CTypedSegmentVector()
	{

	}

public:

	// X轴与Y轴向量的模
	T Vx() const
	{
		return iEndPoint.iX - iStartPoint.iX;
	}
	T Vy() const
	{
		return iEndPoint.iY - iStartPoint.iY;
	}

	// 计算线段的长度
	DOUBLE GetLength() const
	{
		return iStartPoint.Distance(iEndPoint);
	}

	// 计算线段的中心点
	CTypedPoint<T> GetCenterPt() const
	{
		CTypedPoint<T> pt;
		pt.iX = iStartPoint.iX+Vx()/2;
		pt.iY = iStartPoint.iY+Vy()/2;
		return pt;
	}

	CTypedSegmentVector<T>& operator=(const CTypedSegmentVector<T>& aOther)
	{
		if (this!=&aOther)
		{
			iStartPoint = aOther.iStartPoint;
			iEndPoint = aOther.iEndPoint;
		}
		return *this;
	}

	// 线段平移
	void Move(CTypedVector<T> aVector)
	{
		iStartPoint += aVector;
		iEndPoint += aVector;
	}

	// 
	TVectorDirect GetDirection(TDirectCategory aType=EDT_FOURE) const
	{
		if (iStartPoint.iX==iEndPoint.iX && iStartPoint.iY==iEndPoint.iY)
		{
			return EVD_INVALID;
		}
		else 
		{
			T h = Vy();
			T l = Vx();

			CTypedRect<T> newRect;
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

	// 两线段是否平行
	BOOL  IsHorizontal(const CTypedSegmentVector<T>& aOther) const
	{
		CTypedVector<T> unitV1 = GetVector();
		CTypedVector<T> unitV2 = aOther.GetVector();

		return unitV1.IsHorizontal(unitV2);
	}

	// 两线段是否垂直
	BOOL  IsVertical(const CTypedSegmentVector<T>& aOther) const
	{
		CTypedVector<T> unitV1 = GetVector();
		CTypedVector<T> unitV2 = aOther.GetVector();

		return unitV1.IsVertical(unitV2);

	}

	// 线段是否相交 ( 判断线段AB与线段CD[或CD定义的直线]是否相交 )
	// 相交包含共线
	BOOL  IsIntersects(const CTypedSegmentVector<T>& aOther,
		BOOL bLine=FALSE) const
	{
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

		CTypedPoint<T> P1 = iStartPoint;
		CTypedPoint<T> P2 = iEndPoint;
		CTypedPoint<T> Q1 = aOther.iStartPoint;
		CTypedPoint<T> Q2 = aOther.iEndPoint;

		if (!bLine)
		{
			CTypedRect<T> rect1(iStartPoint,iEndPoint);
			CTypedRect<T> rect2(aOther.iStartPoint,aOther.iEndPoint);

			// (1) 快速排斥试验
			if (!rect1.IsIntersects(rect2))
			{
				return FALSE;
			}

			// (2) 跨立试验

			// 判断P1P2跨立Q1Q2
			T r1 = ((P1-Q1)*(Q2-Q1));
			T r2 = ((Q2-Q1)*(P2-Q1));
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
			T r1 = ((P1-Q1)*(Q2-Q1));
			T r2 = ((Q2-Q1)*(P2-Q1));
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

	// 计算两线段的交点
	// Return: 不相交返回FALSE
	// bLine = TRUE 表示计算两直线的交点，否则计算两线段的交点
	BOOL  CalcIntersection(const CTypedSegmentVector<T>& aOther,
		CTypedPoint<T>& ptCross,
		BOOL bLine=FALSE) const
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
		T X1 = iStartPoint.iX;
		T Y1 = iStartPoint.iY;
		T X2 = iEndPoint.iX;
		T Y2 = iEndPoint.iY;
		T X3 = aOther.iStartPoint.iX;
		T Y3 = aOther.iStartPoint.iY;
		T X4 = aOther.iEndPoint.iX;
		T Y4 = aOther.iEndPoint.iY;

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

		ptCross.iX = Round<T>(X0);
		ptCross.iY = Round<T>(Y0);

		// 
		return TRUE;
	}


	// 返回线段的向量表示
	CTypedVector<T> GetVector() const
	{
		return CTypedVector<T>(iEndPoint.iX-iStartPoint.iX,iEndPoint.iY-iStartPoint.iY);
	}

	// 返回方位角( 与正北的夹角，范围[0,2π] )
	DOUBLE GetAzimuth() const
	{

		T detalX = iEndPoint.iX - iStartPoint.iX;
		T detalY = iEndPoint.iY - iStartPoint.iY;

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

	// 得到离起点长度为Len的点坐标(指定长度大于线段的模时，返回FALSE)
	BOOL  GetRemotePoint(CTypedPoint<T>& ptArg, DOUBLE fRemoteLen) const
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

			ptArg.iX = Round<T>(iStartPoint.iX + fDeltaX);
			ptArg.iY = Round<T>(iStartPoint.iY + fDeltaY);
		}

		//
		return TRUE;
	}

public:

	// Rotate clockwise.
	void Rotate(CTypedPoint<T> aAxisPt,float aRadian)
	{
		iStartPoint.Rotate(aAxisPt,aRadian);
		iEndPoint.Rotate(aAxisPt,aRadian);
	} 

	/** 
	描述：判断点A是否在线段上
	aPoint: 点A
	bExtendLine: 是否判断点在线段的延长线上
	*/
	BOOL PointInSegment(const CTypedPoint<T>& aPoint,BOOL bExtendLine=FALSE) const
	{
		/************************************************************************

		设点为Q，线段为P1P2 。 判断点Q在该线段上的依据是：
		( Q - P1 ) × ( P2 - P1 ) = 0 且 Q 在以 P1，P2为对角顶点的矩形内。

		前者保证Q点在直线P1P2上，后者是保证Q点不在线段P1P2的延长线或反向延长线上

		******************************************************************************/
		T x,y,x0,y0,x1,y1;
		x = aPoint.iX;
		y = aPoint.iY;
		x0 = iStartPoint.iX;
		y0 = iStartPoint.iY;
		x1 = iEndPoint.iX;
		y1= iEndPoint.iY;

		T aResult = abs((y-y0)*(x1-x0)-(y1-y0)*(x-x0));

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
				CTypedRect<T> rect(iStartPoint,iEndPoint);
				return rect.Contains(aPoint);
			}
		}        
	}


	// 根据方位角、起始点与逻辑长度构造向量。此向量以aStartPt起点，长度为aLogicLen个逻辑单位，方位角为aAzimuth
	// aAngle : 方位角（与正北方向的夹角），in radian.
	static CTypedSegmentVector<T> BuildSegment(CTypedPoint<T> aStartPt,float aAzimuth,LONG aLogicLen=1000)
	{
		float sinA,cosA;
		sinA = sin(aAzimuth);
		cosA = cos(aAzimuth);

		CTypedPoint<T> endPt;
		endPt.iX = Round<T>(aLogicLen*sinA + aStartPt.iX);
		endPt.iY = Round<T>(aLogicLen*cosA + aStartPt.iY);

		CTypedSegmentVector<T> newVector(aStartPt,endPt);

		return newVector;
	} 

public:

	enum TProjectionPos
	{
		EPP_INSEGMENT = 0,      // 在线段上
		EPP_OFFSETSTART = 5,    // 在线段起点外侧
		EPP_OFFSETEND,          // 在线段终点外侧
	};
	// 点的投影在线段上的位置
	int  ProjectionPosition(CTypedPoint<T> aPt) const
	{
		CTypedVector<T> AO(iStartPoint,aPt);
		CTypedVector<T> AB = GetVector();
		T product = AO.DotProduct(AB);
		if (product<0)
		{
			return EPP_OFFSETSTART;
		}
		else if (product==0)
		{
			return EPP_INSEGMENT; // 投影点与起点重合
		}

		CTypedVector<T> BO(iEndPoint,aPt);
		CTypedVector<T> BA(iEndPoint,iStartPoint);
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
	DOUBLE  Distance(CTypedPoint<T> aPoint) const
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

	/*
	描述： 从点Q作线段AB的垂线，垂足为O。
	返回： <0 表示点P的投影不在线段AB上，无垂足。>=0 返回垂线段长度以及垂足。
	*/
	DOUBLE  Plumbline(CTypedPoint<T> aPointQ,CTypedPoint<T>& aCrossPt) const
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
			aCrossPt = aPointQ;
			return 0;
		}

#ifdef _NEW_PLUMBINE


		T dx = Vx();
		T dy = Vy();

		T aa = GetVector() & CTypedVector<T>(aPointQ,iStartPoint); // 外积： aa = AB*PA
		T bb = dx*dx + dy*dy;

		DOUBLE fDistance = fabs(aa/sqrt(DOUBLE(bb)));

		aCrossPt.iX = Round<T>(aPointQ.iX - DOUBLE(dy*aa)/bb);
		aCrossPt.iY = Round<T>(aPointQ.iY + DOUBLE(dx*aa)/bb);

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

			nMinDist= aPointQ.Distance(CTypedPoint<T>(Round<T>(nUpX),Round<T>(nUpY)));
		}
		else
		{
			nMinDist= aPointQ.Distance(CTypedPoint<T>(Round<T>(nUpX),Round<T>(nUpY)));
		}

		aCrossPt.iX = Round<T>(nUpX);
		aCrossPt.iY = Round<T>(nUpY);

		return nMinDist;
#endif
	}

public:

	// 两线段的夹角(用弧度表示，范围 [0,π])
	DOUBLE Angle(const CTypedSegmentVector<T>& aOther) const
	{
		CTypedVector<T> unitV1 = GetVector();
		CTypedVector<T> unitV2 = aOther.GetVector();

		DOUBLE angle = unitV1.Angle(unitV2);

		return angle;
	}

public:

	CTypedPoint<T>  iStartPoint;
	CTypedPoint<T>  iEndPoint;
};
}
//////////////////////////////////////////////////////////////////////////
#endif
