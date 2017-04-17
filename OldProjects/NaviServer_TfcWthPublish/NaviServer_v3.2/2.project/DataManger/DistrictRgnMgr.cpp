#include "StdAfx.h"
#include "DistrictRgnMgr.h"
#include "GlobalMacro.h"
#include "InterfaceEx.h"

//////////////////////////////////////////////////////////////////////////

#define     FILENAME_MAINCITY   _T("MapCity.can")

#define     MIN_MAPID       274800
#define     MAX_MAPID       806477
//////////////////////////////////////////////////////////////////////////

CDistrictRgnMgr::CDistrictRgnMgr(void)
{
}

CDistrictRgnMgr::~CDistrictRgnMgr(void)
{
}


//////////////////////////////////////////////////////////////////////////

BOOL CDistrictRgnMgr::Open()
{
    m_strFilePath = GetExePath()+PATH_DATA_FILE+FILENAME_MAINCITY;

    CFile mapFile;
    if ( !mapFile.Open(m_strFilePath,CFile::modeRead) )
    {
        return FALSE;
    }
    mapFile.Close();

    return TRUE;
}

short CDistrictRgnMgr::GetDistIdxByPos(DWORD dwLongi,DWORD dwLati) const
{
    long lMapId =  CalMapID( dwLongi,dwLati );
    if (lMapId>=MIN_MAPID && lMapId<=MAX_MAPID)
    {
        short  iCityIdx = 0;
        bGetCityID(  dwLongi , dwLati , lMapId , iCityIdx );
        return iCityIdx+1;
    }
    else
    {
        return EINVALID_DISTID;
    }
}

//////////////////////////////////////////////////////////////////////////

// 判断点C是否在区域内
bool CDistrictRgnMgr::bPointInArea( const long dCx, const long dCy, short nsPointArrCount, POINT vPointArr[] ) const
{
    bool bInside = false;
    POINT*  U0 = NULL;
    POINT*  U1 = NULL;
    for ( int	_d =0, _k = nsPointArrCount-1 ;
        _d < (int)nsPointArrCount;
        _k = _d, _d++						)
    {
        U0 = &vPointArr[ _d ];
        U1 = &vPointArr[ _k ];
        if ( dCy < U1->y )
        {
            if ( U0->y <= dCy )
            {
                if ( ( dCy - U0->y )*( U1->x - U0->x ) > ( dCx - U0->x )*( U1->y - U0->y ))
                {
                    bInside = !bInside;
                }
            }
        }
        else if( dCy < U0->y )
        {
            if ( ( dCy - U0->y )*( U1->x - U0->x ) < ( dCx - U0->x )*( U1->y - U0->y ))
            {
                bInside = !bInside;
            }
        }
    }

    return bInside;
}

bool CDistrictRgnMgr::bGetCityID(const long x, const long y, const int niDisNumber, short& nsCityId ) const
{
    // open file
    FILE* fp = NULL;
    fp = _tfopen( m_strFilePath, _T("rb") );
    if( fp == NULL )
        return false;

    // read index off
    fseek( fp, 24, SEEK_SET );
    unsigned long	nlZIndexOff;
    fread( &nlZIndexOff, sizeof(nlZIndexOff), 1, fp );
    fseek( fp, nlZIndexOff, SEEK_SET );

    // compute index number
    int niIndexToId = (niDisNumber/100 - 2748)*64 + (niDisNumber%100/10*8 + niDisNumber%10 );
    niIndexToId *= 6;
    niIndexToId += nlZIndexOff;
    fseek( fp, niIndexToId, SEEK_SET );

    // read count&off
    short	nsIndexCount; 
    unsigned long nlIndexOff ;
    fread( &nsIndexCount,	sizeof(nsIndexCount),	1, fp );
    fread( &nlIndexOff,sizeof(nlIndexOff),1, fp );
    // 0
    if( nsIndexCount == 0 )
    {
        fclose(fp);
        return false;
    }
    // To  position
    fseek( fp, nlIndexOff, SEEK_SET );

    short	nsIndexName ;
    // if district = 1
    if( nsIndexCount == 1 )	
    {	
        fread( &nsIndexName,	sizeof(nsIndexName),	1, fp );
        nsCityId = nsIndexName -1;
        fclose(fp);
        return true;
    }
    else	// more
    {
        for( int i=0; i<nsIndexCount;i++ )
        {
            // get polygon point arr
            fread( &nsIndexName,	sizeof(nsIndexName),	1, fp );
            fread( &nsIndexCount,	sizeof(nsIndexCount),	1, fp );
            POINT * vPointArr = new POINT[nsIndexCount];
            // read data
            fread( vPointArr, sizeof(POINT), nsIndexCount, fp );

            if( bPointInArea( x, y, nsIndexCount, vPointArr ) ) // if in polygon0
            {
                nsCityId = nsIndexName - 1;
                fclose(fp);
                delete []vPointArr;
                return true;
            }
            delete []vPointArr;
        }
    }
    fclose(fp);
    return false;
}

// 得到MAPID值
long CDistrictRgnMgr::CalMapID(DWORD curdx,DWORD curdy) const
{
    double dx = curdx/(24*3600.0);
    double dy = curdy/(24*3600.0);

    long nCurXParcel = long(dx)-60;
    long nCurYParcel = long(dy*60/40);
    long nSecXParcel = long((dx-int(dx))*8);
    long nSecYParcel = long((dy-nCurYParcel*40/60.0)*12);
    long mapID = (nCurYParcel*100+nCurXParcel)*100;		
    mapID += nSecYParcel *10 + nSecXParcel;
    return mapID ;
}


