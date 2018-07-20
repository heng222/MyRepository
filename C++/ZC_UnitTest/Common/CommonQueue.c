/********************************************************
*                                                                                                            
* �� �� ���� CommonQueue.c   
* ��Ȩ˵���� 
* �� �� �ţ� 1.0
* ����ʱ�䣺 2008.07.29
* ��    �ߣ� 
* ���������� ���к���ʵ��  
* ʹ��ע�⣺ 1.���������õ�Ӧ�÷�ʽ��(������Ӧ�ã������������У�����һ��Ӧ��+һ���жϣ���
*            2 ������֧�ֵ�����������жϺ���������һ��һд����֧����������ͬʱ��������������ͬʱд
*            3 �����㹻�ռ��ֹ����д����
*            4 �벻Ҫ���� 0 qsize��
*            5 �������������ж�����£�����ռ�С����֡���ݵ��������ᷢ�����������ݳ��Ȳ�������ʣ��ռ��ֲ���д����������
*            6 ���������֧��4g�����ݣ�����ʹ����Ӧ����ƽ̨�����������ռ䡣
* �޸ļ�¼��   
*
********************************************************/ 

#include "CommonQueue.h"
#include "stdlib.h"


/*
* ���������� ���г�ʼ�����������ڳ�ʼ��һ�����У���QueueElementFree���ʹ��
*            Ϊ���нṹ���е�q����ռ䣬�������е�size��ʼ��
* ����˵���� QueueStruct *pQueue,    ������ռ�Ķ���
*            UINT32_S QSize,           ������Ҫ�ĳ���
* ����ֵ  �� 1���ɹ�
*            0��ʧ��
*/
UINT8_S QueueInitial(QueueStruct *pQueue, UINT32_S QSize)
{
    UINT8_S bRet = 0;

    /*������ֵ�����ж�*/
    if((NULL != pQueue)&&(0!=QSize))
    {
        /*����ֵ�Ϸ�*/

        /* in=out=0�� ������� */
        pQueue->in = 0; 
        pQueue->out = 0;    
        pQueue->qsize = QSize;
        pQueue->q = (QueueElement* ) malloc(sizeof(QueueElement) * pQueue->qsize);
        if(pQueue->q != NULL)
        {
            /*�ɹ���ʼ��*/

            bRet =    1 ;
        }
        else
        {
            bRet =    0 ;
        }
    }
    else
    {
        /*����ֵ���Ϸ�*/

        bRet =    0 ;
    }

    return bRet;

}


/*
* ���������� ���г�ʼ�����������ڳ�ʼ��һ������
*            QSize��ʼ������QueueInitial��ȣ����ô���Ŀռ���Ϊ����Ԫ�صĿռ䡣
* ����˵���� QueueStruct *pQueue,               ������ռ�Ķ���
*            UINT32_S QSize,                      ������Ҫ�ĳ���
*            QueueElement pQueueElementSpace[], ������Ҫ���ڴ�ռ�
* �� �� ֵ�� 1���ɹ�
*            0��ʧ��
* ʹ��ע�⣺ 1��ȷ��pQueueElementSpace����Ĵ�С���ڵ���QSize�������쳣��
*            2�����ʹ�����������ʼ�������ٵ���QueueElementFree���пռ��ͷš�
*/
UINT8_S StaticQueueInitial(QueueStruct *pQueue, UINT32_S QSize,QueueElement pQueueElementSpace[])
{
    UINT8_S bRet = 0;

    /*������ֵ�����ж�*/
    if((NULL != pQueue)&&(0!=QSize))
    {
        /*����ֵ�Ϸ�*/

        /* in=out=0�� ������� */
        pQueue->in = 0; 
        pQueue->out = 0;    
        pQueue->qsize = QSize;

        pQueue->q = pQueueElementSpace;     /*%RELAX<MISRA_17_6>*/
        bRet =    1 ;

    }
    else
    {
        /*����ֵ���Ϸ�*/
        bRet =    0 ;
    }

    return bRet;    
}

