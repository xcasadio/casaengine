template <class T>
T *Game::GetGameComponent() const
{
	T* res = nullptr;

	for (auto* component : m_Components)
	{
		res = dynamic_cast<T*>(component);

		if (res != nullptr)
		{
			break;
		}
	}

	return res;
}
