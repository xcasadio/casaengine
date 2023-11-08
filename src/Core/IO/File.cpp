#include  "Base.hpp"
#include  "Log/LogManager.hpp"

#include  "File.hpp"

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
		_fullPath = rsh._fullPath;
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
	bool File::Open(const char* fileName, unsigned int mode)
	{
		unsigned int stdMode = 0;
		stdMode |= (mode & (unsigned int)FileMode::READ) == (unsigned int)FileMode::READ ? std::ios::in : 0;
		stdMode |= (mode & (unsigned int)FileMode::WRITE) == (unsigned int)FileMode::WRITE ? std::ios::out : 0;
		stdMode |= (mode & (unsigned int)FileMode::BINARY) == (unsigned int)FileMode::BINARY ? std::ios::binary : 0;

		_fullPath = fileName;
		std::replace(_fullPath.begin(), _fullPath.end(), '/', '\\');

		if (_stream.is_open() == true)
		{
			_stream.close();
		}

		_stream.open(_fullPath.c_str(), static_cast<std::ios_base::openmode>(stdMode));
		return _stream.is_open();
	}

	bool File::Create(const char* fileName, bool append)
	{
		std::ios_base::openmode stdMode = std::ios::out | std::ios::binary;
		stdMode |= append == true ? std::ios::app : std::ios::trunc;

		_fullPath = fileName;
		std::replace(_fullPath.begin(), _fullPath.end(), '/', '\\');

		_stream.open(_fullPath.c_str(), stdMode);
		return _stream.is_open();
	}

	void File::Close()
	{
		if (_stream.is_open() == true)
		{
			_stream.flush();
			_stream.close();
			DestroyBuffer();
		}
	}

	void File::FillBuffer()
	{
		std::filebuf* filebuf = _stream.rdbuf();

		//_bufferSize = static_cast<std::size_t>(pbuf->pubseekoff (0, m_Stream.end, m_Stream.in));
		//pbuf->pubseekpos (0, m_Stream.in);
		_bufferSize = static_cast<std::size_t>(filebuf->pubseekoff(0, std::fstream::end));
		filebuf->pubseekpos(0);

		_buffer = ::new char[_bufferSize + 1];
		memset(_buffer, 0, _bufferSize);
		filebuf->sgetn(_buffer, _bufferSize);
		_buffer[_bufferSize] = '\0';

		/*m_Stream.seekg(0, m_Stream.end);
		_bufferSize = m_Stream.tellg();
		m_Stream.seekg(0, m_Stream.beg);

		_buffer = new char[_bufferSize];
		m_Stream.read(_buffer, _bufferSize);*/

		/*std::ifstream file(fileName_, std::ios::binary);
		m_Stream.seekg(0, std::ios::end);
		_bufferSize = m_Stream.tellg();
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
		return _stream.is_open();
	}

	int File::Read(char* dst, unsigned int size)
	{
		CA_ASSERT(_stream.is_open() == true, "Try to read a file which is not opened");
		_stream.read(dst, size);
		return size;
	}

	int File::Write(char* data_, unsigned int size)
	{
		CA_ASSERT(_stream.is_open() == true, "Try to write a file which is not opened");
		_stream.write(data_, size);
		return size;
	}

	unsigned int File::Seek(const unsigned int off, SeekDir dir)
	{
		CA_ASSERT(_stream.is_open() == true, "Try to read a file which is not opened");
		std::ios::seekdir seekDir = std::ios::beg;

		switch (dir)
		{
		case SeekDir::SEEKDIR_SET:
			seekDir = std::ios::beg;
			break;

		case SeekDir::SEEKDIR_CUR:
			seekDir = std::ios::cur;
			break;

		case SeekDir::SEEKDIR_END:
			seekDir = std::ios::end;
			break;
		}

		_stream.seekg(off, seekDir);
		return static_cast<long>(_stream.tellg());
	}
}