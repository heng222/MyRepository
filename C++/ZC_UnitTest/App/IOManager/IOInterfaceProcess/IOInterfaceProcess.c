/************************************************************************
*
* �ļ���   ��  IOInterfaceProcess.c
* ����ʱ�� ��  2015.08.14
* ����     ��  ZC��
* �������� ��  ��������ӿڴ��� 
* ��  ע   ��  ��
*
************************************************************************/

#include "IOInterfaceProcess.h"
#include "../../../Common/CircQueueStruct.h"
#include "../../SysDataManager/SysDefine.h"
#include "../../../Common/MemSet.h"

#ifdef SYS_TYPE_VXWORKS
#include "../../../PlatformAdapter/AppItf/AdptAppExtDevDataInterface.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../PlatformAdapter/PlatformLog/AdapterLog.h"
#endif

/*��CIͨ�Ŷ���*/
CirQueueStruct gZcToCiDataQueueStru;             /*ZC��CI���ݶ���*/
CirQueueStruct gCiToZcDataQueueStru;             /*CI��ZC���ݶ���*/

/*��ATSͨ�Ŷ���*/
CirQueueStruct gZcToAtsDataQueueStru;            /*ZC��ATS���ݻ�����*/
CirQueueStruct gAtsToZcDataQueueStru;            /*ATS��ZC���ݻ�����*/ /*-bye-*/


/*��ZCͨ�Ŷ���*/
CirQueueStruct gZcToNZcDataQueueStru;            /*ZC��NZc���ݶ���*/
CirQueueStruct gNZcToZcDataQueueStru;            /*NZC��ZC���ݶ���*/

/*�복��ATPͨ�Ŷ���*/
CirQueueStruct gZcToTrainDataQueueStru;           /*ZC������ATP���ݶ���*/
CirQueueStruct gTrainToZcDataQueueStru;           /*����ATP��ZC���ݶ���*/

/*��Ntpͨ�Ŷ���*/
CirQueueStruct gZcToNtpDataQueueStru;            /*ZC��Ntp���ݶ���*/
CirQueueStruct gNtpToZcDataQueueStru;            /*Ntp��ZC���ݶ���*/
 
/*
* ���������� ��ȡƽ̨��������ݽ���������ͨ�Ŷ�����
* ����˵���� void
* ����ֵ  �� ��
*/
void InterfaceInputProcessToLocalQueue(void)
{
    /*���������������д�����ظ���������*/
#ifdef SYS_TYPE_VXWORKS
	UINT8_S  dataBuff[UDP_OUT_FRAME_LEN] = {0U};        /* �������� */
	UINT32_S dataLen = 0U;                              /* ���ݳ��� */
	UINT8_S devType = 0U;
    UINT8_S devId = 0U;
   
    /*��ʼ��*/
    MemorySet(&dataBuff[0],((UINT32_S)(sizeof(UINT8_S) * UDP_OUT_FRAME_LEN)),0U,((UINT32_S)(sizeof(UINT8_S) * UDP_OUT_FRAME_LEN)));

    dataLen = AdptAppExtDevRcvData(dataBuff,UDP_OUT_FRAME_LEN,&devType,&devId);

	while(0U < dataLen)
	{
	    RecvQueueToLocalSingleQueue(devType,&dataBuff[0],dataLen);		
		
	    dataLen = AdptAppExtDevRcvData(dataBuff,UDP_OUT_FRAME_LEN,&devType,&devId);
	}
#endif
}

/*
* ���������� ��֯���ع���ĸ���������Ϣ��������ƽ̨�������
* ����˵���� void
* ����ֵ  �� ��
*/
void InterfaceOutputProcessToPlatform(void)
{
	/*���������������д��ƽ̨��*/
#ifdef SYS_TYPE_VXWORKS

    UINT8_S rtnValue = 0U;
	CirQueueStruct *pCirQueueStru = NULL;              /* �������ݶ���ָ�� */
	
	/* ZC To CI */
	pCirQueueStru = GetZcToCiDataQueueStru();
	rtnValue = LocalSingleQueueToSendQueue(pCirQueueStru);

	
	/* ZC To ATS */
	pCirQueueStru = GetZcToAtsDataQueueStru();
	rtnValue *= LocalSingleQueueToSendQueue(pCirQueueStru);

	
	/* ZC To NZC */
	pCirQueueStru = GetZcToNZcDataQueueStru();
	rtnValue *= LocalSingleQueueToSendQueue(pCirQueueStru);

	
	/* ZC To ATP */
	pCirQueueStru = GetZcToTrainDataQueueStru();
	rtnValue *= LocalSingleQueueToSendQueue(pCirQueueStru);


	/* ZC To NTP */
	pCirQueueStru = GetZcToNtpDataQueueStru();
	rtnValue *= LocalSingleQueueToSendQueue(pCirQueueStru);

	
	/* ZC To Log */
    /* PutLogToSendQueue(); */ 
	AdptAppLogDataPack(INNER_DEVTYPE_LOG,1u);
#endif	
}

