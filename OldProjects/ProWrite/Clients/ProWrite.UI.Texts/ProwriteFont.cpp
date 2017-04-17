#include "StdAfx.h"
#include "ProwriteFont.h"

#include < vcclr.h >

//#using  <System.Windows.dll>
#define     FONTCFG     "fontconfig"
#define     PACKAGE     "package"
#define     PKGNAME     "packagename"

// Font package
#define     FONT_ITEM           "font"
#define     FONT_FILENAME       "filename"
#define     FONT_FONTNAME       "fontname"
#define     FONT_SIZE           "size"
#define     FONT_STYLE          "style"
#define     FONT_AUTO           "autofont"

#define     VALUE_REGULAR        "regular"
#define     VALUE_BOLD           "bold"
#define     VALUE_ITALIC         "italic"
#define     VALUE_BOLDITALIC     "bolditalic"
   

//////////////////////////////////////////////////////////////////////////

//#define     _HARD_CODE_PWFONT_CFG_

//////////////////////////////////////////////////////////////////////////

BOOL         CProwriteFont::m_bInit = FALSE;
wstring      CProwriteFont::m_strShowName = L"ProWrite Font";
CPWFontArray CProwriteFont::m_PWFonts;
LONG         CProwriteFont::m_iPosition = 0;
CRITICAL_SECTION* CProwriteFont::m_pCriticalSection = NULL;

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// 

void  CProwriteFont::Release()
{
    if (m_bInit)
    {
        m_bInit = FALSE;
        m_PWFonts.resize(0);
        if (m_pCriticalSection)
        {
            ::DeleteCriticalSection(m_pCriticalSection);
            delete m_pCriticalSection;
            m_pCriticalSection = NULL;
        }
    }
}

// Parse Font element.
BOOL CProwriteFont::ParseFont(XmlNode^ xmlNode)
{
    if (xmlNode->Name->ToLower()!=FONT_ITEM)
    {
        return FALSE;
    }

    BOOL bRc = TRUE;

    // 
    INT iCount = xmlNode->ChildNodes->Count;
    XmlNode^ childNode = xmlNode->FirstChild;

    // Iterate through every node.
    TPWFont fontValue;
    for(INT i=0; i<iCount; i++)
    {
        String^ name = childNode->Name;
        String^ strValue = childNode->InnerText;
        if (name->ToLower()==FONT_FILENAME)
        {
            pin_ptr<const wchar_t> strFileName = PtrToStringChars(strValue);
            fontValue.m_strFileName = strFileName;
        } 
        else if(name->ToLower()==FONT_FONTNAME)
        {
            pin_ptr<const wchar_t> fontname = PtrToStringChars(strValue);
            if (wstring(fontname).size()<LF_FACESIZE)
            {
                fontValue.m_strFontName = fontname;
            }
            else
            {
                ::MessageBox(NULL,L"Configure file\nThe font name is too long!",
                    L"Error",MB_ICONERROR);
                bRc = FALSE;
                break;
            }
        }
        else if (name->ToLower()==FONT_SIZE)
        {
            fontValue.m_iHeight = Convert::ToUInt16(strValue);            
        }
        else if (name->ToLower()==FONT_STYLE)
        {
            if (strValue->ToLower()==VALUE_BOLD)
            {
                fontValue.m_iFontStyle = EPWF_BOLD;
            }
            else if (strValue->ToLower()==VALUE_ITALIC)
            {
                fontValue.m_iFontStyle = EPWF_ITALICS;
            }
            else if (strValue->ToLower()==VALUE_BOLDITALIC)
            {
                fontValue.m_iFontStyle = EPWF_BOLDITALICS;
            }
            else
            {
                fontValue.m_iFontStyle = EPWF_REGULAR;
            }
        }
        else if (name->ToLower()==FONT_AUTO)
        {
            if (strValue->ToLower()=="true")
            {
                fontValue.m_bAutoFont = TRUE;
            }
            else
            {
                fontValue.m_bAutoFont = FALSE;
            }
        }
        childNode = childNode->NextSibling; 
    } 
    
    if (bRc)
    {
        m_PWFonts.push_back(fontValue);
    }

    return bRc;
}

