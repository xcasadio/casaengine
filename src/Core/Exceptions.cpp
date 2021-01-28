#include <Exceptions.h>
#include <StringUtils.h>

namespace CasaEngine
{
	CException::CException(const std::string& Message) :
		m_Message(Message)
	{
	}

	CException::~CException() throw()
	{
	}

	const char* CException::what() const throw()
	{
		return m_Message.c_str();
	}

	CAssertException::CAssertException(const std::string& File, int Line, const std::string& Message) :
		CException(CStringBuilder(Message)(". ")(File)(" (")(Line)(")"))
	{
	}

	CBadDelete::CBadDelete(const void* Ptr, const std::string& File, int Line, bool NewArray) :
		CException(CStringBuilder("Bad des/allocation ")((NewArray ? "new[] / delete" : "new / delete[]"))(" found")(". ")("Memory address : 0x")(Ptr)("\nSource file : ")(File)(" (")(Line)(")"))
	{
	}

	CLoadingFailed::CLoadingFailed(const std::string& File, const std::string& Message) :
		CException(CStringBuilder("Loading error '")(File)("'. ")(Message))
	{
	}

	COutOfMemory::COutOfMemory(const std::string& Message) :
		CException(Message)
	{
	}

	CUnsupported::CUnsupported(const std::string& Feature) :
		CException(CStringBuilder("Unsupported functionality ")(Feature))
	{
	}

	CBadConversion::CBadConversion(const std::string& Error) :
		CException(Error)
	{
	}

	CArgumentNullException::CArgumentNullException(const std::string& Error) :
		CException(Error)
	{
	}

	CArgumentException::CArgumentException(const std::string& Error) :
		CException(Error)
	{
	}

	CArgumentOutOfRangeException::CArgumentOutOfRangeException(const std::string& Error) :
		CException(Error)
	{
	}

	CNotImplementedException::CNotImplementedException(const std::string& Error) :
		CException(Error)
	{
	}
}