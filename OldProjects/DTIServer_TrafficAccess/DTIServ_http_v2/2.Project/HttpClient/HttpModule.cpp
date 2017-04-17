#include "StdAfx.h"
#include ".\HttpModule.h"
#include <AppLogMgr.h>
#include <XMLFile.h>
//////////////////////////////////////////////////////////////////////////

//#define         __CREATE_MIF_DATA       // 生成Mif文件

using namespace MSXML;
//////////////////////////////////////////////////////////////////////////

#define         OFFSET_LONG         540
#define         OFFSET_LATI         106

//////////////////////////////////////////////////////////////////////////
// 间隔时间
#ifdef _DEBUG
    #define             INTERVALTIME        20  
#else
    #define             INTERVALTIME        10
#endif
//////////////////////////////////////////////////////////////////////////
// HTTP地址
#define                 HTTPSERVERADDR          _T("59.108.229.242")
#define                 HTTPSERVERPORT          8888
#define                 HTTPABSOLUTEURL         _T("http://59.108.229.242:8888/realroad/rrservlet")
#define                 HTTPRELATIVEURL         _T("/realroad/rrservlet")

//////////////////////////////////////////////////////////////////////////
// 临时XML文件名
#define             TEMPXMLFILENAME     _T("RawTfcInf.xml")


//////////////////////////////////////////////////////////////////////////

// POST消息头
#define         POSTHEADER      _T("Content-Type: application/soap+xml")

// POST消息实体
#define         POSTCONTENT     _T("<?xml version=\"1.0\" encoding=\"GB2312\"?> \
                                        <rr_req> <version>1.0</version><!--版本号--> \
                                            <username>123</username><!--用户名，由四通分配--> \
                                            <password>123</password><!--密码--> \
                                        </rr_req>")


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CHttpModule::CHttpModule(CImcDispatcher& aDispatcher):
        CNBaseModule(aDispatcher,ID_MODULE_HTTP)
{
    m_pThread = NULL;
    m_pIntSession = NULL;
    m_pConnection = NULL;
    m_hExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
}

CHttpModule::~CHttpModule(void)
{
}

//////////////////////////////////////////////////////////////////////////
// From CNBaseModule

BOOL CHttpModule::OnInitModule()
{
    m_pIntSession = new CInternetSession( NULL,    0,
        INTERNET_OPEN_TYPE_PRECONFIG,     NULL,    NULL,
        INTERNET_FLAG_DONT_CACHE);     //设置不缓冲

    return TRUE;
}

