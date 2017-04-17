

#ifndef _TYPED_RECT_H_
#define _TYPED_RECT_H_


namespace Mugis
{

	///////////////// Template CTypedRect ////////////////////////////////

	//  valid under Cartesian coordinates && Screen coordinates
	template<class T>
	class CTypedRect
	{

	public:

		typedef T value_type;

		CTypedRect()
		{
			iTl.iX = 0;
			iTl.iY = 1;
			iBr.iX = 1;
			iBr.iY = 0;
		}

		~CTypedRect(){};

		CTypedRect(T aTLx,T aTLy,T aBRx,T aBRy)// 根据左上角与右下角点构造
		{
			iTl.iX = aTLx;
			iTl.iY = aTLy;

			iBr.iX = aBRx;
			iBr.iY = aBRy;
		}

		CTypedRect(const CTypedPoint<T>& aDiagonalPt1,const CTypedPoint<T>& aDiagonalPt2) // 根据对角点构造
		{

			iTl = aDiagonalPt1;
			iBr = aDiagonalPt2;

			NormalizeRect( );

		}

		CTypedRect(const CTypedPoint<T>& aTl,CTypedSize<T> aSize)// TopLeft ＋ Size
		{
			iTl = aTl;
			iBr.iX = aTl.iX + aSize.iWidth;
			iBr.iY = aTl.iY - aSize.iHeight;
		}

		CTypedRect(const CTypedPoint<T>& aCenter,T aWidth,T aHeight)// Center + width +height
		{

			iTl.iX = aCenter.iX - aWidth/2;
			iBr.iX = aCenter.iX + aWidth/2;
			iTl.iY = aCenter.iY + aHeight/2;
			iBr.iY = aCenter.iY - aHeight/2;
		}

		CTypedRect(const std::vector<CTypedPoint<T>>& aPloygon)  // 构造多边形的外接矩形
		{
			//
			INT_PTR number = aPloygon.size();
			if (number<2)
			{
				return;
			}

			CTypedPoint<T> element = aPloygon[0];
			T minX,maxX,minY,maxY;
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


			iTl.iX = minX;
			iBr.iX = maxX;
			iTl.iY = maxY;
			iBr.iY = minY;

		}


		CTypedRect(const CArray<CTypedPoint<T>,CTypedPoint<T>>& aPloygon)  // 构造多边形的外接矩形
		{
			INT_PTR number = aPloygon.GetSize();
			if (number<2)
			{
				return;
			}

			CTypedPoint<T> element = aPloygon[0];
			T minX,maxX,minY,maxY;
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


			iTl.iX = minX;
			iBr.iX = maxX;
			iTl.iY = maxY;
			iBr.iY = minY;
		}

		// New methods
	public:

		// Normalizes CRect so that both the height and width are positive.
		void NormalizeRect( )
		{
			T lpX = min(iTl.iX,iBr.iX);
			T brX = max(iTl.iX,iBr.iX);
			T lpY = max(iTl.iY,iBr.iY);
			T brY = min(iTl.iY,iBr.iY);
			iTl.iX = lpX;
			iBr.iX = brX;
			iTl.iY = lpY;
			iBr.iY = brY;
		}

		// operations overrides
		CTypedRect<T>& operator=(const CTypedRect<T>& aOther)
		{
			if (this != &aOther)
			{
				iTl.iX = aOther.iTl.iX;
				iTl.iY = aOther.iTl.iY;
				iBr.iX = aOther.iBr.iX;
				iBr.iY = aOther.iBr.iY;
			}
			return *this;
		}
		friend CTypedRect<T> operator+(CTypedRect<T> aRect1,CTypedRect<T> aRect2)
		{
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
				T lpX = min(aRect1.iTl.iX,aRect2.iTl.iX);
				T brX = max(aRect1.iBr.iX,aRect2.iBr.iX);
				T lpY = max(aRect1.iTl.iY,aRect2.iTl.iY);
				T brY = min(aRect1.iBr.iY,aRect2.iBr.iY);
				return CTypedRect<T>(lpX,lpY,brX,brY);
			}

		}
		void operator+=(const CTypedRect<T>& aRect)
		{
			*this = *this + aRect;
		}
		void operator-=(CTypedSize<T> size)
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

