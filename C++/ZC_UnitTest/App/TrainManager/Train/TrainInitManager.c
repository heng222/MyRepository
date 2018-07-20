/************************************************************************
 �ļ���   ��  TrainInitManager.c
 ����ʱ�� ��  2015.07.02
 ����     ��  ZC��
 ���� ��  �г���ʼ������
 ��ע �� ��
************************************************************************/
#include "TrainInitManager.h"
#include "TrainStatusData.h"

extern TrainInfoStruct gTrainStatusDataStruBuff[SIZE_MAX_CONTROLE_TRAIN];     /*���ñ�ZC���Ʒ�Χ������г�����*/
extern UINT8_S gLocalTrainIndexBuff[SIZE_MAX_LINE_TRAIN];			          /*�����г��������飬���鳤��Ϊ��·���ܵ�����г�ID*/
extern UINT8_S gTrainCurSum;									              /*���ñ�ZC��ǰ�г�����*/

/*************************************************
  ������:      InitTrainLocalInfo
  ��������:    ��ʼ�����ع�����г���Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void InitTrainLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	/*��ʼ��*/
	gTrainCurSum = 0U;

	for (cycle = DEFAULT_ZERO;cycle < SIZE_MAX_LINE_TRAIN;cycle++)
	{
		gLocalTrainIndexBuff[cycle] = RETURN_UINT8_MAX_VALUE;
	}
}
