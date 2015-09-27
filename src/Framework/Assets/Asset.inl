

template<class T>
T* Asset::GetAsset()
{
	if (m_pObject == nullptr)
	{
		LoadAsset();
	}

	CA_ASSERT(m_pObject != nullptr, "Asset::GetAsset() : can't load the asset %s", GetName().c_str());

	T* val = dynamic_cast<T*>(m_pObject);
	CA_ASSERT(val != nullptr, "Asset::GetAsset() : the asset '%s' is not type of ", GetName().c_str(), typeid(T).name());
	return val;
}
