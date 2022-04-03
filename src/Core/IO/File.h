#ifndef FILE_H
#define FILE_H

#include "CA_Export.h"
#include "IO/IFile.h"
#include <iosfwd>
#include <fstream>

namespace CasaEngine
{
	class CA_EXPORT File : public IFile
	{
	public:
		File();
		File(const File& rsh);
		const File& operator = (const File& rsh);

		~File();

		bool Open(const char* fileName_, unsigned int mode_) override;
		bool Create(const char* fileName_, bool append_) override;
		void Close() override;
		bool Exists() const override;
		int Read(char* dst_, unsigned int size_) override;
		int Write(char* data_, unsigned int size_) override;
		unsigned int Seek(unsigned int off_, SeekDir::TSeekDir dir_) override;

	protected:
		void FillBuffer() override;

	private:
		std::fstream m_Stream;
	};
}

#endif
