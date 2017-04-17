

#ifndef _TYPED_VECTOR_H_
#define _TYPED_VECTOR_H_

//////////////////////////////////////////////////////////////////////////

namespace Mugis
{

	//////////////////////////////////////////////////////////////////////////
	// 向量方向类型

	enum TDirectCategory
	{
		EDT_FOURE,      // 四种方向 （EVD_TOP，EVD_RIGHT，EVD_BOTTOM，EVD_LEFT）
		EDT_EIGHT,      // 八种方向 （四种方向＋EVD_TOP_RIGHT＋EVD_BOTTOM_RIGHT＋EVD_BOTTOM_LEFT＋EVD_TOP_LEFT）
	};

	enum TVectorDirect
	{
		EVD_INVALID,        // 无效的方向
		EVD_TOP = 11,       // 上
		EVD_TOP_RIGHT,      // 右上
		EVD_RIGHT,          // 右
		EVD_BOTTOM_RIGHT,   // 右下
		EVD_BOTTOM,         // 下
		EVD_BOTTOM_LEFT,    // 左下
		EVD_LEFT,           // 左
		EVD_TOP_LEFT,       // 左上
	};

	// 二维向量定义

	// 向量位置定义
	enum TVPType
	{
		ETVP_EQUAL,             // Vector A Equals vector B.
		ETVP_COLLINEAR_REVERSE, // A and B are Collinear, but B is in reverse direction.
		ETVP_COLLINEAR_OBVERSE, // same direction 
		ETVP_CLOCKWISE,         // Clockwise.
		ETVP_COUNTERCLOCKWISE,  // Counterclockwise
	};
	// 斜率定义
	enum TSlopeType
	{
		EST_INVALID,            // invalid
		EST_NORMAL,             // normal slope ([PI/2, -PI/2])
		EST_POSITIVE_INF,       // positive infinite (PI/2)
		EST_NEGATIVE_INF        // negative infinite (-PI/2)
	};

	//-------------------- template Vector definition V = (a,b) --------------------------
	template<class T>
	class CTypedVector
	{

	public:

		typedef T value_type;

		CTypedVector()
		{
			m_lHx = 0;
			m_lVy = 0;
		}

		~CTypedVector(){}

		CTypedVector(T x,T y)
		{
			m_lHx = x;
			m_lVy = y;
		}

		CTypedVector(CTypedPoint<T> ptStart,CTypedPoint<T> ptEnd)
		{
			*this = ptEnd - ptStart;
		}

		// operation override
	public:

		// 取反 重载
		CTypedVector<T> operator-()
		{
			CTypedVector<T> vOther;
			vOther.m_lHx = -m_lHx;
			vOther.m_lVy = -m_lVy;
			return vOther;
		}

		// 赋值号重载
		CTypedVector<T>& operator=(const CTypedVector<T>& aOther)
		{
			if( this != &aOther )
			{
				m_lHx = aOther.m_lHx;
				m_lVy = aOther.m_lVy;
			}

			return *this;
		}

		CTypedVector<T>& operator=(const CTypedSegmentVector<T>& aLine)
		{
			CTypedVector<T> v = aLine.GetVector();
			m_lHx = v.m_lHx;
			m_lVy = v.m_lVy;
			return *this;
		}

		// 向量加法运算
		friend CTypedVector<T>  operator+(const CTypedVector<T>& V1,const CTypedVector<T>& V2)
		{
			CTypedVector<T> result;
			result.m_lHx = V1.m_lHx + V2.m_lHx;
			result.m_lVy = V1.m_lVy + V2.m_lVy;
			return result;
		}

		CTypedVector<T>& operator+=(const CTypedVector<T>& aOther)
		{
			m_lHx += aOther.m_lHx;
			m_lVy += aOther.m_lVy;
			return *this;
		}

		// 向量减法运算
		friend CTypedVector<T>  operator-(const CTypedVector& V1,const CTypedVector<T>& V2)
		{
			CTypedVector<T> result;
			result.m_lHx = V1.m_lHx - V2.m_lHx;
			result.m_lVy = V1.m_lVy - V2.m_lVy;
			return result;
		}

		CTypedVector<T>& operator-=(const CTypedVector<T>& aOther)
		{
			m_lHx -= aOther.m_lHx;
			m_lVy -= aOther.m_lVy;
			return *this;
		}

		// 两向量是否相等
		BOOL  operator==(const CTypedVector<T>& aOther) const
		{
			if (this==&aOther)
			{
				return TRUE;
			}

			return (m_lHx==aOther.m_lHx && m_lVy==aOther.m_lVy);
		}