BOOL CHttpModule::OnStart()
{
	IMsgAppLogs aLog;
	aLog.strComments.Format(_T("创建交通接入通道……"));
	NbsSendModuleMsg(&aLog);

	// 
    m_pConnection =  m_pIntSession->GetHttpConnection(HTTPSERVERADDR,HTTPSERVERPORT,_T(""),_T(""));


    //
    m_pThread = AfxBeginThread(_ThreadEntry,this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);
    TRACE("Http Thread Address = 0X%08X\n",m_pThread);
    ASSERT(m_pThread!=NULL);
    if (m_pThread==NULL)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL CHttpModule::OnActive()
{
    if (m_pThread!=NULL)
    {
        IMsgAppLogs aLog;
        aLog.strComments.Format(_T("启动交通接入通道……"));
        NbsSendModuleMsg(&aLog);
        m_pThread->ResumeThread();
    }

    //
    return CNBaseModule::OnActive();
}

// On receive message from other modules.
void CHttpModule::OnRecvIMCMessage(PTImcMsg aImcMsg)
{

    //
    CNBaseModule::OnRecvIMCMessage(aImcMsg);
}

// On receive message from internal objects.
BOOL CHttpModule::OnRecvInterMessage(PTImcMsg aImcMsg)
{
    return CNBaseModule::OnRecvInterMessage(aImcMsg);
}

void CHttpModule::OnClose()
{
	IMsgAppLogs aLog;
	aLog.strComments.Format(_T("正在关闭交通接入连接……"));
	NbsSendModuleMsg(&aLog);

	// 
    if (m_pThread)
    {
		HANDLE hHandle = m_pThread->m_hThread;

        SetEvent(m_hExitEvent);

        WaitForSingleObject(hHandle,2000);
        
        m_pThread = NULL;
    }

    delete m_pConnection;
    m_pConnection = NULL;

    if (m_pIntSession!=NULL)
    {
        m_pIntSession->Close();
        delete m_pIntSession;
        m_pIntSession = NULL;
    }

	// 
	aLog.logTime = COleDateTime::GetCurrentTime();
	aLog.strComments.Format(_T("交通接入通道已关闭！"));
	NbsSendModuleMsg(&aLog);

    //
    CNBaseModule::OnClose();
}

//////////////////////////////////////////////////////////////////////////
// public function


//////////////////////////////////////////////////////////////////////////
// Private function

BOOL CHttpModule::RequestData(CString& strTfcData)
{
    if (m_pConnection==NULL)
    {
        return FALSE;
    }

	CHttpFile* pHttpFile = NULL;
	try
	{

        // Get CHttpFile
        pHttpFile =  m_pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,HTTPRELATIVEURL);

        // Send Request

        IMsgAppLogs aLog;
        aLog.EnableStorage(FALSE);
        aLog.strComments.Format(_T("发送交通信息请求……"));
        NbsSendModuleMsg(&aLog);

        CString strPostContent(POSTCONTENT);		
		BOOL result = pHttpFile->SendRequest( CString(POSTHEADER), 
            (LPVOID)(LPCTSTR)strPostContent, strPostContent.GetLength());

        // Read string from Server.
		CString strResponse;
		while(pHttpFile->ReadString(strResponse))    // 读取提交数据后的返回结果
		{
			strTfcData += strResponse;
		}
		if (pHttpFile!=NULL)
		{
			pHttpFile->Close();
			delete pHttpFile;
		}
	}
	catch (CInternetException* e)
	{
		TCHAR tcErrMsg[500];
		e->GetErrorMessage(tcErrMsg,sizeof(tcErrMsg));
		TRACE(tcErrMsg);
		TRACE("\n");


		e->Delete();

		if (pHttpFile!=NULL)
		{
			pHttpFile->Close();
			delete pHttpFile;
		}

        // 
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
        aLog.strComments.Format(_T("获取交通信息失败（%s）！"),tcErrMsg);
        NbsSendModuleMsg(&aLog);

		return FALSE;
	}    

    // 写入临时文件
    CFile xmlTmpFile;
    if (!xmlTmpFile.Open(GetExePath()+TEMPXMLFILENAME,CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyNone))
    {
        // 
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("写入交通信息到临时文件%s失败！"),GetExePath()+TEMPXMLFILENAME);
        NbsSendModuleMsg(&aLog);

        return FALSE;
    }
    
    UINT fileSize = strTfcData.GetLength();
    xmlTmpFile.Write(strTfcData.GetBuffer(0),fileSize);
    xmlTmpFile.Close();


    return TRUE;
}

