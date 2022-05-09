#include "Entities/BaseEntity.h"

#include "DebugComponent.h"

#include "AnimatedSpriteComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"
#include "Game/Line3DRendererComponent.h"

namespace CasaEngine
{
	DebugComponent::DebugComponent(BaseEntity* pEntity_)
		: Component(pEntity_, DEBUG_INFO),
		m_DisplayPosition(false),
		m_DisplayAnimation2DCollisions(false),
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
			const auto position = GetEntity()->GetCoordinates().GetWorldMatrix().Translation();
			const auto color = Color::Red;
			constexpr auto scale = 50.0f / 2.0f;
			m_LineRenderer->AddLine(position - Vector3::UnitX() * scale, position + Vector3::UnitX() * scale, color);
			m_LineRenderer->AddLine(position - Vector3::UnitY() * scale, position + Vector3::UnitY() * scale, color);
			m_LineRenderer->AddLine(position - Vector3::UnitZ() * scale, position + Vector3::UnitZ() * scale, color);
		}

		if (m_DisplayAnimation2DCollisions)
		{
			const auto animated_sprite_component = GetEntity()->GetComponentMgr()->GetComponent<AnimatedSpriteComponent>();

			if (animated_sprite_component != nullptr)
			{
				auto* anim = animated_sprite_component->GetCurrentAnimation();
				if (anim != nullptr)
				{
					//anim->GetName()
					if (Game::Instance().GetAssetManager().Contains(anim->CurrentFrame()))
					{
						auto* spriteData = Game::Instance().GetAssetManager().GetAsset<SpriteData>(anim->CurrentFrame());
						auto* line3DRenderer = Game::Instance().GetGameComponent<Line3DRendererComponent>();

						for (auto coll : spriteData->GetCollisions())
						{
							if (coll.GetShape()->Type() == ShapeType::RECTANGLE)
							{
								auto* rect = dynamic_cast<RectangleI*>(coll.GetShape());
								auto color = coll.GetType() == CollisionHitType::Defense ? Color::Blue : Color::Red;
								auto pos = GetEntity()->GetCoordinates().GetWorldMatrix().Translation();
								const auto scaleX = GetEntity()->GetCoordinates().GetLocalScale().x;
								const auto scaleY = GetEntity()->GetCoordinates().GetLocalScale().y;
								auto rectScaled = RectangleI(
									(rect->x - spriteData->GetOrigin().x) * scaleX ,
									(rect->y - spriteData->GetOrigin().y) * scaleY,
									rect->w * scaleX, 
									rect->h * scaleY);

								auto leftTop = Vector3(rectScaled.Left(), rectScaled.Top(), 0.0f) + pos;
								auto leftBottom = Vector3(rectScaled.Left(), rectScaled.Bottom(), 0.0f) + pos;
								auto rightTop = Vector3(rectScaled.Right(), rectScaled.Top(), 0.0f) + pos;
								auto rightBottom = Vector3(rectScaled.Right(), rectScaled.Bottom(), 0.0f) + pos;

								line3DRenderer->AddLine(leftTop, rightTop, color);
								line3DRenderer->AddLine(leftBottom, rightBottom, color);
								line3DRenderer->AddLine(leftTop, leftBottom, color);
								line3DRenderer->AddLine(rightTop, rightBottom, color);
							}
						}
					}
				}
			}
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

	bool DebugComponent::DisplayAnimation2DCollisions() const
	{
		return m_DisplayAnimation2DCollisions;
	}

	void DebugComponent::DisplayAnimation2DCollisions(bool val)
	{
		m_DisplayAnimation2DCollisions = val;
	}
}