/*
* ���������� ����ɨ�躯�������Զ��������е����ݣ����ǶԶ��еĶ�дָ�붼������Ӱ�죬�����������ݻ��ڶ�����
* ����˵���� UINT32_S DataLen,              Ҫ���������ݳ���;
*            QueueElement *pData,         ����������Ҫ��ŵ�����;
*            QueueStruct *pQueue,         Ҫ�������ݵĶ���
* ����ֵ��   1���ɹ�
*            0��ʧ�ܣ��������ݳ��Ȳ���
*/
UINT8_S QueueScan(UINT32_S DataLen,QueueElement *pData,const QueueStruct *pQueue)
{
    register UINT32_S i,j;
    register QueueElement *pOut;
    UINT8_S bRet = 0u;

    /*��������е����ݲ������ͷ��ش���,�����ֹ����0������*/
    if( (QueueStatus(pQueue)<DataLen) || (DataLen == 0) )         
    {
        bRet =    0 ; 
    }
    else
    {

        if((NULL != pData) && (NULL != pQueue) && (NULL != pQueue->q))
        {
            /*����˴���Ȼ�ܹ���֤�������������*/
            pOut =    & ( pQueue->q[pQueue->out] );
            j = pQueue->qsize - (pQueue->out);

            /*�����Ѿ��ܹ��ж����㹻�����ݣ�����Ҫ�ٶ�inֵ�����ж�*/
            if( j >= DataLen )        
            {
                /*����ת���Զ�������    */
                for(i=0;i<DataLen;i++)
                {
                    *pData = *pOut;
                    pData++;
                    pOut++;
                }             
            } 
            else
            {     
                /*����ת���ܶ�������*/

                /*��������β*/
                for(i=0;i<j ;i++)     
                {
                    *pData = *pOut;
                    pData++;
                    pOut++;
                } 

                /*��outָ��ָ��ͷ*/
                pOut = & pQueue->q[0];     

                /*�Ӷ���ͷ��ʼ��ʣ�µ���*/
                for(;i<DataLen;i++) 
                {
                    *pData = *pOut;
                    pData++;
                    pOut++;
                } 

            }     
            bRet =    1u ;
        
        }
    }


    return bRet; /* ����1�������ݳɹ� */    
}


/*
* ���������� �����к��������Զ��������е�����,�������һ�������У����ݶ������ָ�뷢���仯���������������Ѳ����ڶ�����
* ����˵���� UINT32_S  DataLen,                 Ҫ���������ݳ���;
*            QueueElement     *pData,         ����������Ҫ��ŵ�����;
*            QueueStruct *pQueue,             Ҫ�������ݵĶ���
* ����ֵ ��  1���ɹ�
*            0��ʧ�ܣ��������ݳ��Ȳ���
*/
UINT8_S QueueRead(UINT32_S DataLen, QueueElement *pData,QueueStruct *pQueue)
{
    register UINT32_S i,j;
    register QueueElement *pOut;
    UINT8_S bRet = 0u;

    /*��������е����ݲ������ͷ��ش���,�����ֹ����0������*/
    if( (QueueStatus(pQueue)<DataLen) || (DataLen == 0) )         
    {
        bRet =    0 ; 
    }
    else
    {

        if((NULL != pData) && (NULL != pQueue) && (NULL != pQueue->q))
        {
            /*����˴���Ȼ�ܹ���֤�������������*/
            pOut =    & ( pQueue->q[pQueue->out] );
            j = pQueue->qsize - (pQueue->out);

            /*�����Ѿ��ܹ��ж����㹻�����ݣ�����Ҫ�ٶ�inֵ�����ж�*/
            if( j > DataLen )        
            {
                /*����ת���Զ�������    */

                for(i=0;i<DataLen;i++)
                {
                    *pData = *pOut;
                    pData++;
                    pOut++;
                }             
                pQueue->out += DataLen;                    
            } 
            else 
            {       
                /*j<=DataLen ����ת���ܶ�������*/

                /*��������β*/
                for(i=0;i<j;i++)     
                {
                    *pData = *pOut;
                    pData++;
                    pOut++;
                }     

                /*��outָ��ָ��ͷ*/
                pOut = & pQueue->q[0];     

                /*�Ӷ���ͷ��ʼ��ʣ�µ���*/
                for(;i<DataLen;i++)
                {
                    *pData = *pOut;
                    pData++;
                    pOut++;
                }

                pQueue->out = DataLen - j;     
            }     
            bRet =    1 ;

        
        }

    }
    return bRet; /* ����1�������ݳɹ� */    
}

/*
* ���������� ����к������Ѷ����е�in��outֵ��0
* ����˵���� QueueStruct *pQueue�� ��Ҫ��Ķ���ָ��
* ����ֵ��   1���ɹ�
*/
UINT8_S QueueClear(QueueStruct *pQueue)
{
    UINT8_S retVal  = 0u;
    if(NULL != pQueue)
    {
        /* in=out=0 ������� */
        pQueue->in = 0u; 
        pQueue->out = 0u; 
    	retVal = 1u;
    
    }
    return    retVal ;
}

/*
*    ���������� ���������п������ݳ���
*    ����˵���� QueueStruct *pQueue,        Ҫ���������ݳ��ȵĶ���
*    ����ֵ  �� ���ض����п��õ����ݳ��ȣ��������Ϊ�գ�����0
*/
UINT32_S QueueStatus (const QueueStruct *pQueue)
{
    UINT32_S qStatus = 0u;
    UINT32_S retVal = 0u;

	if(NULL != pQueue)
    {
        if(pQueue->qsize!=0)
        {
            qStatus=(pQueue->in+pQueue->qsize-pQueue->out)%pQueue->qsize;
            retVal = qStatus;
        }
        else
        {
            /*�˴�������ִ��󣬷���0���˴��߼�������*/
            retVal = 0u;
        }
    
    }
    return retVal;
}

