#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <ios>
#include <algorithm>
#include "Exceptions.h"

namespace CasaEngine
{
	void Split(const std::string& String, std::vector<std::string>& Tokens, const std::string& Delim = " \t\n");
	unsigned long StringHash(const std::string& String);
	std::string ToLower(const std::string& Text);
	std::string ToUpper(const std::string& Text);

	class CStringBuilder
	{
	public:
		template <typename T> CStringBuilder(const T& Value);
		template <typename T> CStringBuilder& operator ()(const T& Value);

		operator std::string() const;

	private:
		std::ostringstream m_OutStream;
	};

	template <typename T>
	CStringBuilder::CStringBuilder(const T& Value)
	{
		m_OutStream << Value;
	}

	template <typename T>
	CStringBuilder& CStringBuilder::operator ()(const T& Value)
	{
		m_OutStream << Value;
		return *this;
	}

	inline CStringBuilder::operator std::string() const
	{
		return m_OutStream.str();
	}

	/*****************************************************/

	class CStringExtractor
	{
	public:
		CStringExtractor(const std::string& Text);
		template <typename T> CStringExtractor& operator ()(T& Value);
		void ThrowIfEOF();

	private:
		std::istringstream m_InStream;
	};
	inline CStringExtractor::CStringExtractor(const std::string& Text) :
		m_InStream(Text)
	{
	}

	template <typename T>
	CStringExtractor& CStringExtractor::operator ()(T& Value)
	{
		if (!(m_InStream >> std::boolalpha >> Value))
		{
			if (m_InStream.eof())
			{
				throw BadConversion("Try to extract a value with an empty string");
			}
			throw BadConversion("Can't convert a \"string\" to a certain type");
		}

		return *this;
	}

	inline void CStringExtractor::ThrowIfEOF()
	{
		std::string Left;
		if (std::getline(m_InStream, Left))
			throw BadConversion("String too long, \"" + Left + "\" has not been extracted");
	}

	/**********************************************/

	inline void Split(const std::string& String, std::vector<std::string>& Tokens, const std::string& Delim)
	{
		Tokens.clear();

		for (std::string::size_type p1 = 0, p2 = 0; p1 != std::string::npos; )
		{
			p1 = String.find_first_not_of(Delim, p1);
			if (p1 != std::string::npos)
			{
				p2 = String.find_first_of(Delim, p1);
				Tokens.push_back(String.substr(p1, p2 - p1));
				p1 = p2;
			}
		}
	}

	inline unsigned long StringHash(const std::string& String)
	{
		unsigned long Ret = 0;
		for (std::string::const_iterator i = String.begin(); i != String.end(); ++i)
		{
			Ret = 5 * Ret + *i;
		}

		return Ret;
	}

	inline std::string ToLower(const std::string& Text)
	{
		std::string Ret(Text.size(), ' ');
		std::transform(Text.begin(), Text.end(), Ret.begin(), static_cast<int (*)(int)>(std::tolower));
		return Ret;
	}

	inline std::string ToUpper(const std::string& Text)
	{
		std::string Ret(Text.size(), ' ');
		std::transform(Text.begin(), Text.end(), Ret.begin(), static_cast<int (*)(int)>(std::toupper));
		return Ret;
	}
}
