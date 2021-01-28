#include "Entities/BaseEntity.h"

#include "Circle2DColliderComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"


namespace CasaEngine
{

/**
 * 
 */
Circle2DColliderComponent::Circle2DColliderComponent(BaseEntity* pEntity_)
	: ColliderComponent(pEntity_, CIRCLE2D_COLLIDER)
{
	
}

/**
 * 
 */
Circle2DColliderComponent::~Circle2DColliderComponent()
{

}

/**
 * 
 */
void Circle2DColliderComponent::Initialize()
{
	//m_pTransform = GetEntity()->GetComponentMgr()->GetComponent<Transform2DComponent>();
	//CA_ASSERT("Circle2DColliderComponent::Initialize() can't find the Transform2DComponent. Please add it before add a Circle2DColliderComponent", m_pTransform != nullptr);
}

/**
 * 
 */
void Circle2DColliderComponent::Draw()
{
	/*Matrix4 mat = m_pTransform->GetWorldMatrix();
	Vector3F pos3 = mat.GetTranslation();
	Vector2F pos(pos3.x, pos3.y);

	m_pSpriteRenderer->AddSprite(m_pSprite, 
		pos, m_pTransform->GetRotation(), 
		m_pTransform->GetScale(), m_Color, 
		pos3.z, m_SpriteEffect);*/
}

/**
 * 
 */
/*void Circle2DColliderComponent::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
void Circle2DColliderComponent::Write(std::ostream& /*os*/) const
{

}

/**
 * 
 */
void Circle2DColliderComponent::Read (std::ifstream& /*is*/)
{

}

}
