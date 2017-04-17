

#ifndef _TMPOINT_H_Y2U8Z902P_HENG_
#define _TMPOINT_H_Y2U8Z902P_HENG_
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

// STL header and namespace
#include <stdio.h>
#include <tchar.h>
#include <list>
#include <string>
#include <vector>

using namespace std;



// Coordinates system definition
typedef enum _tagCoordinateSystem
{
    ECartesian = 0x0001,     // Cartesian coordinates (Y轴向上递增)
    EPCScreen = 0x0002,      // screen coordinates (Y轴向下递增)

} TCoordinateType;


////////
#define         PIRADIAN        3.1415926535897932384

class TMPoint;
class TMSize;
class TVector;
class TSegmentVector;
class TMRect;

// 逻辑坐标类型
typedef     LONG    TLcType;     

//////////////////////////////////////////////////////////////////////////
// class TMPoint
class TMPoint
{

public:

    TMPoint();
    TMPoint(TLcType aX,TLcType aY);

    ~TMPoint();

    // 加号重载
    // 起始点＋向量 ＝ 终止点
    friend TMPoint operator+(const TMPoint& ptStart,const TVector& aVector); 
    TMPoint& operator+=(const TVector& aVector);

    // 减号重载
    // 点Q－点P＝向量PQ
    friend TVector operator-(TMPoint ptEnd,TMPoint ptStart); 

    // 取反号重载
    TMPoint operator-();

    // 赋值号重载
    TMPoint& operator=(const TMPoint& aOther);

    // 判断相等
    BOOL operator==(const TMPoint& aOther) const;
    BOOL operator!=(const TMPoint& aOther) const;

    // To POINT
    POINT  TOPOINT() const;

public:

    // 两点间距离
    DOUBLE Distance(const TMPoint& aOtherPoint) const;

    // 点A绕点O顺时针旋转aRadian弧度
    void Rotate(TMPoint aAxisPt,DOUBLE aRadian,BOOL aClosewiseRadian=TRUE);


public:

    TLcType iX;
    TLcType iY;

private:

};
typedef vector<TMPoint> CMPointVector;


//////////////////////////////////////////////////////////////////////////
// class TMSize definition

class  TMSize
{
public:

    TMSize();
    TMSize(TLcType aWith,TLcType aHeight);
    ~TMSize();

public:

    TLcType iWidth;
    TLcType iHeight;
};

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
    ETVP_EQUAL,             // Vector a Equals b.
    ETVP_COLLINEAR_REVERSE, // a and b are Collinear, but b is in reverse direction.
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

// Vector definition V = (a,b)
class  TVector
{

public:

    TVector();
    ~TVector();

    TVector(TLcType x,TLcType y);
    TVector(TMPoint ptStart,TMPoint ptEnd);

    // operation override
public:

    // 取反 重载
    TVector operator-();

    // 赋值号重载
    TVector& operator=(const TVector& aOther);
    TVector& operator=(const TSegmentVector& aLine);

    // 向量加法运算
    friend TVector  operator+(const TVector& V1,const TVector& V2);
    TVector& operator+=(const TVector& aOther); 

    // 向量减法运算
    friend TVector  operator-(const TVector& V1,const TVector& V2);
    TVector& operator-=(const TVector& aOther);

    // 两向量是否相等
    BOOL  operator==(const TVector& aOther) const;
    BOOL  operator!=(const TVector& aOther) const;

    // 计算向量的内积（数积、点积）
    TLcType    DotProduct(const TVector& aOther) const;
    friend TLcType operator&(TVector aV1,TVector aV2);

    // 计算向量的外积（叉积）
    TLcType    CrossProduct(const TVector& aOther) const;
    friend TLcType operator*(TVector aV1,TVector aV2);

    // 
public:

    // 是否为零向量
    BOOL  IsZeroVector() const;

    // 计算向量的斜率
    TSlopeType GetSlope(DOUBLE& fSlope) const;

    // 计算向量的模(vector module)
    DOUBLE     GetModule() const;
    DOUBLE     GetLength() const;

    // 计算向量模的平方
    DOUBLE     Square() const;

public:

    // 两向量是否平行(共线)
    BOOL  IsHorizontal(const TVector& aOther) const;

    // 两向量是否垂直
    BOOL  IsVertical(const TVector& aOther) const;

    // 两向量的夹角(用弧度表示，范围 [0,π])。 
    DOUBLE Angle(const TVector& aOther) const;

    // 与X正轴的逆时针夹角(用弧度表示，范围 [0,2π])。
    DOUBLE Angle() const;

    // 沿点aAxisPt顺时针旋转aRadian弧度
    void  Rotate(TMPoint aAxisPt,DOUBLE aRadian);

