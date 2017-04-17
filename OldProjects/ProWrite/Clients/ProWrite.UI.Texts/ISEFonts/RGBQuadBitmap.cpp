#include "StdAfx.h"
#include "RGBQuadBitmap.h"
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
TRGBQuadBitmap::TRGBQuadBitmap(void)
{
    FWidth = 0;
    FHeight = 0;
}

TRGBQuadBitmap::~TRGBQuadBitmap(void)
{
    FBitmapArray.resize(0);
}


//////////////////////////////////////////////////////////////////////////
//
void TRGBQuadBitmap::Blank(const TRGBQuad& clrBkg)
{
    for (size_t i=0; i<FBitmapArray.size(); i++)
    {
        FBitmapArray[i] = clrBkg;
    }
}

void TRGBQuadBitmap::Blank(COLORREF clrBkg)
{
    TRGBQuad quad;
    quad.rgbRed = GetRValue(clrBkg);
    quad.rgbGreen = GetGValue(clrBkg);
    quad.rgbBlue = GetBValue(clrBkg);

    for (size_t i=0; i<FBitmapArray.size(); i++)
    {
        FBitmapArray[i] = quad;
    }
}

size_t TRGBQuadBitmap::GetBitmapLength() const
{
    return FBitmapArray.size();
}

TRGBQuad TRGBQuadBitmap::GetBitmapPixel(INT X,INT Y) const
{
    if ( X>=0 && Y>=0 && Y<FHeight && X<FWidth)
    {
        return FBitmapArray[X+(FHeight-Y-1)*FWidth];
    }
    else
    {
        return rgbqBlack;
    }
}

BOOL TRGBQuadBitmap::GetBitmapStart(TRGBQuadArray*& rgbArray)
{
    if (FBitmapArray.size()> 0)
    {
        rgbArray = &FBitmapArray;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void TRGBQuadBitmap::ResizeBitmap()
{
    if (FWidth>0 && FHeight>0)
    {
        size_t newSize = FWidth * FHeight;
        FBitmapArray.resize(newSize); // stride?
    }
}

void TRGBQuadBitmap::SetBitmapPixel(INT X,INT Y, const TRGBQuad& rgbValue)
{
    if ( (X>=0) &&  (Y>=0) && (X<FWidth) && (Y<FHeight) )
    {
        FBitmapArray[X + (FHeight-Y-1)*FWidth] = rgbValue;
    }
}

void TRGBQuadBitmap::SetHeight(INT iHeight)
{
    FHeight = iHeight;
    ResizeBitmap();
}

void TRGBQuadBitmap::SetWidth(INT iWidth)
{
    FWidth = iWidth;
    ResizeBitmap();
}

INT TRGBQuadBitmap::GetHeight() const
{
    return FHeight;
}

INT TRGBQuadBitmap::GetWidth() const
{
    return FWidth;
}

VOID TRGBQuadBitmap::SetSize(INT iWidth,INT iHeight)
{
    FWidth = iWidth;
    FHeight = iHeight;
    ResizeBitmap();
}


const TRGBQuad* TRGBQuadBitmap::GetBitmapBits()
{
    if (FBitmapArray.size()>0)
    {
        return (&FBitmapArray[0]);
    }
    else
    {
        return NULL;
    }
}


HBITMAP TRGBQuadBitmap::ToHBITMAP()
{
    if (FBitmapArray.size()<=0 || FHeight<=0 || FWidth<=0)
    {
        return NULL;
    }

#if 0
    TBitmapArray    tempBitsArray;

    // Stride
    LONG iStride = (FWidth * 32 / 8 +3)/4 * 4;

    // allocate memory
    LONG lBufSize = iStride * FHeight;
    tempBitsArray.resize(lBufSize);

    // Convert top-down to bottom-up.
    for (INT m=0; m<FHeight; m++)
    {
        memcpy( &tempBitsArray[(FHeight-m-1)*iStride],
            &FBitmapArray[m*FWidth],
            FWidth*4);        
    }

    // Create a 32-bit bitmap.
    HBITMAP hBitmap = ::CreateBitmap(FWidth,FHeight,
        1,32,&FBitmapArray[0]);

    //
    return hBitmap;
#endif

    // create a bitmap information structor
    BITMAPINFO bmpInfo = {
        {
            sizeof(BITMAPINFOHEADER),
            FWidth,	FHeight,	1,	32,	
            BI_RGB,	0,	0,	0
        },{ 0 }
    };


    //
    HDC hdcDesk = ::GetDC(NULL);

    HBITMAP hbm = ::CreateDIBitmap(hdcDesk, 
        &(bmpInfo.bmiHeader),
        CBM_INIT, 
        &FBitmapArray[0], 
        &bmpInfo, 
        DIB_RGB_COLORS);

    ::ReleaseDC(NULL,hdcDesk);

    return hbm;
}
