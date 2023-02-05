#include "Base.h"

#include "MediaManager.h"

#include "IO/IOManager.h"
#include "IO/IFile.h"

#if CA_PLATFORM_WINDOWS
#	include <windows.h>
#endif

namespace CasaEngine
{
	MediaManager::MediaManager()
	{
#if CA_PLATFORM_WINDOWS

		m_Paths.insert("");

		char szDir[MAX_PATH + 1];
		DWORD dw = GetCurrentDirectory(MAX_PATH, szDir);
		if (dw == 0)
		{
			dw = GetLastError();
			// Handle error
		}

		m_RootPath.append(szDir);
		m_RootPath.append("\\");

#endif
	}

	void MediaManager::AddSearchPath(const char* path_)
	{
		std::string Path = path_;

		if (Path.empty() || *Path.rbegin() == '\\' || *Path.rbegin() == '/')
		{
			m_Paths.insert(Path);
		}
		else
		{
			m_Paths.insert(Path + "\\");
		}
	}

	IFile* MediaManager::FindMedia(const std::string& fileName_, bool isBinary_) const
	{
		return FindMedia(fileName_.c_str(), isBinary_);
	}

	IFile* MediaManager::FindMedia(const char* fileName_, bool isBinary_) const
	{
		for (auto dir : m_Paths)
		{
			std::string path = m_RootPath + dir + fileName_;
			//TODO : set if open in BINARY MODE or not
			IFile* pRetFile = IOManager::OpenFile(path, (unsigned int)FileMode::READ | (isBinary_ == true ? (unsigned int)FileMode::BINARY : 0));

			if (pRetFile->Exists() == true)
			{
				return pRetFile;
			}

			delete pRetFile;
		}

		return nullptr;
	}
}