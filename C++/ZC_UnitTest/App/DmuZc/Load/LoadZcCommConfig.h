/*******************************************
* �ļ���	��  LoadZcCommConfig.h
* ��  ��	��  ZC��
* ����ʱ��	��  2015-5-25
* ��������	��	����ZcCommConfig����
* ��  ע	��  ��
*******************************************/
#ifndef LOAD_ZCCOMMCONFIG_H_
#define LOAD_ZCCOMMCONFIG_H_


#include "../../../Common/CommonTypes.h"
#include "../Data/ZcCommConfigData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
* ������	��
* ���������� ����ZcCommConfig����
* ����˵���� void
* ����ֵ  �� 0:�ɹ�
*			-2 ���ݳ��ȴ���
*			-1 ����ָ��Ϊ��
*			1�ӿڷ�������
*			2������������ͺͱ���Ŵ���
*/
INT8_S LoadZcCommConfigData(void);

#ifdef __cplusplus
}
#endif
#endif
