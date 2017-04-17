// ProWrite.UI.Texts.h

#pragma once

#include <vcclr.h>

#include "WPEngine.h"
#include "VATransformer.h"


using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;
using namespace ProWrite::Core;


namespace ProWrite{ namespace UI{ namespace Texts{
//////////////////////////////////////////////////////////////////////////

	public ref class TextMgr
	{

	private:

		CWPEngine* m_pWPEngine;

	public:

		// Allocate the native object on the C++ Heap via a constructor
		TextMgr() ;

		// Deallocate the native object on a destructor
		~TextMgr() ;

	protected:

		// Deallocate the native object on the finalizer just in case no destructor is called
		!TextMgr() ;


		// Exports interface
	public:

        // Ratio
        property int ScaleIndex
        {
            void set(int value)
            {
                CVATransformer::SetRatio(value);
            }

            int get()
            {
                return CVATransformer::GetRatio();
            }
        }

		// adjust style
        void SetStyle(bool bFrameSizeFixed,bool bFontSizeFixed);

		// text
		property String^ Text
		{
			void set(String^ value)
			{
                pin_ptr<const wchar_t> text = PtrToStringChars(value);
                if (m_pWPEngine)
                {
                    m_pWPEngine->SetText(text);
                }
			}

            String^ get()
            {
                return gcnew String(m_pWPEngine->GetText().c_str());
            }
		}

		// sign size
		property Size^ SignSize
		{
			void set(Size^ value)
            {
				SIZE sizeV;
				sizeV.cx = value->Width;
				sizeV.cy = value->Height;

                SIZE sizeA;
                CVATransformer::V2A(sizeV,sizeA);
                if (m_pWPEngine)
                {
                    m_pWPEngine->SetSignSize(sizeA);
                }

			}

            Size^ get()
            {
                Size^ value = gcnew Size();
                SIZE sizeV;

                CVATransformer::A2V(m_pWPEngine->GetSignSize(),sizeV);

                value->Width = sizeV.cx;
                value->Height = sizeV.cy;

                return value;
            }
		}

		// Font height(in Pixel)
		property int FontHeight
        {
            void set(int value)
            {
                LONG lAValue;
                CVATransformer::V2A(value,lAValue);      
                if (m_pWPEngine)
                {
                    m_pWPEngine->SetFontLogicHeight(lAValue);
                }         

            }

            int get()
            {
                LONG iVValue;
                LONG iActualHeight = m_pWPEngine->GetFontLogicHeight(TRUE);
                CVATransformer::A2V(iActualHeight,iVValue);
                return iVValue;
            }
		}
#if 0
        // Font height (in Point)
        property int FontPointHeight
        {
            void set(int value)
            {
                LONG lAValue;
                CVATransformer::V2A(value,lAValue);               

                m_pWPEngine->SetFontPointHeight(lAValue);
            }

            int get()
            {
                LONG iVValue;
                LONG iActualHeight = m_pWPEngine->GetFontPointHeight();
                CVATransformer::A2V(iActualHeight,iVValue);
                return iVValue;
            }
        }
#endif

#if 0
        // Is the current height minimum ?
        property bool IsMiniHeight
        {
            bool get()
            {
                BOOL bValue = m_pWPEngine->IsMinFontHeight();
                return bValue?true:false;
            }
        }
#endif

		// font bold
		property bool Bold
		{
			void set(bool value)
            {
                if (m_pWPEngine)
                {
                    m_pWPEngine->SetFontBold(value?TRUE:FALSE);
                }
			}

            bool get()
            {
                if (m_pWPEngine)
                {
                    return m_pWPEngine->GetFontBold()?true:false;
                }
                else
                {
                    return false;
                }
            }
		}

		// italic
		property bool Italic
		{
			void set(bool value)
            {
                if (m_pWPEngine)
                {
                    m_pWPEngine->SetFontItalic(value?TRUE:FALSE);
                }
            }

            bool get()
            {
                if (m_pWPEngine)
                {
                    return m_pWPEngine->GetFontItalic()?true:false;
                }
                else
                {
                    return false;
                }
            }
		}

		// underline
		property bool Underline
		{
			void set(bool value)
            {
                if (m_pWPEngine)
                {
                    m_pWPEngine->SetFontUnderLine(value?TRUE:FALSE);
                }
            }

            bool get()
            {
                if (m_pWPEngine)
                {
                    return m_pWPEngine->GetFontUnderLine()?true:false;
                }
                else
                {
                    return false;
                }
            }
		}

		// font name
		property String^ FontName
		{
			void set(String^ value)
			{
                pin_ptr<const wchar_t> fontname = PtrToStringChars(value);
                if (m_pWPEngine)
                {
                    m_pWPEngine->SetFontName(fontname);
                }
			}

            String^ get()
            {
                return gcnew String(m_pWPEngine->GetFontFaceName().c_str());
            }
		}

        // Font file name
        property String^ FontFileName
        {
            String^ get()
            {
                return gcnew String(m_pWPEngine->GetFontFileName().c_str());
            }
        }

		// frame size
		property Size^ FrameSize
		{
			void set(Size^ value)
            {
                if (m_pWPEngine)
                {
                    SIZE sizeV;
                    sizeV.cx = value->Width;
                    sizeV.cy = value->Height;

                    SIZE sizeA;
                    CVATransformer::V2A(sizeV,sizeA);

                    m_pWPEngine->SetFrameSize(sizeA.cx,sizeA.cy);
                }
			}

            Size^ get()
            {
                Size^ value = gcnew Size();
                SIZE sizeV;

                CVATransformer::A2V(m_pWPEngine->GetFrameSize(),sizeV);

                value->Width = sizeV.cx;
                value->Height = sizeV.cy;

                return value;
            }
		}

		// alignment
		property Align Alignment
		{
			void set(Align value)
			{
				if (value==Align::LEFT)
				{
					m_pWPEngine->SetTextAlign(TA_LEFT);
				}
                else if (value==Align::CENTER)
                {
                    m_pWPEngine->SetTextAlign(TA_CENTER);
                }
                else if (value==Align::RIGHT)
                {
                    m_pWPEngine->SetTextAlign(TA_RIGHT);
                }
			}

            Align get()
            {
                UINT value = m_pWPEngine->GetTextAlign();
                if (value==TA_LEFT)
                {
                    return Align::LEFT;
                }
                else if (value==TA_CENTER)
                {
                    return Align::CENTER;
                }
                else if (value==TA_RIGHT)
                {
                    return Align::RIGHT;
                }
                else
                {
                    return Align::CENTER;
                }
            }
		}

        // line alignment
        property Valign LineAlignment
        {
            void set(Valign value)
            {
                if (m_pWPEngine)
                {
                    if (value==Valign::TOP)
                    {
                        m_pWPEngine->SetLineAlign(DT_TOP);
                    }
                    else if (value==Valign::MIDDLE)
                    {
                        m_pWPEngine->SetLineAlign(DT_VCENTER);
                    }
                    else if (value==Valign::BOTTOM)
                    {
                        m_pWPEngine->SetLineAlign(DT_BOTTOM);
                    }
                }
            }

            Valign get()
            {
                UINT value = m_pWPEngine->GetLineAlign();
                if (value==DT_TOP)
                {
                    return Valign::TOP;
                }
                else if (value==DT_VCENTER)
                {
                    return Valign::MIDDLE;
                }
                else if (value==DT_BOTTOM)
                {
                    return Valign::BOTTOM;
                }
                else
                {
                    return Valign::MIDDLE;
                }
            }
        }

		// First indent
		property int Firstindent
		{
			void set(int value)
            {
                LONG lAValue;
                CVATransformer::V2A(value,lAValue); 
				m_pWPEngine->SetFirstIndent(lAValue);
			}

			int get()
            {
                LONG iVValue;
                LONG iActual = m_pWPEngine->GetFirstIndent();
                CVATransformer::A2V(iActual,iVValue);

				return iVValue;
			}
        }

        // Lead amount
        property int LeadAmount
        {
            void set(int value)
            {
                LONG lAValue;
                CVATransformer::V2A(value,lAValue); 
                m_pWPEngine->SetLeadAmount(lAValue);
            }

            int get()
            {
                LONG iVValue;
                LONG iActual = m_pWPEngine->GetLeadAmount();
                CVATransformer::A2V(iActual,iVValue);
                return iVValue;
            }
        }

        // Kern amount
        property int KernAmount
        {
            void set(int value)
            {
                LONG lAValue;
                CVATransformer::V2A(value,lAValue); 
                m_pWPEngine->SetKernAmount(lAValue);
            }

            int get()
            {
                LONG iVValue;
                LONG iActual = m_pWPEngine->GetKernAmount();
                CVATransformer::A2V(iActual,iVValue);
                return iVValue;
            }
        }

		// Text color
		property Color^ TextColor
		{
			void set(Color^ value)
			{
                if (value->R ==0 && value->G ==0 && value->B ==0)
                {
                    m_pWPEngine->SetTextColor(CLR_BLACK_AGENT);
                }
                else
                {
				    m_pWPEngine->SetTextColor(GpClr(value->A,value->R, value->G, value->B));
                }
			}
            Color^ get()
            {
                COLORREF clr = m_pWPEngine->GetTextColor();       
                // 
                Color^ value = Color::FromArgb(GetRValue(clr),GetGValue(clr),GetBValue(clr));
                return value;
            }
        }

        // Grid color
        property Color^ GridColor
        {
            void set(Color^ value)
            {
                if (value->R ==0 && value->G ==0 && value->B ==0)
                {
                    m_pWPEngine->SetGridColor(CLR_BLACK_AGENT);
                }
                else
                {
                    m_pWPEngine->SetGridColor(GpClr(value->A,value->R, value->G, value->B));
                }
            }
        }

		// background color
		property Color^ BackColor
		{
			void set(Color^ value)
			{
                if (value->R ==0 && value->G ==0 && value->B ==0)
                {
                    m_pWPEngine->SetBkgColor(CLR_BLACK_AGENT);
                }
                else
                {
                    GpClr clrBkg(value->A,value->R, value->G, value->B);
                    m_pWPEngine->SetBkgColor(clrBkg);
                }
			}

            Color^ get()
            {
                GpClr clrRef = m_pWPEngine->GetBkgColor();
                Color^ value = Color::FromArgb(clrRef.GetA(),clrRef.GetR(),
                    clrRef.GetG(),clrRef.GetB());
                /*
                COLORREF clrRef;
                if (m_pWPEngine->IsTransparent())
                {
                    clrRef = m_pWPEngine->GetTsptAgentColor().ToCOLORREF();
                    BYTE byR = GetRValue(clrRef);
                    BYTE byG = GetGValue(clrRef);
                    BYTE byB = GetBValue(clrRef);
                    value = Color::FromArgb(0,byR,byG,byB);
                }
                else
                {
                    clrRef = m_pWPEngine->GetBkgColor().ToCOLORREF();
                    BYTE byR = GetRValue(clrRef);
                    BYTE byG = GetGValue(clrRef);
                    BYTE byB = GetBValue(clrRef);
                    value = Color::FromArgb(255,byR,byG,byB);
                }*/
                return value;
            }
		}

        // Color key
        property Color^ ColorKey
        {
            Color^ get()
            {
                Color^ value;
                COLORREF clrRef = m_pWPEngine->GetTsptAgentColor().ToCOLORREF();
                BYTE byR = GetRValue(clrRef);
                BYTE byG = GetGValue(clrRef);
                BYTE byB = GetBValue(clrRef);
                value = Color::FromArgb(255,byR,byG,byB);
                return value;
            }
        }

        // Word wrap
        property bool WordWrap
        {
            void set(bool value)
            {
                m_pWPEngine->SetWordBreak(value?TRUE:FALSE);
            }

            bool get()
            {
                BOOL bFlag = m_pWPEngine->GetWordBreak();
                return bFlag?true:false;
            }
        }

        // Generate the bitmap according to the information given.
		bool GenerateBmps( List<Image^>^ imgActualList, 
                           List<Image^>^ imgVirtualList,
                           List<String^>^ strClipList );


        // Text effects interface
        public:

            // Draw grid
            property bool ShowGrid
            {
                void set(bool value)
                {
                    m_pWPEngine->SetGridFlag(value?TRUE:FALSE);
                }

                bool get()
                {
                    BOOL bFlag = m_pWPEngine->GetGridFlag();
                    return bFlag?true:false;
                }
            }


            // Text effect attributes
            property OutlineShadowType TextEffectType
            {
                void set(OutlineShadowType value)
                {
                    if (value==OutlineShadowType::NONE)
                    {
                        m_pWPEngine->SetEffectType(ETE_NONE);
                    }
                    else if (value==OutlineShadowType::SHADED)
                    {
                        m_pWPEngine->SetEffectType(ETE_SHADOW);
                    }
                    else if (value==OutlineShadowType::OUTLINE)
                    {
                        m_pWPEngine->SetEffectType(ETE_OUTLINE);
                    }
                    else
                    {
                        CLR_ASSERT(FALSE);
                        m_pWPEngine->SetEffectType(ETE_NONE);
                    }
                }
                OutlineShadowType get()
                {
                    TTextEffect txtEff = m_pWPEngine->GetEffectType();

                    if (txtEff==ETE_NONE)
                    {
                        return OutlineShadowType::NONE;
                    }
                    else if (txtEff==ETE_NONE)
                    {
                        return OutlineShadowType::SHADED;
                    }
                    else if (txtEff==ETE_NONE)
                    {
                        return OutlineShadowType::OUTLINE;
                    }
                    else
                    {
                        CLR_ASSERT(ERROR);
                        return OutlineShadowType::NONE;
                    }
                }
            }

            // Cancel TextEffect
            void CancelTextEffect()
            {
                m_pWPEngine->SetEffectType(ETE_NONE);
            }


            // Shadow Attributes
            void SetShadowAttri(Color^ clrShadow,int xOffset,int yOffset)
            {                
                m_pWPEngine->SetEffectType(ETE_SHADOW);
                if (clrShadow->R ==0 && clrShadow->G ==0 && clrShadow->B ==0)
                {
                    m_pWPEngine->SetShadowColor(CLR_BLACK_AGENT);
                }
                else
                {
                    m_pWPEngine->SetShadowColor(GpClr(clrShadow->A,clrShadow->R,clrShadow->G,clrShadow->B));
                }
                
                SIZE sizeV;
                sizeV.cx = xOffset;
                sizeV.cy = yOffset;

                SIZE sizeA;
                CVATransformer::V2A(sizeV,sizeA);
                m_pWPEngine->SetShadowDropdown(sizeA);
            }
            property Color^ ShadowColor
            {
                void set(Color^ value)
                {
                    if (value->R ==0 && value->G ==0 && value->B ==0)
                    {
                        m_pWPEngine->SetShadowColor(CLR_BLACK_AGENT);
                    }
                    else
                    {
                        m_pWPEngine->SetShadowColor(GpClr(value->A,value->R,value->G,value->B));
                    }
                }
                Color^ get()
                {
                    COLORREF clr = m_pWPEngine->GetShadowColor();       
                    Color^ value = Color::FromArgb(GetRValue(clr),GetGValue(clr),GetBValue(clr));
                    return value;
                }
            }
            property Size^ ShadowDropdown
            {
                void set(Size^ value)
                {
                    SIZE sizeV;
                    sizeV.cx = value->Width;
                    sizeV.cy = value->Height;

                    SIZE sizeA;
                    CVATransformer::V2A(sizeV,sizeA);

                    m_pWPEngine->SetShadowDropdown(sizeA);

                }
                Size^ get()
                {
                    SIZE sizeA;
                    m_pWPEngine->GetShadowDropdown(sizeA);

                    SIZE sizeV;
                    CVATransformer::A2V(sizeA,sizeV);

                    Size^ value = gcnew Size();
                    value->Width = sizeV.cx;
                    value->Height = sizeV.cy;

                    return value;
                }
            }

            // Outline attribute
            void SetOutlineAttri(Color^ clrOutline,WORD wWidth)
            {
                m_pWPEngine->SetEffectType(ETE_OUTLINE);
                if (clrOutline->R ==0 && clrOutline->G ==0 && clrOutline->B ==0)
                {
                    m_pWPEngine->SetOutlineColor(CLR_BLACK_AGENT);
                }
                else
                {
                    m_pWPEngine->SetOutlineColor(GpClr(clrOutline->A,clrOutline->R,clrOutline->G,clrOutline->B));
                }

                LONG lAValue;
                CVATransformer::V2A(wWidth,lAValue); 
                m_pWPEngine->SetOutlineWidth((WORD)lAValue);
            }
            property Color^ OutlineColor
            {
                void set(Color^ value)
                {
                    if (value->R ==0 && value->G ==0 && value->B ==0)
                    {
                        m_pWPEngine->SetOutlineColor(CLR_BLACK_AGENT);
                    }
                    else
                    {
                        m_pWPEngine->SetOutlineColor(GpClr(value->A,value->R,value->G,value->B));
                    }
                }
                Color^ get()
                {
                    COLORREF clr = m_pWPEngine->GetOutlineColor();       
                    // 
                    Color^ value = Color::FromArgb(GetRValue(clr),GetGValue(clr),GetBValue(clr));
                    return value;
                }
            }
            property int OutlineWidth
            {
                void set(int value)
                {
                    LONG lAValue;
                    CVATransformer::V2A(value,lAValue); 
                    m_pWPEngine->SetOutlineWidth((WORD)lAValue);
                }
                int get()
                {
                    LONG iVValue;
                    LONG iActual = m_pWPEngine->GetOutlineWidth();
                    CVATransformer::A2V(iActual,iVValue);
                    return iVValue;
                }
            }


	}; // End of Class

//////////////////////////////////////////////////////////////////////////
}}}
