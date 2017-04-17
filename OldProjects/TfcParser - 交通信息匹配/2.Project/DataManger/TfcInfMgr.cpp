#include "StdAfx.h"
#include ".\tfcinfmgr.h"
#include <CommonFunc.h>
#include "InterfaceEx.h"
#include "GlobalMacro.h"
#include <XMLFile.h>


//#define _TRACE_GRID_INFO_TFCROAD

//////////////////////////////////////////////////////////////////////////
#define             TEMPXMLFILENAME     _T("RawTfcInf.xml")

#define         OFFSET_LONG         540
#define         OFFSET_LATI         106

#define         EXTENT_SELECTION        3

//////////////////////////////////////////////////////////////////////////
// 
CTfcInfMgr::CTfcInfMgr(void)
{
    m_rectMap.SetNull();
}

CTfcInfMgr::~CTfcInfMgr(void)
{
    Close();
}

//////////////////////////////////////////////////////////////////////////
// From CMapEngine

BOOL CTfcInfMgr::OnInitialize(TEgAttri& aAttri,TMRect& mapRect,CSize& sizeGrid)
{
	// 修改比例尺
    aAttri.dwMaxScale = 1500;
    aAttri.dwMinScale = 740000;
	aAttri.dwZoomScale = 125000;
    aAttri.fUnitZoom = 2;
    aAttri.fPhysicPerLogic = 1000;  

    // 修改网格属性
    mapRect = m_rectMap;
    sizeGrid.cx = 1000;
    sizeGrid.cy = 1000;

    return TRUE;
}


void CTfcInfMgr::OnBuildingGrid()
{
    TMRect rectMap = GetGridMgr()->GetMapRect();
    CSize sizeGrid = GetGridMgr()->GetGridSize();

    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("Road引擎正在构建网格(地图范围(<%d,%d>,<%d,%d>)，每网格大小%d*%d，网格数(%d×%d))……"),
        rectMap.iTl.iX, rectMap.iTl.iY, rectMap.iBr.iX, rectMap.iBr.iY,
        sizeGrid.cx, sizeGrid.cy,   GetGridMgr()->GetNumOfRow(), GetGridMgr()->GetNumOfCol());

    NbsSendModuleMsg(&aLog);
}

void CTfcInfMgr::OnBuildGrid(PTNBMapGrid pGrid)
{
    // 构建网格中包括的自定义数据
    CTfcRoadList* pLinkList = new CTfcRoadList;
    SET_ROADLIST(pGrid,pLinkList);

#ifdef _TRACE_GRID_INFO_TFCROAD

    TRACE("网格%03d，行号%02d，列号%02d，范围<(%d,%d),(%d,%d)>\n",
        pGrid->m_wGridID,pGrid->m_wRowID,pGrid->m_wColID,
        pGrid->m_rectExtent.iTl.iX,pGrid->m_rectExtent.iTl.iY,
        pGrid->m_rectExtent.iBr.iX,pGrid->m_rectExtent.iBr.iY);

#endif
}

void CTfcInfMgr::OnGridsBuilt()
{
    // 将Road数据与网格进行关联  

    IMsgAppLogs aLog;
    aLog.UpdateToCurrentTime();
    aLog.strComments.Format(_T("正在将Road关联到网格中……"));
    NbsSendModuleMsg(&aLog);

    // 将Link与网格关联
    POSITION pos = m_tfcRoadList.GetHeadPosition();
    while (pos)
    {
        PTRawRoadTfcInf pRoad = m_tfcRoadList.GetNext(pos);

        CGridList gridList;
		if (pRoad->strStartName==_T("广安门桥") || pRoad->strEndName==_T("广安门桥"))
		{
			int a =4;
			int b;
			b = a;
		}
		GetGridMgr()->GetGridByRect(pRoad->rectExtent,gridList);

        // 
        POSITION posGrid = gridList.GetHeadPosition();
        while (posGrid)
        {
            PTNBMapGrid pGrid = gridList.GetNext(posGrid);
            CTfcRoadList* pRoadList = RETRIEVE_ROADLIST(pGrid);
            pRoadList->AddTail(pRoad);
        }
    }
}

void CTfcInfMgr::OnDestroyGrid(PTNBMapGrid pGrid)
{
    // 删除网格中包括的自定义数据
    CTfcRoadList* pList = RETRIEVE_ROADLIST(pGrid);
    pList->RemoveAll();
    delete pList;
}

//////////////////////////////////////////////////////////////////////////
//

