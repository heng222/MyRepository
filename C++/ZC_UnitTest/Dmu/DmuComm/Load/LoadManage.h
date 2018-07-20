/********************************************************
* 
* �� �� ���� LoadManage.h 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� �������ͷ�ļ� 
* ��    ע�� �� 
* 
********************************************************/ 

#ifndef LOAD_MANAGE_H_
#define LOAD_MANAGE_H_

#include "../../../Common/CommonTypes.h"

#define LOAD_OBJECT_MAX   50

/*�������ݽṹ��*/
typedef struct LoadObjectStruct
{
    INT8_S (*LoadData)(void); /*��������*/
} LoadObjectStruct;

#ifdef __cplusplus
extern "C" {
#endif

/*
* ���������� ������·���ݹ���
* ����˵���� void
* ����ֵ  �� void       
*/
void LoadLineDataManage(void);

/*
* ���������� ������Ӫ���ݹ���
* ����˵���� void
* ����ֵ  �� void       
*/
void LoadRunDataManage(void);

/*
* ���������� ����ϵͳ�������ݹ���
* ����˵���� void
* ����ֵ  �� void       
*/
void LoadSystemDataManage(void);

/*
* ���������� ����ֽ�����ݹ���
* ����˵���� void
* ����ֵ  �� void       
*/
void LoadDividPointDataManage(void);

/*
* ���������� ��������
* ����˵���� void
* ����ֵ  �� 0:�ɹ�����
*           -1:���󷵻�
*/
INT8_S LoadData(void);

#ifdef __cplusplus
}
#endif

#endif
