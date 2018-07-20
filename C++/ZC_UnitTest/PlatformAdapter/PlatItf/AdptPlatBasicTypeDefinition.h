/********************************************************
* 
* �� �� ���� AdptPlatBasicTypeDefinition.h
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01 
* ���������� ƽ̨�����Եײ��������ͷ�ļ�  
* ��    ע�� �� 
* 
********************************************************/ 

#ifndef ADPT_PLAT_BASIC_TYPE_DEFINITION_H_
#define ADPT_PLAT_BASIC_TYPE_DEFINITION_H_

#include "../../Common/CommonTypes.h"

#include "../../cspadpt/Vcp_File_Interface.h"
#include "../../cspadpt/GL_Basic_Type_Definition.h"

#ifdef SYS_TYPE_WINDOWS
typedef FILE*               FILEType;        /*�ļ��������*/
#else
typedef signed long int     FILEType;         /*�ļ��������*/
#endif

/*����ʵʱʱ�ӵĸ�ʽ*/
typedef struct AdptRealClk
{
  UINT16_S Year ; /*[2 Byte] ���,ȡֵ[0~10000]   */
  UINT8_S  Month; /*[1 Byte] �·�,ȡֵ[1~12]      */
  UINT8_S  Day  ; /*[1 Byte] ����,ȡֵ[1~31]      */
  UINT32_S MiSec; /*[4 Byte] ����,ȡֵ[0~86399999]*/
}AdptRealClkStruct;     /*[8 Byte]*/

/*����ͨ��ԭ����Ϣ*/
typedef struct AdptCellMsg
{
  UINT8_S*  ptrMsg ; /* [4 Bytes] ȡֵ[�����ַ]     */
  UINT32_S  dataLen; /* [4 Bytes] ȡֵ[0, 0xFFFFFFFF]*/
}AdptCellMsgStruct;        /* [8 Bytes] */


#endif



