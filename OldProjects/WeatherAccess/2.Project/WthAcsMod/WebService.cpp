
#include "stdafx.h"
#include "CommonFunc.h"
#include "WebService.h"

//#define _WEATHER_PAYMENT  // 付费定义

//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
    #define             INTERVALTIME        (60*1000)  // 60秒
#else
    #define             INTERVALTIME        (60*3600*1000) // 60分
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
    // 启动接收线程
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
    aLog.strComments.Format(_T("正在关闭气象接入通信……"));
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

        // 退出信号是否激活？
        if (WaitForSingleObject(m_hExitEvent,0)==WAIT_OBJECT_0)
        {
            return FALSE;
        }

        /************************************************************************/
        /* 1.依次获得各城市的气象信息                                           */
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

        //TRACE出原始数据
        for (int ii=0; ii<iRstNum; ii++)
        {
            TRACE("%s\n",CString(*(pStrResult+ii)));
        }

        if (iRstNum<=0 || pStrResult==NULL)
        {
            goto EXIT_LABEL;
        }

        

        // 解析气象信息元素
        /*****************************
        0 = 省份
        1 = 城市名称
        2 = 城市代码
        3 = 城市图片名称 (N/A)
        4 = 最后更新时间
        5 = 当天的气温
        6 = 概况
        7 = 风向和风力
        8 = 天气趋势开始图片名称 (N/A)
        9 = 天气趋势结束图片名称 (N/A)
        10 = 现在的天气实况
        11 = 生活指数
        
        示例如下：
            第0列：直辖市
            第1列：北京
            第2列：54511
            第3列：54511.jpg
            第4列：2007-12-6 13:33:34
            第5列：6℃ / -3℃
            第6列：12月06日 晴
            第7列：北风3-4级转微风
            第8列：0.gif
            第9列：0.gif
            第10列：今日天气实况：晴；4.8℃；风向/风力：北西北风4级；空气质量：良；紫外线强度：中等
            第11列：穿衣指数：气温较低，建议着厚外套加毛衣等春秋服装。年老体弱者宜着大衣、呢外套加羊毛衫。
                    感冒指数：昼夜温差较大，较易发生感冒，请适当增减衣服。体质较弱的朋友请注意防护。
                    晨练指数：风力稍大，较不宜晨练，若坚持户外锻炼，请注意选择避风的地点，避免迎风锻炼。
                    交通指数：天气晴朗，路面干燥，交通气象条件良好，车辆可以正常行驶，是开车出门游玩观光的好天气。
                    …… ……
            
            第12列：7℃ / -3℃
            第13列：12月07日 晴
            第14列：微风
            第15列：0.gif
            第16列：0.gif
            第17列：7℃ / -1℃
            第18列：12月08日 晴
            第19列：微风
            第20列：0.gif
            第21列：0.gif
            第22列：北京位于华北平原西北边缘，市中心位于北纬39度，东经116度，四周被河北省围着，东南和天津市相接。全市面积一万六千多平方公里，辖12区6县，人口1100余万。北京为暖温带半湿润大陆性季风气候……

        *******************************/
        try
        {
            IMsgCityWthInf ifCityWthInf;
            CString strWthItem;

            int iIndex = 0;

            // 省份
            ifCityWthInf.strProvince = CString(*(pStrResult+iIndex));
            //TRACE("----------------------------\n%s\n",CString(*(pStrResult+iIndex)));

            // 城市名称
            iIndex ++;
            ifCityWthInf.strCityName = CString(*(pStrResult+iIndex));
            //TRACE("%s\n",CString(*(pStrResult+iIndex)));

            // 城市代码
            iIndex ++;
            ifCityWthInf.strCityCode = CString(*(pStrResult+iIndex));
            if (ifCityWthInf.strCityCode.IsEmpty())
            {
                goto EXIT_LABEL;
            }
            //TRACE("%s\n",CString(*(pStrResult+iIndex)));

            // 城市图片名称 (N/A)
            iIndex ++;

            // 最后更新时间
            iIndex ++;
            ifCityWthInf.publishTime.ParseDateTime( CString(*(pStrResult+iIndex)));
            //TRACE("%s\n",ifCityWthInf.publishTime.Format(_T("%Y-%m-%d %H:%M:%S")));

            // 当天的气温
            iIndex ++;
            float num1,num2;
            num1 = (float)GetFloatFromStr(CString(*(pStrResult+iIndex)),0,_T("/"));;
            num2 = (float)GetFloatFromStr(CString(*(pStrResult+iIndex)),1,_T("/"));;
            ifCityWthInf.fTodMinTemper = min(num1,num2);
            ifCityWthInf.fTodMaxTemper = max(num1,num2);
            //TRACE("%.2f度 - %.2f度\n",ifCityWthInf.fTodMinTemper,ifCityWthInf.fTodMaxTemper);


            // 当天天气概况
            iIndex ++;
            ifCityWthInf.strTodWthDes = CString(*(pStrResult+iIndex));

            // 风向和风力
            iIndex ++;
            strWthItem = CString(*(pStrResult+iIndex));
            ifCityWthInf.strTodWindDir = strWthItem;
            //TRACE("风向：%s\n",strWthItem);
            ifCityWthInf.iTodMinWindPow = (int)PickupDigit(strWthItem,0);
            ifCityWthInf.iTodMaxWindPow = (int)PickupDigit(strWthItem,1);
            //TRACE("风力：%d至%d级\n",ifCityWthInf.iTodMinWindPow,ifCityWthInf.iTodMaxWindPow);

            // 天气趋势开始图片名称 (N/A)
            iIndex ++;

            // 天气趋势结束图片名称 (N/A)
            iIndex ++;

            // 现在的天气实况
            iIndex ++;
            ifCityWthInf.strCurWthDes = CString(*(pStrResult+iIndex));;

            // 生活指数
            iIndex ++;
            ifCityWthInf.strLifeIndex = CString(*(pStrResult+iIndex));;


            /************************************************************************/
            /* 2.将气象信息发送到数据存储模块                                      */
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
        /* 3.免费用户不能使用高速访问。故显式延时                               */
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
    aLog.strComments.Format(_T("正在获取全国主要城市的气象代码……"));
    NbsSendModuleMsg(&aLog);

    // 获得支持的城市代码
    int iRstNum = 0;
    BSTR* pStrResult = NULL;
    pObject->m_Service.getSupportCity(NULL,&pStrResult,&iRstNum);

    if (iRstNum==0)
    {
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
        aLog.strComments.Format(_T("获取城市气象代码失败！"));
        NbsSendModuleMsg(&aLog);
    }
    else
    {
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.strComments.Format(_T("共获得%d个城市的气象代码"),iRstNum);
        NbsSendModuleMsg(&aLog);
        
        // 
        pObject->m_strlistCityCode.RemoveAll();
        for (int i=0; i<iRstNum; i++)
        {
            TRACE("%03d：%s \t | ",i,CString(*(pStrResult+i)));
            try
            {
                CString strCityCode = GetSFStr((LPCTSTR)(CString(*(pStrResult+i))),1,_T("(")).c_str();
                strCityCode.TrimRight(_T(")"));
                pObject->m_strlistCityCode.AddTail(strCityCode);
                TRACE(" %s\n",strCityCode);
            }
            catch (...)
            {
                TRACE("解析城市代码出错！原字符串为%s\n",CString(*(pStrResult+i)));
            }
        }
    }

    delete pStrResult;

    

    // 根据获得的城市代码请求气象信息
    while (TRUE)
    {

        BOOL rc = pObject->GetInformation();
       
        // Wait ……
        if (WaitForSingleObject(pObject->m_hExitEvent,INTERVALTIME)==WAIT_OBJECT_0)
        {
            break;
        }

    }

    // 
    pObject->m_pThread = NULL;
    return 0L;
}





