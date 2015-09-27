
#ifndef IFILE_H
#define IFILE_H

#include "CA_Export.h"
#include <string>
#include "Memory\MemoryAllocation.h"

namespace CasaEngine
{
	namespace FileMode
	{
		enum TFileMode
		{
			READ		= 0x1,
			STREAM		= 0x2,
			WRITE		= 0x4,
			BINARY		= 0x8,
		};
	}

	namespace SeekDir
	{
		enum TSeekDir
		{
			SEEKDIR_SET, // Beginning of file
			SEEKDIR_CUR, // Current position of the file pointer
			SEEKDIR_END, // End of file
		};
	}

    /**
     * 
     */
	class CA_EXPORT IFile :
		public AllocatedObject<IFile>
    {
    public :

		/**
         * 
         */
        virtual ~IFile();

		/**
		 * 
		 */
		virtual bool Open(const char* fileName_, unsigned int mode_) = 0;
		
		/**
		 * 
		 */
		virtual bool Create(const char* fileName_, bool append_) = 0;
		
		/**
		 *
		 */
		virtual void Close() = 0;

		/**
		 * 
		 */
        virtual bool Exists() const = 0;

		/**
		 * 
		 */
        virtual int Read(char *dst_, unsigned int size_) = 0;
		
		/**
		 * 
		 */
        virtual int Write(char *data_, unsigned int size_) = 0;

		/**
		 * return the new position
		 */
		unsigned int Seek(unsigned int pos_);

		/**
		 * return the new position
		 */
		virtual unsigned int Seek(unsigned int off_, SeekDir::TSeekDir dir_) = 0;

		/**
		 *
		 */
		unsigned int Position() const;

		/**
		 * Get the buffer. Binary and null terminated
		 */
		char *GetBuffer();
		
		/**
		 * 
		 */
		unsigned int GetBufferLength();

        //----------------------------------------------------------
        // Renvoie le nom du fichier avec son chemin complet
        //----------------------------------------------------------
        const std::string& Fullname() const;

        //----------------------------------------------------------
        // Renvoie le nom du fichier sans son chemin
        //----------------------------------------------------------
        std::string Filename() const;

        //----------------------------------------------------------
        // Renvoie le nom du fichier sans extension ni chemin
        //----------------------------------------------------------
        std::string ShortFilename() const;

        //----------------------------------------------------------
        // Renvoie l'extension du fichier
        //----------------------------------------------------------
        std::string Extension() const;

    protected :

		/**
		 *
		 */
        IFile();
		IFile(const IFile& rsh);
		const IFile& operator = (const IFile& rsh);

		/**
		 * 
		 */
		virtual void FillBuffer() = 0;

		/**
		 * 
		 */
		void DestroyBuffer();

        std::string m_Name; ///< fullpath
		std::size_t m_BufferSize;
		char *m_pBuffer;
	};

} // namespace CasaEngine


#endif // IFILE_H
