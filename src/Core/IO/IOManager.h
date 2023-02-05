#pragma once

#include "CA_Export.h"
#include "IFile.h"

#include <string>

#if CA_PLATFORM_ANDROID

#include <android/asset_manager.h>

#endif

namespace CasaEngine
{
	class CA_EXPORT IOManager
	{
	public:
		static IFile* OpenFile(const std::string& fileName, unsigned int mode);
		static IFile* OpenFile(const char* fileName, unsigned int mode);
		static IFile* CreateFile(const std::string& filename, bool append = false);

#if CA_PLATFORM_ANDROID
	public:
		static void SetAssetManager(AAssetManager* mgr);

	private:
		static AAssetManager* m_pAAssetManager;

#endif
	};
}
