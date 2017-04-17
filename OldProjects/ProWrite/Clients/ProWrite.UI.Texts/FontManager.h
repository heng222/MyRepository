#pragma once

//////////////////////////////////////////////////////////////////////////
#include "Stdafx.h"
#include <vcclr.h>

using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;


namespace ProWrite{ namespace UI{ namespace Texts{
//////////////////////////////////////////////////////////////////////////

public ref class FontManager
{
protected:

    FontManager(){};

    // Deallocate the native object on a destructor
    ~FontManager(){};


    // Deallocate the native object on the finalizer just in case no destructor is called
    !FontManager(){};

public:

    // Initialization and release operation when startup and terminate.
    static  BOOL    Initialize(String^ strFileName);
    static  void    Release();


    // Enum system font's attribute
public:

    // enum system all font
    static List<String^>^ GetSystemFonts();

    // enum all truetype fonts
    static List<String^>^ GetTrueTypeFonts();

    // enum all raster fonts
    static List<String^>^ GetRasterFonts();

    // Get Prowrite fonts
    static List<String^>^ GetProWriteFonts();

    // enum specified font height
    static List<int>^ GetSpecifiedFontHeight(String^ aFontname);

    // Get specified font's style
    static WORD   GetFontStyle(String^ aFontname,INT iHeight);

    // Get specified font's type(TrueType or Raster)
    static bool   IsTrueType(String^ aFontname);
};


//////////////////////////////////////////////////////////////////////////
}}}
// End of file