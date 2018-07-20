/*************************************************
  �ļ���   ��ReadManage.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� ��ȡBnf�ļ�����
			��ȡBnf�ļ������ܿɷֽ����£�
			1��	�����ݺ���ע�����
			2��	�����ݴ���
			3��	��ȡ�������ݳ��ȣ�
			4��	��ȡ�������ݣ�
			5��	��ȡϵͳ��Ƚ����ݰ汾�ţ�
			6��	��ȡ�������������ļ��汾�ţ�
			7��	��ȡ�������������ļ���
			8��	��ȡ�������������ļ���·��ţ�
			9��	��ȡ�����ӱ�CRC��
			10��	��ȡ�����ӱ�汾�ţ�
  ��ע    ���ޡ� 
*************************************************/

#include "ReadManage.h"
#include "ReadBnfData.h"



ReadObjectStruct gReadObjStru; /*������ṹ��*/



/*
* ���������� ������
* ����˵���� void
* ����ֵ  �� void       
*/
void ReadManage(void)
{
    gReadObjStru.ReadData = &ReadBnfData;
    gReadObjStru.GetCfgData = &GetReadBnfDataInfo;
    gReadObjStru.GetCfgDataLen = &GetReadBnfDataLen; 
    
    gReadObjStru.GetDataFileVersion = &GetBnfDataFileVersion;
    gReadObjStru.GetDataFileCrc = &GetBnfDataFileCrc;
    gReadObjStru.GetDataFileSignNum = &GetBnfDataFileSignNum;
    

    
    gReadObjStru.GetInterSysCmpDataFileVer = &GetInterSysCmpDataFileVer;
    gReadObjStru.GetDataSubTabVer = &GetDataSubTabVer;
    gReadObjStru.GetDataSubTabCrc = &GetDataSubTabCrc;
}



/*
* ���������� ������
* ����˵���� 
* ������� :bnfFileAddr �������ļ���ַ
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
             1:�򿪶������ļ�ʧ��
             2:��ȡ�������ļ�ʧ��
             3:У��ʧ�ܣ��汾�Ų�һ��
             4:���ݱ�ʶ������
             5:�����������ļ��ĵ�ַΪ��
*/
INT8_S ReadData(CHAR_S* bnfFileAddr)
{    
    INT8_S retVal = 0;/*��������ֵ*/
    if (gReadObjStru.ReadData != NULL)
    {
        retVal = gReadObjStru.ReadData(bnfFileAddr);
    }
    else
    {
        retVal = -1;
    }

    return retVal;
}

/*
* ���������� ��ȡ�������ݳ���
* ����˵���� 
  ���������dataType ��������   �ɲ�ѯ�����궨�巽ʽ����
            sheetID ����ID      �����        
  ���������indexId   �ṹ��ָ��ƫ��
            dataLength ���ݳ���
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1�ӿڷ�������
            2������������ͺͱ���Ŵ���
*/
INT8_S GetConfigDataLen(UINT8_S mainType, UINT8_S subType,UINT32_S* dataLen, UINT8_S* indexId)
{
    INT8_S retVal = 0;/*��������ֵ*/
    if (gReadObjStru.GetCfgDataLen != NULL)
    {
        retVal = gReadObjStru.GetCfgDataLen(mainType, subType,dataLen,indexId);
    }
    else
    {
        retVal = -1;
    }

    return retVal;
}


/*
* ���������� ��ȡ��������
* ����˵���� 
  ���������UINT16 rowLength   �������ܳ���
              dataLength ���ݳ���
            indexId   �ṹ��ָ��ƫ��    
  ���������dataBuf   ���ݵ�ַ
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1�ӿڷ�������
            2��ȡ����ʧ��
*/
INT8_S GetConfigData(UINT16_S rowLength,UINT32_S dataLen, UINT8_S indexId,UINT8_S* dataBuf)
{
    INT8_S retVal = 0;/*��������ֵ*/
    if (gReadObjStru.GetCfgData != NULL)
    {
        retVal = gReadObjStru.GetCfgData(rowLength,dataLen, indexId,dataBuf);
    }
    else
    {
        retVal = -1;
    }

    return retVal;
}

