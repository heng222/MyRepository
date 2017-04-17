

/************************************************************************/
/* Coordinates converter                                                */
/************************************************************************/

#ifndef __COORDINATES_CONVERTER_H__
#define __COORDINATES_CONVERTER_H__

//////////////////////////////////////////////////////////////////////////
#include "typedpoint.h"
#include "TypedSize.h"
#include "TypedVector.h"
#include "TypedSegmentVector.h"
#include "TypedRect.h"
#include "TypedPolygon.h"

//////////////////////////////////////////////////////////////////////////
namespace Mugis
{
	// class CCoordinatesConverter
	class CCoordinatesConverter
	{
	public:

		CCoordinatesConverter(){}
		~CCoordinatesConverter(){}

	public:

		// Cartesian to Screen for Point
		template<class T>
		static void CartesianToScreen(const CTypedPoint<T>& cartesian,CTypedPoint<T>& scr)
		{
			scr.iX = cartesian.iX;
			scr.iY = -cartesian.iY;
		}

		// Screen to Cartesian for Point
		template<class T>
		static void ScreenToCartesian(const CTypedPoint<T>& scr, CTypedPoint<T>& cartesian)
		{
			cartesian.iX = scr.iX;
			cartesian.iY = -scr.iY;
		}

		// Cartesion to Screen for Vector
		template<class T>
		static void CartesianToScreen(const CTypedVector<T>& cartesian,CTypedVector<T>& scr)
		{
			scr.m_lHx = cartesian.m_lHx;
			scr.m_lVy = -cartesian.m_lVy;
		}

		// Screen to Cartesian for Vector
		template<class T>
		static void ScreenToCartesian(const CTypedVector<T>& scr, CTypedVector<T>& cartesian)
		{
			cartesian.m_lHx = scr.m_lHx;
			cartesian.m_lVy = -scr.m_lVy;
		}


		// Cartesion to Screen for SegmentVector
		template<class T>
		static void CartesianToScreen(const CTypedSegmentVector<T>& cartesian,CTypedSegmentVector<T>& scr)
		{
			CartesianToScreen(cartesian.iStartPoint,scr.iStartPoint);
			CartesianToScreen(cartesian.iEndPoint,scr.iEndPoint);
		}

		// Screen to Cartesian for SegmentVector
		template<class T>
		static void ScreenToCartesian(const CTypedSegmentVector<T>& scr, CTypedSegmentVector<T>& cartesian)
		{
			ScreenToCartesian(scr.iStartPoint,cartesian.iStartPoint);
			ScreenToCartesian(scr.iEndPoint,cartesian.iEndPoint);
		}

		// Cartesion to Screen for Rect
		template<class T>
		static void CartesianToScreen(const CTypedRect<T>& cartesian,CTypedRect<T>& scr)
		{
			CartesianToScreen(cartesian.iTl,scr.iTl);
			CartesianToScreen(cartesian.iBr,scr.iBr);
		}

		// Screen to Cartesian for Rect
		template<class T>
		static void ScreenToCartesian(const CTypedRect<T>& scr, CTypedRect<T>& cartesian)
		{
			ScreenToCartesian(scr.iTl,cartesian.iTl);
			ScreenToCartesian(scr.iBr,cartesian.iBr);
		}

		// Cartesion to Screen for Polygon
		template<class T>
		static void CartesianToScreen(const CTypedPolygon<T>& cartesian,CTypedPolygon<T>& scr)
		{
			std::vector<CTypedPoint<T>> vertexes = cartesian.GetVertex();
			size_t iNum = vertexes.size();

			CTypedPoint<T> ptTemp;
			for (size_t i=0; i<iNum; i++)
			{
				CartesianToScreen(vertexes[i],ptTemp);
				scr.AddVertex(ptTemp);
			}
		}

		// Screen to Cartesian for Polygon
		template<class T>
		static void ScreenToCartesian(const CTypedPolygon<T>& scr, CTypedPolygon<T>& cartesian)
		{
			std::vector<CTypedPoint<T>> vertexes = scr.GetVertex();
			size_t iNum = vertexes.size();

			CTypedPoint<T> ptTemp;
			for (size_t i=0; i<iNum; i++)
			{
				ScreenToCartesian(vertexes[i],ptTemp);
				cartesian.AddVertex(ptTemp);
			}
		}

	};

} // namesapce Mugis
//////////////////////////////////////////////////////////////////////////
#endif // __COORDINATES_CONVERTER_H__
