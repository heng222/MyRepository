

#ifndef _TYPED_VECTOR_H_
#define _TYPED_VECTOR_H_

//////////////////////////////////////////////////////////////////////////

namespace Mugis
{

	//////////////////////////////////////////////////////////////////////////
	// ������������

	enum TDirectCategory
	{
		EDT_FOURE,      // ���ַ��� ��EVD_TOP��EVD_RIGHT��EVD_BOTTOM��EVD_LEFT��
		EDT_EIGHT,      // ���ַ��� �����ַ���EVD_TOP_RIGHT��EVD_BOTTOM_RIGHT��EVD_BOTTOM_LEFT��EVD_TOP_LEFT��
	};

	enum TVectorDirect
	{
		EVD_INVALID,        // ��Ч�ķ���
		EVD_TOP = 11,       // ��
		EVD_TOP_RIGHT,      // ����
		EVD_RIGHT,          // ��
		EVD_BOTTOM_RIGHT,   // ����
		EVD_BOTTOM,         // ��
		EVD_BOTTOM_LEFT,    // ����
		EVD_LEFT,           // ��
		EVD_TOP_LEFT,       // ����
	};

	// ��ά��������

	// ����λ�ö���
	enum TVPType
	{
		ETVP_EQUAL,             // Vector A Equals vector B.
		ETVP_COLLINEAR_REVERSE, // A and B are Collinear, but B is in reverse direction.
		ETVP_COLLINEAR_OBVERSE, // same direction 
		ETVP_CLOCKWISE,         // Clockwise.
		ETVP_COUNTERCLOCKWISE,  // Counterclockwise
	};
	// б�ʶ���
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

		// ȡ�� ����
		CTypedVector<T> operator-()
		{
			CTypedVector<T> vOther;
			vOther.m_lHx = -m_lHx;
			vOther.m_lVy = -m_lVy;
			return vOther;
		}

		// ��ֵ������
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

		// �����ӷ�����
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

		// ������������
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

		// �������Ƿ����
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

		// �����������ڻ��������������
		/*
		�ڻ� a��b = |a|��|b|��cos<a, b> = Xa*Ya+Xb+Yb
		������ a,b ���ڻ�����Ϊ a��b���涨Ϊһ��ʵ����a��b = |a|��|b|��cos<a, b>
		*/
		T DotProduct(const CTypedVector<T>& aOther) const
		{
			return (m_lHx*aOther.m_lHx+m_lVy*aOther.m_lVy);
		}

		friend T operator&(CTypedVector<T> aV1,CTypedVector<T> aV2)
		{
			return aV1.DotProduct(aV2);
		}

		// ��������������������
		/*
		��� a �� b = |a|��|b|��Sin<a, b> ; �����������ֶ���
		ʸ�������
		��ʸ��P = ��x1,y1�� ��Q = (x2,y2)����ʸ���������Ϊ��(0,0)��p1��p2��p1+p2����ɵ�
		ƽ���ı��εĴ����ŵ����������P �� Q = x1*y2 - x2*y1��������һ����������Ȼ����
		�� P �� Q = - ( Q �� P ) �� P �� ( - Q ) = - ( P �� Q)��

		�����һ���ǳ���Ҫ�����ǿ���ͨ�����ķ����ж���ʸ���໥֮���˳��ʱ���ϵ��
		1. �� P �� Q > 0 , ��P��Q��˳ʱ�뷽�� 
		2. �� P �� Q < 0 , ��P��Q����ʱ�뷽�� 
		3. �� P �� Q = 0 , ��P��Q���ߣ�������ͬ��Ҳ���ܷ���
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

		// �Ƿ�Ϊ������
		BOOL  IsZeroVector() const
		{
			return (m_lHx==0 && m_lVy==0);
		}

		// ����������б��
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

		// ����������ģ(vector module)
		DOUBLE     GetModule() const
		{
			return sqrt(Square());
		}
		DOUBLE     GetLength() const
		{
			return sqrt(Square());
		}

		// ��������ģ��ƽ��
		DOUBLE     Square() const
		{
			return DOUBLE(m_lHx*m_lHx + m_lVy*m_lVy);
		}

	public:

		// �������Ƿ�ƽ��(����)
		BOOL  IsHorizontal(const CTypedVector<T>& aOther) const
		{
			// ����ƽ�У����ߣ��ĳ�Ҫ������X1*Y2-X2*Y1=0
			T fRc = CrossProduct(aOther);
			return ( abs(fRc)<=1E-6 );
		}

		// �������Ƿ�ֱ(�ڻ�Ϊ0)
		BOOL  IsVertical(const CTypedVector<T>& aOther) const
		{
			T fRc = DotProduct(aOther);
			return ( abs(fRc)<=1E-6 );
		}

		// �������ļн�(�û��ȱ�ʾ����Χ [0,��])�� 
		/*

		1��n����ֵ��ɵ���(x1, x2, x3,���� Xn)��Ϊnά�������Ϊ��д��ĸX 

		|X| = ��x1^2+x2^2+...+xn2 ����Ϊ����X��ģ������X��Y���ڻ�Ϊ�� X��Y=x1*y1+x2*y2+..Xn*Yn


		2������X��Y�������н����Ұ�����ʽ���㣺

		cos(��) = X��Y/(|X|��|Y|) = (X1��Y1+X2��Y2) / (|X|��|Y|) ��     [ PI=>��>=0]

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

		// ��X�������ʱ��н�(�û��ȱ�ʾ����Χ [0,2��])��
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

		// �ص�aAxisPt˳ʱ����תaRadian����
		void  Rotate(CTypedPoint<T> aAxisPt,DOUBLE aRadian)
		{
			CTypedPoint<T> pt1(0,0);
			CTypedPoint<T> pt2(m_lHx,m_lVy);

			pt1.Rotate(aAxisPt,aRadian,TRUE);
			pt2.Rotate(aAxisPt,aRadian,TRUE);

			m_lHx = pt2.iX - pt1.iX;
			m_lVy = pt2.iY - pt1.iY;
		}

		// �ж���������λ�ù�ϵ
		// Return Value: aOther�뵱ǰ������λ�ù�ϵ
		/*
		1. �� P �� Q > 0 , ��P��Q��˳ʱ�뷽�� 
		2. �� P �� Q < 0 , ��P��Q����ʱ�뷽�� 
		3. �� P �� Q = 0 , ��P��Q���ߣ�������ͬ��Ҳ���ܷ���*/
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