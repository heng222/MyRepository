

#ifndef __ZCTCOMMFUNCTION_H
#define __ZCTCOMMFUNCTION_H

//��һ���ַ����еõ���iIndex���ַ���,�ַ�������cCompart�ָ�
extern "C++" __declspec (dllexport) CString GetSFStr(CString strSource, const int &iIndex, char cCompart);

//��һ���ַ����еõ�Ԫ�صĸ�����Ԫ����cCompart���ŷָ�
extern "C" __declspec (dllexport)  int GetItemSum(CString strSource, char cCompart);

//��һ���ַ����еõ���iIndex������
extern "C" __declspec (dllexport)  WORD GetNFStr(const char *chSource, const int &iIndex);

#endif


