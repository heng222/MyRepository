#pragma once
#include "afx.h"

/************************************************************************/
/*  天气预报数据格式                                                    */
//typedef struct _weather_inf
//{
//	COleDateTime publishTime;	// 发布时间
//	char		cFlag;			// 时段指示码
//	char		cAreaID[20];	// 地点指示码
//	
//	char		cWeather[50];	// 天气状况
//	
//	float		fTempMax;		// 最高温度
//
//	float		fTempMin;		// 最低温度
//	
//	char		cWindDirec[50];	// 风向
//	BYTE		byWindPower[2];	// 风力(0:低,1:高)
//	BYTE		byHumidity;		// 相对湿度
//
//	_weather_inf()
//	{
//		memset(this,0,sizeof(_weather_inf));
//	}
//}WTHINF,*PWTHINF;
/************************************************************************/

/************************************************************************/
/*  预报气象数据类
    功能：
	1、从本地读取北京市气象局发送的天气预报信息（含气象指数）
	2、查询指定的数据内容
*/
/************************************************************************/
class CPreWeatherInf : public CPtrList
{
public:
	CPreWeatherInf(void);
	~CPreWeatherInf(void);

private:
    //文件全路径
    CString m_strFilePath;

    //文件上一次修改的时间
    COleDateTime    m_tLastModTime;

    //
    CRITICAL_SECTION m_CriSection;

private:
	//从字符串中得到所需字段
	void GetItems( const CString& strLine,
				   const CString& strSeperator,
				   CStringList& strList);
public:
	// 读取天气预报文件
	BOOL ReadFile();

	//清空数据
	void ClearList(void);

    // 文件是否更改
    BOOL IsFileChange(void);

    // 设置文件路径
    void SetFilePath(const CString& strFilePath);
    CString GetPath() const;
};
