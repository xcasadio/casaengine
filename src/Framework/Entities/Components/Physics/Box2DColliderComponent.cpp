#include "Base.h"
#include "Entities/BaseEntity.h"

#include "Box2DColliderComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include <string>
#include "Game/Game.h"
#include "Maths/Rectangle.h"


namespace CasaEngine
{

/**
 * 
 */
Box2DColliderComponent::Box2DColliderComponent(BaseEntity* pEntity_)
	: ColliderComponent(pEntity_, BOX2D_COLLIDER)
{
	m_pShape = NEW_AO RectangleF();
}

/**
 * 
 */
Box2DColliderComponent::~Box2DColliderComponent()
{
	DELETE_AO m_pShape;
}

/**
 * 
 */
// void Box2DColliderComponent::Initialize()
// {
// }

/**
 * 
 */
void Box2DColliderComponent::Draw()
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
/*void Box2DColliderComponent::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
void Box2DColliderComponent::Write(std::ostream& /*os*/) const
{

}

/**
 * 
 */
void Box2DColliderComponent::Read (std::ifstream& /*is*/)
{

}

}
