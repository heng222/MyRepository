#include "StdAfx.h"
#include "TSignFont.h"

using namespace std;

/////////////////////////// { TSignFont } ///////////////////////////////////////////////

TSignFont::TSignFont()
{
    FFontHeight = 0;
    FFontWidth = 0;
    //FLetterPos = 0;
    FFontID = 0;
}

TSignFont::~TSignFont()
{
    Destroy();
}

VOID  TSignFont::Initialize()
{
    CreateFontName(m_strFontName);
}

VOID  TSignFont::Destroy()
{
    if (FLetterList.size()>0)
    {
        TSignLetter* pSignLetter = NULL;

        for (TSignLetterList::iterator iCur=FLetterList.begin(); iCur!=FLetterList.end(); iCur++)
        {
            pSignLetter = *iCur;
            delete pSignLetter;
        }

        FLetterList.resize(0);
    }
}

TSignLetter* TSignFont::operator[](size_t pos)
{
    return FLetterList[pos];
}

VOID  TSignFont::SortFont()
{
    TSignLetter* pTemp;
    size_t iNum = FLetterList.size();

    for (size_t IndexX=0; IndexX<iNum; IndexX++)
    {
        for (size_t IndexY=IndexX + 1; IndexY<iNum; IndexY++)
        {
            if( FLetterList[IndexX]->GetCharID() > FLetterList[IndexY]->GetCharID() )
            {
                pTemp = FLetterList[IndexX];
                FLetterList[IndexX] = FLetterList[IndexY];
                FLetterList[IndexY] = pTemp;
            }
        }
    }

}

INT TSignFont::Found(INT LetterVal) const
{
    INT Num = 0;
    INT Result = -1;
    INT Low = 0;
    INT High = INT(FLetterList.size() - 1);
    INT Mid = (Low + High) / 2;

    while (Low != High)
    {
        Num = FLetterList[Mid]->GetCharID();
        if (Num > LetterVal)
        {
            High = Mid - 1;
            if(High < 0)
            {
                High = 0;
            }
        }
        else if(Num < LetterVal)
        {
            Low = Mid + 1;
        }
        else
        {
            Low = Mid;
            High = Mid;
        }
        Mid = (Low + High) / 2;
    }


    if (FLetterList[Mid]->GetCharID() == LetterVal)
    {
        Result = Mid;
    }

    return Result;
}

VOID  TSignFont::SetFontHeight(INT Value)
{
    FFontHeight = Value;
}   
INT   TSignFont::GetFontHeight() const
{
    return FFontHeight;
}

VOID  TSignFont::SetFontWidth(INT Value)
{
    FFontWidth = Value;
}
INT   TSignFont::GetFontWidth() const
{
    return FFontWidth;
}

VOID  TSignFont::SetLetterList(const TSignLetterList& Value)
{
    FLetterList = Value;
}
VOID  TSignFont::GetLetterList(TSignLetterList*& pLetterList)
{
    pLetterList = &FLetterList;
}

VOID  TSignFont::GetLetter(INT LetterIndex, TSignLetter*& pLetter)
{
    if ( LetterIndex>=0 && LetterIndex<(INT)(FLetterList.size()) )
    {
        pLetter = FLetterList[LetterIndex];
    }
    else
    {
        pLetter = NULL;
    }
}


INT   TSignFont::GetLetterCount() const
{
    return (INT)FLetterList.size();
}

VOID TSignFont::CreateFontName(TString& strName) 
{

    TCHAR cTemp[20] = {0};

#ifdef _UNICODE
    //_itow(FFontHeight,cTemp,10);
    _itow_s(FFontHeight,cTemp,10);
#else
    _itoa(FFontHeight,cTemp,10);
#endif


    strName = TString(cTemp);
    strName += _T(" High ");

    INT SizeOfPoint = GetSize(_T("."));

    switch (SizeOfPoint)
    {
    case 0:
        strName += _T("Pictorials");
        break;

    case 2:
        strName += _T("Single");
        break;

    case 3:
        strName += _T("Double");
        break;

    case 4:
        strName += _T("Triple");
        break;

    case 5:
        strName += _T("Quad");
        break;

    default :
        strName += _T("Large");
        break;
    }
}

TString TSignFont::GetFontName() const
{
    return m_strFontName;
}


VOID  TSignFont::SetFontID(INT Value)
{
    FFontID = Value;
}
INT   TSignFont::GetFontID() const
{
    return FFontID;
}

