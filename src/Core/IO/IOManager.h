
#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "CA_Export.h"
#include "IFile.h"
#include "Memory/MemoryAllocatedObject.h"

#include <string>

#if CA_PLATFORM_ANDROID

#include <android/asset_manager.h>

#endif


namespace CasaEngine
{
    /**
     * 
     */
	class CA_EXPORT IOManager :
		public AllocatedObject<IOManager>
    {
    public :

		/**
		 * 
		 */
		static IFile *OpenFile(std::string &fileName_, unsigned int mode_);
		
		/**
		 * 
		 */
		static IFile *OpenFile(const char *fileName_, unsigned int mode_);

		/**
		 * 
		 */
		static IFile *CreateFile( const std::string& filename_, bool append_ = false);

#if CA_PLATFORM_ANDROID

		/**
		 * 
		 */
		static void SetAssetManager(AAssetManager* mgr);

#endif

    private :

        IOManager();

#if CA_PLATFORM_ANDROID

		/**
		 * 
		 */
		static AAssetManager* m_pAAssetManager;

#endif
	};

} // namespace CasaEngine


#endif // IOMANAGER_H
