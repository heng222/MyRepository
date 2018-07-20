/************************************************************************
 �ļ�����  MAInitManager.c
 ����  ��  ZC��
 ����ʱ�� ��  2015-04-18
 ���� ��  �ƶ���Ȩ��ʼ������
 ��ע �� ��
************************************************************************/
#include "MAInitManager.h"
#include "MAStatusData.h"

extern MaDataStruct gMaDataStruBuff[COMM_TRAIN_SUM_MAX];                  /*���ñ�ZC���Ʒ�Χ������г��ƶ���Ȩ����*/
extern UINT8_S gMaDataIndexBuff[LINE_MAX_TRAIN_ID];			              /*�����г��ƶ���Ȩ�������飬���鳤��Ϊ��·���ܵ�����г�ID*/
extern UINT8_S gMaCurSum;									              /*���ñ�ZC�ƶ���Ȩ��ǰ�г�����*/

extern NextZcMaDataStruct gNextZcDataStruBuff[COMM_TRAIN_SUM_MAX];        /*��������ZC���Ʒ�Χ������г��ƶ���Ȩ����*/
extern UINT8_S gNextZcMaDataIndexBuff[LINE_MAX_TRAIN_ID];                 /*��������ZC�г��ƶ���Ȩ�������飬���鳤��Ϊ��·���ܵ�����г�ID*/
extern UINT8_S gNextZcMaCurSum;                                           /*���ñ�������ZC MA2����*/

/*************************************************
  ������:      InitMaLocalInfo
  ��������:    ��ʼ�����ع�����ƶ���Ȩ��Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void InitMaLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	/*��ʼ��*/
	gMaCurSum = 0U;

	for (cycle = DEFAULT_ZERO;cycle < LINE_MAX_TRAIN_ID;cycle++)
	{
		gMaDataIndexBuff[cycle] = LINE_MAX_TRAIN_ID;
	}

	gNextZcMaCurSum = 0U;

	for (cycle = DEFAULT_ZERO;cycle < LINE_MAX_TRAIN_ID;cycle++)
	{
		gNextZcMaDataIndexBuff[cycle] = LINE_MAX_TRAIN_ID;
	}
}
