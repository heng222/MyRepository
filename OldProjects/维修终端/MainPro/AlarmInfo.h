// AlarmInfo.h: interface for the CAlarmInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALARMINFO_H__999FDD7E_D1AE_40B9_92C4_F8C4718693DA__INCLUDED_)
#define AFX_ALARMINFO_H__999FDD7E_D1AE_40B9_92C4_F8C4718693DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//警报信息类
typedef		DWORD	TOTALNUMTYPE;	//一个文件中可以存放的所有记录数类型
typedef		WORD	CURNUMTYPE;		//缓冲中当前记录数类型

#define		ALARMMAXNUMBER	200		//最大警报数

struct AINode
{
	TOTALNUMTYPE 	m_wOrder;			//序号
	CTime			m_time;				//时间
	CString			m_sContent;			//内容
	BYTE			m_byLevel;			//级别
	CString			m_sSource;			//来源
	CString         m_sStation;         //车站
	
};
class CAlarmInfo : public CObject  
{
public:
	// Flag values
	enum OpenFlags {
		modeRead =          0x0000,
		modeWrite =         0x0001,
		modeReadWrite=		0x0002
	};
	
public:
	
	//若需要自己指定警报文件存取的路径，则指定strPathName("E:\\a\\b")。
	CAlarmInfo(CString strPathName = "");
	virtual ~CAlarmInfo();
	
public:
	//从已打开的文件中删除指定序号的信息
	BOOL DelItem(TOTALNUMTYPE iOrder);
	//从已打开的文件中查找指定信息，成功则item保存指定的信息且返回TRUE，不成功返回FALSE
	BOOL FindItem(TOTALNUMTYPE iOrder,AINode& item);
	
	//打开文件，在读写文件前必须先打开文件
	BOOL OpenFile(UINT nOpenFlags = modeWrite,CString strFileName = "");
	
	//将文件中的信息总数取出
	//调用此函数前须调用OpenFile
	void ReadFile();
	//与ReadFile联用，返回false说明读取完毕，返回TRUE说明还有文件未读。
	BOOL ReadNext();
	
	//新增一元素
	//调用此函数前须调用OpenFile
	void Add(const AINode& item);
	
	//得到目前缓冲中信息的个数
	CURNUMTYPE GetCurLength();
	//得到指定文件中信息的所有个数
	TOTALNUMTYPE GetTotalNumber();
	
	//得到(缓冲中)索引为iIndex的信息的指针( BASE 0 )
	AINode* GetAt(CURNUMTYPE iIndex);
	
	//设置文件存放的路径
	//在调用OpenFile之前调用此函数,若在构造函数中指定了路径，则不再需要调用此函数
	void SetPathName(CString strPathName);
	
	//关闭文件并释放缓冲(若缓冲中有数据且处于写状态则自动将缓冲中的内容保存)
	void CloseFile();
	
private:
	CFile			m_cFile;					//读文件时的文件指针
	UINT			m_nOpenFlags;				//警报文件打开标志
	
	TOTALNUMTYPE	m_dTotalNumber;				//总共产生的警报数
	CString			m_strDirPath;				//警报所在的路径
	CString			m_strPathName;				//警报文件存放的文件绝对地址
	CURNUMTYPE		m_wCurNumber;				//当前指针数组中存放的警报数
	AINode*			m_pVector[ALARMMAXNUMBER];	//警报结点指针
private:
	//初始化指针数组
	void InitArray();

	//清空所有内容，释放资源
	void ClearArray();


	//将指针数组(即缓冲)指向的内容写入文件
	//调用此函数前须调用OpenFile
	void WriteCacheToFile();

};

#endif // !defined(AFX_ALARMINFO_H__999FDD7E_D1AE_40B9_92C4_F8C4718693DA__INCLUDED_)
