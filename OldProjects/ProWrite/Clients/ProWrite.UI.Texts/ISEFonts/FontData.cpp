#include "StdAfx.h"
#include "FontData.h"
#include <stdlib.h>
#include <fstream>
#include <ios>

using namespace std;
//////////////////////////////////////////////////////////////////////////





//////////////////////////   { TSignFontData } //////////////////////////////////////////

TSignFontData::TSignFontData()
{

}

TSignFontData::~TSignFontData()
{
    Destroy();
}

VOID  TSignFontData::ResizeFonts()
{
    TNumberArray FontAreaList ;
    INT LocalFontCount;
    INT FontIndex;
    INT Index;
    INT IndexY;
    INT Holder;

    INT FontCount = GetFountCount();

    // -1 because the pictorial font isn't included in the sizing
    LocalFontCount = FontCount;

    // Decrement if the 8 high font is being used, or if it is the only one
    // being used.
    FontAreaList.resize(LocalFontCount-1);
    FFontSizeList.resize(LocalFontCount-1);

    FontIndex = 0;

    for(Index = 0; Index<FontCount; Index++)
    {
        if( FValidFonts.find(TTLXSignFont(Index))!=FValidFonts.end() )
        {
            FontAreaList[FontIndex] = FFontList[Index]->GetSize(_T("I")) * FFontList[Index]->GetHeight(_T("I"));
            FFontSizeList[FontIndex] = Index;
            FontIndex++;
        }
    }


    FontAreaList.resize(FontIndex);
    FFontSizeList.resize(FontIndex);

    for( Index= 0; Index< FontIndex - 1; Index++)
    {
        for (IndexY = Index; IndexY< FontIndex; IndexY++)
        {
            if (FontAreaList[Index] < FontAreaList[IndexY]) 
            {
                Holder = FontAreaList[Index];
                FontAreaList[Index] = FontAreaList[IndexY];
                FontAreaList[IndexY] = Holder;
                Holder = FFontSizeList[Index];
                FFontSizeList[Index] = FFontSizeList[IndexY];
                FFontSizeList[IndexY] = Holder;
            }
        }
    }
}


BOOL TSignFontData::Create(const TString& strFileName)
{
    WORD CharCount;
    ifstream DataStream;
    size_t Index;
    INT Index2;
    TSignLetter* NewLetter;
    TSignFont* NewFont;


    // 
    FValidFonts.insert(ft7Double);
    FValidFonts.insert(ft7Single);

    // read data from file
    try
    {
        DataStream.open(strFileName.c_str());
    }
    catch(...)
    {
        return FALSE;
    }

    // determine if open success.
    ios_base::iostate st = DataStream.rdstate();
    if (st!=ios_base::goodbit)
    {
        return FALSE;
    }

    // read the number of letter
    DataStream.read((char*)&CharCount,2);

    // 
    for(Index = 0 ; Index< CharCount; Index++ )
    {
        NewLetter = new TSignLetter;
        NewLetter->ReadLetter(DataStream);

        INT iFontID = NewLetter->GetFontID();    
        INT iNumFonts = INT(FFontList.size());

        // create enought TSignFont
        while( (iFontID+1) > iNumFonts )
        {
            NewFont = new TSignFont;
            NewFont->SetFontID(iNumFonts);
            FFontList.push_back(NewFont);
            iNumFonts = INT(FFontList.size());
        }
   
        // add letter to the relevant TSignFont
        FFontList[iFontID]->AddLetter( NewLetter );
    }

    // clost stream
    DataStream.close();

    // Add replaceable font data here
    for (Index = 1; Index< FFontList.size(); Index++)  // Index=1: we don't need to do this to pictorials
    {
        for ( Index2 = 0; Index2<=4; Index2++) // 4 is hard coded because there are 5 replaceable
        {
            NewLetter = new TSignLetter;
            NewLetter->SetFontID(Index);
            NewLetter->SetCharID(0x15 + Index2);
            FFontList[Index]->AddLetter(NewLetter);
        }
    }

    // sort
    SortFonts();

    // resize
    ResizeFonts();

    // Initialize fonts
    for (Index = 0; Index< FFontList.size(); Index++)  // 
    {        
        FFontList[Index]->Initialize();        
    }

    // return
    return TRUE;
}

VOID TSignFontData::Destroy()
{
    if (FFontList.size()>0)
    {
        for (TSignFontList::iterator iCur=FFontList.begin(); iCur!=FFontList.end(); iCur++)
        {
            TSignFont* pSignFont = *iCur;
            delete pSignFont;
        }

        FFontList.resize(0);
    }
}



INT TSignFontData::GetFountCount()
{
    return (INT)FFontList.size();
}

INT   TSignFontData::GetFontSizeOrder(INT SizeIndex)
{
    if ( (SizeIndex >= 0) && (SizeIndex < (INT)FFontSizeList.size()) )
    {
        return FFontSizeList[SizeIndex];
    }
    else
    {
        return -1;
    }

}

INT   TSignFontData::GetFontSizeOrderCount()
{
      return FFontSizeList.size();
}

VOID  TSignFontData::SetValidFonts(const TTLXFontGroup& Value)
{
    FValidFonts = Value;
    ResizeFonts();
}

VOID  TSignFontData::GetValidFonts(TTLXFontGroup*& pTLXFontGroup)
{
    pTLXFontGroup = &FValidFonts;
}

