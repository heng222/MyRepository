
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
    CStringList    m_strlistCityCode; // 城市代码列表
};

/************************************************************************/
/* 

DES：函数 getWeatherbyCityName 返回的结果。
共23个元素
    String(0) 到 String(4)：省份，城市，城市代码，城市图片名称，最后更新时间。
    String(5) 到 String(11)：    当天的气温，概况，风向和风力，天气趋势开始图片名称(以下称：图标一)，天气趋势结束图片名称(以下称：图标二)，现在的天气实况，生活指数。
    String(12) 到 String(16)：第二天的 气温，概况，风向和风力，图标一，图标二。
    String(17) 到 String(21)：第三天的 气温，概况，风向和风力，图标一，图标二。
    String(22) 被查询的城市或地区的介绍。

*/
/************************************************************************/
