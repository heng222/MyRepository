/*************************************************
  �ļ���   ��TrainInfoData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� TrainInfoData���ݹ���
			DmuCommonData�����TrainInfoData���ܿɷֽ����£�
			1��	��TrainInfoDataStru�ṹ��ָ�����ռ�
			2��	��ȡTrainInfoData����
			3��	��ȡTrainInfoData��Ϣ
			4��	��ȡָ��IDTrainInfoDataStru�Ľṹ���±�
			5��	��ȡָ��IDTrainInfoDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDTrainInfoDataStru���г�����(cm)
			7��	��ȡָ��IDTrainInfoDataStru���г����ǣ�����ٶȣ�cm/s/s��
			8��	��ȡָ��IDTrainInfoDataStru����·��������¶ȣ���·�нǵ�����ֵ*10000��
			9��	��ȡָ��IDTrainInfoDataStru���г���ת����ϵ�����ɳ����ṩ�������ٶ����߼��㣬��λ0.01
			10��	��ȡָ��IDTrainInfoDataStru���������½����ƶ����ٶȡ�ϵͳ��֤��������
			ʵʩ��С���ٶȵĽ����ƶ����ɽ����ƶ���С���ٶ�ֵ���Խ����ƶ���Ч�ʻ��,��λcm/s2
			11��	��ȡָ��IDTrainInfoDataStru�Ľ����ƶ�������Чʱ�䡣������ʱ��,��λ:ms
			12��	��ȡָ��IDTrainInfoDataStru��ǣ���г���ʱ��ʩ�ӽ����ƶ�ʱ���ǵ�ǣ���г���ʱ,��λ:ms
			13��	��ȡָ��IDTrainInfoDataStru����·�ٶ����ޡ���·�涨�ģ��г����κ�λ�ú��κ�ʱ�̶�
			������ﵽ���ٶ�ֵ���ޣ���λkm/h
  ��ע    ���ޡ� 
*************************************************/
#ifndef TRAININFO_DATA_H_
#define TRAININFO_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  TRAININFO_LINE_BYTE_NUM                 13                            /*һ�������ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*�г����ܲ������ñ����ݽṹ��*/
typedef struct BnfTrainInfoStruct
{
    UINT8_S  trainType;                /*�г�����*/        
    UINT16_S trainLength;                /*�г�����(cm)*/
    UINT8_S  trainMaxTracAcc;            /*�г����ǣ�����ٶȣ�cm/s/s��*/    
    UINT16_S lineMaxGrade;            /*��·��������¶ȣ���·�нǵ�����ֵ*10000��*/        
    UINT8_S  trainRotateRate;          /*�г���ת����ϵ�����ɳ����ṩ�������ٶ����߼��㣬��λ0.01*/
    UINT8_S  trainWorstEbAcc;          /*�������½����ƶ����ٶȡ�ϵͳ��֤��������ʵʩ��С���ٶȵĽ����ƶ����ɽ����ƶ���С���ٶ�ֵ���Խ����ƶ���Ч�ʻ��,��λcm/s2*/
    UINT16_S timeEbBrakeBuild;        /*�����ƶ�������Чʱ�䡣������ʱ��,��λ:ms*/
    UINT16_S timeTracCut;                /*ǣ���г���ʱ��ʩ�ӽ����ƶ�ʱ���ǵ�ǣ���г���ʱ,��λ:ms*/
    UINT8_S maxLineLimitSpeed;        /*��·�ٶ����ޡ���·�涨�ģ��г����κ�λ�ú��κ�ʱ�̶�������ﵽ���ٶ�ֵ���ޣ���λkm/h*/    
}BnfTrainInfoStruct;

/*
* ���������� ��TrainInfoDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocTrainInfoDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡTrainInfoData����
* ����˵����
* ����ֵ  �� 
            BnfTrainInfoStruct*
*/
BnfTrainInfoStruct *GetTrainInfoData(void);