BOOL  CProwriteFont::Initialize(String^ strFileName)
{
    if (m_bInit)
    {
        return FALSE;
    }

    //Read configuration file
    try
    {
        XmlDocument xmlDoc; 
        xmlDoc.Load(strFileName);

        // XML Element

        // FontConfig Node
        XmlElement^ xmlEle = xmlDoc.DocumentElement; 
        if (xmlEle->Name->ToLower() != FONTCFG)
        {
            return FALSE;
        }

        // Package Node
        XmlNode^ pkgNode = xmlEle->FirstChild;
        if (pkgNode->Name->ToLower() != PACKAGE)
        {
            return FALSE;
        }

        // Package Name && Font Nodes
        XmlNode^ fontNode = pkgNode->FirstChild;
        INT iCount = pkgNode->ChildNodes->Count;
        
        for(INT i=0; i<iCount; i++) 
        {
            if (fontNode->Name->ToLower()==PKGNAME)
            {
                pin_ptr<const wchar_t> fontname = PtrToStringChars(fontNode->InnerText);
                SetShowName(fontname);
            } 
            else
            {
                ParseFont(fontNode);
            }
            fontNode = fontNode->NextSibling;
        }
    } 
    catch(XmlException^ e)
    {
        pin_ptr<const wchar_t> strEMsg = PtrToStringChars(e->Message);
        wstring strMsg = L"The FontPackage.xml is corrupt!\n";
        strMsg += strEMsg;
        ::MessageBox(NULL,strMsg.c_str(),L"Warning",MB_ICONWARNING);
        return FALSE;
    }
    catch (SystemException^ e)
    {
        pin_ptr<const wchar_t> strMsg = PtrToStringChars(e->Message);
        ::MessageBox(NULL,strMsg,L"Warning",MB_ICONWARNING);
        return FALSE;
    }


    // Sort
    sort(m_PWFonts.begin(),m_PWFonts.end());

    // Critical section
    if (m_pCriticalSection==NULL)
    {
        m_pCriticalSection = new CRITICAL_SECTION;
        if (m_pCriticalSection==NULL)
        {
            return FALSE;
        }
        else
        {
            ::InitializeCriticalSection(m_pCriticalSection);
        }
    }

    // Set flag to TRUE.
    m_bInit = TRUE;

    //
    return TRUE;
}

void  CProwriteFont::AddFont(const wstring& strFontName,
                     INT iHeight,TPWFontStyle iStyle)
{
    TPWFont item;
    item.m_strFontName = strFontName;
    item.m_iHeight = iHeight;
    item.m_iFontStyle = iStyle;
    m_PWFonts.push_back(item);
}

// Determine the given font is ProwriteFont.
BOOL CProwriteFont::IsProwriteFont(const wstring& strFontName)
{
    size_t nSize = m_PWFonts.size();
    for (size_t i=0; i<nSize; i++)
    {
        if (_wcsicmp(m_PWFonts[i].m_strFontName.c_str(),strFontName.c_str())==0)
        {
            return TRUE;
        }
    }

    return FALSE;
}

// 
void CProwriteFont::GetAllHeight(std::vector<INT>& arHeight)
{
    size_t nSize = m_PWFonts.size();
    for (size_t i=0; i<nSize; i++)
    {
        INT iHeight = m_PWFonts[i].m_iHeight;
        if (std::find(arHeight.begin(),arHeight.end(),iHeight)==arHeight.end())
        {
            arHeight.push_back(iHeight);
        }
    }

    // Sort
    std::sort(arHeight.begin(),arHeight.end());
}

INT  CProwriteFont::GetMinHeight()
{
    vector<int> heightList;
    GetAllHeight(heightList);
    if (heightList.size()<=0)
    {
        return 0;
    }
    else
    {
        return m_PWFonts[0].m_iHeight;
    }
}

void  CProwriteFont::SetShowName(const wstring& strName)
{
    m_strShowName = strName;
}

wstring CProwriteFont::GetShowName()
{
    return m_strShowName;
}

BOOL  CProwriteFont::IsShowName(const wstring& strName)
{
    return _wcsicmp(strName.c_str(),m_strShowName.c_str())==0;
}


// Get specific font
WORD  CProwriteFont::GetStyle(INT iHeight)
{
    WORD wStyle = EPWF_REGULAR;
    for (size_t i=0; i<m_PWFonts.size(); i++)
    {
        if (m_PWFonts[i].m_iHeight==iHeight)
        {
            wStyle |= m_PWFonts[i].m_iFontStyle;
        }
    }
    return wStyle;
}

