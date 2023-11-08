#include <Exceptions.hpp>
#include <StringUtils.hpp>

namespace CasaEngine
{
	Exception::Exception(std::string message) :
		m_Message(std::move(message))
	{
	}

	Exception::~Exception() noexcept
		= default;

	const char* Exception::what() const noexcept
	{
		return m_Message.c_str();
	}

	AssertException::AssertException(const std::string& file, int line, const std::string& message) :
		Exception(CStringBuilder(message)(". ")(file)(" (")(line)(")"))
	{
	}

	BadDelete::BadDelete(const void* ptr, const std::string& file, int line, bool new_array) :
		Exception(CStringBuilder("Bad des/allocation ")(new_array ? "new[] / delete" : "new / delete[]")(" found")(". ")("Memory address : 0x")(ptr)("\nSource file : ")(file)(" (")(line)(")"))
	{
	}

	LoadingFailed::LoadingFailed(const std::string& file, const std::string& message) :
		Exception(CStringBuilder("Loading error '")(file)("'. ")(message))
	{
	}

	OutOfMemory::OutOfMemory(const std::string& message) :
		Exception(message)
	{
	}

	Unsupported::Unsupported(const std::string& feature) :
		Exception(CStringBuilder("Unsupported functionality ")(feature))
	{
	}

	BadConversion::BadConversion(const std::string& error) :
		Exception(error)
	{
	}

	ArgumentNullException::ArgumentNullException(const std::string& error) :
		Exception(error)
	{
	}

	ArgumentException::ArgumentException(const std::string& error) :
		Exception(error)
	{
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException(const std::string& error) :
		Exception(error)
	{
	}

	NotImplementedException::NotImplementedException(const std::string& error) :
		Exception(error)
	{
	}
}