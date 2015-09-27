
#include "Base.h"
#include "Entities/BaseEntity.h"

#include "StaticSpriteComponent.h"
#include "Maths/Matrix4.h"
#include "Entities/ComponentTypeEnum.h"
#include <string>
#include "Game/Game.h"
#include "Sprite/SpriteRenderer.h"
#include "Resources/ResourceManager.h"
#include "StringUtils.h"
#include "Sprite/SpriteTypes.h"
#include "Graphics/Color.h"
#include "Assets/AssetManager.h"


namespace CasaEngine
{

/**
 * 
 */
StaticSpriteComponent::StaticSpriteComponent(BaseEntity* pEntity_)
	: Component(pEntity_, STATIC_SPRITE),
		m_pSpriteRenderer(nullptr),
		m_pSprite(nullptr),
		m_pTransform(nullptr)
{
	
}

/**
 * 
 */
StaticSpriteComponent::~StaticSpriteComponent()
{

}

/**
 * 
 */
std::string StaticSpriteComponent::SpriteID() const 
{ 
	return m_SpriteID; 
}

/**
 * 
 */
void StaticSpriteComponent::SpriteID(std::string val) 
{ 
	m_SpriteID = val;

	m_pSprite = AssetManager::Instance().GetAsset<Sprite>(m_SpriteID);
}

/**
 * 
 */
CColor StaticSpriteComponent::GetColor() const 
{ 
	return m_Color; 
}

/**
 * 
 */
void StaticSpriteComponent::SetColor(CColor val) 
{ 
	m_Color = val; 
}

/**
 * 
 */
eSpriteEffects StaticSpriteComponent::GetSpriteEffect() const 
{ 
	return m_SpriteEffect; 
}

/**
 * 
 */
void StaticSpriteComponent::SetSpriteEffect(eSpriteEffects val) 
{ 
	m_SpriteEffect = val; 
}

/**
 * 
 */
void StaticSpriteComponent::Initialize()
{
	m_pSpriteRenderer = Game::Instance()->GetGameComponent<SpriteRenderer>();
	CA_ASSERT(m_pSpriteRenderer != nullptr, 
		"StaticSpriteComponent::Initialize() can't find the component SpriteRenderer");

	m_pTransform = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();
	CA_ASSERT(m_pTransform != nullptr, 
		"StaticSpriteComponent::Initialize() can't find the Transform2DComponent. Please add it before add a StaticSpriteComponent");
}

/**
 * 
 */
void StaticSpriteComponent::Update(const GameTime& /*gameTime_*/)
{
}

/**
 * 
 */
void StaticSpriteComponent::Draw()
{
	Matrix4 mat = m_pTransform->GetWorldMatrix();
	Vector3F pos3 = mat.GetTranslation();
	Vector2F pos(pos3.x, pos3.y);
	Vector2F scale(m_pTransform->GetScale().x, m_pTransform->GetScale().y);

	m_pSpriteRenderer->AddSprite(m_pSprite, 
		pos, /*m_pTransform->GetRotation()*/0.0f, 
		scale, m_Color, 
		pos3.z, m_SpriteEffect);
}

/**
 * 
 */
/*void StaticSpriteComponent::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
void StaticSpriteComponent::Write(std::ostream& /*os*/) const
{

}

/**
 * 
 */
void StaticSpriteComponent::Read (std::ifstream& /*is*/)
{

}

} // namespace CasaEngine
