#include "StdAfx.h"
#include "BBCChecksum.h"

BYTE   CBBCChecksum::GetBBCChecksum(const unsigned char* pRawData,
                       unsigned long lDataLen)
{
    // У���ʼֵ
    unsigned char byBBC = 0;

    for(unsigned long i=0;i<lDataLen; i++) 
    {
        byBBC ^= pRawData[i];
    }

    return byBBC;
}