BOOL CTfcInfMgr::Open()
{
    if (!m_roadIDMgr.ReadMapFile())
    {
        return FALSE;
    }
    
    // 读取有交通流监测的道路数据
    IMsgAppLogs aLog1;
    aLog1.strComments.Format(_T("正在读取道路（交通流）数据……"));
    NbsSendModuleMsg(&aLog1);

    // 打开临时XML文件
    CXMLFile m_xmlFile;
    CString strFileName = GetExePath()+PATH_DATA_FILE+TEMPXMLFILENAME;
    if (!m_xmlFile.load( strFileName, "rr_resp" ))
    {
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("找不到文件%s"),strFileName);
        NbsSendModuleMsg(&aLog);

        return FALSE;            
    }

    BOOL bFlag;

    // 
    MSXML2::IXMLDOMNodePtr layerNode=NULL;

    m_xmlFile.GetNode("body",layerNode);
    if (layerNode==NULL)
    {
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("文件%s的格式有误，无法进行解析！"),strFileName);
        NbsSendModuleMsg(&aLog);

        return FALSE;
    }
    int iCount = m_xmlFile.GetChildNodeNum(layerNode);
    MSXML2::IXMLDOMNodeListPtr layersList = layerNode->GetchildNodes();
    long iLength=layersList->Getlength();


    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("共有%d条交通流道路"),iLength);
    NbsSendModuleMsg(&aLog);


    // 解析数据

    CString strValue;

    for(long i=0;i<iLength;i++)
    {

        layerNode=layersList->Getitem(i);

        bFlag = m_xmlFile.MyLoad(layerNode->Getxml());
        if (!bFlag)
        {
            return FALSE;
        }

        PTRawRoadTfcInf pTfcRoad = new TRawRoadTfcInf;


        // 道路ID
        m_xmlFile.GetNodeValue(layerNode,"road_info/road_id",pTfcRoad->strRoadID);
        PTRoadIDMap pRoadIDMap = NULL;
        m_roadIDMgr.Lookup(pTfcRoad->strRoadID,pRoadIDMap);
        ASSERT(pRoadIDMap!=NULL);
        if (pRoadIDMap!=NULL)
        {
            pTfcRoad->dwRoadID = pRoadIDMap->dwRoadID;
        }

        // 起始点名称
        m_xmlFile.GetNodeValue(layerNode,"road_info/start_pt",pTfcRoad->strStartName);


        // 终止点名称
        m_xmlFile.GetNodeValue(layerNode,"road_info/end_pt",pTfcRoad->strEndName);


        // 速度
        m_xmlFile.GetNodeValue(layerNode,"road_info/velocity",strValue);
        pTfcRoad->fSpeed = (float)atof(strValue.GetBuffer(0));


        // 起点经纬度
        m_xmlFile.GetNodeValue(layerNode,"road_info/start_point_x",strValue);
        pTfcRoad->ptStartPos.iX = LONG(atof(strValue.GetBuffer(0))*3600*24);

        m_xmlFile.GetNodeValue(layerNode,"road_info/start_point_y",strValue);
        pTfcRoad->ptStartPos.iY = LONG(atof(strValue.GetBuffer(0))*3600*24);


        // 瑞图数据中对应的起点坐标
        pTfcRoad->ptCorStaPos.iX = pTfcRoad->ptStartPos.iX+OFFSET_LONG;
        pTfcRoad->ptCorStaPos.iY = pTfcRoad->ptStartPos.iY+OFFSET_LATI;


        // 终点经纬度
        m_xmlFile.GetNodeValue(layerNode,"road_info/end_point_x",strValue);
        pTfcRoad->ptEndPos.iX = LONG(atof(strValue.GetBuffer(0))*3600*24);

        m_xmlFile.GetNodeValue(layerNode,"road_info/end_point_y",strValue);
        pTfcRoad->ptEndPos.iY = LONG(atof(strValue.GetBuffer(0))*3600*24);


        // 瑞图数据中对应的终点坐标
        pTfcRoad->ptCorEndPos.iX = pTfcRoad->ptEndPos.iX+OFFSET_LONG;
        pTfcRoad->ptCorEndPos.iY = pTfcRoad->ptEndPos.iY+OFFSET_LATI;


        // 发布时间
        m_xmlFile.GetNodeValue(layerNode,"road_info/publish_time",strValue);
        int iDotPos = strValue.Find(_T("."));
        strValue.Truncate(iDotPos);
        pTfcRoad->timePublish.ParseDateTime(strValue);


        // 道路名称

        m_tfcRoadList.AddTail(pTfcRoad);

        // 
        pTfcRoad->rectExtent = TMRect(pTfcRoad->ptCorStaPos,pTfcRoad->ptEndPos);
        m_rectMap += pTfcRoad->rectExtent;
    }

    //---------------------------------------------------------------------------------
    m_roadIDMgr.Clear();

    return TRUE;
}