/*
* ���������� д���к�������һ�������е�����д��һ��������
*            ��һ�����еĲ�����������������ͬʱд��
*            �����ǲ�����д���ģ����д���º�������0
* ����˵���� UINT32_S  DataLen,             Ҫд������ݳ���;
*            QueueElement *pData,         Ҫд������ݴ�ŵ�����;
*            QueueStruct *pQueue,         Ҫд�����ݵĶ���
* ����ֵ ��  1���ɹ�
*            0��ʧ��,��������
*/
UINT8_S QueueWrite(UINT32_S DataLen,const QueueElement *pData,QueueStruct *pQueue)
{
    register UINT32_S i,j;
    register QueueElement *pIn;
    UINT8_S bRet = 0u;

    /*���ж϶����Ƿ����ܹ��Ŀռ�����д�������,�������Ҫ���ˣ��Ͳ�����д�� */
	if((NULL != pData) && (NULL != pQueue) && (NULL != pQueue->q))
    {
        if( DataLen >= (pQueue->qsize - QueueStatus(pQueue)) )
        {
            bRet =    0 ;    
        }
        else
        {

            /*�����Ѿ��ܹ��ж����㹻�Ŀռ䣬����Ҫ�ٶ�outֵ�����ж�*/
            j =    pQueue->qsize- (pQueue->in); 
            pIn =    & ( pQueue->q[pQueue->in] );

            if( j > DataLen )        
            { 
                /*д��ʱ���Բ��÷�ת*/

                /*���Լ�ָ������������ָ���ִ���ٶ�*/
                for(i=0;i<DataLen;i++)
                {
                    *pIn = *pData;    
                    pIn++;
                    pData++;
                }

                pQueue->in += DataLen;    
            }
            else /*j <= DataLen*/
            {    
                /*д������б�Ȼ��ת*/

                /*�����ݴӵ�ǰָ�뵽������β����д��ĳ���Ϊj*/
                for(i=0;i<j;i++) 
                {
                    *pIn = *pData;    
                    pIn++;
                    pData++;
                }

                /*�Ѿ�д��������β���ˣ�Ӧ�ôӻ�����ͷ��ʼд��*/
                pIn = & pQueue->q[0];

                /*�Ӷ���ͷ��ʼд��i�ĳ�ʼֵΪj������Ϊ�ϴ�д��������β�ĳ��� */
                for(;i<DataLen;i++)     
                {
                    *pIn = *pData;    
                    pIn++;
                    pData++;
                }

                /*�������е�inָ��Ϊд����ܳ��ȼ�ȥд��������β�����ݳ���*/
                pQueue->in = DataLen - j;                
            }
            bRet= 1 ;
        }    
    }
    return bRet; 
}

/*
* ���������� ���д洢�ռ��ͷź���
*            �ڲ���Ҫĳ�����е�ʱ�򣬰Ѷ��е�Ԫ������ռ��ͷŵ�,��QueueInitial���ʹ��
* ����˵���� QueueStruct *pQueue,       ����
* ����ֵ  �� 1���ɹ�
*/
UINT8_S QueueElementFree(QueueStruct *pQueue)
{

    UINT8_S ret = 0u;

	if(NULL != pQueue)
    {
        /*����ָ���λ*/
        pQueue->in = 0; 
        pQueue->out = 0;
        pQueue->qsize = 0;

        /*�ͷŶ��пռ�*/
        if(pQueue->q != NULL )
        {
            #ifdef SYS_TYPE_WINDOWS
            free(pQueue->q);
            #endif
            pQueue->q = NULL;
        	ret = 1u;
        }
    }
    return ret ;
}

/*
* ���������� �ڶ�����ɾ��һ����Ԫ�ء�
* ����˵���� UINT16_S Length,             Ҫɾ����Ԫ�ظ���
*            QueueStruct *pQueue,       Ҫɾ��Ԫ�صĶ���
* ����ֵ ��  1���ɹ�
*/
UINT8_S QueueElementDiscard( UINT16_S Length, QueueStruct *pQueue)
{
    UINT8_S bRet = 0u;

    
    if(NULL != pQueue)
    {
        /* ���������ֽ�����Ԫ�ظ�����Ҫ��*/
        if( QueueStatus(pQueue) < Length)
        {
            QueueClear(pQueue);
        } 
        else
        {
            pQueue->out = (pQueue->out + Length) % pQueue->qsize;
        }
        
        bRet=1;
    }
    return bRet;
}

/*
*    ���������� ���������п��ÿռ��С
*    ����˵���� QueueStruct *pQueue,  ָ���Ķ���
*    ����ֵ  �� ���ض����п��õĿռ��С,���ڶ��в���д������������һ���ռ䲻����
*/
UINT32_S QueueGetSpace (const QueueStruct *pQueue)
{
    UINT32_S qSpace = 0u;
    UINT32_S retVal = 0u;

	if(NULL != pQueue)
    {
        if(pQueue->qsize != 0u)
        {
            qSpace =(pQueue->out+pQueue->qsize-pQueue->in-1)%pQueue->qsize;
            retVal = qSpace;
        }
        else
        {
            /*�˴�������ִ��󣬷���0���˴��߼�������*/
            qSpace = 0u;
            retVal = qSpace;
        }
    }
    return retVal;
}

