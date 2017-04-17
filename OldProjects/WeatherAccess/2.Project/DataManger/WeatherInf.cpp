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

// ��ȡ����Ԥ���ļ�
BOOL CPreWeatherInf::ReadFile()
{
	CFile fp;
	if (!fp.Open(m_strFilePath,CFile::modeRead|CFile::shareDenyNone))
	{
		TRACE("ERROR! �޷����ļ� %s\n",m_strFilePath);
		return FALSE;
	}
	fp.Close();

    EnterCriticalSection(&m_CriSection);

	/************************************************************************/
	/*  ��վ�����                                                          */
	/************************************************************************/
	ClearList();

	/************************************************************************/
	/*  ��ȡ����Ԥ����Ϣ                                                    */
	/************************************************************************/
	CStdioFile	stdFile(m_strFilePath,CFile::modeRead|CFile::shareDenyNone);
	CString	strLine;
	while (stdFile.ReadString(strLine))
	{
		/**********************************************/
		/*  ȥ��������Ч�Ŀո�                        */
		/**********************************************/
		strLine.TrimLeft();
		strLine.TrimRight();

		/**********************************************/
		/*  �õ������ֶ�                              */
		/**********************************************/
		CStringList strItemList;
		GetItems(strLine,",",strItemList);

		/**********************************************/
		/*  ����洢�ռ�                              */
		/**********************************************/
		PTWeatherInf pWthInf = new TWeatherInf;

		/**********************************************/
		/*  ���и�ֵ                                  */
		/**********************************************/
		CString strItem;
		POSITION pos = strItemList.GetHeadPosition();		
		//����ʱ��
		strItem = strItemList.GetNext(pos);
		int iYear = atoi(strItem.Left(4));
		int iMonth = atoi(strItem.Mid(4,2));
		int iDay = atoi(strItem.Mid(6,2));
		int iHour = atoi(strItem.Mid(8,2));
		//pWthInf->publishTime.ParseDateTime("2006-09-14");
		pWthInf->publishTime.SetDateTime(iYear,iMonth,iDay,iHour,0,0);
		//Ԥ��ʱ��ָʾ��
		strItem = strItemList.GetNext(pos);
        strItem.MakeLower();
        pWthInf->cPeriodFlag = (TWeatherInf::TPeriodCode)(strItem.GetAt(0));     
		//�ص�ָʾ��
		pWthInf->strDistID = strItemList.GetNext(pos);
		
		//����״��
		pWthInf->strWeatherDes = strItemList.GetNext(pos);
		
		//�޶���
		strItem = strItemList.GetNext(pos);
		//����¶�
		strItem = strItemList.GetNext(pos);
		pWthInf->fTempMax = (float)atof(strItem);
		//����¶�
		strItem = strItemList.GetNext(pos);
		pWthInf->fTempMin = (float)atof(strItem);
		//����
		pWthInf->strWindDirec = strItemList.GetNext(pos);
		
		//����
		strItem = strItemList.GetNext(pos);
        if (strItem.GetLength()>3)
        {
            pWthInf->byWindPowerMin = (BYTE)atoi(CString(strItem.GetAt(0)));
            pWthInf->byWindPowerMax = (BYTE)atoi(CString(strItem.GetAt(3)));
        }
		
		//���ʪ��
		strItem = strItemList.GetNext(pos);
		pWthInf->byHumidity = atoi(strItem);

		/**********************************************/
		/*  ������Ϣ                                  */
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

// �ļ��Ƿ����
BOOL CPreWeatherInf::IsFileChange(void)
{
    BOOL bReturn = FALSE;

    //���ļ�
    CFile cfile;
    if (!cfile.Open(m_strFilePath,CFile::modeRead|CFile::shareDenyNone))
    {
        TRACE("Read file error!\n");
        return FALSE;
    }

    CFileStatus status;


    //�õ��ļ����һ���޸ĵ�ʱ��		
    if( cfile.GetStatus( status ) )
    {
        //�ļ���С
        /*
        LONG m_lSize = status.m_size;
        CString strSize;
        if (m_lSize<1024)
        {
            strSize.Format(" %d�ֽ�",m_lSize);
        }
        else
        {
            strSize.Format(" %.2fK",m_lSize/1024.0);
        }
        //*/

        //��ʱ��ı䣬�����
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

// �����ļ�·��
void CPreWeatherInf::SetFilePath(const CString& strFilePath)
{
    m_strFilePath = strFilePath;

    //���ļ�
    CFile cfile;
    if (!cfile.Open(m_strFilePath,CFile::modeRead|CFile::shareDenyNone))
    {
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("�޷�����������%s��"),m_strFilePath);
        NbsSendModuleMsg(&aLog);
    }
    cfile.Close();
}

CString CPreWeatherInf::GetPath() const
{
    return m_strFilePath;
}