		BOOL  operator!=(const CTypedVector<T>& aOther) const
		{
			return !(*this==aOther);
		}

		// 计算向量的内积（数积、点积）
		/*
		内积 a·b = |a|·|b|·cos<a, b> = Xa*Ya+Xb+Yb
		两向量 a,b 的内积，记为 a·b，规定为一个实数：a·b = |a|·|b|·cos<a, b>
		*/
		T DotProduct(const CTypedVector<T>& aOther) const
		{
			return (m_lHx*aOther.m_lHx+m_lVy*aOther.m_lVy);
		}

		friend T operator&(CTypedVector<T> aV1,CTypedVector<T> aV2)
		{
			return aV1.DotProduct(aV2);
		}

		// 计算向量的外积（叉积）
		/*
		外积 a × b = |a|·|b|·Sin<a, b> ; 方向：适用右手定律
		矢量叉积：
		设矢量P = （x1,y1） ，Q = (x2,y2)，则矢量叉积定义为由(0,0)、p1、p2和p1+p2所组成的
		平行四边形的带符号的面积，即：P × Q = x1*y2 - x2*y1，其结果是一个标量。显然有性
		质 P × Q = - ( Q × P ) 和 P × ( - Q ) = - ( P × Q)。

		叉积的一个非常重要性质是可以通过它的符号判断两矢量相互之间的顺逆时针关系：
		1. 若 P × Q > 0 , 则P在Q的顺时针方向。 
		2. 若 P × Q < 0 , 则P在Q的逆时针方向。 
		3. 若 P × Q = 0 , 则P与Q共线，但可能同向也可能反向。
		*/
		T CrossProduct(const CTypedVector<T>& aOther) const
		{
			return (m_lHx*aOther.m_lVy-aOther.m_lHx*m_lVy);
		}

		friend T operator*(CTypedVector<T> aV1,CTypedVector<T> aV2)
		{
			return aV1.CrossProduct(aV2);
		}

		// 
	public:

		// 是否为零向量
		BOOL  IsZeroVector() const
		{
			return (m_lHx==0 && m_lVy==0);
		}

		// 计算向量的斜率
		TSlopeType GetSlope(DOUBLE& fSlope) const
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

		// 计算向量的模(vector module)
		DOUBLE     GetModule() const
		{
			return sqrt(Square());
		}
		DOUBLE     GetLength() const
		{
			return sqrt(Square());
		}

		// 计算向量模的平方
		DOUBLE     Square() const
		{
			return DOUBLE(m_lHx*m_lHx + m_lVy*m_lVy);
		}

	public:

		// 两向量是否平行(共线)
		BOOL  IsHorizontal(const CTypedVector<T>& aOther) const
		{
			// 向量平行（共线）的充要条件：X1*Y2-X2*Y1=0
			T fRc = CrossProduct(aOther);
			return ( abs(fRc)<=1E-6 );
		}

		// 两向量是否垂直(内积为0)
		BOOL  IsVertical(const CTypedVector<T>& aOther) const
		{
			T fRc = DotProduct(aOther);
			return ( abs(fRc)<=1E-6 );
		}

		// 两向量的夹角(用弧度表示，范围 [0,π])。 
		/*

		1、n个数值组成的行(x1, x2, x3,…… Xn)称为n维向量简记为大写字母X 

		|X| = √x1^2+x2^2+...+xn2 定义为向量X的模，向量X与Y的内积为： X·Y=x1*y1+x2*y2+..Xn*Yn


		2、向量X及Y的向量夹角余弦按照下式计算：

		cos(θ) = X·Y/(|X|×|Y|) = (X1×Y1+X2×Y2) / (|X|×|Y|) 。     [ PI=>θ>=0]

		*/
		DOUBLE Angle(const CTypedVector<T>& aOther) const
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

		// 与X正轴的逆时针夹角(用弧度表示，范围 [0,2π])。
		DOUBLE Angle() const
		{
			CTypedVector<T> vTemp(10,0);

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

		// 沿点aAxisPt顺时针旋转aRadian弧度
		void  Rotate(CTypedPoint<T> aAxisPt,DOUBLE aRadian)
		{
			CTypedPoint<T> pt1(0,0);
			CTypedPoint<T> pt2(m_lHx,m_lVy);

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
		TVPType GetPositionType(const CTypedVector<T>& aOther) const
		{
			if (*this==aOther)
			{
				return ETVP_EQUAL;
			}

			CTypedVector P = *this;
			CTypedVector Q = aOther;
			T result = P*Q;

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

	public:

		T    m_lHx;
		T    m_lVy;
	};
} // namespace Mugis
//////////////////////////////////////////////////////////////////////////
#endif