#pragma once
#include "afx.h"

//////////////////////////////////////////////////////////////////////////
typedef struct _area_info
{
    CString     strFID;     //��������ֵ�������
    CString     strFName;   //

    CString     strTID;     //����������
    CString     strTName;
}TAreaInf,*PTAreaInf;

/************************************************************************/
/*  
                            ���������������        
���ܣ�
    ��������������������������֮���ת��
                                                                        */
/************************************************************************/
class CAreaIDMgr :   public CPtrList
{
    friend class CDataModule;
public:
    CAreaIDMgr(void);
    ~CAreaIDMgr(void);
    
private:

public:
    // �������ļ��ж�ȡ������
    BOOL ReadFile(LPCSTR lpFileName);
    
    // ת������ID
    /*
        [in] strAreaID: ԭID
        [in] bDirection: ΪTRUEʱ��ʾ������ת��Ϊ��������ֵı��
                        ΪFALSEʱ��ʾ����������ֵı��ת��Ϊ���� 
    */
    void TransferID(const CString strAreaID, BOOL bDirection,CStringList& strList);

    // ����AreaID�õ�AreaName
    void GetAreaName(const CString& strAreaID,CString& strAreaName) const;

private:

    // �������������Ϣ
    void ClearInf(void);

    //
    CString GetSValue(const CString& strLine);
};
