/*******************************************
 * �ļ���	��  LoadZcManage.c
 * ��  ��	��  ZC��
 * ����ʱ��	��  2015-5-25
 * ��������	��	����ZC����
 * ��  ע	��  ��
*******************************************/
#include "LoadZcManage.h"
#include "LoadZcCommConfig.h"
#include "LoadZcSignInfo.h"
#include "LoadZcSystemConfig.h"
#include "LoadZcTimeConfig.h"

static LoadZCObjectStruct LoadZcObjStru[LOADZC_OBJECT_MAX]; /*�������*/
static UINT8_S LoadZcObjCount = 0U; /*����������*/

/*******************************************
* ���������� ����ZC������ݹ���
* ����˵���� void
* ����ֵ  �� void       
*/
void LoadZcManage(void)
{
	LoadZcObjStru[LoadZcObjCount].LoadData = &LoadZcCommConfigData;
    LoadZcObjCount = LoadZcObjCount + 1U;

	LoadZcObjStru[LoadZcObjCount].LoadData = &LoadZcSignInfoData;
    LoadZcObjCount = LoadZcObjCount + 1U;

	LoadZcObjStru[LoadZcObjCount].LoadData = &LoadZcSystemConfigData;
    LoadZcObjCount = LoadZcObjCount + 1U;

	LoadZcObjStru[LoadZcObjCount].LoadData = &LoadZcTimeConfigData;
    LoadZcObjCount = LoadZcObjCount + 1U;
}

/*******************************************
* ���������� ����ZC����
* ����˵���� void
* ����ֵ  �� 0:�ɹ�����
*           -1:���󷵻�
*/
INT8_S LoadZcData(void)
{
	INT8_S retVal = 0;/*��������ֵ*/
	UINT8_S ii = 0U;
	for (ii = 0U; ii < LoadZcObjCount; ii++)
	{
		if (LoadZcObjStru[ii].LoadData != NULL)
		{
			retVal = LoadZcObjStru[ii].LoadData();
			if (retVal != 0)
			{
				break;
			}
		}
		else
		{
			retVal = -1;
			break;
		}
	}
	return retVal;
}
