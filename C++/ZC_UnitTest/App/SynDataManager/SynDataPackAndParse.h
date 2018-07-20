/************************************************************************
*
* �ļ���   ��  SynDataPackAndParse.h
* ����ʱ�� ��  2016.1.18
* ����     ��  ZC��
* �������� ��  2ϵͬ�����ݵĴ���ͽ���
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SYN_DATA_PACK_AND_PARSE_H_
#define SYN_DATA_PACK_AND_PARSE_H_

#include "../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
* ���������� ����֡���е�ȫ����Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S ParseAllInfoFromFrame(const UINT8_S inFrameContent[]);

/*
* ���������� ����֡���е�ȫ����Ϣ
* ����˵���� UINT8 outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S PackAllInfoToFrame(UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�AC��Ϣ
* ����˵���� UINT32 *buffIndex,֡���յ��±�
*            UINT8_S FrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetACInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�ACȫ����Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetACInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡����DR�������۷���ť��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡���յ��±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetDRButtonInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�DRȫ����Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetDRButtonInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡����DR�������۷�����Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡���յ��±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetDRLampInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡����DR�������۷�����Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetDRLampInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���еĽ���ͣ����ťESB��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetESBInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�ESB��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetESBInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�������PSD��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetPSDInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�PSD��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetPSDInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�LogicSection��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetLogicSectionInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�LogicSection��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetLogicSectionInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�Overlap��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetOverlapInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�Overlap��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetOverlapInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�Route��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetRouteInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�Route��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetRouteInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�Signal��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetSignalInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�Signal��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetSignalInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�Switch��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetSwitchInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�Switch��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetSwitchInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�Tsr��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetTsrInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�Tsr��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetTsrInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�Train��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetTrainInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�Train��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetTrainInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�CommTarget��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetCommTargetInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�ͨѶ�豸��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetCommTargetInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�NTPУʱ�ɹ���־��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetNTPTimeFlagInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�NTPУʱ�ɹ���־��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetNTPTimeFlagInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�NTPУʱ����ʱ����Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetNTPLocalTimeInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�NTPУʱ����ʱ����Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetNTPLocalTimeInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�NTPУʱ�ṹ��ʱ����Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetNTPStructTimeInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�NTPУʱ�ṹ��ʱ����Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetNTPStructTimeInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�ZC�ϵ��ǳɹ���־��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetZCPowerUpFlagInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�ZC�ϵ��ǳɹ���־��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetZCPowerUpFlagInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* ���������� ����֡���е�CRC32��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetCRC32InfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* ���������� ����֡���е�CRC32��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetCRC32InfoToFrame(UINT32_S *buffIndex,const UINT8_S outFrameContent[]);

#ifdef __cplusplus
}
#endif

#endif 
