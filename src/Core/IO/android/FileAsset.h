
#ifndef FILEASSET_H
#define FILEASSET_H


#include "CA_Export.h"
#include "IO/IFile.h"

#include <android/asset_manager.h>
#include <string>

namespace CasaEngine
{
    /**
	 * Handle an AAsset
	 */
    class CA_Export FileAsset : public IFile
    {
    public :

		/**
		 *
		 */
        FileAsset(AAssetManager *pMgr_);
		
		/**
		 *
		 */
		FileAsset(const FileAsset& rsh);
		
		/**
		 *
		 */
		const FileAsset& operator = (const FileAsset& rsh);

		/**
         * 
         */
        ~FileAsset();

		/**
		 * 
		 */
		bool Open( const char* fileName_, unsigned int mode_ );


		/**
		 * 
		 */
		bool Create(const char* fileName_, bool append_);
		
		/**
		 *
		 */
		void Close();
		
		/**
		 *
		 */
		void FillBuffer();

        /**
         * 
         */
        bool Exists() const;

		/**
		 * 
		 */
		int Read(char *dst_, unsigned int size_);
		
		/**
		 * 
		 */
		int Write(char *data_, unsigned int size_);
		
		/**
		 * 
		 */
		unsigned int Seek(unsigned int off_, SeekDir::TSeekDir dir_);

    private :
		AAssetManager *m_pAAssetManager;
		AAsset *m_pAAsset;
	};

} // namespace CasaEngine


#endif // FILEASSET_H
