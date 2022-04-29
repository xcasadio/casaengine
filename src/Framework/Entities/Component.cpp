#include "Base.h"
#include "Log/LogManager.h"
#include "Component.h"
#include "BaseEntity.h"

#include "CA_Assert.h"

namespace CasaEngine
{
	Component::Component(BaseEntity* entity, int type)
	{
		CA_ASSERT(entity != nullptr, "Component::Component() : BaseEntity is nullptr");
		m_pEntity = entity;
		m_Type = type;
	}

	Component::~Component() = default;

	BaseEntity* Component::GetEntity()
	{
		return m_pEntity;
	}

	bool Component::HandleMessage(const Telegram& /*msg*/)
	{
		return false;
	}

	void Component::Draw()
	{
	}

	int Component::Type() const
	{
		return m_Type;
	}

#if EDITOR
	void Component::ShowDebugWidget()
	{
	}
#endif
}