/*
* ���������� �����ն��е������ݷ��뵥�����ݶ���
* ����˵���� UINT8_S devType,����
*            const UIN8_S dataBuff[],��������
*            UINT32_S datalen,���ݳ���
* ����ֵ  �� void
*/

void RecvQueueToLocalSingleQueue(UINT8_S devType,const UINT8_S dataBuff[],UINT32_S datalen)
{
    /* �����ն��е������ݷ��뵥�����ݶ��� */
#ifdef SYS_TYPE_VXWORKS

    CirQueueStruct *pCirQueueStru = NULL;

	switch(devType)
    {
        case INNER_DEVTYPE_CI:
			{
			    pCirQueueStru = GetCiToZcDataQueueStru();
        	}
			break;
		case INNER_DEVTYPE_ZC:
			{
                pCirQueueStru = GetNZcToZcDataQueueStru();
		    }
			break;
		case INNER_DEVTYPE_TRAIN:
			{
		        pCirQueueStru = GetTrainToZcDataQueueStru();
		    }
			break;
		case INNER_DEVTYPE_NTP:
			{
                pCirQueueStru = GetNtpToZcDataQueueStru();				
			}
			break;
		case INNER_DEVTYPE_ATS:
			{
				/* û��ATS���� */
				pCirQueueStru = GetAtsToZcDataQueueStru();/*-bye-*/
			}
			break;
		default:
			break;
    }

    if((NULL != pCirQueueStru) && (NULL != dataBuff)
		&& (datalen > 0U))
    {
        /*��������ӵ�������*/
		if (0 == AddQueueData(pCirQueueStru,dataBuff,datalen))
		{
            /* ������ */

		}
		
    }	
#endif

}

/*
* ���������� �������������ݷ��뷢�͵Ķ��е���
* ����˵���� CirQueueStruct *pCirQueueStru ����ָ��
* ����ֵ  �� 0: ʧ��
*            1: �ɹ�
*/

UINT8_S LocalSingleQueueToSendQueue(CirQueueStruct *pCirQueueStru)
{
    /* �������������ݷ��뷢�͵Ķ��е��� */
    UINT8_S rtnValue = RETURN_ERROR;
#ifdef SYS_TYPE_VXWORKS
    
    UINT32_S i = 0U;        /**/
	UINT32_S pkgCount = 0U;                             /* �������� */
	UINT8_S  dataBuff[UDP_MAX_BUFF_SIZE] = {0U};        /* �������� */
	UINT32_S dataLen = 0U;                              /* ���ݳ��� */
    UINT32_S startIndex = 0U;
	UINT8_S destDevType = 0U;
    UINT8_S destDevId = 0U;
    UINT8_S addFlag = 0U;       /* ���뷢�Ͷ��еĳɹ�����־*/
	UINT8_S breakFlag = 0U;

    /*��ʼ��*/
    MemorySet(&dataBuff[0],((UINT32_S)(sizeof(UINT8_S) * UDP_MAX_BUFF_SIZE)),0U,((UINT32_S)(sizeof(UINT8_S) * UDP_MAX_BUFF_SIZE)));
	
    if (NULL != pCirQueueStru)
    {
        /* ��ȡ���ݰ��ĸ��� */
        pkgCount = GetQueuePkgCount(pCirQueueStru);   
		
        for(i = 0U;i < pkgCount;i++)
        {
            MemorySet(&dataBuff[0],((UINT32_S)(sizeof(UINT8_S) * UDP_MAX_BUFF_SIZE)),0U,((UINT32_S)(sizeof(UINT8_S) * UDP_MAX_BUFF_SIZE)));

            dataLen = GetQueuePkgData(pCirQueueStru,&dataBuff[0],UDP_MAX_BUFF_SIZE);
		
			if(0U < dataLen)
			{
			    /* ��ȡĿ�����ͺ�ID */
                destDevType = dataBuff[2];
                destDevId =dataBuff[3];

				/* ATS��NTP����־ȥ��4��ͷ */
				if(((INNER_DEVTYPE_ATS == destDevType) || (INNER_DEVTYPE_NTP == destDevType))
					&& (dataLen >= 4U))
				{
				    startIndex = 4U;
					dataLen = dataLen - 4U;
				}

                /* ������д�뷢�Ͷ��е��� */
                addFlag = AdptAppExtDevSndData(&dataBuff[startIndex],dataLen,destDevType,destDevId);

                if(0U == addFlag)
                { 
                    breakFlag = FLAG_SET;
                    break;
                }  
			}           
        }

        if(FLAG_SET == breakFlag)
        {
            rtnValue = RETURN_ERROR;
        }
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }
    	
#endif	

    return rtnValue;
}

