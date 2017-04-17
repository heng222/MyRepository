

#ifndef __ZCTCOMMFUNCTION_H
#define __ZCTCOMMFUNCTION_H

//从一个字符串中得到第iIndex个字符串,字符串间以cCompart分隔
extern "C++" __declspec (dllexport) CString GetSFStr(CString strSource, const int &iIndex, char cCompart);

//从一个字符串中得到元素的个数，元素以cCompart符号分隔
extern "C" __declspec (dllexport)  int GetItemSum(CString strSource, char cCompart);

//从一个字符串中得到第iIndex个整数
extern "C" __declspec (dllexport)  WORD GetNFStr(const char *chSource, const int &iIndex);

#endif


