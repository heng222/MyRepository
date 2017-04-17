// Color.h


#ifndef _STATIONDRAW_COLOR_H
#define _STATIONDRAW_COLOR_H

//#######################################################################################

#define BLACKCOLOR			RGB(0,0,0)			//ºÚÉ«

#define WHITECOLOR			RGB(255,255,255)	//°×

#define REDCOLOR			RGB(255,0,0)		//ºì
#define LIGHTRED			RGB(255,10,70)		//Ç³ºì
#define DARKRED				RGB(128,0,0)		//°µºì
#define FUCHSINECLR			RGB(255,0,255)		//Æ·ºì£¬Ñóºì
#define DARKFUCHSINE		RGB(128,0,128)		//°µÆ·ºì

#define BLUECOLOR			RGB(0,0,255)		//À¶É«
#define LIGHTBLUE			RGB(0,190,188)		//Ç³À¶
#define DARKBLUE			RGB(0,0,128)		//°µÀ¶
#define INDIGOBLUE			RGB(85,120,182)		//µåÀ¶
#define CYANINE				RGB(5,135,167)		//ÇàÀ¶

#define GREENCOLOR			RGB(0,255,0)		//ÂÌÉ«
#define LIGHTGREEN			RGB(0,192,0)		//Ç³ÂÌ
#define DARKGREEN			RGB(0,128,0)		//°µÂÌ
#define BLUEGREEN			RGB(0,128,128)		//À¶ÂÌ

#define PURPLECLR			RGB(123,65,255)		//×ÏÉ«


#define YELLOWCOLOR			RGB(255,255,0)		//»Æ
#define DARKYELLOW			RGB(128,128,0)		//°µ»Æ


#define DEEPGRAY			RGB(128,128,128)	//Éî»ÒÉ«
#define LIGHTGRAY			RGB(192,192,192)	//Ç³»ÒÉ«
#define DARKGRAY			RGB(64,64,64)		//°µ»ÒÉ«

  

#define LA_BTN_CLR1			GREENCOLOR      /* LieChe button color */
#define LA_BTN_CLR2			LIGHTBLUE      /* LieChe button color when it's down */
#define DA_BTN_CLR1			LIGHTGRAY      /* DiaoChe button color */
#define DA_BTN_CLR2			YELLOWCOLOR     /* DiaoChe button color when it's down */
#define DC_BTN_CLR1			DARKGRAY       /* DanCao button color when DaoCha is SiKai */
#define DC_BTN_CLR2			LIGHTGREEN     /* DanCao button color when DaoCha is DingWei */
#define DC_BTN_CLR3			YELLOWCOLOR     /* DanCao button color when DaoCha is FanWei */
#define DC_BTN_CLR4			REDCOLOR       /* DanCao button color when DaoCha is JiCha */

#define BLACKLIGHT_CLR		BLACKCOLOR
#define WHITELIGHT_CLR		WHITECOLOR
#define GREENLIGHT_CLR		LIGHTGREEN
#define REDLIGHT_CLR		REDCOLOR
#define BLUELIGHT_CLR		BLUECOLOR
#define YELLOWLIGHT_CLR		YELLOWCOLOR


//-----------------------------------
#define COL_BLACK		0x00//ºÚ
#define COL_WITHE		0x01//°×
#define COL_BLUE		0x02//Blue
#define COL_GREEN		0x03//ÂÌ 
#define COL_RED			0x04//ºì   
#define COL_YELLOW		0x05//»Æ   
#define COL_DY			0x06//Ë«»Æ   
#define COL_DG			0x07//Ë«ÂÌ
#define COL_RW			0x08//ºì°×  
#define COL_FB			0x09//¶ÏË¿ (filament break off)
#define COL_GY			0x11//ÂÌ»Æ   
#define COL_WF			0x12//°×ÉÁ   
#define COL_RF			0x13//ºìÉÁ   
#define COL_YF			0x14//»ÆÉÁ   
#define COL_GF			0x15//ÂÌÉÁ   
#define COL_YFY			0x16//»ÆÉÁ»Æ 
   

/* QuDuan Color Band Status Definition */
			
#define ZHENGYONG_CLR		GREENCOLOR		//Õ÷ÓÃÑÕÉ«
#define SUOBI_CLR			WHITECOLOR		//Ëø±ÕÑÕÉ«
#define ZHANYONG_CLR		REDCOLOR		//Õ¼ÓÃÑÕÉ«
#define KONGXIAN_CLR		CYANINE			//¿ÕÏÐÑÕÉ«

#define RED_BAND       0x20  /* ºì¹â´ø *///Ëø±Õ
#define WHITE_BAND     0x08  /* °×¹â´ø *///Õ¼ÓÃ
#define CYAN_BAND      0x02  /* Çà¹â´ø *///Õ÷ÓÃ


#define PENWIDTH       4

//###########################################################################################
//{{_END_STATION_DRAW_COLOR_H
#endif