		// CRect operation
		void Copy(CRect aOther)
		{
			iTl.iX = aOther.left;
			iTl.iY = aOther.top;
			iBr.iX = aOther.right;
			iBr.iY = aOther.bottom;
			NormalizeRect();
		}
		void GetRect(CRect& aNewRect) const
		{
			aNewRect.left = LONG(iTl.iX);
			aNewRect.top = LONG(iTl.iY);
			aNewRect.right = LONG(iBr.iX);
			aNewRect.bottom = LONG(iBr.iY);
			aNewRect.NormalizeRect();
		}
		RECT    ToRECT() const
		{
			RECT aNewRect;
			aNewRect.left   = min(LONG(iTl.iX),LONG(iBr.iX));
			aNewRect.top    = min(LONG(iTl.iY),LONG(iBr.iY));
			aNewRect.right  = max(LONG(iTl.iX),LONG(iBr.iX));
			aNewRect.bottom = max(LONG(iTl.iY),LONG(iBr.iY));

			return aNewRect;
		}

		// Attributes
		T Top() const
		{
			return iTl.iY;
		}
		T Bottom() const
		{
			return iBr.iY;
		}
		T Left() const
		{
			return iTl.iX;
		}
		T Right() const
		{
			return iBr.iX;
		}

		CTypedPoint<T> TopRight() const
		{
			return CTypedPoint<T>(iBr.iX,iTl.iY);
		}
		CTypedPoint<T> BottomLeft() const
		{
			return CTypedPoint<T>(iTl.iX,iBr.iY);
		}

		CTypedPoint<T> Center() const
		{
			T x = iTl.iX + (iBr.iX - iTl.iX)/2;
			T y = iBr.iY + (iTl.iY - iBr.iY)/2;
			return CTypedPoint<T>(x,y);
		}

		T Width() const
		{
			return abs(iBr.iX-iTl.iX);
		}
		T Height() const
		{
			return abs(iTl.iY-iBr.iY);
		}

		void GetLocation(CTypedPoint<T>* aPt) const
		{
			if (aPt!=NULL)
			{
				*aPt = iTl;
			}
		}

		// Is valid
		BOOL IsValid() const
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

		// Determines whether CTypedRect is empty. CTypedRect is empty if the width and/or height are 0.
		BOOL IsEmpty() const
		{
			return (Width()==0 || Height()==0);
		}

		// Determines whether the top, bottom, left, and right member variables are all equal to 0.
		BOOL IsNull() const
		{
			return (Left()==0 && Right()==0 && Top()==0 && Bottom()==0);
		}
		void SetNull()
		{
			iTl.iX = iTl.iY = 0;
			iBr.iX = iBr.iY = 0;
		}

		// Move
		void MoveAlongVector(const CTypedVector<T>& aVector)
		{
			T x = aVector.m_lHx;
			T y = aVector.m_lVy;

			iTl.iX += x;
			iTl.iY += y;

			iBr.iX += x;
			iBr.iY += y;
		}
		void MoveLeft(T aLen)
		{
			iTl.iX -= aLen;
			iBr.iX -= aLen;
		}
		void MoveRight(T aLen)
		{
			iTl.iX += aLen;
			iBr.iX += aLen;
		}
		void MoveTop(T aLen)
		{
			iTl.iY += aLen;
			iBr.iY += aLen;
		}
		void MoveBottom(T aLen)
		{
			iTl.iY -= aLen ;
			iBr.iY -= aLen ;
		}
		void Offset(CTypedPoint<T> aPt)
		{
			iTl.iX += aPt.iX;
			iBr.iX += aPt.iX;

			iTl.iY += aPt.iY;
			iBr.iY += aPt.iY;
		}

		// Inflate && Deflate
		void Shrink(const CTypedSize<T>& aSize)
		{
			iTl.iX += aSize.iWidth;
			iBr.iX -= aSize.iWidth;

			iTl.iY -= aSize.iHeight;
			iBr.iY += aSize.iHeight;
		}
		void Shrink(float aMultiple=0.125)
		{
			iTl.iX += Round<T>(Width()*aMultiple);
			iBr.iX -= Round<T>(Width()*aMultiple);

			iTl.iY -= Round<T>(Height()*aMultiple);
			iBr.iY += Round<T>(Height()*aMultiple);
		}
		void Grow(const CTypedSize<T>& aSize)
		{
			iTl.iX -= aSize.iWidth;
			iBr.iX += aSize.iWidth;

			iTl.iY += aSize.iHeight;
			iBr.iY -= aSize.iHeight;
		}
		void Grow(float aMultiple=0.5)
		{
			iTl.iX -= Round<T>(Width()*aMultiple);
			iBr.iX += Round<T>(Width()*aMultiple);

			iTl.iY += Round<T>(Height()*aMultiple);
			iBr.iY -= Round<T>(Height()*aMultiple);
		} 

