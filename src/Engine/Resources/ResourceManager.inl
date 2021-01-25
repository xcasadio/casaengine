template <class T>
inline T* ResourceManager::Get(const char* pName_) const
{
	std::string name = pName_;
	TResourcesMap::const_iterator It = m_Resources.find(name);

	if (It != m_Resources.end())
	{
		It->second->AddRef();
		return static_cast<T*>(It->second);
	}
	return nullptr;
}