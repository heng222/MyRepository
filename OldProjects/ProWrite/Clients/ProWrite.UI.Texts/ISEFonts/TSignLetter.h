#ifndef _SIGN_LETTER_HPP_
#define _SIGN_LETTER_HPP_
//////////////////////////////////////////////////////////////////////////

#include "RGBQuadBitmap.h"


enum TTLXSignFont
{ 
    ftPictorials = 0,
    ft16Triple, 
    ft12Double, 
    ft7Double, 
    ft7Single,
    ft8Double, 
    ft8Single, 
    ft24Quad, 
    ft11Double, 
    ftExtra3, 
    ftExtra4,
    ftExtra5, 
    ftExtra6, 
    ftExtra7, 
    ftExtra8, 
    ftDefault
};

typedef std::set<TTLXSignFont> TTLXFontGroup;

//////////////////////////////////////////////////////////////////////////
// TSignLetter
class TSignLetter
{
public:

    TSignLetter(VOID);
    ~TSignLetter(VOID);


    //
    inline bool operator<(const TSignLetter &other) const
    {
        return FCharID<other.FCharID; 
    }

public:

    VOID  ReadLetter(std::ifstream& DataStream);

    VOID  DrawLetter(INT XPos,INT YPos, 
            const TRGBQuad& clrLetter,
            TRGBQuadBitmap& MyBitmap, 
            BOOL bBottomUp = FALSE );

    VOID  SetHeight(INT iValue);
    INT   GetHeight() const;

    VOID  SetWidth(INT iValue);
    INT   GetWidth() const;

    VOID  SetBitmap(const TBitmapArray& bmpArray);
    VOID  GetBitmap(TBitmapArray*& bmpArray);

    VOID  SetCharID(WORD wValue);
    WORD  GetCharID() const;

    VOID  SetFontID(BYTE byID);
    BYTE  GetFontID() const;

    VOID  GetText(TString& strText) const;

    TSignLetter& operator=(const TSignLetter& another);
    BYTE&  operator[](size_t pos);

public:


protected:

    VOID  ResizeBitmap();


private:

    INT   FHeight;  // letter's height
    INT   FWidth;   // letter's width

    WORD  FCharID;
    BYTE  FFontID;
    char  FText[25]; // for pictorial letter

    TBitmapArray  FBitmap; // letter's content

};

typedef std::vector<TSignLetter*> TSignLetterList;

//////////////////////////////////////////////////////////////////////////
#endif