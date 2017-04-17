#include "StdAfx.h"
#include "FontManager.h"
#include "ProwriteFont.h"
#include "FontsMgr.h"

using namespace ProWrite::UI::Texts;

//////////////////////////////////////////////////////////////////////////


// Initialization and release operation when startup and terminate.
BOOL  FontManager::Initialize(String^ strFileName)
{
    BOOL bFlag = CProwriteFont::Initialize(strFileName);

    return bFlag;
}

void  FontManager::Release()
{
    CProwriteFont::Release();
}

//////////////////////////////////////////////////////////////////////////
// enum system all font
List<String^>^ FontManager::GetSystemFonts()
{
    List<String^> ^value = gcnew List<String^>(10);
    INT iPos = 0;

    // Enum system font
    vector<CFontInfo> fontInfor;
    EnumFontInfo(fontInfor,L"");
    wstring strPwFontName = CProwriteFont::GetShowName();

    //
    vector<CFontInfo>::iterator iCurFont = fontInfor.begin(); 
    for(;iCurFont != fontInfor.end(); ++iCurFont)
    {
        const wchar_t* pName = iCurFont->m_strFontName.c_str();

        if(!CProwriteFont::IsProwriteFont(pName))// Exclude Prowrite Fonts
        {
            value->Add(gcnew String(pName));

            //
            INT iCmp = _wcsicmp(pName,strPwFontName.c_str());
            if (iCmp<0) 
            {
                iPos ++; // update Insert position.
            }
        }
    }

    // Add Prowrite Font 
    value->Insert(iPos,gcnew String(strPwFontName.c_str()));

    return value;
}

// enum all truetype fonts
List<String^>^ FontManager::GetTrueTypeFonts()
{
    List<String^> ^value = gcnew List<String^>(10);

    //			
    vector<CFontInfo> fontInfor;
    EnumFontInfo(fontInfor,L"");

    //
    vector<CFontInfo>::iterator iCurFont = fontInfor.begin();
    for(;iCurFont != fontInfor.end(); ++iCurFont)
    {
        const wchar_t* ws = iCurFont->m_strFontName.c_str();

        //String^ strName = Marshal::PtrToStringUni((IntPtr)((void*)ws));
        if (iCurFont->m_bTrueType)
        {
            value->Add(gcnew String(ws));
        }
    }

    return value;
}

// Enum all raster fonts
List<String^>^ FontManager::GetRasterFonts()
{
    List<String^> ^value = gcnew List<String^>(10);
    INT iPos = 0;

    //			
    vector<CFontInfo> fontInfor;
    EnumFontInfo(fontInfor,L"");

    //
    wstring strPwFontName = CProwriteFont::GetShowName();

    //
    vector<CFontInfo>::iterator iCurFont = fontInfor.begin();
    for(; iCurFont != fontInfor.end(); ++iCurFont)
    {
        const wchar_t* pName = iCurFont->m_strFontName.c_str();

        //String^ strName = Marshal::PtrToStringUni((IntPtr)((void*)ws));
        if (iCurFont->m_bRaster)
        {
            if(!CProwriteFont::IsProwriteFont(pName))// Exclude Prowrite Fonts
            {
                value->Add(gcnew String(pName));

                //
                INT iCmp = _wcsicmp(pName,strPwFontName.c_str());
                if (iCmp<0) 
                {
                    iPos ++; // update Insert position.
                }
            }
        }
    }

    // Add Prowrite Font 
    value->Insert(iPos,gcnew String(strPwFontName.c_str()));

    return value;
}

// Get Prowrite fonts
List<String^>^ FontManager::GetProWriteFonts()
{
    List<String^> ^value = gcnew List<String^>(10);

    // Get 
    wstring strPwFontName = CProwriteFont::GetShowName();

    value->Add(gcnew String(strPwFontName.c_str()));

    return value;
}

// Get Prowrite fonts
// List<String^>^ FontManager::GetProWriteFonts()
// {
//     List<String^> ^value = gcnew List<String^>(10);
// 
//     //			
//     vector<CFontInfo> fontInfor;
//     EnumFontInfo(fontInfor,L"");
// 
//     //
//     vector<CFontInfo>::iterator iCurFont = fontInfor.begin();
//     for(; iCurFont != fontInfor.end(); ++iCurFont)
//     {
//         const wchar_t* ws = iCurFont->m_strFontName.c_str();
// 
//         String^ strName = Marshal::PtrToStringUni((IntPtr)((void*)ws));
//         if (iCurFont->m_bRaster)
//         {
//             const wchar_t* pName = iCurFont->m_strFontName.c_str();
//             if (CProwriteFont::IsProwriteFont(pName))
//             {
//                 value->Add(gcnew String(ws));
//             }
//         }
//     }
// 
//     return value;
// }


// enum specified font height
List<int>^ FontManager::GetSpecifiedFontHeight(String^ aFontname)
{
    pin_ptr<const wchar_t> fontname = ::PtrToStringChars(aFontname);

    //     
    if ( !CProwriteFont::IsShowName(fontname) ) // NOT Prowrite Fonts
    {
        vector<CFontInfo> fontInforVector;
        EnumFontInfo(fontInforVector,fontname);
        // 
        if(fontInforVector.size()>0)
        {
            CFontInfo* pFontInfo = &(fontInforVector[0]);
            List<int>^ value = gcnew List<int>(10);
            list<int>::iterator iCurFont = pFontInfo->m_listHeight.begin();
            for(; iCurFont != pFontInfo->m_listHeight.end(); ++iCurFont)
            {
                value->Add(*iCurFont);
            }
            return value;
        }
        else
        {
            return nullptr;
        }
    }
    else // Prowrite Font
    {
        vector<int> heightList;
        CProwriteFont::GetAllHeight(heightList);
        if (heightList.size()<=0)
        {
            return nullptr;
        }

        // build result
        List<int>^ value = gcnew List<int>(10);
        vector<int>::iterator iCur = heightList.begin(); 
        for(;iCur != heightList.end(); ++iCur)
        {
            value->Add(*iCur);
        }
        return value;
    }
}

// 
WORD FontManager::GetFontStyle(String^ aFontname,INT iHeight)
{
    pin_ptr<const wchar_t> fontname = ::PtrToStringChars(aFontname);
    if (CProwriteFont::IsShowName(fontname)) // Prowrite font.
    {
        return CProwriteFont::GetStyle(iHeight);
    }
    else
    {
        return -1;
    }

}


// Get specified font's type(TrueType or Raster)
bool  FontManager::IsTrueType(String^ aFontname)
{
    pin_ptr<const wchar_t> fontname = ::PtrToStringChars(aFontname);

    //     
    if ( !CProwriteFont::IsShowName(fontname) ) // NOT Prowrite Fonts
    {
        vector<CFontInfo> fontInforVector;
        EnumFontInfo(fontInforVector,fontname);
        // 
        if(fontInforVector.size()==1)
        {
            return fontInforVector[0].m_bTrueType?true:false;
        }
        else
        {
            return false;
        }
    }
    else // Prowrite Font
    {
        return true;
    }
}