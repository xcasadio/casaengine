#include "Entities/BaseEntity.h"

#include "Transform2DComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include "Entities/Events/BaseEntityEvents.h"

namespace CasaEngine
{

Transform2DComponent::Transform2DComponent(BaseEntity* pEntity_) :
	TransformComponent(pEntity_, TRANSFORM_2D),
		m_pParentTransform(nullptr)
{
	m_LocalRotation = 0.0f;
	m_LocalPosition.Set(0.0f, 0.0f);
	m_LocalScale.Set(1.0f, 1.0f);

	m_ParentChangedConnection = pEntity_->subscribeEvent(
		EntityParentChangeEvent::GetEventName(),
		Event::Subscriber(&Transform2DComponent::OnParentChange, this));
}

Transform2DComponent::~Transform2DComponent()
{
	m_ParentChangedConnection->disconnect();
}

void Transform2DComponent::Initialize()
{
	//throw std::exception("The method or operation is not implemented.");
}

//all entities must implement an update function
void  Transform2DComponent::Update(const GameTime& /*gameTime_*/)
{

}

/**
 *
 */
void Transform2DComponent::Write(std::ostream& /*os*/) const
{

}

/**
 * 
 */
void Transform2DComponent::Read (std::ifstream& /*is*/)
{

}


void Transform2DComponent::SetLocalMatrix(Matrix4 val) 
{ 
	m_LocalMatrix = val;
	m_LocalMatrixChanged = true;
}

void Transform2DComponent::SetWorldMatrix(Matrix4 val) 
{ 
	m_WorldMatrix = val;
}


Vector2F Transform2DComponent::GetLocalPosition() const 
{ 
	return m_LocalPosition; 
}

void Transform2DComponent::SetLocalPosition(Vector2F val) 
{ 
	m_LocalPosition = val;
	m_LocalMatrixChanged = true;
}

float Transform2DComponent::GetLocalRotation() const 
{ 
	return m_LocalRotation; 
}


void Transform2DComponent::SetLocalRotation(float val) 
{ 
	m_LocalRotation = val;
	m_LocalMatrixChanged = true;
}

Vector2F Transform2DComponent::GetLocalScale() const 
{ 
	return m_LocalScale; 
}

void Transform2DComponent::SetLocalScale(Vector2F val) 
{ 
	m_LocalScale = val;
	m_LocalMatrixChanged = true;
}

/**
 * 
 */
Vector2F Transform2DComponent::GetPosition() const 
{ 
	return m_pParentTransform == nullptr ? m_LocalPosition : m_LocalPosition + m_pParentTransform->GetPosition();
}

/**
 * 
 */
float Transform2DComponent::GetRotation() const 
{ 
	return m_pParentTransform == nullptr ? m_LocalRotation : m_LocalRotation + m_pParentTransform->GetRotation(); 
}

/**
 * 
 */
Vector2F Transform2DComponent::GetScale() const 
{ 
	return m_pParentTransform == nullptr ? m_LocalScale : m_LocalScale + m_pParentTransform->GetScale(); 
}


/*
 *	
 */
bool Transform2DComponent::OnParentChange(const EventArgs &e)
{
	const EntityParentChangeEvent &event = static_cast<const EntityParentChangeEvent &>(e);

	BaseEntity* pParent = event.getParent();

	if (pParent != nullptr)
	{
		m_pParentTransform = pParent->GetComponentMgr()->GetComponent<Transform2DComponent>();
	}
	else
	{
		m_pParentTransform = nullptr;
	}

	UpdateWorldMatrix();

	return false;
}

/*
 *	
 */
void Transform2DComponent::UpdateLocalMatrix()
{
	if (m_LocalMatrixChanged == true)
	{
		m_LocalMatrixChanged = false;

		Matrix4 matS, matRot;
		matS.CreateScale(m_LocalScale.x, m_LocalScale.y, 1.0f);
		matRot.CreateRotationZ(m_LocalRotation);

		m_LocalMatrix = matS * matRot;
		m_LocalMatrix.SetTranslation(m_LocalPosition.x, m_LocalPosition.y, 0.0f);
	}
}

/*
 *	
 */
void Transform2DComponent::UpdateWorldMatrix()
{
	UpdateLocalMatrix();

	if (m_pParentTransform != nullptr)
	{
		m_WorldMatrix = m_LocalMatrix * m_pParentTransform->GetWorldMatrix();
	}
	else
	{
		m_WorldMatrix = m_LocalMatrix;
	}
}


}
