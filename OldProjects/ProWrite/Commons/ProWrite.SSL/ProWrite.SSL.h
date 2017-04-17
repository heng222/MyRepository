// ProWrite.SSL.h

#pragma once

#include <vcclr.h>
#include "rc4/rc4.h"

using namespace System;
using namespace System::Collections::Generic;



namespace ProWrite{ namespace SSL {

    public ref class RC4SymmetricAlgorithm
    {
        // TODO: Add your methods for this class here.


    private:

        //RC4_KEY*     m_pRc4Key;

    public:

        // Allocate the native object on the C++ Heap via a constructor
        RC4SymmetricAlgorithm() //: m_pRc4Key(new RC4_KEY)
        {

        }

        // Deallocate the native object on a destructor
        ~RC4SymmetricAlgorithm() 
        {
            //delete m_pRc4Key;
        }


    protected:

        // Deallocate the native object on the finalizer just in case no destructor is called
        !RC4SymmetricAlgorithm() 
        {
            //delete m_pRc4Key;
        }

        // 
    public:

        static List<unsigned char>^   RC4(List<unsigned char>^ strKey,List<unsigned char>^ strSource);

    };
}}
