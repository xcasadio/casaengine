#pragma once

#include "CA_Export.hpp"
#include  "IO/IFile.hpp"
#include <iosfwd>
#include <fstream>

namespace CasaEngine
{
	class CA_EXPORT File : public IFile
	{
	public:
		File() = default;
		File(const File& rsh);
		File& operator = (const File& rsh);

		~File() override;

		bool Open(const char* fileName, unsigned int mode) override;
		bool Create(const char* fileName, bool append) override;
		void Close() override;
		bool Exists() const override;
		int Read(char* dst, unsigned int size) override;
		int Write(char* data, unsigned int size) override;
		unsigned int Seek(unsigned int off, SeekDir dir) override;

	protected:
		void FillBuffer() override;

	private:
		std::fstream _stream;
	};
}
