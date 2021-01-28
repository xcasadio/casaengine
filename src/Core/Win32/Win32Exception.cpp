#include <TCHAR.H>
#include <Windows.h>

#include "Win32Exception.h"

namespace CasaEngine
{
	Win32Exception::Win32Exception()
		: m_szErrMsg(nullptr)
	{
		unsigned int dwLastErr = GetLastError();
		doFormatMessage(dwLastErr);
	}

	// Smart copy
	Win32Exception::Win32Exception(const Win32Exception& rRHS)
		: m_szErrMsg(nullptr)
	{
		addRef(rRHS);
	}

	// Use this form of construction if you yourself
	// call ::GetLastError() just before instantiation.
	// Also useful for returning success status (arg = 0 ).
	Win32Exception::Win32Exception(unsigned int dwLastError)
		: m_szErrMsg(nullptr)
	{
		doFormatMessage(dwLastError);
	}

	// Smart copy.
	const Win32Exception& Win32Exception::operator=(const Win32Exception& rRHS)
	{
		if (this != &rRHS)
		{
			releaseRef();
			addRef(rRHS);
		}
		return *this;
	}

	// Automatically frees the internal buffer once
	// the internal reference count drops to zero.
	// TODO: Make dtor virtual, if deriving from this.
	Win32Exception::~Win32Exception()
	{
		releaseRef();
	}

	//----- Returning the state without modification -----------------------

		// The Win32 error code currently held in this object.
	unsigned int Win32Exception::ErrorCode() const
	{
		return metaMem() ? metaMem()->m_fwErrCode : -1;
	}

	// The Win32 error code currently held in this object.
	Win32Exception::operator unsigned int() const
	{
		return metaMem() ? metaMem()->m_fwErrCode : -1;
	}

	// TCHAR count including the terminating nullptr TCHAR. That is not
	// necessarily equal to byte count. (Depends on UNICODE/MBCS).
	int Win32Exception::MessageLength() const
	{
		return metaMem() ? metaMem()->m_nMsgStrLen : 0;
	}

	// Internal buffer returned!! Do not modify, delete[] or free.
	// You can directly pass this object to any function that
	// accepts a const char* argument, e.g. to AfxMessageBox().
	// Makes available the Win32 API error string held internally.
	Win32Exception::operator const TCHAR* () const
	{
		return m_szErrMsg;
	}

	// The function form for returning the error string.
	// Internal buffer returned!! Do not modify, delete[] or free.
	const TCHAR* Win32Exception::Description() const
	{
		return m_szErrMsg;
	}

	//----- Resetting the internal state -----------------------------------

		// Note: GetLastError() is being called for the n+1 time
		// now. (The first time was in construction.) The two values
		// may differ if ::SetLastError() was called in between.
		// This can happen if either you call SetLastError yourself
		// of if you call some Win32 API (such as CreateFile() )
		// that on its own calls SetLastError()
	void Win32Exception::ReGetLastError()
	{
		///CA_ASSERT( metaMem() );

		// Get the error code of the current thread
		unsigned int dwNewErr = GetLastError();

		// A simple check for performance: Reformatting is only
		// necessary if the new code value is different.
		if (dwNewErr != metaMem()->m_fwErrCode)
		{
			releaseRef();
			doFormatMessage(dwNewErr);
		}
	}

	// struct for smart copying. Meta info is prepended to
	// the actual string, something like in BASIC strings (BSTRs).
	Win32Exception::SMetaMem::SMetaMem()
		: m_nMsgStrLen(0), m_fwErrCode(0), m_nRefCnt(0)
	{
	}

	TCHAR* Win32Exception::SMetaMem::getString()
	{
		return (TCHAR*)(this + 1);
	}

	void Win32Exception::addRef(const Win32Exception& rOrig)
	{
		::InterlockedIncrement(&rOrig.metaMem()->m_nRefCnt);
		m_szErrMsg = rOrig.m_szErrMsg;
	}

	void Win32Exception::releaseRef()
	{
		if (!metaMem())
		{
			return;
		}
		if (!::InterlockedDecrement(&metaMem()->m_nRefCnt))
		{
			freeBuffer();
		}
	}

	void Win32Exception::doFormatMessage(unsigned int dwLastErr)
	{
		m_szErrMsg = nullptr;

		TCHAR* pTemp = nullptr;
		int nLen = ::FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_FROM_SYSTEM,
			nullptr,
			dwLastErr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&pTemp,
			1,
			nullptr);
		allocCopyData(pTemp, nLen, dwLastErr);
		LocalFree(pTemp);
		pTemp = nullptr;
	}

	void Win32Exception::allocCopyData(TCHAR* pTemp, int nLen, unsigned int dwLastErr)
	{
		SMetaMem* pSM = nullptr;
		pSM = (SMetaMem*) ::new unsigned char[sizeof(SMetaMem) + (nLen + 1) * sizeof(TCHAR)];
		if (!pSM)
		{
			return;
		}
		pSM->m_fwErrCode = dwLastErr;
		pSM->m_nRefCnt = 1;
		pSM->m_nMsgStrLen = nLen;
		m_szErrMsg = pSM->getString();
		memcpy(m_szErrMsg, pTemp, nLen * sizeof(TCHAR));
		m_szErrMsg[nLen] = '\0';
	}

	void Win32Exception::freeBuffer()
	{
		if (metaMem())
		{
			delete[](unsigned char*) metaMem();
			m_szErrMsg = nullptr;
		}
	}

	Win32Exception::SMetaMem* Win32Exception::metaMem() const
	{
		return m_szErrMsg ? (SMetaMem*)m_szErrMsg - 1 : nullptr;
	}
}