		// Rotate clockwise and return the outer rectangle.
		void Rotate(CTypedPoint<T> aAxisPt,float aRadian)
		{
			CTypedPoint<T> topRight = TopRight();
			CTypedPoint<T> leftBottom = BottomLeft();

			topRight.Rotate(aAxisPt,aRadian);
			leftBottom.Rotate(aAxisPt,aRadian);
			iTl.Rotate(aAxisPt,aRadian);
			iBr.Rotate(aAxisPt,aRadian);

			std::vector<CTypedPoint<T>> ptArray;
			ptArray.push_back(topRight);
			ptArray.push_back(leftBottom);
			ptArray.push_back(iTl);
			ptArray.push_back(iBr);

			CTypedRect<T> newRect(ptArray);
			iTl = newRect.iTl;
			iBr = newRect.iBr;

		} 

		// Determines whether the specified point/segment/rect lies within CTypedRect.
		BOOL Contains(const CTypedPoint<T>& aPoint) const
		{

			/************************************************************************

			判断矩形是否包含点

			只要判断该点的横坐标和纵坐标是否夹在矩形的左右边和上下边之间。

			************************************************************************/

			BOOL bFlag = (aPoint.iX>=iTl.iX) && (aPoint.iX<=iBr.iX);

			if ( !bFlag )
			{
				return FALSE;
			}

			bFlag = (aPoint.iY>=iBr.iY) && (aPoint.iY<=iTl.iY);

			return bFlag;
		}

		BOOL Contains(const CTypedSegmentVector<T>& aSegment) const
		{
			if ( !Contains(aSegment.iStartPoint) )
			{
				return FALSE;
			}

			if ( !Contains(aSegment.iEndPoint) )
			{
				return FALSE;
			}

			return TRUE;
		}

		BOOL Contains(const CTypedRect<T>& aRect) const
		{
			/************************************************************************/
			/* 
			判断线段、折线、多边形是否在矩形中

			因为矩形是个凸集，所以只要判断所有端点是否都在矩形中就可以了。

			/************************************************************************/
			BOOL rc = Contains(aRect.iTl);
			if (!rc)
			{
				return FALSE;
			}

			return Contains(aRect.iBr);   
		}

		// Determines whether the specified rect intersects with aRect.
		BOOL IsIntersects(const CTypedRect<T>& aRect) const
		{
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
			BOOL rc = !(iTl.iY < aRect.iBr.iY || iBr.iX < aRect.iTl.iX ||
					iBr.iY > aRect.iTl.iY || iTl.iX > aRect.iBr.iX );

			return rc;

		}

		// Determines whether the specified segment intersects with aRect.
		BOOL IsIntersects(const CTypedSegmentVector<T>& aSegment) const
		{    
			// 矩形与线段是否相交：分别判断矩形四个线段和目标线段是否相交

			// 如果线段在矩形内，认为相交
			if ( Contains(aSegment) )
			{
				return TRUE;
			}

			// TopLeft -> BottomLeft 
			CTypedSegmentVector<T> svTl2Bl(iTl,BottomLeft());
			if ( aSegment.IsIntersects(svTl2Bl) )
			{
				return TRUE;
			}

			// BottomLeft -> BottomRight
			CTypedSegmentVector<T> svBl2Br(BottomLeft(),iBr);
			if ( aSegment.IsIntersects(svBl2Br) )
			{
				return TRUE;
			}

			// BottomRight -> TopRight
			CTypedSegmentVector<T> svBr2Tr(iBr,TopRight());
			if ( aSegment.IsIntersects(svBr2Tr) )
			{
				return TRUE;
			}

			// TopRight -> TopLeft
			CTypedSegmentVector<T> svTr2Tl(TopRight(),iTl);
			if ( aSegment.IsIntersects(svTr2Tl) )
			{
				return TRUE;
			}

			return FALSE;
		}

		// Gets a CRect equal to the intersection of two rectangles.
		CTypedRect<T> Intersersects(const CTypedRect<T>& aRect) const
		{
			if (!IsIntersects(aRect))
			{
				// 不相交，返回空矩形
				return CTypedRect<T>(0,0,0,0);
			}

			CTypedRect<T> rect;

			rect.iTl.iX = max( Left(), aRect.Left() );
			rect.iBr.iX = min( Right(), aRect.Right() );
			rect.iBr.iY = max( Bottom(), aRect.Bottom() );
			rect.iTl.iY = min( Top(), aRect.Top() );

			return rect;
		}

		// Gets a CRect equal to the union of two rectangles.
		CTypedRect<T> UnionRect(const CTypedRect<T>& aRect) const
		{
			return (*this) + aRect;
		}


	public:

		CTypedPoint<T> iTl;
		CTypedPoint<T> iBr;

	};

}
//////////////////////////////////////////////////////////////////////////
#endif