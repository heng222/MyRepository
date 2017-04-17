#include "StdAfx.h"
#include "TSignLetter.h"

#include <fstream>
using namespace std;

//////////////////////////////////////////////////////////////////////////
TSignLetter::TSignLetter(void)
{
    FHeight = 0;
    FWidth = 0;
    FCharID = 0;
    FFontID = 0;
    ZeroMemory(FText,sizeof(FText));
}

TSignLetter::~TSignLetter(void)
{
    FBitmap.resize(0);
}

//////////////////////////////////////////////////////////////////////////
// TSignLetter

TSignLetter& TSignLetter::operator =(const TSignLetter& another)
{
    if (this!=&another)
    {
        FHeight = another.FHeight;
        FWidth = another.FWidth;
        FBitmap = another.FBitmap;
        FCharID = another.FCharID;
        FFontID = another.FFontID;
        memcpy(FText,another.FText,sizeof(FText));
    }

    return *this;
}

BYTE&  TSignLetter::operator[](size_t pos)
{
    return FBitmap[pos];
}

VOID  TSignLetter::ReadLetter(std::ifstream& DataStream)
{
    DataStream.read((char*)&FFontID,1);
    DataStream.read((char*)&FCharID,2);
    DataStream.read((char*)&FWidth,1);
    DataStream.read((char*)&FHeight,1);

    ResizeBitmap();

    for (INT i=0; i<(FWidth * FHeight); i++)
    {
        DataStream.read((char*)&FBitmap[i],1);
    }

    if (FFontID==0) 
    {
        DataStream.read(FText,25);
    }
}

VOID  TSignLetter::DrawLetter(INT XPos,INT YPos, const TRGBQuad& clrLetter,
                              TRGBQuadBitmap& MyBitmap, BOOL bBottomUp )
{    
    INT iRawIndex = 0;

    if (!bBottomUp)
    {
        for(INT YIndex= 0; YIndex<FHeight; YIndex++) 
        {
            for(INT XIndex=0; XIndex<FWidth; XIndex++)
            {
                iRawIndex = (YIndex*FWidth) + XIndex;
                if(FBitmap[iRawIndex] > 0)
                {
                    MyBitmap.SetBitmapPixel(XPos+XIndex,
                        YPos+YIndex,
                        clrLetter);
                }
            }
        }   
    }
    else
    {
        INT iCanvasHeight = MyBitmap.GetHeight();

        for(INT YIndex= 0; YIndex<FHeight; YIndex++) 
        {
            for(INT XIndex=0; XIndex<FWidth; XIndex++)
            {
                iRawIndex = (FHeight-YIndex-1)*FWidth + XIndex;
                if(FBitmap[iRawIndex] > 0)
                {
                    MyBitmap.SetBitmapPixel(XPos+XIndex,
                        ((iCanvasHeight-1)-FHeight)+YIndex-YPos,
                        clrLetter );
                }
            }
        }   
        
    }

}

VOID  TSignLetter::SetHeight(INT iValue)
{
    FHeight = iValue;
    ResizeBitmap();
}

INT   TSignLetter::GetHeight() const
{
    return FHeight;
}

VOID  TSignLetter::SetWidth(INT iValue)
{
    FWidth = iValue;
    ResizeBitmap();
}

INT   TSignLetter::GetWidth() const
{
    return FWidth;

}

VOID  TSignLetter::SetBitmap(const TBitmapArray& bmpArray)
{
    FBitmap = bmpArray;
}

VOID  TSignLetter::GetBitmap(TBitmapArray*& bmpArray)
{
    bmpArray = &FBitmap;
}

VOID  TSignLetter::SetCharID(WORD wValue)
{
    FCharID = wValue;
}

WORD  TSignLetter::GetCharID() const
{
    return FCharID;
}

VOID  TSignLetter::SetFontID(BYTE byID)
{
    FFontID = byID;
}

BYTE  TSignLetter::GetFontID() const
{
    return FFontID;
}

VOID  TSignLetter::GetText(TString& strText) const
{

#ifdef _UNICODE
    for (INT i=0; i<sizeof(FText)/sizeof(FText[0]); i++)
    {
        if (FText[i]!=0)
        {
            strText.push_back(FText[0]);
        }
        else
        {
            break;
        }
    }
#else
    strText = FText;
#endif
}

VOID  TSignLetter::ResizeBitmap()
{
    size_t newSize = FWidth * FHeight;
    if (newSize>=0)
    {
        FBitmap.resize(newSize);
    }
    else
    {
        FBitmap.resize(0);
    }
}






