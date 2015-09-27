
template<class T>
T* AssetManager::GetAsset(std::string name_)
{
	std::map<std::string, Asset *>::const_iterator asset = m_Assets.find(name_);
	CA_ASSERT(asset !=  m_Assets.end(),
		(CStringBuilder("AssetManager::GetAsset(): can't find the asset '")(name_)("'")).c_str() );
	return asset->second->GetAsset<T>();
}
