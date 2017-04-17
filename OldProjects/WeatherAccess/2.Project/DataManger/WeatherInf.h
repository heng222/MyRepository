#pragma once
#include "afx.h"

/************************************************************************/
/*  ����Ԥ�����ݸ�ʽ                                                    */
//typedef struct _weather_inf
//{
//	COleDateTime publishTime;	// ����ʱ��
//	char		cFlag;			// ʱ��ָʾ��
//	char		cAreaID[20];	// �ص�ָʾ��
//	
//	char		cWeather[50];	// ����״��
//	
//	float		fTempMax;		// ����¶�
//
//	float		fTempMin;		// ����¶�
//	
//	char		cWindDirec[50];	// ����
//	BYTE		byWindPower[2];	// ����(0:��,1:��)
//	BYTE		byHumidity;		// ���ʪ��
//
//	_weather_inf()
//	{
//		memset(this,0,sizeof(_weather_inf));
//	}
//}WTHINF,*PWTHINF;
/************************************************************************/

/************************************************************************/
/*  Ԥ������������
    ���ܣ�
	1���ӱ��ض�ȡ����������ַ��͵�����Ԥ����Ϣ��������ָ����
	2����ѯָ������������
*/
/************************************************************************/
class CPreWeatherInf : public CPtrList
{
public:
	CPreWeatherInf(void);
	~CPreWeatherInf(void);

private:
    //�ļ�ȫ·��
    CString m_strFilePath;

    //�ļ���һ���޸ĵ�ʱ��
    COleDateTime    m_tLastModTime;

    //
    CRITICAL_SECTION m_CriSection;

private:
	//���ַ����еõ������ֶ�
	void GetItems( const CString& strLine,
				   const CString& strSeperator,
				   CStringList& strList);
public:
	// ��ȡ����Ԥ���ļ�
	BOOL ReadFile();

	//�������
	void ClearList(void);

    // �ļ��Ƿ����
    BOOL IsFileChange(void);

    // �����ļ�·��
    void SetFilePath(const CString& strFilePath);
    CString GetPath() const;
};
