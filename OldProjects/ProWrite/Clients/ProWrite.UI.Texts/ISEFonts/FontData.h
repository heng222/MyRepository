#pragma once

#include "TSignFont.h"


//////////////////////////////////////////////////////////////////////////
// TSignFontData

class TSignFontData
{
public:

    TSignFontData();
    ~TSignFontData();

    TSignFont* operator[](size_t pos);

public:

    BOOL  Create(const TString& strFileName);
    VOID  Destroy();   
    
    INT   GetFountCount();
    
    INT   GetFontSizeOrder(INT SizeIndex);
    
    INT   GetFontSizeOrderCount();
    
    VOID  SetValidFonts(const TTLXFontGroup& Value);
    VOID  GetValidFonts(TTLXFontGroup*& pTLXFontGroup);

    VOID  SortFonts();

    INT   FontSizeIndex(TTLXSignFont FontIndex);

    VOID  UpdateFontPrototypes(const TString& Str1,
            const TString& Str2,
            const TString& Str3,
            const TString& Str4, 
            const TString& Str5);

public:

    // return number of fonts.
    INT   EnumFontNames(TStringList& fontNameList) const;

    // 
    //INT   GetProperFont(const TString& strText,);
    
    //
    BOOL  IsISEFont(const TString& strFontName) const;


    TSignFont*  GetFont(const TString& strFontName);

    INT   GetFontHeight(const TString& strFontName) const;


protected:


    VOID  UpdateLetter(TSignFont& CurrFont,WORD LetterVal, const TString& NewData);
    VOID  ResizeFonts();

private:

    TSignFontList  FFontList;

    TNumberArray   FFontSizeList ;

    TTLXFontGroup  FValidFonts ;

};

//////////////////////////////////////////////////////////////////////////
// End of file