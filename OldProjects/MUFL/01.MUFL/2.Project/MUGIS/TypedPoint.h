
#ifndef _TYPEDPOINT_H_
#define _TYPEDPOINT_H_
//////////////////////////////////////////////////////////////////////////

// STL header and namespace
#include <stdio.h>
#include <tchar.h>
#include <list>
#include <string>
#include <vector>
#include <math.h>



namespace Mugis
{

	// the value of π.
	#define         PIRADIAN        3.1415926535897932384

	// declare forward
	template<class T> class CTypedPoint;
	template<class T> class CTypedSize;
	template<class T> class CTypedVector;
	template<class T> class CTypedSegmentVector;
	template<class T> class CTypedRect;

	/////////////////////// template CTypedPoint ////////////////////////////////////
	template<class T>
	class CTypedPoint
	{

	public:

		typedef T value_type;

		CTypedPoint()
		{
			iX = 0;
			iY = 0;
		}

		CTypedPoint(T aX,T aY)
		{
			iX = aX;
			iY = aY;
		}

		~CTypedPoint()
		{
		}

		// + operation( original point ＋vector ＝ end point )
		friend CTypedPoint<T> operator+(const CTypedPoint<T>& ptStart,const CTypedVector<T>& aVector)
		{
			CTypedPoint endPoint;
			endPoint.iX = ptStart.iX + aVector.m_lHx;
			endPoint.iY = ptStart.iY + aVector.m_lVy;
			return endPoint;
		}

		// += operation
		CTypedPoint<T>& operator+=(const CTypedVector<T>& aVector)
		{
			iX += aVector.m_lHx;
			iY += aVector.m_lVy;
			return *this;
		}

		// - operation( point Q － point P＝ vector PQ )
		friend CTypedVector<T> operator-(CTypedPoint<T> ptEnd,CTypedPoint<T> ptStart)
		{
			CTypedVector<T> vPQ;
			vPQ.m_lHx = ptEnd.iX-ptStart.iX;
			vPQ.m_lVy = ptEnd.iY-ptStart.iY;
			return vPQ;
		}

		// - operation
		CTypedPoint<T> operator-()
		{
			return CTypedPoint(-iX,-iY);
		}

		// = operation
		CTypedPoint<T>& operator=(const CTypedPoint<T>& aOther)
		{
			if (this!=&aOther)
			{
				iX = aOther.iX;
				iY = aOther.iY;
			}
			return *this;
		}

		// == operation
		BOOL operator==(const CTypedPoint<T>& aOther) const
		{
			return (iX==aOther.iX && iY==aOther.iY);
		}
		BOOL operator!=(const CTypedPoint<T>& aOther) const
		{
			return !(*this==aOther);
		}

		// To POINT
		POINT  TOPOINT() const
		{
			POINT pt = {iX,iY};
			return pt;
		}

	public:

		// distance between A and B
		DOUBLE Distance(const CTypedPoint<T>& aOtherPoint) const
		{
			T ndX = aOtherPoint.iX - iX;
			T ndY = aOtherPoint.iY - iY;
			DOUBLE nReturn = sqrt(DOUBLE(ndX*ndX + ndY*ndY));

			return nReturn;
		}

		// 点A绕点O旋转aRadian弧度
		void Rotate(CTypedPoint<T> aAxisPt,DOUBLE aRadian,BOOL clockwise=TRUE)
		{
			if (*this==aAxisPt)
			{
				return;
			}

			if ( !clockwise )
			{
				aRadian = -aRadian;
			}

			T x = iX - aAxisPt.iX;
			T y = iY - aAxisPt.iY;

			DOUBLE xTemp = (x*cos(aRadian) + y*sin(aRadian)) + aAxisPt.iX;
			DOUBLE yTemp = (-x*sin(aRadian) + y*cos(aRadian)) + aAxisPt.iY;

			iX = Round<T>(xTemp);    
			iY = Round<T>(yTemp);
		}


	public:

		value_type iX;
		value_type iY;

	};



	//////////////////////////////////////////////////////////////////////////
	// some utility function
	#define FLOAT_TOLERANCE 0.0001
	static BOOL IsEqual(DOUBLE f1, DOUBLE f2)
	{
		return (fabs(f1 - f2)<=FLOAT_TOLERANCE);
	}

	// Rounding function.
	template<typename T>
	T Round(DOUBLE fValue)
	{
		T iX = static_cast<T>(fValue);
		if (fabs(fValue-iX)>=0.5)
		{
			(fValue-iX>0) ? iX++ : iX--;
		}
		return iX;
	}

	//////////////////////////////////////////////////////////////////////////
} // namespace Mugis
#endif // _TYPEDPOINT_H_

/*
操作符重载 建 议  

1. 所有一元操作符重载为成员函数
2. = () [] ->  必须为成员函数
3. += -= /= *= ^= &= != %= >>= <<=  成员 
4. 其它二元操作符  非成员函数（友元） 
*/