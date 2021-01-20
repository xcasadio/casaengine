#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

#include <algorithm>
#include <cctype>
#include <map>
#include <set>
#include <string>


#include "GenHierarchies.h"
#include "IO/IFile.h"
#include "StringUtils.h"

#include "Loaders/Loader.h"
#include "Graphics/Mesh/Mesh.h"

#include "Exceptions.h"
#include "Log/Logger.h"
#include "Log/LogManager.h"
#include "Parsers/Xml/tinyxml2.h"

namespace CasaEngine
{
	typedef TYPELIST_2(Mesh, tinyxml2::XMLDocument) MediaList;

	template <class T>
	struct CMediaHolder
	{
		typedef std::map<std::string, ILoader<T>*> TLoadersMap;
		TLoadersMap m_Loaders;
	};

	class CA_EXPORT MediaManager :
		public CScatteredHierarchy<MediaList, CMediaHolder>
	{
	public:
		MediaManager();
		
		void AddSearchPath(const char* path_);
		template <class T> void RegisterLoader(ILoader<T>* Loader, const char* Extensions);
		template <class T> void UnregisterLoader(const std::string& Extensions);
		template <class T> T* LoadMediaFromFile(const std::string& Filename, unsigned int mode_) const;
		template <class T> void SaveMediaToFile(const T* Object, const IFile* Filename) const;

		/**
		 * Search a file in all registered directories
		 * @return nullptr if the file doesn't exist in all registered directories
		 */
		IFile* FindMedia(const char* fileName_, bool isBinary_ = true) const;

		/**
		 * Search a file in all registered directories
		 * @return nullptr if the file doesn't exist in all registered directories
		 */
		IFile* FindMedia(const std::string& fileName_, bool isBinary_ = true) const;

	private:
		template <class T> ILoader<T>& FindLoader(const IFile* Filename) const;

		std::set<std::string> m_Paths;
		std::string m_RootPath;
	};

#include "MediaManager.inl"
}

#endif
