#include  "IFile.hpp"
#include  "Exceptions.hpp"

namespace CasaEngine
{
	IFile::IFile() :
		_bufferSize(0),
		_buffer(nullptr)
	{
	}

	IFile::IFile(const IFile& rsh) :
		_bufferSize(0),
		_buffer(nullptr)
	{
		*this = rsh;
	}

	IFile& IFile::operator = (const IFile& rsh)
	{
		if (&rsh != this)
		{
			_fullPath = rsh._fullPath;

			if (rsh._bufferSize > 0 && rsh._buffer != nullptr)
			{
				FillBuffer();
			}
		}
		return *this;
	}

	IFile::~IFile()
	{
		DestroyBuffer();
	}

	char* IFile::GetBuffer()
	{
		if (_buffer == nullptr)
		{
			FillBuffer();
		}

		return _buffer;
	}

	std::size_t IFile::GetBufferLength()
	{
		if (_buffer == nullptr)
		{
			FillBuffer();
		}

		return _bufferSize;
	}

	void IFile::DestroyBuffer()
	{
		if (_buffer != nullptr)
		{
			delete[] _buffer;
			_buffer = nullptr;
		}
	}

	unsigned int IFile::Seek(const unsigned int pos)
	{
		return Seek(pos, SeekDir::SEEKDIR_SET);
	}

	unsigned int IFile::Position()
	{
		throw NotImplementedException("IFile::Position() not implemented");
	}

	const std::string& IFile::Fullname() const
	{
		return _fullPath;
	}

	std::string IFile::Filename() const
	{
		if (const std::string::size_type pos = _fullPath.find_last_of("\\/"); pos != std::string::npos)
		{
			return _fullPath.substr(pos + 1, std::string::npos);
		}

		return _fullPath;
	}

	std::string IFile::ShortFilename() const
	{
		return Filename().substr(0, Filename().find_last_of('.'));
	}

	std::string IFile::Extension() const
	{
		if (const std::string::size_type pos = _fullPath.find_last_of('.'); pos != std::string::npos)
		{
			return _fullPath.substr(pos + 1, std::string::npos);
		}
		return "";
	}
}