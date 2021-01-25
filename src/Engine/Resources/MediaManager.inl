#include "Log\LogManager.h"

template <class T>
inline void MediaManager::RegisterLoader(ILoader<T>* Loader, const char* Extensions)
{
	std::vector<std::string> Ext;
	Split(Extensions, Ext, " /\\*.,;|-_\t\n'\"");

	ILoader<T>* Ptr = Loader;
	for (std::vector<std::string>::iterator i = Ext.begin(); i != Ext.end(); ++i)
	{
		CMediaHolder<T>::m_Loaders[ToLower(*i)] = Ptr;
	}
}

template <class T>
inline void MediaManager::UnregisterLoader(const std::string& Extensions)
{
	std::vector<std::string> Ext;
	Split(Extensions, Ext, " /\\*.,;|-_\t\n'\"");

	for (std::vector<std::string>::iterator i = Ext.begin(); i != Ext.end(); ++i)
		CMediaHolder<T>::m_Loaders.erase(ToLower(*i));
}

template <class T>
inline T* MediaManager::LoadMediaFromFile(const std::string& Filename, unsigned int mode_) const
{
	IFile* MediaPath = FindMedia(Filename, mode_);

	if (MediaPath == nullptr)
	{
		throw CLoadingFailed(Filename, "MediaManager::LoadMediaFromFile() : Can't find the file (maybe add a reference to the right directory ?)");
	}

	T* Media = FindLoader<T>(MediaPath).LoadFromFile(MediaPath);

	if (Media == nullptr)
	{
		CA_DEBUG("Error when load the resource: '%s'\n", MediaPath->Fullname().c_str());
	}
	else
	{
		CA_DEBUG("Resource loaded : '%s'\n", MediaPath->Fullname().c_str());
		DELETE_AO MediaPath; // TODO : crash if called
	}

	return Media;
}

template <class T>
inline void MediaManager::SaveMediaToFile(const T* Object, const IFile* Filename) const
{
	FindLoader<T>(Filename).SaveToFile(Object, Filename->Fullname());

	CA_DEBUG("Resource saved : %s\n", Filename->Fullname().c_str());
}

template <class T>
inline ILoader<T>& MediaManager::FindLoader(const IFile* Filename) const
{
	typename CMediaHolder<T>::TLoadersMap::const_iterator It =
		CMediaHolder<T>::m_Loaders.find(ToLower(Filename->Extension()));

	if ((It != CMediaHolder<T>::m_Loaders.end()) && It->second)
		return *It->second;

	throw CLoadingFailed(Filename->Fullname(), "No loader found for this type of file");
}