BOOL CHttpModule::ParseData()
{
    // 打开临时XML文件
	CXMLFile m_xmlFile;
    if (!m_xmlFile.load( GetExePath()+TEMPXMLFILENAME, "rr_resp" ))
    {
        return FALSE;            
    }
	
    BOOL bFlag;
    
    // 
    MSXML2::IXMLDOMNodePtr layerNode=NULL;
    m_xmlFile.GetNode("body",layerNode);
    int iCount = m_xmlFile.GetChildNodeNum(layerNode);
    MSXML2::IXMLDOMNodeListPtr layersList = layerNode->GetchildNodes();
    long iLength=layersList->Getlength();


    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("获取%d条路况信息"),iLength);
    NbsSendModuleMsg(&aLog);


    // 构造消息
    IMsgRawTrafInf rawTfcInfMsg;

    for(long i=0;i<iLength;i++)
    {

        if (WaitForSingleObject(m_hExitEvent,0)==WAIT_OBJECT_0)
        {
            break;
        }
        
        layerNode=layersList->Getitem(i);

        //处理layerNode结点的属性
        /*CString strName="",strPath="",strType="",strSize="",strSymbol="",strRenderField="";
        MSXML2::IXMLDOMNamedNodeMapPtr attributeList=layerNode->Getattributes();
        MSXML2::IXMLDOMNodePtr Node=attributeList->getNamedItem("name");
        if(Node) strName=Node->GetnodeValue().bstrVal;
        Node=attributeList->getNamedItem("path");
        if(Node) strPath=Node->GetnodeValue().bstrVal;*/
        bFlag = m_xmlFile.MyLoad(layerNode->Getxml());
        if (!bFlag)
        {
            return FALSE;
        }

        CString strValue;
        // 道路ID
        m_xmlFile.GetNodeValue(layerNode,"road_info/road_id",rawTfcInfMsg.m_tfcRawRoadInf.strRoadID);

        // 起始点名称
        m_xmlFile.GetNodeValue(layerNode,"road_info/start_pt",rawTfcInfMsg.m_tfcRawRoadInf.strStartName);


        // 终止点名称
        m_xmlFile.GetNodeValue(layerNode,"road_info/end_pt",rawTfcInfMsg.m_tfcRawRoadInf.strEndName);


        // 速度
        m_xmlFile.GetNodeValue(layerNode,"road_info/velocity",strValue);
        rawTfcInfMsg.m_tfcRawRoadInf.fSpeed = (float)atof(strValue.GetBuffer(0));

        
        // 起点经纬度
        m_xmlFile.GetNodeValue(layerNode,"road_info/start_point_x",strValue);
        rawTfcInfMsg.m_tfcRawRoadInf.ptStartPos.iX = LONG(atof(strValue.GetBuffer(0))*3600*24);

        m_xmlFile.GetNodeValue(layerNode,"road_info/start_point_y",strValue);
        rawTfcInfMsg.m_tfcRawRoadInf.ptStartPos.iY = LONG(atof(strValue.GetBuffer(0))*3600*24);


        // 瑞图数据中对应的起点坐标
        rawTfcInfMsg.m_tfcRawRoadInf.ptCorStaPos.iX = rawTfcInfMsg.m_tfcRawRoadInf.ptStartPos.iX+OFFSET_LONG;
        rawTfcInfMsg.m_tfcRawRoadInf.ptCorStaPos.iY = rawTfcInfMsg.m_tfcRawRoadInf.ptStartPos.iY+OFFSET_LATI;


        // 终点经纬度
        m_xmlFile.GetNodeValue(layerNode,"road_info/end_point_x",strValue);
        rawTfcInfMsg.m_tfcRawRoadInf.ptEndPos.iX = LONG(atof(strValue.GetBuffer(0))*3600*24);

        m_xmlFile.GetNodeValue(layerNode,"road_info/end_point_y",strValue);
        rawTfcInfMsg.m_tfcRawRoadInf.ptEndPos.iY = LONG(atof(strValue.GetBuffer(0))*3600*24);



        // 瑞图数据中对应的终点坐标
        rawTfcInfMsg.m_tfcRawRoadInf.ptCorEndPos.iX = rawTfcInfMsg.m_tfcRawRoadInf.ptEndPos.iX+OFFSET_LONG;
        rawTfcInfMsg.m_tfcRawRoadInf.ptCorEndPos.iY = rawTfcInfMsg.m_tfcRawRoadInf.ptEndPos.iY+OFFSET_LATI;



        // 发布时间
        m_xmlFile.GetNodeValue(layerNode,"road_info/publish_time",strValue);
        int iDotPos = strValue.Find(_T("."));
        strValue.Truncate(iDotPos);
        rawTfcInfMsg.m_tfcRawRoadInf.timePublish.ParseDateTime(strValue);


        // 道路名称

        // 交通事件
        


        // 发送消息
        NbsSendModuleMsg(&rawTfcInfMsg);

    }

    return TRUE;
}
void CHttpModule::CheckTfcInf()
{
    CString strTfcData;

    // 从Http请求数据
    if (RequestData(strTfcData))
    {

        //
#ifdef __CREATE_MIF_DATA
#pragma message("\n__CREATE_MIF_DATA defined!\n")
        CreateMifData();
#else
#pragma message("\n__CREATE_MIF_DATA NOT DEFINED!\n")

#endif

        // 解析数据
        ParseData();
    }    
}

UINT CHttpModule::_ThreadEntry(LPVOID pParam)
{
    CoInitialize(NULL);

    CHttpModule* pObject = (CHttpModule*)pParam;

    while (TRUE)
    {
        // 
        pObject->CheckTfcInf();

        // 刷新交通信息显示界面
        TImcMsg msg(EMSG_FLASH_TFCRAW,ID_MODULE_HTTP,ID_MODULE_DATABASE);
        NbsSendModuleMsg(&msg);

        // 间隔INTERVALTIME时间检查一次交通信息
        DWORD dwRc = WaitForSingleObject(pObject->m_hExitEvent,INTERVALTIME*1000);
        if ( dwRc==WAIT_OBJECT_0 )
        {
            break;
        }

    }

    ::CoUninitialize();
    pObject->m_pThread = NULL;
    return 0L;
}


