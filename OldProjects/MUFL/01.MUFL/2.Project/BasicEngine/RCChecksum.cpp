#include "StdAfx.h"
#include "RCChecksum.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
WORD CRCChecksum::GetCRC16(const BYTE *pBuf, int iLen)
{
    int i, j;
    WORD ch, crc=0;

    for( i=0; i<iLen; i++ )
    {
        ch = pBuf[i];
        ch <<= 8;
        for( j=0; j<8; j++, ch<<=1 )
        {
            if((crc ^ ch) & 0x8000) crc=(crc<<1)^0x1021;
            else crc <<= 1;
        }
    }

    return crc;
}

/* Based on follow polynomial .
// x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1 and initial value is 0 
*/
DWORD CRCChecksum::GetCRC32( const BYTE *pBuf, int iLen )
{
    int i, j;
    DWORD ch, crc=0;

    for( i=0; i<iLen; i++ )
    {
        ch = pBuf[i];
        ch <<= 24;
        for( j=0; j<8; j++, ch<<=1 )
        {
            if((crc ^ ch) & 0x80000000L) crc=(crc<<1)^0x04C11DB7L;
            else crc <<= 1;
        }
    }

    return crc;
}
