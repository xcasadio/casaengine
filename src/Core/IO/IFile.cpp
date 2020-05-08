#include "Base.h"

#include "IFile.h"
#include "Exceptions.h"

namespace CasaEngine
{
	IFile::IFile() :
		m_BufferSize(0),
		m_pBuffer(nullptr)
	{

	}

	IFile::IFile(const IFile& rsh) :
		m_BufferSize(0),
		m_pBuffer(nullptr)
	{
		*this = rsh;
	}

	const IFile& IFile::operator = (const IFile& rsh)
	{
		m_Name = rsh.m_Name;

		if (rsh.m_BufferSize > 0 && rsh.m_pBuffer != nullptr)
		{
			FillBuffer();
		}

		return *this;
	}

	IFile::~IFile()
	{
		DestroyBuffer();
	}

	char* IFile::GetBuffer()
	{
		if (m_pBuffer == nullptr)
		{
			FillBuffer();
		}

		return m_pBuffer;
	}

	unsigned int IFile::GetBufferLength()
	{
		if (m_pBuffer == nullptr)
		{
			FillBuffer();
		}

		return m_BufferSize;
	}

	void IFile::DestroyBuffer()
	{
		if (m_pBuffer != nullptr)
		{
			delete[] m_pBuffer;
			m_pBuffer = nullptr;
		}
	}

	unsigned int IFile::Seek(unsigned int pos_)
	{
		return Seek(pos_, SeekDir::SEEKDIR_SET);
	}

	unsigned int IFile::Position()
	{
		throw CNotImplementedException("IFile::Position() not implemented");
	}

	const std::string& IFile::Fullname() const
	{
		return m_Name;
	}

	std::string IFile::Filename() const
	{
		std::string::size_type Pos = m_Name.find_last_of("\\/");

		if (Pos != std::string::npos)
		{
			return m_Name.substr(Pos + 1, std::string::npos);
		}

		return m_Name;
	}

	std::string IFile::ShortFilename() const
	{
		return Filename().substr(0, Filename().find_last_of("."));
	}

	std::string IFile::Extension() const
	{
		std::string::size_type Pos = m_Name.find_last_of(".");
		if (Pos != std::string::npos)
			return m_Name.substr(Pos + 1, std::string::npos);
		return "";
	}

}
