/******************************************************************************
*  File Name:   CRC48.h
*  Copyright:   Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
*  Create Date: 20-����-2012 11:33:59
*  Description: ���õ����Ͷ��塢ö�ٶ��壬�ṹ����.
*  REV1.0.0 20054209
******************************************************************************/

#ifndef CRC48_H_
#define CRC48_H_


#include "CommonTypes.h"

/*
*  ���������� CRC48����������������£�ע�⣺����CRC�Ǵ��������ݵ�һ���ֽڵ����BIT��ʼ��
*             ���õĶ���ʽ0x4c11db7L����ʼֵΪ0x00000000,δ���񣬽�����ϵ��Ϊ0x00000000
*             ���DataLen=0������ֵҲΪ0.
*  ����˵���� pData,    ����ָ��
*             DataLen,  ���ݳ��ȣ��ֽڣ�
*              UINT8_S* reg_aU8 CRCֵ
*  ����ֵ��   1 �ɹ�  0 ʧ��
*/
UINT8_S CRC48(const UINT8_S *pData,UINT32_S DataLen,UINT8_S* reg_aU8);

#endif

