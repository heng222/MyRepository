/********************************************************
*                                                                                                            
* �� �� ���� CommonTypes.h
* ��Ȩ˵����  
* ����ʱ�䣺 2013-09-22
* ��    �ߣ� 
* ���������� �����������Ͷ���  
* �޸ļ�¼��   
*
********************************************************/

#ifndef COMMON_TYPES_H_
#define COMMON_TYPES_H_

/**************************����ƽ̨ѡ����ض���***************************************/


#define SYS_TYPE_VXWORKS      

/*#define SYS_TYPE_WINDOWS */
#ifndef PLATFORM_ARTESYN_FILEOPERATION
#define PLATFORM_ARTESYN_FILEOPERATION
#endif

/*************************��������ֵ��Χ��ض���**********************************/
#define UINT8_MAX              0xFFu
#define UINT16_MAX             0xFFFFu
#define UINT32_MAX             0xFFFFFFFFu

#define INT8_MIN               (-128)
#define INT8_MAX               (127)
#define INT16_MIN              (-32768)
#define INT16_MAX              (32767)
#define INT32_MIN              (-2147483647L - 1)
#define INT32_MAX              (2147483647)

#define FLOAT32_MAX            (3.402823466e+38F)
#define FLOAT64_MAX            (1.7976931348623158e+308)



/*************************������ض���**********************************/
#if defined SYS_TYPE_MOTOROLA

typedef char                CHAR_S;
typedef signed char         INT8_S;
typedef unsigned char       UINT8_S;
typedef unsigned char       UCHAR_S;
typedef short int           INT16_S;
typedef unsigned short int  UINT16_S;
typedef long                INT32_S;
typedef unsigned long       UINT32_S;
typedef float               FLOAT32_S;
typedef double              FLOAT64_S;


#elif defined SYS_TYPE_VXWORKS

typedef char                     CHAR_S;
typedef    unsigned char            UCHAR_S;
typedef    signed char              INT8_S;
typedef    unsigned char            UINT8_S;
typedef    signed   short int       INT16_S;
typedef    unsigned short int       UINT16_S;
typedef    signed long  int         INT32_S;
typedef    unsigned long  int       UINT32_S;
typedef float                    FLOAT32_S;
typedef double                   FLOAT64_S;



#elif defined SYS_TYPE_WINDOWS  

typedef char                CHAR_S;
typedef signed char         INT8_S;
typedef unsigned char       UINT8_S;
typedef unsigned char       UCHAR_S;
typedef short int           INT16_S;
typedef unsigned short int  UINT16_S;
typedef int                 INT32_S;
typedef unsigned int        UINT32_S;
typedef float               FLOAT32_S;
typedef double              FLOAT64_S;
#else

#endif


/*************************����Ĭ��ֵ��ض���**********************************/
#ifndef NULL
#define NULL 0
#else
#endif





#endif