VOID  TSignFont::AddLetter(TSignLetter* ALetter)
{
    FLetterList.push_back(ALetter);

    // 
    if (FFontHeight < ALetter->GetHeight())
    {
        FFontHeight = ALetter->GetHeight();
    }

    // 
    if (FFontWidth < ALetter->GetWidth())
    {
        FFontWidth = ALetter->GetWidth();
    }

}

VOID  TSignFont::DrawLetter(TRGBQuadBitmap& ABitmap, INT& XPos,INT& YPos,
                            WORD TheDrawLetter, INT FontHeight)
{
    INT FLetterPos = Found(TheDrawLetter);
    if ( FLetterPos!=-1 )
    {
        INT YOff = FontHeight - FLetterList[FLetterPos]->GetHeight();

        FLetterList[FLetterPos]->DrawLetter(XPos,YPos+YOff,rgbqWhite,ABitmap);

        XPos += FLetterList[FLetterPos]->GetWidth();
    }

}

VOID  TSignFont::TextOut( int nXStart,// x-coordinate of starting position
              int nYStart,// y-coordinate of starting position
              const TString& strText, // character string
              const TRGBQuad& clrText,
              TRGBQuadBitmap& bmpText, // bitmap
              INT iKernAmount  // 
              ) const
{
    size_t iNum = strText.size();
    INT FLetterPos;

    for (size_t i=0; i<iNum; i++)
    {
        FLetterPos = Found(strText[i]);
        if ( FLetterPos!=-1 )
        {
            TSignLetter* pLetter = FLetterList[FLetterPos];
            pLetter->DrawLetter(nXStart,nYStart,clrText,bmpText);
            nXStart += pLetter->GetWidth();
            nXStart += iKernAmount;
        }
    }
}

INT TSignFont::GetSize(const TString& TextData) const
{
    INT DrawValue;
    INT BigDrawValue = 0;
    INT Result = 0;
    INT FLetterPos;

    for (size_t Index=0; Index<TextData.size(); Index++) 
    {
        DrawValue = TextData[Index];

        if (BigDrawValue > 0 )
        {
            DrawValue += BigDrawValue * 256;
            BigDrawValue = 0;
        }

        if ((DrawValue < 256) && (DrawValue > 239))
        {
            BigDrawValue = DrawValue;
        }
        else if( (FLetterPos=Found(DrawValue))!=-1 ) 
        {
            Result += FLetterList[FLetterPos]->GetWidth();
        }
        else
        {
            // do nothing.
        }
    }

    return Result;
}

INT   TSignFont::GetHeight(const TString& TextData) const
{

    INT  DrawValue;
    INT  BigDrawValue = 0;
    INT  Result = 0;

    BOOL SpaceFound = FALSE;
    BOOL PictorialFound = FALSE;
    BOOL NonPictorialFound = FALSE;

    if (TextData.empty() && (FFontID != 0) )
    {
        Result = FFontHeight;
    }

    for(size_t Index=0; Index<TextData.size(); Index++)
    {
        DrawValue = TextData[Index];

        if( BigDrawValue > 0 )
        {
            DrawValue = DrawValue + BigDrawValue * 256;
            BigDrawValue = 0;
        }

        if((DrawValue > 26) && (DrawValue < 128) )
        {
            NonPictorialFound = TRUE;
        }

        if (DrawValue > 127) 
        {
            PictorialFound = TRUE;
        }

        if ((DrawValue < 256) && (DrawValue > 239))
        {
            BigDrawValue = DrawValue;
        }
        else if ((DrawValue == 14) && (FFontID != 0)) 
        {
            if (NonPictorialFound)
            {
                Result = FFontHeight;
            }
            else if (TextData.size() == 1)
            {
                Result = FFontHeight;
            }
        }
        else if(DrawValue == 32)
        {
            SpaceFound = TRUE;
        }
        else if (DrawValue == 0x0C)
        {
            Result = Result;
        }
        else 
        {
            INT FLetterPos = Found(DrawValue) ;
            if (FLetterPos!=-1)
            {
                if ( Result < FLetterList[FLetterPos]->GetHeight() )
                {
                    Result = FLetterList[FLetterPos]->GetHeight();
                }
            }
        }
    } // End of for

    if (SpaceFound && (FFontID != 0) && (!PictorialFound))
    {
        Result = FFontHeight;
    }

    return Result;
}