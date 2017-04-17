

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

	// X����Y��������ģ
	T Vx() const
	{
		return iEndPoint.iX - iStartPoint.iX;
	}
	T Vy() const
	{
		return iEndPoint.iY - iStartPoint.iY;
	}

	// �����߶εĳ���
	DOUBLE GetLength() const
	{
		return iStartPoint.Distance(iEndPoint);
	}

	// �����߶ε����ĵ�
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

	// �߶�ƽ��
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

	// ���߶��Ƿ�ƽ��
	BOOL  IsHorizontal(const CTypedSegmentVector<T>& aOther) const
	{
		CTypedVector<T> unitV1 = GetVector();
		CTypedVector<T> unitV2 = aOther.GetVector();

		return unitV1.IsHorizontal(unitV2);
	}

	// ���߶��Ƿ�ֱ
	BOOL  IsVertical(const CTypedSegmentVector<T>& aOther) const
	{
		CTypedVector<T> unitV1 = GetVector();
		CTypedVector<T> unitV2 = aOther.GetVector();

		return unitV1.IsVertical(unitV2);

	}

	// �߶��Ƿ��ཻ ( �ж��߶�AB���߶�CD[��CD�����ֱ��]�Ƿ��ཻ )
	// �ཻ��������
	BOOL  IsIntersects(const CTypedSegmentVector<T>& aOther,
		BOOL bLine=FALSE) const
	{
		/************************************************************************

		1���ж����߶��Ƿ��ཻ��

		������ȷ�������߶��Ƿ��ཻ��

		(1) �����ų�����
		�����߶� P1P2 Ϊ�Խ��ߵľ���ΪR�� �����߶� Q1Q2 Ϊ�Խ��ߵľ���ΪT��
		���R��T���ཻ����Ȼ���߶β����ཻ��

		(2) �������� ������߶��ཻ�������߶α�Ȼ�໥�����Է�����P1P2����Q1Q2 ��
		��ʸ�� (P1 - Q1) ��(P2 - Q1)λ��ʸ��( Q2 - Q1 ) �����࣬
		��( P1 - Q1 ) �� ( Q2 - Q1 ) * ( P2 - Q1 ) �� ( Q2 - Q1 ) < 0��
		��ʽ�ɸ�д��( P1 - Q1 ) �� ( Q2 - Q1 ) * ( Q2 - Q1 ) �� ( P2 - Q1 ) > 0��
		�� ( P1 - Q1 ) �� ( Q2 - Q1 ) = 0 ʱ��˵�� ( P1 - Q1 ) �� ( Q2 - Q1)���ߣ�
		������Ϊ�Ѿ�ͨ�������ų����飬���� P1 һ�����߶� Q1Q2�ϣ�ͬ��
		( Q2 - Q1 ) ��(P2 - Q1 ) = 0 ˵�� P2 һ�����߶� Q1Q2�ϡ�

		�����ж�P1P2����Q1Q2�������ǣ�
		( P1 - Q1 ) �� ( Q2 - Q1 ) * ( Q2 - Q1 ) �� ( P2 - Q1 ) >= 0��

		ͬ���ж�Q1Q2����P1P2�������ǣ�
		( Q1 - P1 ) �� ( P2 - P1 ) * ( P2 - P1 ) �� ( Q2 - P1 ) >= 0��


		2���ж��߶κ�ֱ���Ƿ��ཻ


		����߶� P1P2��ֱ��Q1Q2�ཻ����P1P2����Q1Q2������

		( P1 - Q1 ) �� ( Q2 - Q1 )  *  ( Q2 - Q1 ) �� ( P2 - Q1 )  >=  0


		����߶� Q1Q2��ֱ��P1P2�ཻ����Q1Q2����P1P2������

		( Q1 - P1 ) �� ( P2 - P1 ) * ( P2 - P1 ) �� ( Q2 - P1 ) >= 0��


		/************************************************************************/

		CTypedPoint<T> P1 = iStartPoint;
		CTypedPoint<T> P2 = iEndPoint;
		CTypedPoint<T> Q1 = aOther.iStartPoint;
		CTypedPoint<T> Q2 = aOther.iEndPoint;

		if (!bLine)
		{
			CTypedRect<T> rect1(iStartPoint,iEndPoint);
			CTypedRect<T> rect2(aOther.iStartPoint,aOther.iEndPoint);

			// (1) �����ų�����
			if (!rect1.IsIntersects(rect2))
			{
				return FALSE;
			}

			// (2) ��������

			// �ж�P1P2����Q1Q2
			T r1 = ((P1-Q1)*(Q2-Q1));
			T r2 = ((Q2-Q1)*(P2-Q1));
			if (r1<0 && r2>0 || r1>0 && r2<0)
			{
				return FALSE;
			}

			// �ж�Q1Q2����P1P2
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

	// �������߶εĽ���
	// Return: ���ཻ����FALSE
	// bLine = TRUE ��ʾ������ֱ�ߵĽ��㣬����������߶εĽ���
	BOOL  CalcIntersection(const CTypedSegmentVector<T>& aOther,
		CTypedPoint<T>& ptCross,
		BOOL bLine=FALSE) const
	{  
		// ��ƽ�У�����FASLE
		if (IsHorizontal(aOther))
		{
			return FALSE;
		}

		// ������߶β��ཻ������FALSE 
		if (!IsIntersects(aOther,bLine))
		{
			return FALSE;
		}

		// �ཻ��������ཻ��
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


	// �����߶ε�������ʾ
	CTypedVector<T> GetVector() const
	{
		return CTypedVector<T>(iEndPoint.iX-iStartPoint.iX,iEndPoint.iY-iStartPoint.iY);
	}

	// ���ط�λ��( �������ļнǣ���Χ[0,2��] )
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


			// ��һ����
			if (detalX>0 && detalY>0)
			{
				//azimuth = (float)atanl(float(detalY)/float(detalX));
				return PIRADIAN/2-azimuth;
			}

			// �ڶ�����
			else if (detalX<0 && detalY>0)
			{
				//azimuth = (float)atanl(float(detalY)/float(-detalX));
				return 3*PIRADIAN/2+azimuth;
			}

			// ��������
			else if (detalX<0 && detalY<0)
			{
				//azimuth = (float)atanl(float(-detalY)/float(-detalX));
				return PIRADIAN*3/2-azimuth;
			}

			// ��������
			else 
			{
				//azimuth = (float)atanl(float(-detalY)/float(detalX));
				return PIRADIAN/2+azimuth;
			}

		}
	}

	// �õ�����㳤��ΪLen�ĵ�����(ָ�����ȴ����߶ε�ģʱ������FALSE)
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
	�������жϵ�A�Ƿ����߶���
	aPoint: ��A
	bExtendLine: �Ƿ��жϵ����߶ε��ӳ�����
	*/
	BOOL PointInSegment(const CTypedPoint<T>& aPoint,BOOL bExtendLine=FALSE) const
	{
		/************************************************************************

		���ΪQ���߶�ΪP1P2 �� �жϵ�Q�ڸ��߶��ϵ������ǣ�
		( Q - P1 ) �� ( P2 - P1 ) = 0 �� Q ���� P1��P2Ϊ�ԽǶ���ľ����ڡ�

		ǰ�߱�֤Q����ֱ��P1P2�ϣ������Ǳ�֤Q�㲻���߶�P1P2���ӳ��߻����ӳ�����

		******************************************************************************/
		T x,y,x0,y0,x1,y1;
		x = aPoint.iX;
		y = aPoint.iY;
		x0 = iStartPoint.iX;
		y0 = iStartPoint.iY;
		x1 = iEndPoint.iX;
		y1= iEndPoint.iY;

		T aResult = abs((y-y0)*(x1-x0)-(y1-y0)*(x-x0));

		// �㲻��ֱ����
		if (aResult!=0)
		{
			return FALSE;
		}
		else
		{
			// ����ֱ����
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


	// ���ݷ�λ�ǡ���ʼ�����߼����ȹ�����������������aStartPt��㣬����ΪaLogicLen���߼���λ����λ��ΪaAzimuth
	// aAngle : ��λ�ǣ�����������ļнǣ���in radian.
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
		EPP_INSEGMENT = 0,      // ���߶���
		EPP_OFFSETSTART = 5,    // ���߶�������
		EPP_OFFSETEND,          // ���߶��յ����
	};
	// ���ͶӰ���߶��ϵ�λ��
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
			return EPP_INSEGMENT; // ͶӰ��������غ�
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
			return EPP_INSEGMENT; // ͶӰ�����յ��غ�
		}

		return EPP_INSEGMENT;
	}

	// �㵽�߶εľ���
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
	������ �ӵ�Q���߶�AB�Ĵ��ߣ�����ΪO��
	���أ� <0 ��ʾ��P��ͶӰ�����߶�AB�ϣ��޴��㡣>=0 ���ش��߶γ����Լ����㡣
	*/
	DOUBLE  Plumbline(CTypedPoint<T> aPointQ,CTypedPoint<T>& aCrossPt) const
	{
		// �Ƿ�Ϊ������
		if (GetVector().IsZeroVector())
		{
			return -1;
		}

		// ���ͶӰ�Ƿ����߶���
		if (ProjectionPosition(aPointQ)!=EPP_INSEGMENT)
		{
			return -1;
		}

		// ���Ƿ�������
		if (PointInSegment(aPointQ))
		{
			aCrossPt = aPointQ;
			return 0;
		}

#ifdef _NEW_PLUMBINE


		T dx = Vx();
		T dy = Vy();

		T aa = GetVector() & CTypedVector<T>(aPointQ,iStartPoint); // ����� aa = AB*PA
		T bb = dx*dx + dy*dy;

		DOUBLE fDistance = fabs(aa/sqrt(DOUBLE(bb)));

		aCrossPt.iX = Round<T>(aPointQ.iX - DOUBLE(dy*aa)/bb);
		aCrossPt.iY = Round<T>(aPointQ.iY + DOUBLE(dx*aa)/bb);

		return fDistance;

#else   

		/************************************************************************/
		/* ���㷨Ч�ʽϵ�,�����Եõ�����                                        */
		/************************************************************************/
		DOUBLE nUpX,nUpY;  //����ֱ�ߴ�ֱ�ཻ�Ľ���
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
				// ����p1p2��б��
				double k1 = (double)(iEndPoint.iY - iStartPoint.iY) / (double)(iEndPoint.iX - iStartPoint.iX);
				// ���ߵ�б��
				double k2 = (double)-1 / k1;
				// ����ֱ�߹�ʽ���㴹��
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
		if(nUpX < nMinX || nUpX >nMaxX ||nUpY <nMinY||nUpY>nMaxY)  // ����δ�����߶���
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

	// ���߶εļн�(�û��ȱ�ʾ����Χ [0,��])
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
