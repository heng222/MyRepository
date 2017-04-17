
#ifndef _SMARTLPTR_H_IUBWOS_34
#define _SMARTLPTR_H_IUBWOS_34
//////////////////////////////////////////////////////////////////////////


//Ignore UDT boundary warning on WORD size data.
//Note: Do not use the arrow operator with WORD-sized data.
#pragma warning( push )
#pragma warning( disable : 4284 ) 

template<class TYPE>
class CSmartPtr
{
public:
	CSmartPtr(TYPE*	pc = NULL)
	{
		m_pc = pc;
	}

	~CSmartPtr(void)
	{
		if (m_pc !=	NULL)
			delete m_pc;
	}

	operator TYPE*() const
	{
		return (TYPE*)m_pc;
	}

	TYPE* operator ->(void)
	{
		return m_pc;
	}

	const TYPE*	operator ->(void) const
	{
		return m_pc;
	}

	TYPE& operator *(void)
	{
		return *m_pc;
	}

	const TYPE&	operator *(void) const
	{
		return *m_pc;
	}

	TYPE** operator&(void)
	{
		return &m_pc;
	};

	int	operator == (TYPE* pPtr) const
	{
		return (m_pc == pPtr);
	}

	int	operator != (TYPE* pPtr) const
	{
		return (m_pc != pPtr);
	}

	operator TYPE* &(void)
	{
	    return m_pc;
	}

	TYPE* Detach()
	{
		TYPE* pPtr = m_pc;
		m_pc = NULL;
		return pPtr;
	}

	HRESULT Attach(TYPE* pPtr)
	{
		RTN_HR_IF_FALSE(!m_pc);
		m_pc = pPtr;
		return pPtr;
	}
	HRESULT Delete()
	{
		if(m_pc)
		{
			delete m_pc;
			m_pc = NULL;
		}
		return S_OK;
	}

	TYPE* operator = (TYPE* pPtr)
	{
		if(&pPtr != &m_pc)
		{
			Delete();
			m_pc = pPtr;
		}
		return pPtr;
	}

	TYPE* m_pc;

private:
	const CSmartPtr<TYPE>& operator = (const CSmartPtr<TYPE>& autoPtr);
	CSmartPtr(const CSmartPtr<TYPE>&);
};


#pragma warning( pop )

//////////////////////////////////////////////////////////////////////////
#endif
// End of file