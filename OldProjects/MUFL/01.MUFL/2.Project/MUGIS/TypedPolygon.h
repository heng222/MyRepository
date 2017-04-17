
#ifndef _TYPED_POLYGON_H_
#define _TYPED_POLYGON_H_

//////////////////////////////////////////////////////////////////////////

/*////////////////////////////////////////////////////////////////////////
1. 所谓凸多边形，就是把一个多边形任意一边向两方无限延长成为一条直线，如果多
边形的其他各边均在此直线的同旁，那么这个多边形就叫做凸多边形，也可以理解为
通过凸多边形的任意一条边作平面，并与此多边形所在的平面相异，那么凸多边形的
其他所有部分都在所作平面的同一侧。

2. 凸多边形包含三角形和平面四边形。
*/////////////////////////////////////////////////////////////////////////

namespace Mugis
{
////////////////////// Template CTypedPolygon ///////////////////////////////

// class CTypedPolygon (closed polygon definition without edges crossed.) 
// Include convex polygon and concave polygon 

template<class T>
class CTypedPolygon
{
	// Constructors
public:

	CTypedPolygon(){}
	CTypedPolygon(const std::vector<CTypedPoint<T>>& vertexes)
	{
		m_Vertex = vertexes;
	}


	// Methods
public:

	// Add a vertex.
	VOID    AddVertex(const CTypedPoint<T>& aVertex)
	{
		if (!IsVertex(aVertex))
		{
			m_Vertex.push_back(aVertex);
		}
	}

	// get the vertexes
	std::vector<CTypedPoint<T>> GetVertex() const
	{
		return m_Vertex;
	}

	// Add a edge.
	VOID    AddEdge(const CTypedSegmentVector<T>& edge)
	{
		AddVertex(edge.iStartPoint);
		AddVertex(edge.iEndPoint);
	}

	// normalize to convex polygon.
	// TRUE: success
	BOOL    Normalize2Convex()
	{
		size_t iNum = m_Vertex.size();
		if (iNum==3) // triangle
		{
			return TRUE;
		}

		// 中心点
		CTypedPoint<T> ptCenter = Center();

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
		std::vector<CTypedPoint<T>> vertexTemp = m_Vertex;
		for (size_t j=0; j<iNum; j++)
		{
			CTypedPoint<T> ptTemp = vertexTemp[arrIndex[j]];
			m_Vertex[j] = ptTemp;
		}

		// 
		return IsConvex();
	}

	// operations overrides
	CTypedPolygon<T>& operator=(const CTypedPolygon<T>& aOther)
	{
		if (this!=&aOther)
		{
			this->m_Vertex = aOther.m_Vertex;
		}
		return *this;
	}

	// const methods
public:

	// Is this a polygon?
	BOOL    IsValid() const
	{
		return (m_Vertex.size()>=3);
	}

	// Is this a convex polygon?
	BOOL    IsConvex() const
	{
		/*/////////////////////////////////////////////////////////
		1．凸多边形的内角均小于180°，边数为n（n为整数且n大于2）的
		凸多边形内角和为（n－2）×180°，但任意凸多边形外角和均
		为360°，并可通过反证法证明凸多边形内角中锐角的个数不能
		多于3个。

		2．凸多边形所有对角线都在内部，边数为n的凸多边形对角线条数
		为n（n－3）／2，其中通过任一顶点可与其余n－3个顶点连对角
		线。
		*///////////////////////////////////////////////////////////

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

	// Get the number of vertex.
	BYTE    GetNumVertex() const
	{
		return (BYTE)(m_Vertex.size());
	}

	// Get the sum of angles.(In Radian)
	// bInner = TRUE: sum of outer angles.
	// bInner = FALSE: sum of inner angles.
	DOUBLE  GetSumOfAngle(BOOL bInner = FALSE) const
	{
		DOUBLE fSum = 0;

		// get all edges.
		std::vector<CTypedSegmentVector<T>> edges;
		GetEdges(edges);

		// 
		size_t iNum = edges.size();
		if (iNum>=2)
		{
			CTypedSegmentVector<T> edgeStart = edges[0];

			// 
			BOOL bClockwise = IsClockwise();

			DOUBLE fAngle = 0; // angle made with neighboring edge.
			T crossProduct = 0; // cross product

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
	VOID    GetEdges(std::vector<CTypedSegmentVector<T>>& edges) const
	{
		if (!IsValid())
		{
			return;
		}

		size_t iNum = m_Vertex.size();

		// 
		CTypedPoint<T> ptStart = m_Vertex[0];
		size_t i = 1;
		for (; i<iNum; i++)
		{
			CTypedSegmentVector<T> edgeItem(ptStart,m_Vertex[i]);
			edges.push_back(edgeItem);
			ptStart = m_Vertex[i];
		}

		edges.push_back(CTypedSegmentVector<T>(ptStart,m_Vertex[0]));
	}

	// get the external rectangular.
	BOOL    GetExternalRect(CTypedRect<T>& rectExternal) const
	{
		if (!IsValid())
		{
			return FALSE;
		}

		size_t number = m_Vertex.size();

		CTypedPoint<T> element = m_Vertex[0];
		T minX,maxX,minY,maxY;
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

	// the quality center.
	CTypedPoint<T> Center() const
	{
		DOUBLE xSum = 0, ySum = 0;
		size_t iNum = m_Vertex.size();
		for (size_t i=0; i<iNum; i++)
		{
			xSum += m_Vertex[i].iX;
			ySum += m_Vertex[i].iY;
		}

		T x = Round<T>(xSum / iNum);
		T y = Round<T>(ySum / iNum);
		return CTypedPoint<T>(x,y);
	}


	// To HRGN
	HRGN    ToHRGN() const
	{
		INT iNum = GetNumVertex();
		if (iNum<=0)
		{
			return NULL;
		}

		//
		return ::CreatePolygonRgn((POINT*)(&(m_Vertex[0])),iNum,ALTERNATE);
	}


	// const methods operator with other objects.
public:

	// Is the given Point a vertex?
	BOOL  IsVertex(const CTypedPoint<T>& aPoint) const
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
	BOOL   Contains(const CTypedPoint<T>& aPoint) const
	{
		CTypedRect<T> rectExternal;
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
		T raysLen = rectExternal.Width() + rectExternal.Height();
		CTypedPoint<T> raysEnd(aPoint.iX+raysLen,aPoint.iY);
		CTypedSegmentVector<T> rays(aPoint,raysEnd);
		//rays.Rotate(aPoint,PIRADIAN/4);

		// get all edges.
		std::vector<CTypedSegmentVector<T>> edges;
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

	// private functions
private:

	struct TAngleValue
	{
		DOUBLE  fAngle;
		INT     iIndex;
	};
	VOID     Sort( const std::vector<DOUBLE>& arrValue,
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

	// is the circle made by polygon clockwise?
	BOOL     IsClockwise() const
	{
		// get all edges.
		std::vector<CTypedSegmentVector<T>> edges;
		GetEdges(edges); 

		//
		CTypedPoint<T> ptCenter = Center();

		size_t iNum = edges.size();
		for (size_t iIndex = 0; iIndex<iNum; iIndex++)
		{
			CTypedSegmentVector<T> V1(ptCenter,edges[iIndex].iStartPoint);
			CTypedSegmentVector<T> V2(edges[iIndex].iEndPoint,ptCenter);
			T product = V1.GetVector()*V2.GetVector();
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

	// Members
private:

	std::vector<CTypedPoint<T>>  m_Vertex;
};
}
//////////////////////////////////////////////////////////////////////////
#endif