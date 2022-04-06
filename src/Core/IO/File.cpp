#include "Base.h"
#include "Log/LogManager.h"

#include "File.h"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace CasaEngine
{
	File::File(const File& rsh)
		: IFile(rsh)
	{
		*this = rsh;
	}

	File& File::operator = (const File& rsh)
	{
		m_Name = rsh.m_Name;
		return *this;
	}

	File::~File()
	{
		File::Close();
	}

	/**
	 * /param mode default is std::ifstream::in
	 * all mode :
	 * in		input		File open for reading: the internal stream buffer supports input operations.
	 * out		output		File open for writing: the internal stream buffer supports output operations.
	 * binary	binary		Operations are performed in binary mode rather than text.
	 * ate		at end		The output position starts at the end of the file.
	 * app		append		All output operations happen at the end of the file, appending to its existing contents.
	 * trunc	truncate	Any contents that existed in the file before it is open are discarded.
	 */
	bool File::Open(const char* fileName_, unsigned int mode_)
	{
		unsigned int stdMode = 0;
		stdMode |= (mode_ & (unsigned int)FileMode::READ) == (unsigned int)FileMode::READ ? std::ios::in : 0;
		stdMode |= (mode_ & (unsigned int)FileMode::WRITE) == (unsigned int)FileMode::WRITE ? std::ios::out : 0;
		stdMode |= (mode_ & (unsigned int)FileMode::BINARY) == (unsigned int)FileMode::BINARY ? std::ios::binary : 0;

		m_Name = fileName_;
		std::replace(m_Name.begin(), m_Name.end(), '/', '\\');

		if (m_Stream.is_open() == true)
		{
			m_Stream.close();
		}

		m_Stream.open(m_Name.c_str(), static_cast<std::ios_base::openmode>(stdMode));
		return m_Stream.is_open();
	}

	bool File::Create(const char* fileName_, bool append_)
	{
		std::ios_base::openmode stdMode = std::ios::out | std::ios::binary;
		stdMode |= append_ == true ? std::ios::app : std::ios::trunc;

		m_Name = fileName_;
		std::replace(m_Name.begin(), m_Name.end(), '/', '\\');

		m_Stream.open(m_Name.c_str(), stdMode);
		return m_Stream.is_open();
	}

	void File::Close()
	{
		if (m_Stream.is_open() == true)
		{
			m_Stream.flush();
			m_Stream.close();
			DestroyBuffer();
		}
	}

	void File::FillBuffer()
	{
		std::filebuf* pbuf = m_Stream.rdbuf();

		//m_BufferSize = static_cast<std::size_t>(pbuf->pubseekoff (0, m_Stream.end, m_Stream.in));
		//pbuf->pubseekpos (0, m_Stream.in);
		m_BufferSize = static_cast<std::size_t>(pbuf->pubseekoff(0, m_Stream.end));
		pbuf->pubseekpos(0);

		m_pBuffer = ::new char[m_BufferSize + 1];
		memset(m_pBuffer, 0, m_BufferSize);
		pbuf->sgetn(m_pBuffer, m_BufferSize);
		m_pBuffer[m_BufferSize] = '\0';

		/*m_Stream.seekg(0, m_Stream.end);
		m_BufferSize = m_Stream.tellg();
		m_Stream.seekg(0, m_Stream.beg);

		m_pBuffer = new char[m_BufferSize];
		m_Stream.read(m_pBuffer, m_BufferSize);*/

		/*std::ifstream file(fileName_, std::ios::binary);
		m_Stream.seekg(0, std::ios::end);
		m_BufferSize = m_Stream.tellg();
		m_Stream.seekg(0, std::ios::beg);

		//std::vector<char> buffer(size);
		//if (m_Stream.read(buffer.data(), m_Stream))
		char *pBuffer = new char[m_Stream];
		if (m_Stream.read(pBuffer, m_Stream))
		{
			m_Stream.rdbuf()->pubsetbuf(pBuffer, size);
		}*/

		//====================================
	}

	bool File::Exists() const
	{
		return m_Stream.is_open();
	}

	int File::Read(char* dst_, unsigned int size_)
	{
		CA_ASSERT(m_Stream.is_open() == true, "Try to read a file which is not opened");
		m_Stream.read(dst_, size_);
		return size_;
	}

	int File::Write(char* data_, unsigned int size_)
	{
		CA_ASSERT(m_Stream.is_open() == true, "Try to write a file which is not opened");
		m_Stream.write(data_, size_);
		return size_;
	}

	unsigned int File::Seek(unsigned int off_, SeekDir dir_)
	{
		CA_ASSERT(m_Stream.is_open() == true, "Try to read a file which is not opened");
		std::ios::seekdir dir;

		switch (dir_)
		{
		case SeekDir::SEEKDIR_SET:
			dir = std::ios::beg;
			break;

		case SeekDir::SEEKDIR_CUR:
			dir = std::ios::cur;
			break;

		case SeekDir::SEEKDIR_END:
			dir = std::ios::end;
			break;

		default:
			dir = std::ios::beg;
			break;
		}

		m_Stream.seekg(off_, dir);
		return m_Stream.tellg();
	}
}