
#include "Base.h"
#include "Entities/BaseEntity.h"

#include "TransformComponent.h"
#include "Maths/Matrix4.h"



namespace CasaEngine
{

TransformComponent::TransformComponent(BaseEntity* pEntity_, int type_)
	: Component(pEntity_, type_)
{
	m_LocalMatrix.Identity();
	m_WorldMatrix.Identity();
	m_LocalMatrixChanged = true;
}

TransformComponent::~TransformComponent()
{

}

Matrix4 TransformComponent::GetLocalMatrix() 
{ 
	if (m_LocalMatrixChanged == true)
	{
		UpdateLocalMatrix();
	}

	return m_LocalMatrix; 
}
/*
void TransformComponent::SetLocalMatrix(Matrix4 val) 
{ 
	localMatrix = val; 
}*/

Matrix4 TransformComponent::GetWorldMatrix() 
{ 
	UpdateWorldMatrix();
	return m_WorldMatrix; 
}
/*
void TransformComponent::SetWorldMatrix(Matrix4 val) 
{ 
	worldMatrix = val; 
}*/


void TransformComponent::Write(std::ostream& /*os*/) const
{

}

void TransformComponent::Read (std::ifstream& /*is*/)
{

}

} // namespace CasaEngine