BOOL  CProwriteFont::GetLogicFont(LOGFONT& logFont,INT iHeight,TPWFontStyle iStyle)
{
    BOOL bRc = FALSE;

    INT nSize = INT(m_PWFonts.size());
    for (INT i=0; i<nSize; i++)
    {
        PTPWFont pFont = &(m_PWFonts[i]);
        if ( pFont->m_iHeight==iHeight &&
             pFont->m_iFontStyle==iStyle)
        {            
            bRc = GetLOGFONT(i,logFont);             
            break;
        }
    }

    return bRc;
}

// Get the Prowrite font
PTPWFont   CProwriteFont::GetPWFont(const wstring& strFontName)
{
	INT nSize = INT(m_PWFonts.size());
	for (INT i=0; i<nSize; i++)
	{
		PTPWFont pFont = &(m_PWFonts[i]);
		if ( _wcsicmp(pFont->m_strFontName.c_str(),strFontName.c_str())==0 )
		{            
			return pFont;
		}
	}

	return NULL;
}


// Get file name according to FontName
wstring  CProwriteFont::GetFileName(const wstring& strFontName)
{
    size_t nSize = m_PWFonts.size();
    for (size_t i=0; i<nSize; i++)
    {
        if (_wcsicmp(m_PWFonts[i].m_strFontName.c_str(),strFontName.c_str())==0)
        {
            return m_PWFonts[i].m_strFileName;
        }
    }

    return L"";
}

BOOL  CProwriteFont::GetLOGFONT(INT iIndex,LOGFONT& logFont)
{
    if (iIndex<0 || iIndex>INT(m_PWFonts.size()))
    {
        return FALSE;
    }

    memset(&(logFont), 0, sizeof(logFont));
    logFont.lfHeight = m_PWFonts[iIndex].m_iHeight;
    logFont.lfWidth = 0;
    logFont.lfEscapement = 0;
    logFont.lfOrientation = 0;
    logFont.lfWeight =  FW_NORMAL;// must be set FW_NORMAL 
    logFont.lfItalic = FALSE;   // must be set FALSE 
    logFont.lfUnderline = FALSE;
    logFont.lfStrikeOut = 0;
    logFont.lfCharSet = DEFAULT_CHARSET;
    logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
    logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS ;
    logFont.lfQuality = NONANTIALIASED_QUALITY;
    logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    wcscpy_s(logFont.lfFaceName,m_PWFonts[iIndex].m_strFontName.c_str());

    return TRUE;
}

BOOL CProwriteFont::IsAutoFont(INT iIndex)
{
    if (iIndex<0 || iIndex>INT(m_PWFonts.size()))
    {
        return FALSE;
    }

    return m_PWFonts[iIndex].IsAutoFont();
}

//////////////////////////////////////////////////////////////////////////
// Travel fonts
VOID  CProwriteFont::NextAutoFontPos()
{
    if (m_pCriticalSection)
    {   
        ::EnterCriticalSection(m_pCriticalSection);

        while (m_iPosition>=0)
        {
            BOOL bFlag = IsAutoFont(m_iPosition);
            if (bFlag)
            {
                break;
            }
            else
            {
                m_iPosition--;
            }
        }

        ::LeaveCriticalSection(m_pCriticalSection);
    }
}

BOOL  CProwriteFont::GetFirstFont(LOGFONT& logFont,BOOL bAutoFont/*=TRUE*/)
{
    if (m_pCriticalSection==NULL)
    {
        return FALSE;
    }
    else
    {
        ::EnterCriticalSection(m_pCriticalSection);
    }

    m_iPosition = LONG(m_PWFonts.size() - 1);
    if (bAutoFont)
    {
        NextAutoFontPos();
    }

    ::LeaveCriticalSection(m_pCriticalSection);

    // 
    return GetLOGFONT(m_iPosition,logFont);

}

BOOL  CProwriteFont::GetNextFont(LOGFONT& logFont,BOOL bAutoFont/*=TRUE*/)
{
    if (m_pCriticalSection==NULL)
    {
        return FALSE;
    }
    else
    {
        ::EnterCriticalSection(m_pCriticalSection);
    }

    m_iPosition--;
    if (bAutoFont)
    {
        NextAutoFontPos();
    }

    ::LeaveCriticalSection(m_pCriticalSection);

    return GetLOGFONT(m_iPosition,logFont);
}