/*******************************************
* �ļ���	��  LoadZcManage.h
* ��  ��	��  ZC��
* ����ʱ��	��  2015-5-25
* ��������	��	����ZC����
* ��  ע	��  ��
*******************************************/
#ifndef LOADZC_MANAGE_H_
#define LOADZC_MANAGE_H_

#include "../../../Common/CommonTypes.h"

#define LOADZC_OBJECT_MAX   50U

/*�������ݽṹ��*/
typedef struct LoadZCObjectStruct
{
	INT8_S (*LoadData)(void); /*��������*/
} LoadZCObjectStruct;

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
* ���������� ����ZC������ݹ���
* ����˵���� void
* ����ֵ  �� void       
*/
void LoadZcManage(void);

/*******************************************
* ���������� ����ZC����
* ����˵���� void
* ����ֵ  �� 0:�ɹ�����
*           -1:���󷵻�
*/
INT8_S LoadZcData(void);

#ifdef __cplusplus
}
#endif

#endif
