#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "CA_Export.h"
#include <exception>
#include <string>

namespace CasaEngine
{
	class CA_EXPORT CException :
		public std::exception
	{
	public:
		CException(const std::string& Message = "");
		virtual ~CException() throw();
		const char* what() const throw() override;

	private:
		std::string m_Message;
	};

	struct CA_EXPORT CAssertException : public CException
	{
		CAssertException(const std::string& File, int Line, const std::string& Message);
	};

	struct CA_EXPORT CBadDelete : public CException
	{
		CBadDelete(const void* Ptr, const std::string& File, int Line, bool NewArray);
	};

	struct CA_EXPORT CLoadingFailed : public CException
	{
		CLoadingFailed(const std::string& File, const std::string& Message);
	};

	struct CA_EXPORT COutOfMemory : public CException
	{
		COutOfMemory(const std::string& Message);
	};

	struct CA_EXPORT CUnsupported : public CException
	{
		CUnsupported(const std::string& Feature);
	};

	struct CA_EXPORT CBadConversion : public CException
	{
		CBadConversion(const std::string& Error);
	};

	struct CA_EXPORT CArgumentNullException : public CException
	{
		CArgumentNullException(const std::string& Error);
	};

	struct CA_EXPORT CArgumentException : public CException
	{
		CArgumentException(const std::string& Error);
	};

	struct CA_EXPORT CArgumentOutOfRangeException : public CException
	{
		CArgumentOutOfRangeException(const std::string& Error);
	};

	struct CA_EXPORT CNotImplementedException : public CException
	{
		CNotImplementedException(const std::string& Error);
	};
}

#endif