/*
* ���������� ��ȡϵͳ��Ƚ����ݰ汾��
* ����˵���� 
* �������: const UINT8_S verIndex 
* �������:dataVersion   ���ݰ汾��
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1���ݶ�ȡ���ɹ�
*/
INT8_S DmuGetIntSysCmpDataFileVer(const UINT8_S cmpVerIndex ,UINT32_S* dataVersion)
{
    INT8_S retVal = 0;/*��������ֵ*/

    if (gReadObjStru.GetInterSysCmpDataFileVer != NULL)
    {
        retVal =  gReadObjStru.GetInterSysCmpDataFileVer(cmpVerIndex,dataVersion);
    }
    else
    {
        retVal = -1;
    }

    return retVal;
}

/*
* ���������� ��ȡ�������������ļ��汾��
* ����˵���� 
* �������: ��
* �������:dataVersion   �������������ļ��汾��
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1���ݶ�ȡ���ɹ�
*/
INT8_S DmuGetDataFileVersion(UINT32_S* dataFileVersion)
{
    INT8_S retVal = 0;/*��������ֵ*/

    if (gReadObjStru.GetDataFileVersion != NULL)
    {
        retVal =  gReadObjStru.GetDataFileVersion(dataFileVersion);
    }
    else
    {
        retVal = -1;
    }

    return retVal;
}
    
/*
* ���������� ��ȡ�������������ļ�CRC
* ����˵���� 
* �������: ��
* �������:dataFileCrc   �������������ļ�CRC
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1���ݶ�ȡ���ɹ�
*/
INT8_S DmuGetDataFileCrc(UINT32_S* dataFileCrc)
{
    INT8_S retVal = 0;/*��������ֵ*/

    if (gReadObjStru.GetDataFileCrc != NULL)
    {
        retVal =  gReadObjStru.GetDataFileCrc(dataFileCrc);
    }
    else
    {
        retVal = -1;
    }

    return retVal;
}

/*
* ���������� ��ȡ�������������ļ���·���
* ����˵���� 
* �������: ��
* �������:dataFileCrc   �������������ļ���·���
* ����ֵ  �� 0 �ɹ�
                          -1 ����ָ��Ϊ��
                          1���ݶ�ȡ���ɹ�
*/
INT8_S DmuGetDataFileSignNum(UINT32_S* dataFileSignNum)
{
    INT8_S retVal = 0;/*��������ֵ*/

    if (gReadObjStru.GetDataFileSignNum != NULL)
    {
        retVal =  gReadObjStru.GetDataFileSignNum(dataFileSignNum);
    }
    else
    {
        retVal = -1;
    }

    return retVal;
}


/*
* ���������� ��ȡ�����ӱ�CRC
*����˵����
    ���������const UINT8_S subTabType    �����ӱ�����(���вμ�ReadDataTypeDefine.h����صĶ���)
    ���������subTabDataCrc    4�ֽ�CRC
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1���ݶ�ȡ���ɹ�
*/
INT8_S  DmuGetDataSubTabCrc(const UINT8_S subTabType,UINT32_S* subTabDataCrc)
{
    INT8_S retVal = 0;/*��������ֵ*/

    if (gReadObjStru.GetDataSubTabCrc != NULL)
    {
        retVal =  gReadObjStru.GetDataSubTabCrc(subTabType,subTabDataCrc);
    }
    else
    {
        retVal = -1;
    }

    return retVal;
}


/*
* ���������� ��ȡ�����ӱ�汾��
*����˵����
    ���������const UINT8_S subTabType    �����ӱ�����(���вμ�ReadDataTypeDefine.h����صĶ���)
    ���������subTabDataVer    4�ֽڰ汾��
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1���ݶ�ȡ���ɹ�
*/
INT8_S  DmuGetDataSubTabVer(const UINT8_S subTabType,UINT32_S* subTabDataVer)
{
    INT8_S retVal = 0;/*��������ֵ*/

    if (gReadObjStru.GetDataSubTabVer != NULL)
    {
        retVal =  gReadObjStru.GetDataSubTabVer(subTabType,subTabDataVer);
    }
    else
    {
        retVal = -1;
    }

    return retVal;
}

