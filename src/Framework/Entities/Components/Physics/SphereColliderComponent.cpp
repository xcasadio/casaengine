#include "Entities/BaseEntity.h"

#include "SphereColliderComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"


namespace CasaEngine
{

/**
 * 
 */
SphereColliderComponent::SphereColliderComponent(BaseEntity* pEntity_)
	: ColliderComponent(pEntity_, SPHERE_COLLIDER)
{
	
}

/**
 * 
 */
SphereColliderComponent::~SphereColliderComponent()
{

}

/**
 * 
 */
void SphereColliderComponent::Initialize()
{
	//m_pTransform = GetEntity()->GetComponentMgr()->GetComponent<Transform2DComponent>();
	//CA_ASSERT("SphereColliderComponent::Initialize() can't find the Transform2DComponent. Please add it before add a SphereColliderComponent", m_pTransform != nullptr);
}


/**
 * 
 */
void SphereColliderComponent::Draw()
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
/*void SphereColliderComponent::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
void SphereColliderComponent::Write(std::ostream& /*os*/) const
{

}

/**
 * 
 */
void SphereColliderComponent::Read (std::ifstream& /*is*/)
{

}

}
