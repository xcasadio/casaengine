#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

#include <set>
#include <string>

#include "IO/IFile.h"
#include "Log/LogManager.h"

namespace CasaEngine
{
	class CA_EXPORT MediaManager
	{
	public:
		MediaManager();

		void AddSearchPath(const char* path_);

		IFile* FindMedia(const char* fileName_, bool isBinary_ = true) const;
		IFile* FindMedia(const std::string& fileName_, bool isBinary_ = true) const;

	private:
		std::set<std::string> m_Paths;
		std::string m_RootPath;
	};
}

#endif
