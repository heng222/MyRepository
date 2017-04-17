
#include "stdafx.h"
#include "CommonFunc.h"
#include "WebService.h"

//#define _WEATHER_PAYMENT  // ���Ѷ���

//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
    #define             INTERVALTIME        (60*1000)  // 60��
#else
    #define             INTERVALTIME        (60*3600*1000) // 60��
#endif


//////////////////////////////////////////////////////////////////////////
CWeatherClient::CWeatherClient()
{
    m_hExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
    m_pThread = NULL;
}

CWeatherClient::~CWeatherClient()
{
    m_Service.Cleanup();
    m_Service.CleanupClient();
}

BOOL CWeatherClient::Initialize()
{  
    return TRUE;
}

BOOL CWeatherClient::Start()
{
    // ���������߳�
    m_pThread = AfxBeginThread(_ThreadEntry,this);

    TRACE("WebServ Thread Address = 0X%08X\n",m_pThread);

    if (m_pThread==NULL)
    {
        return FALSE;
    }

    return TRUE;

}

void CWeatherClient::Stop()
{
    m_pThread->SuspendThread();
}

void CWeatherClient::Terminate()
{
    // 
    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("���ڹر��������ͨ�š���"));
    NbsSendModuleMsg(&aLog);

    // 
    SetEvent(m_hExitEvent);
    if (m_pThread!=NULL)
    {
        WaitForSingleObject(m_pThread->m_hThread,2000);
        delete m_pThread;
    }
    CloseHandle(m_hExitEvent);
}

BOOL CWeatherClient::GetInformation()
{

#ifdef _WEATHER_PAYMENT
    POSITION pos = m_strlistCityCode.GetHeadPosition();
#else
    BOOL bOrder = (COleDateTime::GetCurrentTime().GetDay()%2==0);
    POSITION pos=NULL;
    if (bOrder)
    {
        pos = m_strlistCityCode.GetHeadPosition();
    }
    else
    {
        pos = m_strlistCityCode.GetTailPosition();
    }
#endif
    
    while(pos)
    {

        // �˳��ź��Ƿ񼤻
        if (WaitForSingleObject(m_hExitEvent,0)==WAIT_OBJECT_0)
        {
            return FALSE;
        }

        /************************************************************************/
        /* 1.���λ�ø����е�������Ϣ                                           */
        /************************************************************************/
        CString strCityCode;
        
#ifdef _WEATHER_PAYMENT
        strCityCode = m_strlistCityCode.GetNext(pos);
#else
        if (bOrder)
        {
            strCityCode = m_strlistCityCode.GetNext(pos);
        }
        else
        {
            strCityCode = m_strlistCityCode.GetPrev(pos);
        }
#endif
        BSTR bsCityCode = strCityCode.AllocSysString();
        int iRstNum = 0;
        BSTR* pStrResult = NULL;
        m_Service.getWeatherbyCityName(bsCityCode,&pStrResult,&iRstNum);

        //TRACE��ԭʼ����
        for (int ii=0; ii<iRstNum; ii++)
        {
            TRACE("%s\n",CString(*(pStrResult+ii)));
        }

        if (iRstNum<=0 || pStrResult==NULL)
        {
            goto EXIT_LABEL;
        }

        

        // ����������ϢԪ��
        /*****************************
        0 = ʡ��
        1 = ��������
        2 = ���д���
        3 = ����ͼƬ���� (N/A)
        4 = ������ʱ��
        5 = ���������
        6 = �ſ�
        7 = ����ͷ���
        8 = �������ƿ�ʼͼƬ���� (N/A)
        9 = �������ƽ���ͼƬ���� (N/A)
        10 = ���ڵ�����ʵ��
        11 = ����ָ��
        
        ʾ�����£�
            ��0�У�ֱϽ��
            ��1�У�����
            ��2�У�54511
            ��3�У�54511.jpg
            ��4�У�2007-12-6 13:33:34
            ��5�У�6�� / -3��
            ��6�У�12��06�� ��
            ��7�У�����3-4��ת΢��
            ��8�У�0.gif
            ��9�У�0.gif
            ��10�У���������ʵ�����磻4.8�棻����/��������������4������������������������ǿ�ȣ��е�
            ��11�У�����ָ�������½ϵͣ������ź����׼�ë�µȴ����װ���������������Ŵ��¡������׼���ë����
                    ��ðָ������ҹ�²�ϴ󣬽��׷�����ð�����ʵ������·������ʽ�����������ע�������
                    ����ָ���������Դ󣬽ϲ��˳���������ֻ����������ע��ѡ��ܷ�ĵص㣬����ӭ�������
                    ��ָͨ�����������ʣ�·������ͨ�����������ã���������������ʻ���ǿ�����������۹�ĺ�������
                    ���� ����
            
            ��12�У�7�� / -3��
            ��13�У�12��07�� ��
            ��14�У�΢��
            ��15�У�0.gif
            ��16�У�0.gif
            ��17�У�7�� / -1��
            ��18�У�12��08�� ��
            ��19�У�΢��
            ��20�У�0.gif
            ��21�У�0.gif
            ��22�У�����λ�ڻ���ƽԭ������Ե��������λ�ڱ�γ39�ȣ�����116�ȣ����ܱ��ӱ�ʡΧ�ţ����Ϻ��������ӡ�ȫ�����һ����ǧ��ƽ�����Ͻ12��6�أ��˿�1100���򡣱���Ϊů�´���ʪ���½�Լ������򡭡�

        *******************************/
        try
        {
            IMsgCityWthInf ifCityWthInf;
            CString strWthItem;

            int iIndex = 0;

            // ʡ��
            ifCityWthInf.strProvince = CString(*(pStrResult+iIndex));
            //TRACE("----------------------------\n%s\n",CString(*(pStrResult+iIndex)));

            // ��������
            iIndex ++;
            ifCityWthInf.strCityName = CString(*(pStrResult+iIndex));
            //TRACE("%s\n",CString(*(pStrResult+iIndex)));

            // ���д���
            iIndex ++;
            ifCityWthInf.strCityCode = CString(*(pStrResult+iIndex));
            if (ifCityWthInf.strCityCode.IsEmpty())
            {
                goto EXIT_LABEL;
            }
            //TRACE("%s\n",CString(*(pStrResult+iIndex)));

            // ����ͼƬ���� (N/A)
            iIndex ++;

            // ������ʱ��
            iIndex ++;
            ifCityWthInf.publishTime.ParseDateTime( CString(*(pStrResult+iIndex)));
            //TRACE("%s\n",ifCityWthInf.publishTime.Format(_T("%Y-%m-%d %H:%M:%S")));

            // ���������
            iIndex ++;
            float num1,num2;
            num1 = (float)GetFloatFromStr(CString(*(pStrResult+iIndex)),0,_T("/"));;
            num2 = (float)GetFloatFromStr(CString(*(pStrResult+iIndex)),1,_T("/"));;
            ifCityWthInf.fTodMinTemper = min(num1,num2);
            ifCityWthInf.fTodMaxTemper = max(num1,num2);
            //TRACE("%.2f�� - %.2f��\n",ifCityWthInf.fTodMinTemper,ifCityWthInf.fTodMaxTemper);


            // ���������ſ�
            iIndex ++;
            ifCityWthInf.strTodWthDes = CString(*(pStrResult+iIndex));

            // ����ͷ���
            iIndex ++;
            strWthItem = CString(*(pStrResult+iIndex));
            ifCityWthInf.strTodWindDir = strWthItem;
            //TRACE("����%s\n",strWthItem);
            ifCityWthInf.iTodMinWindPow = (int)PickupDigit(strWthItem,0);
            ifCityWthInf.iTodMaxWindPow = (int)PickupDigit(strWthItem,1);
            //TRACE("������%d��%d��\n",ifCityWthInf.iTodMinWindPow,ifCityWthInf.iTodMaxWindPow);

            // �������ƿ�ʼͼƬ���� (N/A)
            iIndex ++;

            // �������ƽ���ͼƬ���� (N/A)
            iIndex ++;

            // ���ڵ�����ʵ��
            iIndex ++;
            ifCityWthInf.strCurWthDes = CString(*(pStrResult+iIndex));;

            // ����ָ��
            iIndex ++;
            ifCityWthInf.strLifeIndex = CString(*(pStrResult+iIndex));;


            /************************************************************************/
            /* 2.��������Ϣ���͵����ݴ洢ģ��                                      */
            /************************************************************************/
            NbsSendModuleMsg(&ifCityWthInf);

            
        }
        catch (...)
        {
        	
        }

EXIT_LABEL:

        delete pStrResult;

#ifndef _WEATHER_PAYMENT
        /************************************************************************/
        /* 3.����û�����ʹ�ø��ٷ��ʡ�����ʽ��ʱ                               */
        /************************************************************************/
        Sleep(1000);
#endif
    }   


    return TRUE;
}

