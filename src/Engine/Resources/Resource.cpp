#include "Base.h"

#include "Resources/Resource.h"
#include <Resources/ResourceManager.h>

#include "Game/Game.h"

namespace CasaEngine
{
	IResource::IResource() :
		m_Name(""),
		m_RefCount(1)
	{

	}

	IResource::~IResource()
	{
		if (m_Name != "")
			Game::Instance().GetResourceManager().Remove(m_Name);
	}
	
	const std::string& IResource::GetName() const
	{
		return m_Name;
	}

	void IResource::AddRef()
	{
		++m_RefCount;
	}

	int IResource::Release()
	{
		int RefCount = --m_RefCount;

		if (RefCount == 0)
			DELETE_AO this;

		return RefCount;
	}

}
