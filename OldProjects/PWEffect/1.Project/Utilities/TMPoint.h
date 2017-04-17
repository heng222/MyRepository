

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
    ECartesian = 0x0001,     // Cartesian coordinates (Y�����ϵ���)
    EPCScreen = 0x0002,      // screen coordinates (Y�����µ���)

} TCoordinateType;


////////
#define         PIRADIAN        3.1415926535897932384

class TMPoint;
class TMSize;
class TVector;
class TSegmentVector;
class TMRect;

// �߼���������
typedef     LONG    TLcType;     

//////////////////////////////////////////////////////////////////////////
// class TMPoint
class TMPoint
{

public:

    TMPoint();
    TMPoint(TLcType aX,TLcType aY);

    ~TMPoint();

    // �Ӻ�����
    // ��ʼ�㣫���� �� ��ֹ��
    friend TMPoint operator+(const TMPoint& ptStart,const TVector& aVector); 
    TMPoint& operator+=(const TVector& aVector);

    // ��������
    // ��Q����P������PQ
    friend TVector operator-(TMPoint ptEnd,TMPoint ptStart); 

    // ȡ��������
    TMPoint operator-();

    // ��ֵ������
    TMPoint& operator=(const TMPoint& aOther);

    // �ж����
    BOOL operator==(const TMPoint& aOther) const;
    BOOL operator!=(const TMPoint& aOther) const;

    // To POINT
    POINT  TOPOINT() const;

public:

    // ��������
    DOUBLE Distance(const TMPoint& aOtherPoint) const;

    // ��A�Ƶ�O˳ʱ����תaRadian����
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
    ETVP_EQUAL,             // Vector a Equals b.
    ETVP_COLLINEAR_REVERSE, // a and b are Collinear, but b is in reverse direction.
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

    // ȡ�� ����
    TVector operator-();

    // ��ֵ������
    TVector& operator=(const TVector& aOther);
    TVector& operator=(const TSegmentVector& aLine);

    // �����ӷ�����
    friend TVector  operator+(const TVector& V1,const TVector& V2);
    TVector& operator+=(const TVector& aOther); 

    // ������������
    friend TVector  operator-(const TVector& V1,const TVector& V2);
    TVector& operator-=(const TVector& aOther);

    // �������Ƿ����
    BOOL  operator==(const TVector& aOther) const;
    BOOL  operator!=(const TVector& aOther) const;

    // �����������ڻ��������������
    TLcType    DotProduct(const TVector& aOther) const;
    friend TLcType operator&(TVector aV1,TVector aV2);

    // ��������������������
    TLcType    CrossProduct(const TVector& aOther) const;
    friend TLcType operator*(TVector aV1,TVector aV2);

    // 
public:

    // �Ƿ�Ϊ������
    BOOL  IsZeroVector() const;

    // ����������б��
    TSlopeType GetSlope(DOUBLE& fSlope) const;

    // ����������ģ(vector module)
    DOUBLE     GetModule() const;
    DOUBLE     GetLength() const;

    // ��������ģ��ƽ��
    DOUBLE     Square() const;

public:

    // �������Ƿ�ƽ��(����)
    BOOL  IsHorizontal(const TVector& aOther) const;

    // �������Ƿ�ֱ
    BOOL  IsVertical(const TVector& aOther) const;

    // �������ļн�(�û��ȱ�ʾ����Χ [0,��])�� 
    DOUBLE Angle(const TVector& aOther) const;

    // ��X�������ʱ��н�(�û��ȱ�ʾ����Χ [0,2��])��
    DOUBLE Angle() const;

    // �ص�aAxisPt˳ʱ����תaRadian����
    void  Rotate(TMPoint aAxisPt,DOUBLE aRadian);

    // �ж���������λ�ù�ϵ
    TVPType GetPositionType(const TVector& aOther) const;

public:

    TLcType    m_lHx;
    TLcType    m_lVy;
};


//////////////////////////////////////////////////////////////////////////
// �����߶�
class TSegmentVector
{

public:

    TSegmentVector();
    TSegmentVector(const TMPoint& ptEnd);
    TSegmentVector(POINT aStart,POINT aEnd);
    TSegmentVector(TMPoint aStartPt,TMPoint aEndPt);
    ~TSegmentVector();

public:

