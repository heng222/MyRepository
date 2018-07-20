/********************************************************                                                                                                            
 �� �� ���� MaintainManager.h
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015-04-18
 ������ ά����־����
 ��ע�� ��  
********************************************************/

#ifndef MAINTAIN_MANAGER_H_
#define MAINTAIN_MANAGER_H_

#include "../../Common/CommonTypes.h"

/* �����Vxworks�棬����ƽ̨��������־��¼���� */
#ifdef SYS_TYPE_VXWORKS
#include "../../cspadpt/Vcp_Device_Definition_Inf.h"
#include "../../cspadpt/Vcp_Service_Interface.h"
#include "../../cspadpt/Vcp_Service_TestInterface.h"
#include "../../PlatformAdapter/PlatformLog/AdapterLog.h"

#define LogPrintf   AdptAppLogPrintf      /* �������־��ӡ */
#define LogPrintBuff AdptAppLogPrintBuff  /* �������־��ӡ����*/
#endif

#define LOG_TYPE   1                    /* ��¼logΪ1������¼logΪ0 */
#define MAINTAIN_DATA_LEN_MAX 25000u    /* ��־����ĳ��� */
#define UDP_OUT_FRAME_LEN_1 25000u      /* UDP����ĳ��� */


#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
  ������:      SetLogPrintfType
  ��������:    ���ô�ӡlog��Ϣ����
  ����:        const UINT8_S logPrintfType ��¼��־��ʶ
  ���:        ��
  ����ֵ:      ��
*************************************************/
void SetLogPrintfType(const UINT8_S logPrintfType);

/*************************************************
  ������:      LogPrintf
  ��������:    ��ӡlog��Ϣ
  ����:        UINT8_S chRunSystem, ��ʶ
               const char * lpszFormat ָ��
  ���:        ��
  ����ֵ:      0u ʧ��
               1u �ɹ�
*************************************************/
#ifdef SYS_TYPE_WINDOWS
UINT8_S LogPrintf(UINT8_S chRunSystem, const char * lpszFormat, ...);
#endif

/*************************************************
  ������:      LogPrintf_Windows
  ��������:    ��ӡWindows��log��Ϣ
  ����:        const char * szFileName, �ļ���
               const char * lpszFormat, ָ��
               const UINT32_S dwLength, ����
  ���:        ��
  ����ֵ:      -1:  ʧ��
               !=-1: �ɹ�
*************************************************/
#ifdef SYS_TYPE_WINDOWS
INT32_S LogPrintf_Windows(const char * szFileName, const char * lpszFormat,const UINT32_S dwLength);
#endif

/*************************************************
  ������:      LogPrintBuff
  ��������:    ������������ת��Ϊ�ַ���
  ����:        const UINT8_S dataBuf[]�� �����׵�ַ
               const UINT16_S bufLength,���鳤��
               const UINT16_S dataLength ���ݳ���
  ���:        ��
  ����ֵ:      0U,ʧ��
               1U,�ɹ�
*************************************************/
#ifdef SYS_TYPE_WINDOWS
UINT8_S LogPrintBuff(const UINT8_S dataBuf[],const UINT16_S bufLength,const UINT16_S dataLength);
#endif

/*************************************************
  ������:      LogBufPeriodClear
  ��������:    �����������
  ����:        ��
  ���:        ��
  ����ֵ:      0��
*************************************************/
void LogBufPeriodClear(void);

/*************************************************
  ������:      GetgMaintainDataArr
  ��������:    ��ȡ��־�ֽ�������׵�ַ
  ����:        ��
  ���:        ��
  ����ֵ:      �����׵�ַ
*************************************************/
UINT8_S *GetgMaintainDataArr(void);

/*************************************************
  ������:      GetgMaintainLen
  ��������:    ��ȡ��־�������ֽڵ�����
  ����:        ��
  ���:        ��
  ����ֵ:      �ֽڳ���
*************************************************/
UINT32_S *GetgMaintainLen(void);


#ifdef __cplusplus
}
#endif

#endif
