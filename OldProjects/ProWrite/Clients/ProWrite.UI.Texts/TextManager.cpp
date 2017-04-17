// 这是主 DLL 文件。

#include "stdafx.h"

#include "TextManager.h"

using namespace ProWrite::UI::Texts;
//////////////////////////////////////////////////////////////////////////

// Allocate the native object on the C++ Heap via a constructor
TextMgr::TextMgr() : m_pWPEngine(new CWPEngine)
{

}

// Deallocate the native object on a destructor
TextMgr::~TextMgr() 
{
    if (m_pWPEngine)
    {
        delete m_pWPEngine;
        m_pWPEngine = NULL;
    }
}

// Deallocate the native object on the finalizer just in case no destructor is called
TextMgr::!TextMgr() 
{
    if (m_pWPEngine)
    {
        delete m_pWPEngine;
        m_pWPEngine = NULL;
    }
}


//////////////////////////////////////////////////////////////////////////
// Generate the bitmap according to the information given.
// adjust style
void TextMgr::SetStyle(bool bFrameSizeFixed,bool bFontSizeFixed)
{
    BOOL bFrameFixed = bFrameSizeFixed;
    BOOL bFontFixed = bFontSizeFixed;
    if (m_pWPEngine)
    {
        m_pWPEngine->SetAdjustStyle(bFrameFixed,bFontFixed);
    }
}

// 
bool TextMgr::GenerateBmps( List<Image^>^ imgActualList, 
                  List<Image^>^ imgVirtualList,
                  List<String^>^ strClipList )
{
    if (m_pWPEngine==NULL)
    {
        return false;
    }

    // Reset
    imgActualList->Clear();
    imgVirtualList->Clear();
    strClipList->Clear();

    // generate bitmaps
    CHBmpArray arActual,arVirtual;
    CWStrList strList;
    BOOL bFlag = m_pWPEngine->GenerateBmp(arActual,arVirtual,strList);

    GpClr clrTspt = m_pWPEngine->GetTsptAgentColor();
    BYTE byA = clrTspt.GetA();
    BYTE byR = clrTspt.GetR();
    BYTE byG = clrTspt.GetG();
    BYTE byB = clrTspt.GetB();

    // Actual Bitmap list
    HBITMAP hBmp32 = NULL;
    for(CHBmpArray::iterator iCurBmp = arActual.begin(); iCurBmp != arActual.end(); ++iCurBmp)
    {
        hBmp32 = *iCurBmp;

        IntPtr^ ptr = gcnew IntPtr(hBmp32);
        Bitmap^ bmp = Bitmap::FromHbitmap(*ptr);

        // Transparent.
        bmp->MakeTransparent(Color::FromArgb(byA,byR,byG,byB));
        imgActualList->Add(bmp);

        ::DeleteObject(hBmp32);
    }

    // Virtual Bitmap list
    for(CHBmpArray::iterator iCurBmp = arVirtual.begin(); iCurBmp != arVirtual.end(); ++iCurBmp)
    {
        hBmp32 = *iCurBmp;

        IntPtr^ ptr = gcnew IntPtr(hBmp32);
        Bitmap^ bmp = Bitmap::FromHbitmap(*ptr);

        // Transparent
        bmp->MakeTransparent(Color::FromArgb(byA,byR,byG,byB));
        imgVirtualList->Add(bmp);

        ::DeleteObject(hBmp32);
    }

    // String clip list
    for(CWStrList::iterator iCurText = strList.begin(); iCurText != strList.end(); ++iCurText)
    {
        wstring strClip = *iCurText;
        strClipList->Add(gcnew String(strClip.c_str()));
    }

    //
    return bFlag?true:false;
}