    // 判断两向量的位置关系
    TVPType GetPositionType(const TVector& aOther) const;

public:

    TLcType    m_lHx;
    TLcType    m_lVy;
};


//////////////////////////////////////////////////////////////////////////
// 有向线段
class TSegmentVector
{

public:

    TSegmentVector();
    TSegmentVector(const TMPoint& ptEnd);
    TSegmentVector(POINT aStart,POINT aEnd);
    TSegmentVector(TMPoint aStartPt,TMPoint aEndPt);
    ~TSegmentVector();

public:

    // X轴与Y轴向量的模
    TLcType Vx() const;
    TLcType Vy() const;

    // 计算线段的长度
    DOUBLE GetLength() const;

    // 计算线段的中心点
    TMPoint GetCenterPt() const;

    TSegmentVector& operator=(const TSegmentVector& aOther);

    // 线段平移
    void Move(TVector aVector);

    // 
    TVectorDirect GetDirection(TDirectCategory aType=EDT_FOURE) const;

    // 两线段是否平行
    BOOL  IsHorizontal(const TSegmentVector& aOther) const;

    // 两线段是否垂直
    BOOL  IsVertical(const TSegmentVector& aOther) const;

    // 线段是否相交 ( 判断线段AB与线段CD[或CD定义的直线]是否相交 )
    // 相交包含共线
    BOOL  IsIntersects(const TSegmentVector& aOther,
            BOOL bLine=FALSE) const;

    // 计算两线段的交点
    // Return: 不相交返回FALSE
    // bLine = TRUE 表示计算两直线的交点，否则计算两线段的交点
    BOOL  CalcIntersection(const TSegmentVector& aOther,
            TMPoint& ptCross,
            BOOL bLine=FALSE) const;

    // 返回线段的向量表示
    TVector GetVector() const;

    // 返回方位角( 与正北的夹角，范围[0,2π] )
    DOUBLE GetAzimuth() const;

    // 得到离起点长度为Len的点坐标(指定长度大于线段的模时，返回FALSE)
    BOOL  GetRemotePoint(TMPoint& ptArg, DOUBLE fRemoteLen) const;

public:

    // Rotate clockwise.
    void Rotate(TMPoint aAxisPt,float aRadian); 

    /** 
        描述：判断点A是否在线段上
            aPoint: 点A
            bExtendLine: 是否判断点在线段的延长线上
    */
    BOOL PointInSegment(const TMPoint& aPoint,BOOL bExtendLine=FALSE) const;


    // 根据方位角、起始点与逻辑长度构造向量。此向量以aStartPt起点，长度为aLogicLen个逻辑单位，方位角为aAzimuth
    // aAngle : 方位角（与正北方向的夹角），in radian.
    static TSegmentVector BuildSegment(TMPoint aStartPt,float aAzimuth,LONG aLogicLen=1000); 

public:

    enum TProjectionPos
    {
        EPP_INSEGMENT = 0,      // 在线段上
        EPP_OFFSETSTART = 5,    // 在线段起点外侧
        EPP_OFFSETEND,          // 在线段终点外侧
    };
    // 点的投影在线段上的位置
    int  ProjectionPosition(TMPoint aPt) const;

    // 点到线段的距离
    DOUBLE  Distance(TMPoint aPoint) const;

    /*
        描述： 从点Q作线段AB的垂线，垂足为O。
        返回： <0 表示点P的投影不在线段AB上，无垂足。>=0 返回垂线段长度以及垂足。
    */
    DOUBLE  Plumbline(TMPoint aPointQ,TMPoint& aCrossPt) const;

public:

    // 两线段的夹角(用弧度表示，范围 [0,π])
    DOUBLE Angle(const TSegmentVector& aOther) const;

public:

    TMPoint  iStartPoint;
    TMPoint  iEndPoint;
};
typedef vector<TSegmentVector> CMSegmentArray;


//////////////////////////////////////////////////////////////////////////
//#######################################################################
// class TMRect ( valid under Cartesian coordinates && Screen coordinates)
class TMRect
{

public:

    TMRect(TCoordinateType iType = ECartesian);
    ~TMRect();

    void    SetCoordinateType(TCoordinateType iType);

    TMRect(TLcType aTLx,TLcType aTLy,TLcType aBRx,TLcType aBRy,
        TCoordinateType iType = ECartesian);// 根据左上角与右下角点构造

    TMRect(const TMPoint& aDiagonalPt1,const TMPoint& aDiagonalPt2,
        TCoordinateType iType = ECartesian); // 根据任意两点构造

    TMRect(const TMPoint& aTl,TMSize aSize,
        TCoordinateType iType = ECartesian);// TopLeft ＋ Size

    TMRect(const TMPoint& aCenter,TLcType aWidth,TLcType aHeight,
        TCoordinateType iType = ECartesian);// Center + width +height

