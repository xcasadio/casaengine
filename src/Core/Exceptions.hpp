#pragma once

#include "CA_Export.hpp"
#include <exception>
#include <string>

namespace CasaEngine
{
	class CA_EXPORT Exception :
		public std::exception
	{
	public:
		Exception(std::string message = "");
		~Exception() noexcept override;
		Exception(const Exception& rsh) = default;
		Exception& operator=(const Exception& rsh) = default;
		Exception(Exception&& rsh) = default;
		Exception& operator=(Exception&& rsh) = default;

		const char* what() const noexcept override;

	private:
		std::string m_Message;
	};

	struct CA_EXPORT AssertException : Exception
	{
		AssertException(const std::string& file, int line, const std::string& message);
	};

	struct CA_EXPORT BadDelete : Exception
	{
		BadDelete(const void* ptr, const std::string& file, int line, bool new_array);
	};

	struct CA_EXPORT LoadingFailed : Exception
	{
		LoadingFailed(const std::string& file, const std::string& message);
	};

	struct CA_EXPORT OutOfMemory : Exception
	{
		OutOfMemory(const std::string& message);
	};

	struct CA_EXPORT Unsupported : Exception
	{
		Unsupported(const std::string& feature);
	};

	struct CA_EXPORT BadConversion : Exception
	{
		BadConversion(const std::string& error);
	};

	struct CA_EXPORT ArgumentNullException : Exception
	{
		ArgumentNullException(const std::string& error);
	};

	struct CA_EXPORT ArgumentException : Exception
	{
		ArgumentException(const std::string& error);
	};

	struct CA_EXPORT ArgumentOutOfRangeException : Exception
	{
		ArgumentOutOfRangeException(const std::string& error);
	};

	struct CA_EXPORT NotImplementedException : Exception
	{
		NotImplementedException(const std::string& error);
	};
}
