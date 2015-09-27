#include "Base.h"
#include "Entities/BaseEntity.h"

#include "BoxColliderComponent.h"
#include "Maths/Matrix4.h"
#include "Entities/ComponentTypeEnum.h"
#include <string>
#include "Game/Game.h"


namespace CasaEngine
{

/**
 * 
 */
BoxColliderComponent::BoxColliderComponent(BaseEntity* pEntity_)
	: ColliderComponent(pEntity_, BOX_COLLIDER)
{
	
}


CasaEngine::Box BoxColliderComponent::Shape() const
{
	return m_Shape;
}


/**
 * 
 */
BoxColliderComponent::~BoxColliderComponent()
{

}

/**
 * 
 */
void BoxColliderComponent::Initialize()
{
	//m_pTransform = GetEntity()->GetComponentMgr()->GetComponent<Transform2DComponent>();
	//CA_ASSERT("BoxColliderComponent::Initialize() can't find the Transform2DComponent. Please add it before add a BoxColliderComponent", m_pTransform != nullptr);
}

/**
 * 
 */
void BoxColliderComponent::Draw()
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
/*void BoxColliderComponent::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
void BoxColliderComponent::Write(std::ostream& /*os*/) const
{

}

/**
 * 
 */
void BoxColliderComponent::Read (std::ifstream& /*is*/)
{

}

} // namespace CasaEngine
