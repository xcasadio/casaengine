#include "Entities/BaseEntity.h"

#include "TransformComponent.h"
#include "Maths/Matrix4.h"

namespace CasaEngine
{
	TransformComponent::TransformComponent(BaseEntity* pEntity_, int type_)
		: Component(pEntity_, type_), m_LocalMatrixChanged(true)
	{
		m_LocalMatrix.Identity();
		m_WorldMatrix.Identity();
	}

	Matrix4 TransformComponent::GetLocalMatrix()
	{
		if (m_LocalMatrixChanged == true)
		{
			UpdateLocalMatrix();
		}

		return m_LocalMatrix;
	}

	Matrix4 TransformComponent::GetWorldMatrix()
	{
		UpdateWorldMatrix();
		return m_WorldMatrix;
	}

	void TransformComponent::Write(std::ostream& /*os*/) const
	{

	}

	void TransformComponent::Read(std::ifstream& /*is*/)
	{

	}
}
