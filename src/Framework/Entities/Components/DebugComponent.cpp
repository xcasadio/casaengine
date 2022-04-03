#include "Entities/BaseEntity.h"

#include "DebugComponent.h"

#include "Transform3DComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"
#include "Game/Line3DRendererComponent.h"

namespace CasaEngine
{
	DebugComponent::DebugComponent(BaseEntity* pEntity_)
		: Component(pEntity_, DEBUG_INFO),
		m_DisplayPosition(false),
		m_LineRenderer(nullptr)
	{
	}

	void DebugComponent::Initialize()
	{
		m_LineRenderer = Game::Instance().GetGameComponent<Line3DRendererComponent>();
		CA_ASSERT(m_LineRenderer != nullptr, "DebugComponent : Line3DRendererComponent is null")
	}

	void DebugComponent::Update(const GameTime& gameTime_)
	{
	}

	void DebugComponent::Draw()
	{
		if (m_DisplayPosition)
		{
			const auto position = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>()->GetLocalPosition();
			const auto color = CColor::Red;
			constexpr auto scale = 5.0f;
			m_LineRenderer->AddLine(position - Vector3F::UnitX() * scale, position + Vector3F::UnitX() * scale, color);
			m_LineRenderer->AddLine(position - Vector3F::UnitY() * scale, position + Vector3F::UnitY() * scale, color);
			m_LineRenderer->AddLine(position - Vector3F::UnitZ() * scale, position + Vector3F::UnitZ() * scale, color);
		}
	}

	bool DebugComponent::DisplayPosition() const
	{
		return m_DisplayPosition;
	}

	void DebugComponent::DisplayPosition(bool val)
	{
		m_DisplayPosition = val;
	}
}
