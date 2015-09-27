
template <class T>
T *Game::GetGameComponent() const
{
	T* res = nullptr;

	for (size_t i=0; i<m_Components.size(); i++)
	{
		res = dynamic_cast<T *>(m_Components[i]);

		if (res != nullptr)
		{
			break;
		}
	}

	return res;
}
