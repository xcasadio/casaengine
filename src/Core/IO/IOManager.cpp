#include "Base.h"

#include "IOManager.h"
#include "Log\LogManager.h"
#include "File.h"

#if CA_PLATFORM_ANDROID

#include "android/FileAsset.h"

#endif

namespace CasaEngine
{
#if CA_PLATFORM_ANDROID

	AAssetManager* IOManager::m_pAAssetManager(nullptr);

	/**
	 *
	 */
	void IOManager::SetAssetManager(AAssetManager* mgr)
	{
		CA_ASSERT(mgr != nullptr, "IOManager::SetAssetManager() : AAssetManager is nullptr");
		m_pAAssetManager = mgr;
	}

#endif

	/**
	 *
	 */
	IFile* IOManager::OpenFile(std::string& fileName_, unsigned int mode_)
	{
		return OpenFile(fileName_.c_str(), mode_);
	}

	/**
	 *
	 */
	IFile* IOManager::OpenFile(const char* fileName_, unsigned int mode_)
	{
		IFile* pRes = nullptr;

#if CA_PLATFORM_ANDROID
		CA_ASSERT(m_pAAssetManager != nullptr, "AAssetManager is not set.");
		pRes = new FileAsset(m_pAAssetManager);

		//mContext.getFilesDir(); //directory where the application is
		//mContext.getExternalFilesDir(null); // external SDCard
#else
		pRes = new File();
#endif

		pRes->Open(fileName_, mode_);
		return pRes;
	}

	/**
	 *
	 */
	IFile* IOManager::CreateFile(const std::string& Filename, bool append_)
	{
		IFile* pRes = new File();

		if (pRes->Create(Filename.c_str(), append_) == false)
		{
			delete pRes;
			pRes = nullptr;
		}

		return pRes;
	}
}