UINT CWeatherClient::_ThreadEntry(LPVOID pParam)
{
    CoInitialize(NULL);
    CWeatherClient* pObject = (CWeatherClient*)pParam;

    // 
    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("���ڻ�ȡȫ����Ҫ���е�������롭��"));
    NbsSendModuleMsg(&aLog);

    // ���֧�ֵĳ��д���
    int iRstNum = 0;
    BSTR* pStrResult = NULL;
    pObject->m_Service.getSupportCity(NULL,&pStrResult,&iRstNum);

    if (iRstNum==0)
    {
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
        aLog.strComments.Format(_T("��ȡ�����������ʧ�ܣ�"));
        NbsSendModuleMsg(&aLog);
    }
    else
    {
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.strComments.Format(_T("�����%d�����е��������"),iRstNum);
        NbsSendModuleMsg(&aLog);
        
        // 
        pObject->m_strlistCityCode.RemoveAll();
        for (int i=0; i<iRstNum; i++)
        {
            TRACE("%03d��%s \t | ",i,CString(*(pStrResult+i)));
            try
            {
                CString strCityCode = GetSFStr((LPCTSTR)(CString(*(pStrResult+i))),1,_T("(")).c_str();
                strCityCode.TrimRight(_T(")"));
                pObject->m_strlistCityCode.AddTail(strCityCode);
                TRACE(" %s\n",strCityCode);
            }
            catch (...)
            {
                TRACE("�������д������ԭ�ַ���Ϊ%s\n",CString(*(pStrResult+i)));
            }
        }
    }

    delete pStrResult;

    

    // ���ݻ�õĳ��д�������������Ϣ
    while (TRUE)
    {

        BOOL rc = pObject->GetInformation();
       
        // Wait ����
        if (WaitForSingleObject(pObject->m_hExitEvent,INTERVALTIME)==WAIT_OBJECT_0)
        {
            break;
        }

    }

    // 
    pObject->m_pThread = NULL;
    return 0L;
}





