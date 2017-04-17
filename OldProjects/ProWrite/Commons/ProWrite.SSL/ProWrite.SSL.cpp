// This is the main DLL file.

#include "stdafx.h"
#include <windows.h>
#include <string>
using namespace std;

#include "ProWrite.SSL.h"

using namespace ProWrite::SSL;

// 
List<unsigned char>^   RC4SymmetricAlgorithm::RC4(List<unsigned char>^ key,List<unsigned char>^ inData)
{
    int iDataLength = inData->Count;
    int iKeyLength  = key->Count;

    unsigned char* pKeyData = NULL;
    unsigned char* pInData  = NULL;
    unsigned char* pOutData = NULL;
    List<unsigned char>^ value = nullptr;
    try
    {
        // Key Data
        pKeyData = new unsigned char[iKeyLength];
        for (int m=0; m<iKeyLength; m++)
        {
            pKeyData[m] = key[m];
        }

        // InData
        pInData = new unsigned char[iDataLength];
        for (int i=0; i<iDataLength; i++)
        {
            pInData[i] = inData[i];
        }

        // OutData
        pOutData = new unsigned char[iDataLength];
        ZeroMemory(pOutData,iDataLength);

        // calculate RC4
        RC4_KEY rc4key;
        ::RC4_set_key(&rc4key, iKeyLength, pKeyData);
        ::RC4(&rc4key,iDataLength,pInData,pOutData);


        // construct return value
        value = gcnew List<unsigned char>(0);
        for (int i=0; i<iDataLength; i++)
        {
            value->Add(pOutData[i]);
        }

    }
    catch(...)
    {
        throw std::exception("RC4SymmetricAlgorithm Error!");
    }
    finally
    {
        delete[] pKeyData;
        delete[] pOutData;
        delete[] pInData;
    }
    // 
    return value;
}