    TMRect(const CMPointVector& aPloygon,
        TCoordinateType iType = ECartesian);  // 构造多边形的外接矩形

    // Normalizes CRect so that both the height and width are positive.
    void NormalizeRect( );

    // operations overrides
    TMRect& operator=(const TMRect& aOther);

    friend TMRect operator+(TMRect aRect1,TMRect aRect2);
    void operator+=(const TMRect& aRect);

    void operator-=(TMSize size);
    

    // CRect operation
//    void Copy(CRect aOther);
    RECT    ToRECT() const;

    // Attributes
    TLcType Top() const;
    TLcType Bottom() const;
    TLcType Left() const;
    TLcType Right() const;

    TMPoint TopRight() const;
    TMPoint BottomLeft() const;
    TMPoint Center() const;

    TLcType Width() const;
    TLcType Height() const;

    void GetLocation(TMPoint* aPt) const;

    // Is valid
    BOOL IsValid() const;

    // Determines whether TMRect is empty. TMRect is empty if the width and/or height are 0.
    BOOL IsEmpty() const;

    // Determines whether the top, bottom, left, and right member variables are all equal to 0.
    BOOL IsNull() const;
    void SetNull();

    // Move
    void MoveAlongVector(const TVector& aVector);
    void MoveLeft(TLcType aLen);
    void MoveRight(TLcType aLen);
    void MoveTop(TLcType aLen);
    void MoveBottom(TLcType aLen);
    void Offset(TMPoint aPt);

    // Inflate && Deflate
    void Shrink(const TMSize& aSize);
    void Shrink(float aMultiple=0.125);
    void Grow(const TMSize& aSize);
    void Grow(float aMultiple=0.5); 

    // Rotate clockwise and return the outer rectangle.
    void Rotate(TMPoint aAxisPt,float aRadian); 

    // Determines whether the specified point/segment/rect lies within TMRect.
    BOOL Contains(const TMPoint& aPoint) const;
    BOOL Contains(const TSegmentVector& aSegment) const;
    BOOL Contains(const TMRect& aRect) const;
    
    // Determines whether the specified rect intersects with aRect.
    BOOL IsIntersects(const TMRect& aRect) const;

    // Determines whether the specified segment intersects with aRect.
    BOOL IsIntersects(const TSegmentVector& aSegment) const;

    // Gets a CRect equal to the intersection of two rectangles.
    TMRect Intersersects(const TMRect& aRect) const;

    // Gets a CRect equal to the union of two rectangles.
    TMRect UnionRect(const TMRect& aRect) const;


public:

    TMPoint iTl;
    TMPoint iBr;

private:

    TCoordinateType m_iType;
};

typedef vector<TMRect> CMRectVector;

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//#######################################################################
// class TMPolygon (closed polygon definition without edges crossed.) 
// Include convex polygon and concave polygon 
class TMPolygon
{
    // Constructors
public:

    TMPolygon();
    TMPolygon(const std::vector<TMPoint>& vertexes);


    // Methods
public:

    // Add a vertex.
    VOID    AddVertex(const TMPoint& aVertex);

    // Add a edge.
    VOID    AddEdge(const TSegmentVector& edge);

    // normalize to convex polygon.
    // TRUE: success
    BOOL    Normalize2Convex();

    // operations overrides
    TMPolygon& operator=(const TMPolygon& aOther);

    // const methods
public:

    // Is this a polygon?
    BOOL    IsValid() const;

    // Is this a convex polygon?
    BOOL    IsConvex() const;
    
    // Get the number of vertex.
    BYTE    GetNumVertex() const;

    // Get the sum of angles.(In Radian)
    // bInner = TRUE: sum of outer angles.
    // bInner = FALSE: sum of inner angles.
    DOUBLE  GetSumOfAngle(BOOL bInner = FALSE) const;

    // Get all edges.
    VOID    GetEdges(std::vector<TSegmentVector>& edges) const;

    // get the external rectangular.
    BOOL    GetExternalRect(TMRect& rectExternal) const;

    // the quality center.
    TMPoint Center() const;

    // To HRGN
    HRGN    ToHRGN() const;

    // const methods operator with other objects.
public:

    // Is the given Point a vertex?
    BOOL  IsVertex(const TMPoint& aPoint) const;

    // Determines whether the specified point lies within the polygon.
    BOOL   Contains(const TMPoint& aPoint) const;

    // private functions
private:

    VOID     Sort( const std::vector<DOUBLE>& arrValue,
                    std::vector<INT>& arrIndex) const;
    
    // is the circle made by polygon clockwise?
    BOOL     IsClockwise() const;

    // Members
private:
    
    std::vector<TMPoint>  m_Vertex;
};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
#endif


