#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <algorithm>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <ios>
#include "Exceptions.h"

#include "Memory\MemoryAllocation.h"

namespace CasaEngine
{
	void Split(const std::string& String, std::vector<std::string>& Tokens, const std::string& Delim = " \t\n");
	unsigned long StringHash(const std::string& String);
	std::string ToLower(const std::string& Text);
	std::string ToUpper(const std::string& Text);

	class CStringBuilder :
		public AllocatedObject<CStringBuilder>
	{
	public:
		CStringBuilder();
		template <typename T> CStringBuilder(const T& Value);
		template <typename T> CStringBuilder& operator ()(const T& Value);

		operator std::string();
		const char* c_str();

	private:
		std::ostringstream m_OutStream;
	};

	class CStringExtractor :
		public AllocatedObject<CStringBuilder>
	{
	public:
		CStringExtractor(const std::string& Text);
		template <typename T> CStringExtractor& operator ()(T& Value);
		void ThrowIfEOF();

	private:
		std::istringstream m_InStream;
	};

#include "StringUtils.inl"
}

#endif
