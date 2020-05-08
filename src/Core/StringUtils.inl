inline void Split(const std::string& String, std::vector<std::string>& Tokens, const std::string& Delim)
{
    Tokens.clear();

    for (std::string::size_type p1 = 0, p2 = 0; p1 != std::string::npos; )
    {
        p1 = String.find_first_not_of(Delim, p1);
        if (p1 != std::string::npos)
        {
            p2 = String.find_first_of(Delim , p1);
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


inline CStringBuilder::CStringBuilder()
{

}

template <typename T>
inline CStringBuilder::CStringBuilder(const T& Value)
{
    m_OutStream << Value;
}

template <typename T>
inline CStringBuilder& CStringBuilder::operator ()(const T& Value)
{
    m_OutStream << Value;
    return *this;
}

inline CStringBuilder::operator std::string()
{
    return m_OutStream.str();
}

inline const char* CStringBuilder::c_str()
{
	return m_OutStream.str().c_str();
}


inline CStringExtractor::CStringExtractor(const std::string& Text) :
m_InStream(Text)
{

}

template <typename T>
inline CStringExtractor& CStringExtractor::operator ()(T& Value)
{
    if (!(m_InStream >> std::boolalpha >> Value))
    {
		if (m_InStream.eof())
			throw CBadConversion("Try to extract a value with an empty string");
		else
			throw CBadConversion("Can't convert a \"string\" to a certain type");
    }

    return *this;
}

inline void CStringExtractor::ThrowIfEOF()
{
    std::string Left;
    if (std::getline(m_InStream, Left))
        throw CBadConversion("String too long, \"" + Left + "\" has not been extracted");
}
