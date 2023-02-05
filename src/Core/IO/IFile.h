#pragma once

#include "CA_Export.h"
#include <string>

namespace CasaEngine
{
	enum class FileMode : unsigned int
	{
		READ = 0x1,
		STREAM = 0x2,
		WRITE = 0x4,
		BINARY = 0x8,
	};

	enum class SeekDir
	{
		SEEKDIR_SET, // Beginning of file
		SEEKDIR_CUR, // Current position of the file pointer
		SEEKDIR_END, // End of file
	};


	class CA_EXPORT IFile
	{
	public:
		virtual ~IFile();
		virtual bool Open(const char* fileName, unsigned int mode_) = 0;
		virtual bool Create(const char* fileName, bool append) = 0;
		virtual void Close() = 0;
		virtual bool Exists() const = 0;
		virtual int Read(char* dst, unsigned int size) = 0;
		virtual int Write(char* data, unsigned int size) = 0;
		unsigned int Seek(unsigned int pos);
		virtual unsigned int Seek(unsigned int off, SeekDir dir) = 0;
		unsigned int Position();
		char* GetBuffer();
		std::size_t GetBufferLength();
		const std::string& Fullname() const;
		std::string Filename() const;
		std::string ShortFilename() const;
		std::string Extension() const;

	protected:
		IFile();
		IFile(const IFile& rsh);
		IFile& operator = (const IFile& rsh);
		virtual void FillBuffer() = 0;
		void DestroyBuffer();

		std::string _fullPath;
		std::size_t _bufferSize;
		char* _buffer;
	};
}
