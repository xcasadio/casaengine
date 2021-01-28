#include "Base.h"
#include "Entities/BaseEntity.h"

#include "StaticSpriteComponent.h"
#include "Maths/Matrix4.h"
#include "Entities/ComponentTypeEnum.h"
#include <string>
#include "Game/Game.h"
#include "Sprite/SpriteRenderer.h"
#include "Sprite/SpriteTypes.h"
#include "Graphics/Color.h"
#include "Assets/AssetManager.h"


namespace CasaEngine
{
	StaticSpriteComponent::StaticSpriteComponent(BaseEntity* pEntity_)
		: Component(pEntity_, STATIC_SPRITE),
		m_pSpriteRenderer(nullptr),
		m_pSprite(nullptr),
		m_pTransform(nullptr)
	{

	}

	StaticSpriteComponent::~StaticSpriteComponent()
	{

	}

	std::string StaticSpriteComponent::GetSpriteID() const
	{
		return m_SpriteID;
	}

	void StaticSpriteComponent::SetSpriteID(std::string val)
	{
		m_SpriteID = val;
		m_pSprite = NEW_AO Sprite(*Game::Instance().GetAssetManager().GetAsset<SpriteData>(m_SpriteID));
	}

	CColor StaticSpriteComponent::GetColor() const
	{
		return m_Color;
	}

	void StaticSpriteComponent::SetColor(CColor val)
	{
		m_Color = val;
	}

	eSpriteEffects StaticSpriteComponent::GetSpriteEffect() const
	{
		return m_SpriteEffect;
	}

	void StaticSpriteComponent::SetSpriteEffect(eSpriteEffects val)
	{
		m_SpriteEffect = val;
	}

	void StaticSpriteComponent::Initialize()
	{
		m_pSpriteRenderer = Game::Instance().GetGameComponent<SpriteRenderer>();
		CA_ASSERT(m_pSpriteRenderer != nullptr,
			"StaticSpriteComponent::Initialize() can't find the component SpriteRenderer");

		m_pTransform = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();
		CA_ASSERT(m_pTransform != nullptr,
			"StaticSpriteComponent::Initialize() can't find the Transform2DComponent. Please add it before add a StaticSpriteComponent");
	}

	void StaticSpriteComponent::Update(const GameTime& /*gameTime_*/)
	{
	}

	void StaticSpriteComponent::Draw()
	{
		m_pSpriteRenderer->AddSprite(m_pSprite, m_pTransform->GetWorldMatrix(),
			m_Color, m_pTransform->GetLocalMatrix().GetTranslation().z, m_SpriteEffect);
	}
}