BOOL CTfcInfMgr::GetRoadByPoint(TMPoint point,CTfcRoadList& aRoadList)
{
    PTNBMapGrid pGrid = GetGridMgr()->GetGridByPoint(point);

    if (pGrid==NULL)
    {
        return FALSE;
    }

    CTfcRoadList* pList = RETRIEVE_ROADLIST(pGrid);

    POSITION pos = pList->GetHeadPosition();
    while (pos)
    {
        PTRawRoadTfcInf pRoad = pList->GetNext(pos);
        TSegmentVector vRoad(pRoad->ptCorStaPos,pRoad->ptCorEndPos);

        DOUBLE fDis = vRoad.Distance(point);
        fDis = LlToDl(fDis);
        TRACE("像素距离(%s,%s) = %f\n",pRoad->strStartName, pRoad->strEndName,fDis);
        if (fDis<=EXTENT_SELECTION)
        {
            TRACE("\n>> 选中道路(%s,%s)\n",pRoad->strStartName, pRoad->strEndName);
            aRoadList.AddTail(pRoad);
        }
    }

    return TRUE;
}

void CTfcInfMgr::DrawTfcStream(CDC* pDC,BOOL bDrawName)
{
    CPen newPen;
    CBrush brush;
    CFont  font;
    CPen* pOldPen = NULL;
    CBrush* pOldBrush = NULL;
    CFont* pOldFont = NULL;


    POSITION pos;
    PTRawRoadTfcInf pRoad = NULL;

    // 画所有的路
    newPen.CreatePen(PS_SOLID,3,CLR_DARKGRAY);
    pOldPen = pDC->SelectObject(&newPen);

    pos = m_tfcRoadList.GetHeadPosition();
    while (pos)
    {
        pRoad = m_tfcRoadList.GetNext(pos);
        pRoad->DrawRoad(pDC,*this);
    }
    pDC->SelectObject(pOldPen);
    newPen.DeleteObject();


    // 画激活状态的道路
    newPen.CreatePen(PS_SOLID,3,CLR_BLUE);
    pOldPen = pDC->SelectObject(&newPen);
    pos = m_tfcRoadActived.GetHeadPosition();
    while (pos)
    {
        pRoad = m_tfcRoadActived.GetNext(pos);
        pRoad->DrawRoad(pDC,*this);
    }
    pDC->SelectObject(pOldPen);
    newPen.DeleteObject();


    // 画节点名称
    int iFontHeight;
    iFontHeight = 12;
    font.CreateFont(iFontHeight,0, 0, 0, FW_THIN, false, false, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, "宋体");

    pOldFont = pDC->SelectObject(&font);
    pDC->SetTextColor(CLR_BLACK);
    pDC->SetBkMode(TRANSPARENT);

    if (bDrawName)
    {
        pos = m_tfcRoadList.GetHeadPosition();
        while (pos)
        {
            pRoad = m_tfcRoadList.GetNext(pos);
            pRoad->DrawRoadName(pDC,*this);
        }
    }
    pDC->SelectObject(pOldFont);
    font.DeleteObject();


    // 画节点
    newPen.CreatePen(PS_SOLID,1,CLR_DARKGREEN);
    pOldPen = pDC->SelectObject(&newPen);
    brush.CreateSolidBrush(CLR_RED);
    pOldBrush = pDC->SelectObject(&brush);

    pos = m_tfcRoadList.GetHeadPosition();
    while (pos)
    {
        pRoad = m_tfcRoadList.GetNext(pos);
        pRoad->DrawNode(pDC,*this);
    }
    pDC->SelectObject(pOldPen);
    newPen.DeleteObject();
    pDC->SelectObject(pOldBrush);
    brush.DeleteObject();

}

void CTfcInfMgr::SetActivedRoad(const CTfcRoadList& aRoadList)
{
    m_tfcRoadActived.RemoveAll();

    POSITION pos = aRoadList.GetHeadPosition();
    while (pos)
    {
        m_tfcRoadActived.AddTail(aRoadList.GetNext(pos));
    }
}

void CTfcInfMgr::Close()
{
    while(m_tfcRoadList.GetHeadPosition())
    {
        delete m_tfcRoadList.RemoveHead();
    }

    m_roadIDMgr.Clear();

    CNBMapEngine::Close();
}
