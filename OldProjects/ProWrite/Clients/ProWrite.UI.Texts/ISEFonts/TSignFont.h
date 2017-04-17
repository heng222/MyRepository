

#ifndef _TSIGN_FONT_HPP_20090112_
#define _TSIGN_FONT_HPP_20090112_

#include "TSignLetter.h"

//////////////////////////////////////////////////////////////////////////
// TSignFont

class TSignFont
{

    friend class TSignFontData;

public:

    TSignFont(VOID);
    ~TSignFont(VOID);

    TSignLetter* operator[](size_t pos);

public:

    VOID  Initialize();
    VOID  Destroy();

    VOID  SetFontHeight(INT Value);
    INT   GetFontHeight() const;

    VOID  SetFontWidth(INT Value);
    INT   GetFontWidth() const;

    VOID  SetLetterList(const TSignLetterList& Value);
    VOID  GetLetterList(TSignLetterList*& pLetterList);

    VOID  GetLetter(INT LetterIndex, TSignLetter*& pLetter);

    INT   GetLetterCount() const;
    
    TString  GetFontName() const;

    VOID  SetFontID(INT Value);
    INT   GetFontID() const;

    VOID  AddLetter(TSignLetter* ALetter);

    VOID  DrawLetter(TRGBQuadBitmap& ABitmap, INT& XPos,INT& YPos,
                WORD TheDrawLetter, INT FontHeight);

    VOID  TextOut( int nXStart,       // x-coordinate of starting position
                   int nYStart,       // y-coordinate of starting position
                   const TString& strText, // character string
                   const TRGBQuad& clrText, // text color
                   TRGBQuadBitmap& bmpText, // bitmap
                   INT iKernAmount = 0  // 
                   ) const;

    INT   GetSize(const TString& TextData) const;

    INT   GetHeight(const TString& TextData) const;


protected:

    VOID  SortFont();

    INT   Found(INT LetterVal) const;

    VOID  CreateFontName(TString& strName) ;

private:

    TSignLetterList  FLetterList;

    INT  FFontHeight; // max height
    INT  FFontWidth;  // max width

    //INT  FLetterPos;

    INT  FFontID;

private:

    TString  m_strFontName;
};

typedef std::vector<TSignFont*> TSignFontList;

//////////////////////////////////////////////////////////////////////////
#endif