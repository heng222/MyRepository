
#pragma once
//////////////////////////////////////////////////////////////////////////

#include "cn_comwebxmlwebservice.h"
#include <afxtempl.h>
#include "InterfaceEx.h"
#include "cncomwebxml.h"

//////////////////////////////////////////////////////////////////////////

using namespace WeatherWS;

//////////////////////////////////////////////////////////////////////////
/************************************************************************/


//////////////////////////////////////////////////////////////////////////
// 
class AFX_EXT_CLASS CWeatherClient
{
public:

    // Constructor && Destructor
    CWeatherClient();
    ~CWeatherClient();

    // New function
    BOOL        Initialize();
    BOOL        Start();
    void        Stop();
    void        Terminate();
    BOOL        GetInformation();

private:
    static UINT _ThreadEntry(LPVOID pParam);

protected:
    CWinThread*                  m_pThread;
    HANDLE                       m_hExitEvent;

private:
    CWeatherWS     m_Service;
    CStringList    m_strlistCityCode; // ���д����б�
};

/************************************************************************/
/* 

DES������ getWeatherbyCityName ���صĽ����
��23��Ԫ��
    String(0) �� String(4)��ʡ�ݣ����У����д��룬����ͼƬ���ƣ�������ʱ�䡣
    String(5) �� String(11)��    ��������£��ſ�������ͷ������������ƿ�ʼͼƬ����(���³ƣ�ͼ��һ)���������ƽ���ͼƬ����(���³ƣ�ͼ���)�����ڵ�����ʵ��������ָ����
    String(12) �� String(16)���ڶ���� ���£��ſ�������ͷ�����ͼ��һ��ͼ�����
    String(17) �� String(21)��������� ���£��ſ�������ͷ�����ͼ��һ��ͼ�����
    String(22) ����ѯ�ĳ��л�����Ľ��ܡ�

*/
/************************************************************************/