VOID  TSignFontData::SortFonts()
{
    TSignFont* pTemp;

    // sort font
    for( size_t m = 0; m<FFontList.size(); m++)
    {
        for( size_t n = m+1; n<FFontList.size(); n++)
        {
            if( FFontList[m]->GetFontHeight() > FFontList[n]->GetFontHeight() )
            {
                pTemp = FFontList[m];
                FFontList[m] = FFontList[n];
                FFontList[n] = pTemp;
            }
        }
    }

    // sort letter
    for( size_t Index = 0; Index<FFontList.size(); Index++)
    {
        FFontList[Index]->SortFont();
    }

}

INT   TSignFontData::FontSizeIndex(TTLXSignFont FontIndex)
{
    for( INT Index = 0; Index<= GetFontSizeOrderCount() - 1; Index++ )
    {
        if ( GetFontSizeOrder(Index) == FontIndex )
        {
            return Index;
        }
    }

    return -1;
}
VOID  TSignFontData::UpdateLetter(TSignFont& CurrFont, WORD LetterVal, const TString& NewData)
{

    TSignLetter* UpdatedLetter ;
    TCHAR CurrDataChar;
    TSignLetter* DataSearchLetter ;
    size_t Index1;
    INT IndexLX;
    INT IndexLY;
    INT CurrWidth;
    INT iPos;
    
    iPos = CurrFont.Found(LetterVal);
    if( iPos!=-1 )
    {
        CurrFont.GetLetter(iPos,UpdatedLetter);
        UpdatedLetter->SetWidth(0);
        // If UpdatedLetter.Width = 0 Then Begin

        for (Index1 = 0; Index1< NewData.size(); Index1++ )
        {
            CurrDataChar = NewData[Index1];
            iPos = CurrFont.Found(INT(CurrDataChar));
            if ( iPos!=-1 )
            {
                CurrFont.GetLetter(iPos, DataSearchLetter);
                UpdatedLetter->SetWidth( UpdatedLetter->GetWidth() + DataSearchLetter->GetWidth());

                if (UpdatedLetter->GetHeight() < DataSearchLetter->GetHeight())
                {
                    UpdatedLetter->SetHeight(DataSearchLetter->GetHeight());
                }

            }
        }

        //
        CurrWidth = 0;

        //
        for (Index1 = 0; Index1<NewData.size(); Index1++ )
        {
            CurrDataChar = NewData[Index1];

            iPos = CurrFont.Found((CurrDataChar));
            if ( iPos!=-1 )
            {
                CurrFont.GetLetter(iPos,DataSearchLetter);
                
                for (IndexLY = 0;  IndexLY<DataSearchLetter->GetHeight(); IndexLY++)
                {
                    for (IndexLX = 0;  IndexLX<DataSearchLetter->GetWidth(); IndexLX++ )
                    {
                        (*UpdatedLetter)[IndexLY * UpdatedLetter->GetWidth() + IndexLX + CurrWidth] =
                        (*DataSearchLetter)[IndexLY * DataSearchLetter->GetWidth() + IndexLX];
                    }
                }

                CurrWidth += DataSearchLetter->GetWidth();
            }
        }

        //      End; {If}
    }
}

VOID  TSignFontData::UpdateFontPrototypes(const TString& Str1,
                           const TString& Str2,
                           const TString& Str3,
                           const TString& Str4, 
                           const TString& Str5)
{
    // Put more stuff here
    for( size_t IndexX = 1; IndexX<FFontList.size(); IndexX++)
    {
        UpdateLetter(*FFontList[IndexX],0x15,Str1);
        UpdateLetter(*FFontList[IndexX],0x16,Str2);
        UpdateLetter(*FFontList[IndexX],0x17,Str3);
        UpdateLetter(*FFontList[IndexX],0x18,Str4);
        UpdateLetter(*FFontList[IndexX],0x19,Str5);
    }
}


TSignFont* TSignFontData::operator[](size_t pos)
{
    return FFontList[pos];
}


INT TSignFontData::EnumFontNames(TStringList& fontNameList) const
{
    TString strName;
    INT iNum = (INT)FFontList.size();

    for (INT i=0; i<iNum; i++)
    {
        strName = FFontList[i]->GetFontName();
        fontNameList.push_back(strName);
    }

    return (INT)fontNameList.size();
}


BOOL  TSignFontData::IsISEFont(const TString& strFontName) const
{
    TString strName;
    INT iNum = (INT)FFontList.size();

    for (INT i=0; i<iNum; i++)
    {
        strName = FFontList[i]->GetFontName();
        if (strName.compare(strFontName)==0)
        {
            return TRUE;
        }
    }

    return FALSE;
}


TSignFont*  TSignFontData::GetFont(const TString& strFontName)
{
    if (strFontName.empty())
    {
        return NULL;
    }

    // 
    TString strName;
    INT iNum = (INT)FFontList.size();

    for (INT i=0; i<iNum; i++)
    {
        strName = FFontList[i]->GetFontName();
        if (strName.compare(strFontName)==0)
        {
            return FFontList[i];
        }
    }

    return NULL;
}

INT TSignFontData::GetFontHeight(const TString& strFontName) const
{
    TString strName;
    INT iNum = (INT)FFontList.size();

    for (INT i=0; i<iNum; i++)
    {
        strName = FFontList[i]->GetFontName();
        if (strName.compare(strFontName)==0)
        {
            return FFontList[i]->GetFontHeight();
        }
    }

    return -1;
}