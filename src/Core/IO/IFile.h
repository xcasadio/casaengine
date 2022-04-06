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
		virtual bool Open(const char* fileName_, unsigned int mode_) = 0;
		virtual bool Create(const char* fileName_, bool append_) = 0;
		virtual void Close() = 0;
		virtual bool Exists() const = 0;
		virtual int Read(char* dst_, unsigned int size_) = 0;
		virtual int Write(char* data_, unsigned int size_) = 0;
		unsigned int Seek(unsigned int pos_);
		virtual unsigned int Seek(unsigned int off_, SeekDir dir_) = 0;
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

		std::string m_Name; ///< fullpath
		std::size_t m_BufferSize;
		char* m_pBuffer;
	};
}
