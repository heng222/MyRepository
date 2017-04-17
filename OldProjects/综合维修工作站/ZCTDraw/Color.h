// Color.h


#ifndef _STATIONDRAW_COLOR_H
#define _STATIONDRAW_COLOR_H

//#######################################################################################

#define BLACKCOLOR			RGB(0,0,0)			//��ɫ

#define WHITECOLOR			RGB(255,255,255)	//��

#define REDCOLOR			RGB(255,0,0)		//��
#define LIGHTRED			RGB(255,10,70)		//ǳ��
#define DARKRED				RGB(128,0,0)		//����
#define FUCHSINECLR			RGB(255,0,255)		//Ʒ�죬���
#define DARKFUCHSINE		RGB(128,0,128)		//��Ʒ��

#define BLUECOLOR			RGB(0,0,255)		//��ɫ
#define LIGHTBLUE			RGB(0,190,188)		//ǳ��
#define DARKBLUE			RGB(0,0,128)		//����
#define INDIGOBLUE			RGB(85,120,182)		//����
#define CYANINE				RGB(5,135,167)		//����

#define GREENCOLOR			RGB(0,255,0)		//��ɫ
#define LIGHTGREEN			RGB(0,192,0)		//ǳ��
#define DARKGREEN			RGB(0,128,0)		//����
#define BLUEGREEN			RGB(0,128,128)		//����

#define PURPLECLR			RGB(123,65,255)		//��ɫ


#define YELLOWCOLOR			RGB(255,255,0)		//��
#define DARKYELLOW			RGB(128,128,0)		//����


#define DEEPGRAY			RGB(128,128,128)	//���ɫ
#define LIGHTGRAY			RGB(192,192,192)	//ǳ��ɫ
#define DARKGRAY			RGB(64,64,64)		//����ɫ

  

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
#define COL_BLACK		0x00//��
#define COL_WITHE		0x01//��
#define COL_BLUE		0x02//Blue
#define COL_GREEN		0x03//�� 
#define COL_RED			0x04//��   
#define COL_YELLOW		0x05//��   
#define COL_DY			0x06//˫��   
#define COL_DG			0x07//˫��
#define COL_RW			0x08//���  
#define COL_FB			0x09//��˿ (filament break off)
#define COL_GY			0x11//�̻�   
#define COL_WF			0x12//����   
#define COL_RF			0x13//����   
#define COL_YF			0x14//����   
#define COL_GF			0x15//����   
#define COL_YFY			0x16//������ 
   

/* QuDuan Color Band Status Definition */
			
#define ZHENGYONG_CLR		GREENCOLOR		//������ɫ
#define SUOBI_CLR			WHITECOLOR		//������ɫ
#define ZHANYONG_CLR		REDCOLOR		//ռ����ɫ
#define KONGXIAN_CLR		CYANINE			//������ɫ

#define RED_BAND       0x20  /* ���� *///����
#define WHITE_BAND     0x08  /* �׹�� *///ռ��
#define CYAN_BAND      0x02  /* ���� *///����


#define PENWIDTH       4

//###########################################################################################
//{{_END_STATION_DRAW_COLOR_H
#endif