#pragma once
#include "afx.h"

//////////////////////////////////////////////////////////////////////////
typedef struct _area_info
{
    CString     strFID;     //北京气象局的区域编号
    CString     strFName;   //

    CString     strTID;     //国标区域编号
    CString     strTName;
}TAreaInf,*PTAreaInf;

/************************************************************************/
/*  
                            《区域码表》管理类        
功能：
    北京市气象局区域编码与国标编码之间的转换
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
    // 从配置文件中读取区域编号
    BOOL ReadFile(LPCSTR lpFileName);
    
    // 转换区域ID
    /*
        [in] strAreaID: 原ID
        [in] bDirection: 为TRUE时表示将国标转换为北京气象局的编号
                        为FALSE时表示将北京气象局的编号转换为国标 
    */
    void TransferID(const CString strAreaID, BOOL bDirection,CStringList& strList);

    // 根据AreaID得到AreaName
    void GetAreaName(const CString& strAreaID,CString& strAreaName) const;

private:

    // 清空所有区域信息
    void ClearInf(void);

    //
    CString GetSValue(const CString& strLine);
};