BOOL CHttpModule::CreateMifData()
{
    // 打开临时XML文件
    CXMLFile m_xmlFile;
    if (!m_xmlFile.load( GetExePath()+TEMPXMLFILENAME, "rr_resp" ))
    {
        return FALSE;            
    }

    CString strLine;


    // 创建MIF文件
    CStdioFile mifFile;
    if (!mifFile.Open(GetExePath()+"TfcRoad.mif",CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyNone))
    {
        return FALSE;
    }

    strLine = "Version 450 \n";
    strLine += "Charset \"WindowsSimpChinese\" \n";
    strLine += "Delimiter \",\" \n";
    strLine += "CoordSys Earth Projection 1, 104 Bounds (73, 18) (136, 54) \n";
    strLine += "Columns 3 \n";
    strLine += "  RoadID Char(30) \n";
    strLine += "  StartName Char(50) \n";
    strLine += "  EndName   Char(50) \n";
    strLine += "Data \n\n";

    mifFile.WriteString(strLine);

    

    // 创建MID文件
    CStdioFile midFile;
    if (!midFile.Open(GetExePath()+"TfcRoad.mid",CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyNone))
    {
        return FALSE;
    }

     
    //

    BOOL bFlag;

    // 
    MSXML2::IXMLDOMNodePtr layerNode=NULL;
    m_xmlFile.GetNode("body",layerNode);
    int iCount = m_xmlFile.GetChildNodeNum(layerNode);
    MSXML2::IXMLDOMNodeListPtr layersList = layerNode->GetchildNodes();
    long iLength=layersList->Getlength();



    // 构造消息
    TRawRoadTfcInf tfcRawRoadInf;

    for(long i=0;i<iLength;i++)
    {
        layerNode=layersList->Getitem(i);

        bFlag = m_xmlFile.MyLoad(layerNode->Getxml());
        if (!bFlag)
        {
            return FALSE;
        }

        CString strValue;

        // 道路ID
        m_xmlFile.GetNodeValue(layerNode,"road_info/road_id",tfcRawRoadInf.strRoadID);
        

        // 起始点名称
        m_xmlFile.GetNodeValue(layerNode,"road_info/start_pt",tfcRawRoadInf.strStartName);

        // 终止点名称
        m_xmlFile.GetNodeValue(layerNode,"road_info/end_pt",tfcRawRoadInf.strEndName);

        strLine.Format("%s,%s,%s \n",
            tfcRawRoadInf.strRoadID,tfcRawRoadInf.strStartName,tfcRawRoadInf.strEndName);
        midFile.WriteString(strLine);


        // 速度
        /*m_xmlFile.GetNodeValue(layerNode,"road_info/velocity",strValue);
        tfcRawRoadInf.fSpeed = (float)atof(strValue.GetBuffer(0));*/


        // 起点经纬度
        m_xmlFile.GetNodeValue(layerNode,"road_info/start_point_x",strValue);
        tfcRawRoadInf.ptStartPos.iX = LONG(atof(strValue.GetBuffer(0))*3600*24);
        m_xmlFile.GetNodeValue(layerNode,"road_info/start_point_y",strValue);
        tfcRawRoadInf.ptStartPos.iY = LONG(atof(strValue.GetBuffer(0))*3600*24);
        // 瑞图数据中对应的起点坐标
        tfcRawRoadInf.ptCorStaPos.iX = tfcRawRoadInf.ptStartPos.iX+OFFSET_LONG;
        tfcRawRoadInf.ptCorStaPos.iY = tfcRawRoadInf.ptStartPos.iY+OFFSET_LATI;


        // 终点经纬度
        m_xmlFile.GetNodeValue(layerNode,"road_info/end_point_x",strValue);
        tfcRawRoadInf.ptEndPos.iX = LONG(atof(strValue.GetBuffer(0))*3600*24);
        m_xmlFile.GetNodeValue(layerNode,"road_info/end_point_y",strValue);
        tfcRawRoadInf.ptEndPos.iY = LONG(atof(strValue.GetBuffer(0))*3600*24);
        // 瑞图数据中对应的终点坐标
        tfcRawRoadInf.ptCorEndPos.iX = tfcRawRoadInf.ptEndPos.iX+OFFSET_LONG;
        tfcRawRoadInf.ptCorEndPos.iY = tfcRawRoadInf.ptEndPos.iY+OFFSET_LATI;

        

        strLine.Format("Pline 2 \n %f %f \n %f %f \n Pen (1,2,0) \n\n",
            tfcRawRoadInf.ptCorStaPos.iX/3600.0/24.0,tfcRawRoadInf.ptCorStaPos.iY/3600.0/24.0,
            tfcRawRoadInf.ptCorEndPos.iX/3600.0/24.0,tfcRawRoadInf.ptCorEndPos.iY/3600.0/24.0);
        

        mifFile.WriteString(strLine);

        // 发布时间
       /* m_xmlFile.GetNodeValue(layerNode,"road_info/publish_time",strValue);
        int iDotPos = strValue.Find(_T("."));
        strValue.Truncate(iDotPos);
        tfcRawRoadInf.timePublish.ParseDateTime(strValue);*/


    }

    mifFile.Close();
    midFile.Close();


    return TRUE;
}