    // X����Y��������ģ
    TLcType Vx() const;
    TLcType Vy() const;

    // �����߶εĳ���
    DOUBLE GetLength() const;

    // �����߶ε����ĵ�
    TMPoint GetCenterPt() const;

    TSegmentVector& operator=(const TSegmentVector& aOther);

    // �߶�ƽ��
    void Move(TVector aVector);

    // 
    TVectorDirect GetDirection(TDirectCategory aType=EDT_FOURE) const;

    // ���߶��Ƿ�ƽ��
    BOOL  IsHorizontal(const TSegmentVector& aOther) const;

    // ���߶��Ƿ�ֱ
    BOOL  IsVertical(const TSegmentVector& aOther) const;

    // �߶��Ƿ��ཻ ( �ж��߶�AB���߶�CD[��CD�����ֱ��]�Ƿ��ཻ )
    // �ཻ��������
    BOOL  IsIntersects(const TSegmentVector& aOther,
            BOOL bLine=FALSE) const;

    // �������߶εĽ���
    // Return: ���ཻ����FALSE
    // bLine = TRUE ��ʾ������ֱ�ߵĽ��㣬����������߶εĽ���
    BOOL  CalcIntersection(const TSegmentVector& aOther,
            TMPoint& ptCross,
            BOOL bLine=FALSE) const;

    // �����߶ε�������ʾ
    TVector GetVector() const;

    // ���ط�λ��( �������ļнǣ���Χ[0,2��] )
    DOUBLE GetAzimuth() const;

    // �õ�����㳤��ΪLen�ĵ�����(ָ�����ȴ����߶ε�ģʱ������FALSE)
    BOOL  GetRemotePoint(TMPoint& ptArg, DOUBLE fRemoteLen) const;

public:

    // Rotate clockwise.
    void Rotate(TMPoint aAxisPt,float aRadian); 

    /** 
        �������жϵ�A�Ƿ����߶���
            aPoint: ��A
            bExtendLine: �Ƿ��жϵ����߶ε��ӳ�����
    */
    BOOL PointInSegment(const TMPoint& aPoint,BOOL bExtendLine=FALSE) const;


    // ���ݷ�λ�ǡ���ʼ�����߼����ȹ�����������������aStartPt��㣬����ΪaLogicLen���߼���λ����λ��ΪaAzimuth
    // aAngle : ��λ�ǣ�����������ļнǣ���in radian.
    static TSegmentVector BuildSegment(TMPoint aStartPt,float aAzimuth,LONG aLogicLen=1000); 

public:

    enum TProjectionPos
    {
        EPP_INSEGMENT = 0,      // ���߶���
        EPP_OFFSETSTART = 5,    // ���߶�������
        EPP_OFFSETEND,          // ���߶��յ����
    };
    // ���ͶӰ���߶��ϵ�λ��
    int  ProjectionPosition(TMPoint aPt) const;

    // �㵽�߶εľ���
    DOUBLE  Distance(TMPoint aPoint) const;

    /*
        ������ �ӵ�Q���߶�AB�Ĵ��ߣ�����ΪO��
        ���أ� <0 ��ʾ��P��ͶӰ�����߶�AB�ϣ��޴��㡣>=0 ���ش��߶γ����Լ����㡣
    */
    DOUBLE  Plumbline(TMPoint aPointQ,TMPoint& aCrossPt) const;

public:

    // ���߶εļн�(�û��ȱ�ʾ����Χ [0,��])
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
        TCoordinateType iType = ECartesian);// �������Ͻ������½ǵ㹹��

    TMRect(const TMPoint& aDiagonalPt1,const TMPoint& aDiagonalPt2,
        TCoordinateType iType = ECartesian); // �����������㹹��

    TMRect(const TMPoint& aTl,TMSize aSize,
        TCoordinateType iType = ECartesian);// TopLeft �� Size

    TMRect(const TMPoint& aCenter,TLcType aWidth,TLcType aHeight,
        TCoordinateType iType = ECartesian);// Center + width +height

    TMRect(const CMPointVector& aPloygon,
        TCoordinateType iType = ECartesian);  // �������ε���Ӿ���

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


