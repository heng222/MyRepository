// AlarmInfo.h: interface for the CAlarmInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALARMINFO_H__999FDD7E_D1AE_40B9_92C4_F8C4718693DA__INCLUDED_)
#define AFX_ALARMINFO_H__999FDD7E_D1AE_40B9_92C4_F8C4718693DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//������Ϣ��
typedef		DWORD	TOTALNUMTYPE;	//һ���ļ��п��Դ�ŵ����м�¼������
typedef		WORD	CURNUMTYPE;		//�����е�ǰ��¼������

#define		ALARMMAXNUMBER	200		//��󾯱���

struct AINode
{
	TOTALNUMTYPE 	m_wOrder;			//���
	CTime			m_time;				//ʱ��
	CString			m_sContent;			//����
	BYTE			m_byLevel;			//����
	CString			m_sSource;			//��Դ
	CString         m_sStation;         //��վ
	
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
	
	//����Ҫ�Լ�ָ�������ļ���ȡ��·������ָ��strPathName("E:\\a\\b")��
	CAlarmInfo(CString strPathName = "");
	virtual ~CAlarmInfo();
	
public:
	//���Ѵ򿪵��ļ���ɾ��ָ����ŵ���Ϣ
	BOOL DelItem(TOTALNUMTYPE iOrder);
	//���Ѵ򿪵��ļ��в���ָ����Ϣ���ɹ���item����ָ������Ϣ�ҷ���TRUE�����ɹ�����FALSE
	BOOL FindItem(TOTALNUMTYPE iOrder,AINode& item);
	
	//���ļ����ڶ�д�ļ�ǰ�����ȴ��ļ�
	BOOL OpenFile(UINT nOpenFlags = modeWrite,CString strFileName = "");
	
	//���ļ��е���Ϣ����ȡ��
	//���ô˺���ǰ�����OpenFile
	void ReadFile();
	//��ReadFile���ã�����false˵����ȡ��ϣ�����TRUE˵�������ļ�δ����
	BOOL ReadNext();
	
	//����һԪ��
	//���ô˺���ǰ�����OpenFile
	void Add(const AINode& item);
	
	//�õ�Ŀǰ��������Ϣ�ĸ���
	CURNUMTYPE GetCurLength();
	//�õ�ָ���ļ�����Ϣ�����и���
	TOTALNUMTYPE GetTotalNumber();
	
	//�õ�(������)����ΪiIndex����Ϣ��ָ��( BASE 0 )
	AINode* GetAt(CURNUMTYPE iIndex);
	
	//�����ļ���ŵ�·��
	//�ڵ���OpenFile֮ǰ���ô˺���,���ڹ��캯����ָ����·����������Ҫ���ô˺���
	void SetPathName(CString strPathName);
	
	//�ر��ļ����ͷŻ���(���������������Ҵ���д״̬���Զ��������е����ݱ���)
	void CloseFile();
	
private:
	CFile			m_cFile;					//���ļ�ʱ���ļ�ָ��
	UINT			m_nOpenFlags;				//�����ļ��򿪱�־
	
	TOTALNUMTYPE	m_dTotalNumber;				//�ܹ������ľ�����
	CString			m_strDirPath;				//�������ڵ�·��
	CString			m_strPathName;				//�����ļ���ŵ��ļ����Ե�ַ
	CURNUMTYPE		m_wCurNumber;				//��ǰָ�������д�ŵľ�����
	AINode*			m_pVector[ALARMMAXNUMBER];	//�������ָ��
private:
	//��ʼ��ָ������
	void InitArray();

	//����������ݣ��ͷ���Դ
	void ClearArray();


	//��ָ������(������)ָ�������д���ļ�
	//���ô˺���ǰ�����OpenFile
	void WriteCacheToFile();

};

#endif // !defined(AFX_ALARMINFO_H__999FDD7E_D1AE_40B9_92C4_F8C4718693DA__INCLUDED_)