/*
* ���������� ��ȡTrainInfoData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfTrainInfoStruct*
*/
BnfTrainInfoStruct *GetTrainInfoDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDTrainInfoDataStru�Ľṹ���±�
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetTrainInfoDataStruIndex(const UINT8_S trainType);

/*
** ���������� ��ȡָ��IDTrainInfoDataStru�Ľṹ��ָ��
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfTrainInfoStruct* GetIndexIdTrainInfoDataStru(const UINT8_S trainType);

/*
** ���������� ��ȡָ��IDTrainInfoDataStru���г�����(cm)
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �г�����(cm)
*/ 
UINT16_S GetTrainInfoDataStrutrainLength(const UINT8_S trainType);

/*
** ���������� ��ȡָ��IDTrainInfoDataStru���г����ǣ�����ٶȣ�cm/s/s��
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �г����ǣ�����ٶȣ�cm/s/s��
*/ 
UINT8_S GetTrainInfoDataStrutrainMaxTracAcc(const UINT8_S trainType);

/*
** ���������� ��ȡָ��IDTrainInfoDataStru����·��������¶ȣ���·�нǵ�����ֵ*10000��
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��·��������¶ȣ���·�нǵ�����ֵ*10000��
*/ 
UINT16_S GetTrainInfoDataStrulineMaxGrade(const UINT8_S trainType);

/*
** ���������� ��ȡָ��IDTrainInfoDataStru���г���ת����ϵ�����ɳ����ṩ�������ٶ����߼��㣬��λ0.01
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �г���ת����ϵ�����ɳ����ṩ�������ٶ����߼��㣬��λ0.01
*/ 
UINT8_S GetTrainInfoDataStrutrainRotateRate(const UINT8_S trainType);

/*
** ���������� ��ȡָ��IDTrainInfoDataStru���������½����ƶ����ٶȡ�ϵͳ��֤��������ʵʩ��С���ٶȵĽ����ƶ����ɽ����ƶ���С���ٶ�ֵ���Խ����ƶ���Ч�ʻ��,��λcm/s2
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������½����ƶ����ٶȡ�ϵͳ��֤��������ʵʩ��С���ٶȵĽ����ƶ����ɽ����ƶ���С���ٶ�ֵ���Խ����ƶ���Ч�ʻ��,��λcm/s2
*/ 
UINT8_S GetTrainInfoDataStrutrainWorstEbAcc(const UINT8_S trainType);

/*
** ���������� ��ȡָ��IDTrainInfoDataStru�Ľ����ƶ�������Чʱ�䡣������ʱ��,��λ:ms
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����ƶ�������Чʱ�䡣������ʱ��,��λ:ms
*/ 
UINT16_S GetTrainInfoDataStrutimeEbBrakeBuild(const UINT8_S trainType);

/*
** ���������� ��ȡָ��IDTrainInfoDataStru��ǣ���г���ʱ��ʩ�ӽ����ƶ�ʱ���ǵ�ǣ���г���ʱ,��λ:ms
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ǣ���г���ʱ��ʩ�ӽ����ƶ�ʱ���ǵ�ǣ���г���ʱ,��λ:ms
*/ 
UINT16_S GetTrainInfoDataStrutimeTracCut(const UINT8_S trainType);

/*
** ���������� ��ȡָ��IDTrainInfoDataStru����·�ٶ����ޡ���·�涨�ģ��г����κ�λ�ú��κ�ʱ�̶�������ﵽ���ٶ�ֵ���ޣ���λkm/h
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��·�ٶ����ޡ���·�涨�ģ��г����κ�λ�ú��κ�ʱ�̶�������ﵽ���ٶ�ֵ���ޣ���λkm/h
*/ 
UINT8_S GetTrainInfoDataStrumaxLineLimitSpeed(const UINT8_S trainType);


#ifdef __cplusplus
}
#endif

#endif
