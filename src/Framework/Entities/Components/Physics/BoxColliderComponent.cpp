#include "Entities/BaseEntity.h"

#include "BoxColliderComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"

namespace CasaEngine
{
	BoxColliderComponent::BoxColliderComponent(BaseEntity* entity)
		: ColliderComponent(entity, BOX_COLLIDER)
	{
	}

	Box BoxColliderComponent::Shape() const
	{
		return m_Shape;
	}

	BoxColliderComponent::~BoxColliderComponent()
	{
	}

	void BoxColliderComponent::Initialize()
	{
		//m_pTransform = GetEntity()->GetComponentMgr()->GetComponent<Transform2DComponent>();
		//CA_ASSERT("BoxColliderComponent::Initialize() can't find the Transform2DComponent. Please add it before add a BoxColliderComponent", m_pTransform != nullptr);
	}

	void BoxColliderComponent::Draw()
	{
		/*Matrix4 mat = m_pTransform->GetWorldMatrix();
		Vector3 pos3 = mat.GetTranslation();
		Vector2 pos(pos3.x, pos3.y);

		m_pSpriteRenderer->AddSprite(m_pSprite,
			pos, m_pTransform->GetRotation(),
			m_pTransform->GetScale(), _color,
			pos3.z, m_SpriteEffect);*/
	}

	void BoxColliderComponent::Write(std::ostream& /*os*/) const
	{
	}

	void BoxColliderComponent::Read(std::ifstream& /*is*/)
	{
	}
}