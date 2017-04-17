

#ifndef _TYPED_SIZE_H_
#define _TYPED_SIZE_H_

//////////////////////////////////////////////////////////////////////////


namespace Mugis
{
/////////////////// template CTypedSize definition //////////////////////////////////// 
template<class T>
class CTypedSize
{
public:

	CTypedSize(){}
	CTypedSize(T aWith,T aHeight)
	{
		iWidth = aWith;
		iHeight = aHeight;
	}
	~CTypedSize(){}

public:

	T iWidth;
	T iHeight;
};


}
//////////////////////////////////////////////////////////////////////////
#endif