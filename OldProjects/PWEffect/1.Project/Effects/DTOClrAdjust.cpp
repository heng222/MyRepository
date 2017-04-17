

#include "stdafx.h"
#include "DTOClrAdjust.h"
#include "ocidl.h"	// Added by ClassView
//////////////////////////////////////////////////////////////////////////

//
//  --------------- CDTOClrAdjust ----------------
//
HRESULT CDTOClrAdjust::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    // 
    m_iAdjustType = ENoChange;
    m_clrSunglass = 0xFFFFFFFF;
    
    return S_OK;
}

HRESULT CDTOClrAdjust::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here
    
    //
    return S_OK;
}

HRESULT CDTOClrAdjust::OnTerminate()
{
    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


// 
HRESULT CDTOClrAdjust::OnImplEffect(IN DWORD* pInputBuf,
                                    IN DWORD* pOutputBuf,
                                    IN INT iWidth,
                                    IN INT iHeight)
{   
    
    // Get the pitch in multiples of 4.
    long lOffset = 0; // 每行的起始位置
   
    
    // Now loop through each scanline.
    for (int j = 0; j < iHeight; j++)
    {
        // Loop across each row (destination row)
        
        if (m_iAdjustType!=ENoChange)
        {
            
            for (int i = 0; i < iWidth; i++)
            {
                int nOffsetSrc = lOffset + i; // 原像素
                int nOffsetDest = lOffset + i; // 目的像素
                
                // Adjust color according to sunglass color.
                AdjustPixel(pOutputBuf+nOffsetDest, 
                    pInputBuf+nOffsetSrc);
            }
            
        }
        else
        {
            // Copy the whole line at a time.
            memcpy( pOutputBuf+lOffset, 
                pInputBuf+lOffset, iWidth*4 );
        }
        
        
        // 
        lOffset += iWidth;
    }
    
    return S_OK;
}
//////////////////////////////////////////////////////////////////////////
// Utilities methods
HRESULT CDTOClrAdjust::AdjustPixel(DWORD* pdwOutput, const DWORD* pdwInput)
{
	RTN_HR_IF_BADPTR(pdwOutput);
	RTN_HR_IF_BADPTR(pdwInput);

    DWORD rcValue = 0;

	BYTE byRed	= _basex::GetRed(*pdwInput);
	BYTE byGreen= _basex::GetGreen(*pdwInput);
	BYTE byBlue	= _basex::GetBlue(*pdwInput);
	

	// 
	if (RGB(byRed,byGreen,byBlue)!=RGB(0,0,0))
	{
        // 24bit Color [RGB]  8bit Red, 8 bit Green, 8 bit Blue  can be 
        // shifted to a single color spectrum of 8 bits via the equation:   
        // Y = (R * 0.299)  + (G * 0.587) + (B * 0.114)
        // NOTE:  This is actually getting the luminance of the image.
        // So if the sign color is Red, then the output content to 
        // the CXC would have a Red component equal to the equation above.
        // I.e. an single pixel with RGB = [256,246, 236]  would be:
        /************************************************************************/
        /*
        Y = (R * 0. 299) + (G * 0. 587) + (B * 0. 114)
        = (256 * 0. 299) + (246 * 0. 587) + (236 * 0.114)
        = 77 + 151 + 26
        = 254
        
        The resultant pixel then would be on a RED sign, an RGB pixel color of RBG = [254, 0, 0]
        The resultant pixel then would be on a GREEN sign, an RGB pixel color of RBG = [0, 254, 0]
        The resultant pixel then would be on a BLUE sign, an RGB pixel color of RBG = [0, 0, 254]
        The resultant pixel then would be on a WHITE sign, an RGB pixel color of RBG = [254, 254, 254]
        */
        /***********************************************************************************/

		BYTE bySpectrum = BYTE((byRed*0.299) + (byGreen*0.587) + (byBlue*0.114));

        // 根据AdjustType作不同的处理
        if (m_iAdjustType==EGray)
        {
            rcValue = _basex::MakeDXSAMPLE(bySpectrum,bySpectrum,bySpectrum);
        }
        else if (m_iAdjustType==ERed)
        {
            rcValue = _basex::MakeDXSAMPLE(bySpectrum,0,0);
        }		
        else if (m_iAdjustType==EGreen)
        {
            rcValue = _basex::MakeDXSAMPLE(0,bySpectrum,0);
        }	
        else if (m_iAdjustType==EBlue)
        {
            rcValue = _basex::MakeDXSAMPLE(0,0,bySpectrum);
        }	
        else if (m_iAdjustType==EWhite)
        {
            rcValue = _basex::MakeDXSAMPLE(bySpectrum,bySpectrum,bySpectrum);
        }
		else if (m_iAdjustType==EAmber)
		{
			// 0xFFCA6924 = 琥珀色
			/*
			BYTE byGray = BYTE(sat);
		    BYTE byAmberR = 0xCA*byGray/255;
		    BYTE byAmberG = 0x69*byGray/255;
		    BYTE byAmberB = 0x24*byGray/255;
		    rcValue = _basex::MakeDXSAMPLE(byAmberR,byAmberG,byAmberB);
            */


            // Amber is different in that we want a little more yellowish 
            // orange color.  Thus, The result is                 
            // Red component = Y (luminance)
            // Green Component = Y (luminance) * .8
            // The resultant pixel then would be on an AMBER sign, an RGB 
            // pixel color of RBG = [254, 203, 0]

            rcValue = _basex::MakeDXSAMPLE(bySpectrum,BYTE(bySpectrum*0.8),0);
			
        }	
        else if (m_iAdjustType==EBlueGreen)
        {
            /************************************************************************/
            /*  BLUE - GREEN sign is also different  the red component is accounted for by adding it to the Green and Blue Colors. 
                R = 0;
                G = (G + R*0.299) & 0XFF;
                B = (B + R*0.299) & 0XFF;
            
                I.e. an single pixel with RGB = [100,206, 186]  would be:
                The BLUE - GREEN result would be:
              
                R = 0
                G = (206+ (100 * 0.299) ) & 0xFF = 236
                B = (186 + (100 * 0.299) ) & 0xFF = 216
            */
            /************************************************************************/
            BYTE R = 0;
            BYTE G = BYTE(byGreen + byRed*0.299) ;
            BYTE B = BYTE(byBlue  + byRed*0.299) ;
            rcValue = _basex::MakeDXSAMPLE(R,G,B);
        }	
        else if (m_iAdjustType==ERedGreen)
        {
            /************************************************************************/
            /*  RED - GREEN sign is also different  the blue component is accounted 
                for by adding it to the Red and Green Colors. 
                R = (R + B *0.114) & 0XFF;
                G = (G + B *0.114) & 0XFF;
                B = 0;
            
                I.e. an single pixel with RGB = [100,206, 186]  would be:
                The RED - GREEN result would be:
                R = (100+ (186 * 0.114) ) & 0xFF = 121
                G = (206+ (186 * 0.114) ) & 0xFF = 227
                B = 0                                                               */
            /************************************************************************/
            BYTE R = BYTE( byRed   + byBlue*0.114);
            BYTE G = BYTE( byGreen + byBlue*0.114);
            BYTE B = 0;
            rcValue = _basex::MakeDXSAMPLE(R,G,B);
        }

        /*
	    INT byGray = (INT)dwSpectrum;
	            BYTE byNewR = GetRValue(m_clrSunglass) * byGray / 255;
	            BYTE byNewG = GetGValue(m_clrSunglass) * byGray / 255;
	            BYTE byNewB = GetBValue(m_clrSunglass) * byGray / 255;
	    	    rcValue = _basex::MakeDXSAMPLE(byNewR,byNewG,byNewB);*/
	}
    else
    {
        rcValue = _basex::MakeDXSAMPLE(_basex::GetBlackAgentClr());
    }

	*pdwOutput = rcValue;

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// Properties operations

STDMETHODIMP CDTOClrAdjust::get_AdjustType(BSTR* pstrType)
{
    RTN_HR_IF_BADPTR(pstrType);
    
    if (m_iAdjustType==ERed)
    {
        *pstrType = CComBSTR(AT_RED).Copy();
    } 
    else if(m_iAdjustType==EGray)
    {
        *pstrType = CComBSTR(AT_GRAY).Copy();
    }
    else if (m_iAdjustType==EAmber)
    {
        *pstrType = CComBSTR(AT_AMBER).Copy();
    }
    else
    {
        *pstrType = CComBSTR(AT_NOCHANGE).Copy();
    }
    
    return S_OK;
}

STDMETHODIMP CDTOClrAdjust::put_AdjustType(BSTR strType)
{    
    if (CComBSTR(strType)==AT_GRAY)
    {
        m_iAdjustType = EGray;
    }
    else if (CComBSTR(strType)==AT_RED)
    {		
        m_iAdjustType = ERed;
    }
    else if (CComBSTR(strType)==AT_GREEN )
    {
        m_iAdjustType = EGreen;
    }
    else if (CComBSTR(strType)==AT_BLUE )
    {
        m_iAdjustType = EBlue;
    }
    else if (CComBSTR(strType)==AT_WHITE )
    {
        m_iAdjustType = EWhite;
    }
    else if (CComBSTR(strType)==AT_AMBER)
    {
        m_iAdjustType = EAmber;
    }
    else if (CComBSTR(strType)==AT_BLUEGREEN )
    {
        m_iAdjustType = EBlueGreen;
    }
    else if (CComBSTR(strType)==AT_REDGREEN)
    {
        m_iAdjustType = ERedGreen;
    }
    else
    {
        m_iAdjustType = ENoChange;
    }
    
    return S_OK;
}


STDMETHODIMP CDTOClrAdjust::get_SunglassColor(OLE_COLOR *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_clrSunglass;
	return S_OK;
}

STDMETHODIMP CDTOClrAdjust::put_SunglassColor(OLE_COLOR newVal)
{    
    // TODO: Add your implementation code here    
    if (_basex::IsTransparent(newVal))
    {
        m_clrSunglass = CLR_TRANSPARENT_AGENT;
    }
    else
    {
        m_clrSunglass = (newVal&0x00FFFFFF);
        
        if (m_clrSunglass==0)
        {
            m_clrSunglass = _basex::GetBlackAgentClr();
        }
    }
	return S_OK;
}
