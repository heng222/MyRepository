#include "stdafx.h"
#include ".\weatherinf.h"
#include "InterfaceEx.h"

CPreWeatherInf::CPreWeatherInf(void)
{
    InitializeCriticalSection(&m_CriSection);
}

CPreWeatherInf::~CPreWeatherInf(void)
{
	ClearList();
    DeleteCriticalSection(&m_CriSection);
}

void CPreWeatherInf::ClearList(void)
{
    EnterCriticalSection(&m_CriSection);
	while (GetHeadPosition())
	{
		delete (PTWeatherInf)RemoveHead();
	}
    LeaveCriticalSection(&m_CriSection);
}

// 读取天气预报文件
BOOL CPreWeatherInf::ReadFile()
{
	CFile fp;
	if (!fp.Open(m_strFilePath,CFile::modeRead|CFile::shareDenyNone))
	{
		TRACE("ERROR! 无法打开文件 %s\n",m_strFilePath);
		return FALSE;
	}
	fp.Close();

    EnterCriticalSection(&m_CriSection);

	/************************************************************************/
	/*  清空旧数据                                                          */
	/************************************************************************/
	ClearList();

	/************************************************************************/
	/*  提取所有预报信息                                                    */
	/************************************************************************/
	CStdioFile	stdFile(m_strFilePath,CFile::modeRead|CFile::shareDenyNone);
	CString	strLine;
	while (stdFile.ReadString(strLine))
	{
		/**********************************************/
		/*  去除左右无效的空格                        */
		/**********************************************/
		strLine.TrimLeft();
		strLine.TrimRight();

		/**********************************************/
		/*  得到所有字段                              */
		/**********************************************/
		CStringList strItemList;
		GetItems(strLine,",",strItemList);

		/**********************************************/
		/*  分配存储空间                              */
		/**********************************************/
		PTWeatherInf pWthInf = new TWeatherInf;

		/**********************************************/
		/*  进行赋值                                  */
		/**********************************************/
		CString strItem;
		POSITION pos = strItemList.GetHeadPosition();		
		//发布时间
		strItem = strItemList.GetNext(pos);
		int iYear = atoi(strItem.Left(4));
		int iMonth = atoi(strItem.Mid(4,2));
		int iDay = atoi(strItem.Mid(6,2));
		int iHour = atoi(strItem.Mid(8,2));
		//pWthInf->publishTime.ParseDateTime("2006-09-14");
		pWthInf->publishTime.SetDateTime(iYear,iMonth,iDay,iHour,0,0);
		//预报时段指示码
		strItem = strItemList.GetNext(pos);
        strItem.MakeLower();
        pWthInf->cPeriodFlag = (TWeatherInf::TPeriodCode)(strItem.GetAt(0));     
		//地点指示码
		pWthInf->strDistID = strItemList.GetNext(pos);
		
		//天气状况
		pWthInf->strWeatherDes = strItemList.GetNext(pos);
		
		//无定义
		strItem = strItemList.GetNext(pos);
		//最高温度
		strItem = strItemList.GetNext(pos);
		pWthInf->fTempMax = (float)atof(strItem);
		//最低温度
		strItem = strItemList.GetNext(pos);
		pWthInf->fTempMin = (float)atof(strItem);
		//风向
		pWthInf->strWindDirec = strItemList.GetNext(pos);
		
		//风力
		strItem = strItemList.GetNext(pos);
        if (strItem.GetLength()>3)
        {
            pWthInf->byWindPowerMin = (BYTE)atoi(CString(strItem.GetAt(0)));
            pWthInf->byWindPowerMax = (BYTE)atoi(CString(strItem.GetAt(3)));
        }
		
		//相对湿度
		strItem = strItemList.GetNext(pos);
		pWthInf->byHumidity = atoi(strItem);

		/**********************************************/
		/*  保存信息                                  */
		/**********************************************/
		AddTail(pWthInf);
	}
	stdFile.Close();
    //
    LeaveCriticalSection(&m_CriSection);
	return TRUE;
}

// 
void CPreWeatherInf::GetItems(const CString& strLine,
						   const CString& strSeperator,
						   CStringList& strList)
{
	int iIndex = 0;
	int iEnd = 0;
	CString strItem;
	while (iEnd != -1)
	{
		iEnd = strLine.Find(strSeperator,iIndex);
		//
		if (iEnd!=-1)
		{
			strItem = strLine.Mid(iIndex,iEnd-iIndex);
		} 
		else
		{
			strItem = strLine.Mid(iIndex,strLine.GetLength()-iIndex);
		}
		//
		strList.AddTail(strItem);
		//TRACE("%s\n",strItem);
		//
		iIndex = iEnd + strSeperator.GetLength();
	}
}

// 文件是否更改
BOOL CPreWeatherInf::IsFileChange(void)
{
    BOOL bReturn = FALSE;

    //打开文件
    CFile cfile;
    if (!cfile.Open(m_strFilePath,CFile::modeRead|CFile::shareDenyNone))
    {
        TRACE("Read file error!\n");
        return FALSE;
    }

    CFileStatus status;


    //得到文件最后一次修改的时间		
    if( cfile.GetStatus( status ) )
    {
        //文件大小
        /*
        LONG m_lSize = status.m_size;
        CString strSize;
        if (m_lSize<1024)
        {
            strSize.Format(" %d字节",m_lSize);
        }
        else
        {
            strSize.Format(" %.2fK",m_lSize/1024.0);
        }
        //*/

        //若时间改变，则更新
        if (m_tLastModTime != COleDateTime(status.m_mtime.GetTime()))
        {
            m_tLastModTime = COleDateTime(status.m_mtime.GetTime());
            bReturn = TRUE;
        }
    }
    //
    cfile.Close();
    return bReturn;
}

// 设置文件路径
void CPreWeatherInf::SetFilePath(const CString& strFilePath)
{
    m_strFilePath = strFilePath;

    //打开文件
    CFile cfile;
    if (!cfile.Open(m_strFilePath,CFile::modeRead|CFile::shareDenyNone))
    {
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("无法打开气象数据%s！"),m_strFilePath);
        NbsSendModuleMsg(&aLog);
    }
    cfile.Close();
}

CString CPreWeatherInf::GetPath() const
{
    return m_strFilePath;
}
