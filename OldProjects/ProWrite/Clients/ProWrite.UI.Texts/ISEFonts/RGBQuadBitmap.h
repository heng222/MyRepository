#pragma once

//////////////////////////////////////////////////////////////////////////


#include <vector>
#include <set>
#include <list>
#include <string>


//////////////////////////////////////////////////////////////////////////
// TYPE

typedef  RGBQUAD    TRGBQuad;  

typedef  std::vector<TRGBQuad>  TRGBQuadArray;

typedef  std::vector<BYTE>      TBitmapArray;

typedef  std::vector<INT>       TNumberArray;

#ifdef _UNICODE
typedef std::wstring        TString;
#else
typedef std::string         TString;
#endif

typedef  std::vector<TString>   TStringList;

//////////////////////////////////////////////////////////////////////////
// CONST

const TRGBQuad rgbqBlack = {0,0, 0,0};
const TRGBQuad rgbqWhite = {255, 255, 255, 255};
const TRGBQuad rgbqTransparent = {0,0,0,1};



//////////////////////////////////////////////////////////////////////////
// class TRGBQuadBitmap
class TRGBQuadBitmap
{
public:

    TRGBQuadBitmap(void);
    ~TRGBQuadBitmap(void);

public:

    VOID  Blank(const TRGBQuad& clrBkg);
    VOID  Blank(COLORREF clrBkg);

    INT   GetHeight() const;
    VOID  SetHeight(INT iHeight);

    INT   GetWidth() const;
    VOID  SetWidth(INT iWidth);

    VOID  SetSize(INT iWidth,INT iHeight);

    BOOL  GetBitmapStart(TRGBQuadArray*& rgbArray);

    size_t GetBitmapLength() const;

    TRGBQuad  GetBitmapPixel(INT X,INT Y) const;
    VOID      SetBitmapPixel(INT X,INT Y, const TRGBQuad& rgbValue);

public:

    const TRGBQuad*  GetBitmapBits();

    // convert TRGBQuadBitmpa to HBITMAP
    HBITMAP ToHBITMAP();


protected:

    VOID  ResizeBitmap();

private:


private:

    TRGBQuadArray  FBitmapArray;
    INT  FWidth;
    INT  FHeight;

private:


};


//////////////////////////////////////////////////////////////////////////
// End of file