/*
* ���������� ��ȡZcToCi�ӿڶ���
* ����˵���� void
* ����ֵ  �� NULL: ��ȡ����ʧ��
*           !NULL: �ӿڶ���
*/
CirQueueStruct* GetZcToCiDataQueueStru(void)
{
	return &gZcToCiDataQueueStru;
}

/*
* ���������� ��ȡCiToZc�ӿڶ���
* ����˵���� void
* ����ֵ  �� NULL: ��ȡ����ʧ��
*           !NULL: �ӿڶ���
*/
CirQueueStruct* GetCiToZcDataQueueStru(void)
{
	return &gCiToZcDataQueueStru;
}

/*
* ���������� ��ȡZcTo����ATP�ӿڶ���
* ����˵���� void
* ����ֵ  �� NULL: ��ȡ����ʧ��
*           !NULL: �ӿڶ���
*/
CirQueueStruct* GetZcToTrainDataQueueStru(void)
{
	return &gZcToTrainDataQueueStru;
}

/*
* ���������� ��ȡ����ATPToZc�ӿڶ���
* ����˵���� void
* ����ֵ  �� NULL: ��ȡ����ʧ��
*           !NULL: �ӿڶ���
*/
CirQueueStruct* GetTrainToZcDataQueueStru(void)
{
	return &gTrainToZcDataQueueStru;
}

/*
* ���������� ��ȡZcToAts�ӿڶ���
* ����˵���� void
* ����ֵ  �� NULL: ��ȡ����ʧ��
*           !NULL: �ӿڶ���
*/
CirQueueStruct* GetZcToAtsDataQueueStru(void)
{
	return &gZcToAtsDataQueueStru;
}

/*
* ���������� ��ȡAtsToZc�ӿڶ���
* ����˵���� void
* ����ֵ  �� NULL: ��ȡ����ʧ��
*           !NULL: �ӿڶ���
*/
CirQueueStruct* GetAtsToZcDataQueueStru(void)/*-bye-*/
{
    return &gAtsToZcDataQueueStru;
}


/*
* ���������� ��ȡZcToNZc�ӿڶ���
* ����˵���� void
* ����ֵ  �� NULL: ��ȡ����ʧ��
*           !NULL: �ӿڶ���
*/
CirQueueStruct* GetZcToNZcDataQueueStru(void)
{
	return &gZcToNZcDataQueueStru;
}

/*
* ���������� ��ȡNZcToZc�ӿڶ���
* ����˵���� void
* ����ֵ  �� NULL: ��ȡ����ʧ��
*           !NULL: �ӿڶ���
*/
CirQueueStruct* GetNZcToZcDataQueueStru(void)
{
	return &gNZcToZcDataQueueStru;
}

/*
* ���������� ��ȡZcToNtp�ӿڶ���
* ����˵���� void
* ����ֵ  �� NULL: ��ȡ����ʧ��
*           !NULL: �ӿڶ���
*/
CirQueueStruct* GetZcToNtpDataQueueStru(void)
{
	return &gZcToNtpDataQueueStru;
}

/*
* ���������� ��ȡNtpToZc�ӿڶ���
* ����˵���� void
* ����ֵ  �� NULL: ��ȡ����ʧ��
*           !NULL: �ӿڶ���
*/
CirQueueStruct* GetNtpToZcDataQueueStru(void)
{
	return &gNtpToZcDataQueueStru;
}


/*
* ���������� ��ȡZC����־�Ľӿڶ���
* ����˵���� void
* ����ֵ  �� NULL: ��ȡ����ʧ��
*           !NULL: �ӿڶ���
*/
CirQueueStruct* GetZcToLogDataQueueStru(void)
{
	/*return &gZcToLogDataQueueStru;*/
    return NULL;
}
