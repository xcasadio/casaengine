#include "Entities/BaseEntity.h"

#include "CapsuleColliderComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"


namespace CasaEngine
{

/**
 * 
 */
CapsuleColliderComponent::CapsuleColliderComponent(BaseEntity* pEntity_)
	: ColliderComponent(pEntity_, CAPSULE_COLLIDER)
{
	
}

/**
 * 
 */
CapsuleColliderComponent::~CapsuleColliderComponent()
{

}

/**
 * 
 */
void CapsuleColliderComponent::Initialize()
{
	//m_pTransform = GetEntity()->GetComponentMgr()->GetComponent<Transform2DComponent>();
	//CA_ASSERT("CapsuleColliderComponent::Initialize() can't find the Transform2DComponent. Please add it before add a CapsuleColliderComponent", m_pTransform != nullptr);
}

/**
 * 
 */
void CapsuleColliderComponent::Draw()
{
	/*Matrix4 mat = m_pTransform->GetWorldMatrix();
	Vector3 pos3 = mat.GetTranslation();
	Vector2 pos(pos3.x, pos3.y);

	m_pSpriteRenderer->AddSprite(m_pSprite, 
		pos, m_pTransform->GetRotation(), 
		m_pTransform->GetScale(), m_Color, 
		pos3.z, m_SpriteEffect);*/
}

/**
 * 
 */
/*void CapsuleColliderComponent::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
void CapsuleColliderComponent::Write(std::ostream& /*os*/) const
{

}

/**
 * 
 */
void CapsuleColliderComponent::Read (std::ifstream& /*is*/)
{

}

}
