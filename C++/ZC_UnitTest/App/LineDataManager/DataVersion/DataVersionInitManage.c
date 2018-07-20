/************************************************************************
*
* �ļ���   ��  DataVersionInitManage.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ���ݰ汾��ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#include "DataVersionConfigData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Dmu/Read/ReadDataTypeDefine.h"
#include "../../../Common/Convert.h"
#include "DataVersionInitManage.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"
#include "DataVersionDefine.h"

extern DataVersionStruct gLocalDataVersionStru;                 /*���屾�����ݵİ汾����Ϣ*/

/*
* ���������� ��ʼ���������ݰ汾��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			 1: ��ʼ���ɹ�
*/
UINT8_S InitLocalDataVersion(void)
{
	UINT16_S initErrorFlag = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/* ZC�Լ�ʹ�õ����ݰ汾��Ϣ */
	if (RETURN_SUCCESS == InitLocalZcSelfDataVersion())
	{
        /*������*/	
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_2);
	}

    /* ZC��ATP�Աȵ����ݰ汾 */
    if (RETURN_SUCCESS == InitZcAtpDataVersion())
    {
        /* ������ */
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_3);
    }

	if (DEFAULT_ZERO == initErrorFlag)
	{
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	LogPrintf(1U,"InitLocalDV Err %d\n",initErrorFlag);
	return rtnValue;
}

/*
* ���������� ��ʼ���������ݰ汾��Ϣ(ZC�Լ����ݰ汾)
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			 1: ��ʼ���ɹ�
*/
UINT8_S InitLocalZcSelfDataVersion(void)
{
	UINT8_S versionBuff[SINGLE_VERSION_LEN_MAX] = {DEFAULT_ZERO};
	INT8_S tempRtn = 1;
	UINT32_S dataVerison = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;

	MemorySet(&versionBuff[0],((UINT32_S)(SIZE_UINT8 * SINGLE_VERSION_LEN_MAX)),
                0U,((UINT32_S)(SIZE_UINT8 * SINGLE_VERSION_LEN_MAX)));

	/*��ȡZC�Լ�ʹ�õ����ݰ汾��Ϣ*/
	tempRtn = DmuGetDataFileVersion(&dataVerison);

	if (0 == tempRtn)
	{
		LongToChar(dataVerison,versionBuff);

		for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
		{
			gLocalDataVersionStru.SelfDataVersion[cycle] = versionBuff[cycle];
		}

		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ʼ���������ݰ汾��Ϣ(ZC��ATP���ݰ汾)
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			 1: ��ʼ���ɹ�
*/
UINT8_S InitZcAtpDataVersion(void)
{
    UINT8_S versionBuff[SINGLE_VERSION_LEN_MAX] = {DEFAULT_ZERO};
    INT8_S tempRtn = 1;
    UINT32_S dataVerison = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;

    MemorySet(&versionBuff[0],((UINT32_S)(SIZE_UINT8 * SINGLE_VERSION_LEN_MAX)),
        0U,((UINT32_S)(SIZE_UINT8 * SINGLE_VERSION_LEN_MAX)));

    /*��ȡZC��ATP�Աȵ����ݰ汾��Ϣ*/
    tempRtn = DmuGetIntSysCmpDataFileVer(((UINT8_S)(INTERSYSVERCMP_IDX_ATPZC)),&dataVerison);

    if (0 == tempRtn)
    {
        LongToChar(dataVerison,versionBuff);

        for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
        {
            gLocalDataVersionStru.ZcATPDataVersion[cycle] = versionBuff[cycle];
        }

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}