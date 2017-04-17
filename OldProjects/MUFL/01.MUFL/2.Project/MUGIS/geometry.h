

#ifndef _GEOMETRY_H_78UIUO_
#define _GEOMETRY_H_78UIUO_
//////////////////////////////////////////////////////////////////////////

#ifndef _MUGIS_PROJECT_

#ifdef _DEBUG
    #ifdef _UNICODE
        #define _MU_GIS_DLL "MUGISUD"   
    #else
        #define _MU_GIS_DLL "MUGISD"  
    #endif     
#else
    #ifdef _UNICODE
        #define _MU_GIS_DLL "MUGISU"   
    #else
        #define _MU_GIS_DLL "MUGIS"  
    #endif 
#endif // end of _DEBUG

#pragma comment( lib, _MU_GIS_DLL )

#endif // end of _MUGIS_PROJECT_

//////////////////////////////////////////////////////////////////////////
#include "typedpoint.h"
#include "TypedSize.h"
#include "TypedVector.h"
#include "TypedSegmentVector.h"
#include "TypedRect.h"
#include "TypedPolygon.h"
#include "CoordinatesConverter.h"

using namespace Mugis;

typedef LONG TLcType;

typedef CTypedPoint<TLcType> TMPoint;
typedef CTypedSize<TLcType> TMSize;

typedef CTypedVector<TLcType> TVector;
typedef CTypedSegmentVector<TLcType> TSegmentVector;
typedef CTypedRect<TLcType> TMRect;
typedef CTypedPolygon<TLcType> TMPolygon;

typedef CArray<TMPoint,TMPoint> CMPointArray;
typedef std::vector<TMPoint> CMPointVector;


//////////////////////////////////////////////////////////////////////////
#endif

