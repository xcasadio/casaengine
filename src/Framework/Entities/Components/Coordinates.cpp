#include "Coordinates.h"
#include "Entities/BaseEntity.h"

namespace CasaEngine
{
	Coordinates::Coordinates() :
		_parent(nullptr),
		m_LocalMatrixChanged(true)
	{
		m_LocalScale.Set(1.0f, 1.0f, 1.0f);
		m_LocalRotation.Identity();
		m_LocalMatrix.Identity();
		m_WorldMatrix.Identity();
	}

	Matrix4 Coordinates::GetLocalMatrix()
	{
		return m_LocalMatrix;
	}

	Matrix4 Coordinates::GetWorldMatrix()
	{
		UpdateWorldMatrix();
		return m_WorldMatrix;
	}

	void Coordinates::SetLocalMatrix(const Matrix4& val)
	{
		m_LocalMatrix = val;
		m_LocalMatrixChanged = true;
	}

	void Coordinates::SetWorldMatrix(const Matrix4& val)
	{
		m_WorldMatrix = val;
	}

	Vector3 Coordinates::GetCenterOfRotation() const
	{
		return m_LocalCenterOfRotation;
	}

	void Coordinates::SetCenterOfRotation(const Vector3& val)
	{
		m_LocalCenterOfRotation = val;
		m_LocalMatrixChanged = true;
	}

	Vector3 Coordinates::GetLocalPosition() const
	{
		return m_LocalPosition;
	}

	void Coordinates::SetLocalPosition(const Vector3& val)
	{
		m_LocalPosition = val;
		m_LocalMatrixChanged = true;
	}

	Quaternion Coordinates::GetLocalRotation() const
	{
		return m_LocalRotation;
	}
	void Coordinates::SetLocalRotation(const Quaternion& val)
	{
		m_LocalRotation = val;
		m_LocalMatrixChanged = true;
	}

	Vector3 Coordinates::GetLocalScale() const
	{
		return m_LocalScale;
	}

	void Coordinates::SetLocalScale(const Vector3& val)
	{
		m_LocalScale = val;
		m_LocalMatrixChanged = true;
	}

	Vector3 Coordinates::GetPosition() const
	{
		return _parent == nullptr ? m_LocalPosition : m_LocalPosition + _parent->GetPosition();
	}

	Quaternion Coordinates::GetRotation() const
	{
		return _parent == nullptr ? m_LocalRotation : m_LocalRotation * _parent->GetRotation();
	}

	Vector3 Coordinates::GetScale() const
	{
		return _parent == nullptr ? m_LocalScale : m_LocalScale + _parent->GetScale();
	}

	void Coordinates::SetParent(Coordinates* parent)
	{
		_parent = parent;
	}

	void Coordinates::UpdateLocalMatrix()
	{
		if (m_LocalMatrixChanged == true)
		{
			m_LocalMatrixChanged = false;

			Matrix4 transCenter, trans;
			trans.Translation(m_LocalPosition);
			transCenter.Translation(m_LocalCenterOfRotation);
			Matrix4 matS = Matrix4::CreateScale(m_LocalScale.x, m_LocalScale.y, m_LocalScale.z);
			Matrix4 matRot = Matrix4::CreateFromQuaternion(m_LocalRotation); //m_LocalRotation.ToMatrix4();

			m_LocalMatrix = transCenter * matS * matRot * trans;
		}
	}

	void Coordinates::UpdateWorldMatrix()
	{
		UpdateLocalMatrix();

		if (_parent != nullptr)
		{
			m_WorldMatrix = m_LocalMatrix * _parent->GetWorldMatrix();
		}
		else
		{
			m_WorldMatrix = m_LocalMatrix;
		}
	}

#if EDITOR
	void Coordinates::ShowDebugWidget()
	{
		/*
		const ImGuiStyle& style = ImGui::GetStyle();

		if (ImGui::CollapsingHeader("Transform 3D"))
		{
			const float widgetWidth = 50.0f;

			ImGui::PushItemWidth(widgetWidth); ImGui::Text("Location");
			ImGui::SameLine(0, style.ItemInnerSpacing.x); ImGui::PushItemWidth(widgetWidth); ImGui::DragFloat("X", &m_LocalPosition.x, 0.005f);
			ImGui::SameLine(0, style.ItemInnerSpacing.x); ImGui::PushItemWidth(widgetWidth); ImGui::DragFloat("Y", &m_LocalPosition.y, 0.005f);
			ImGui::SameLine(0, style.ItemInnerSpacing.x); ImGui::PushItemWidth(widgetWidth); ImGui::DragFloat("Z", &m_LocalPosition.z, 0.005f);

			ImGui::PushItemWidth(widgetWidth); ImGui::Text("Rotation");
			ImGui::SameLine(0, style.ItemInnerSpacing.x); ImGui::PushItemWidth(widgetWidth); ImGui::SliderAngle("X", &m_LocalRotation.x);
			ImGui::SameLine(0, style.ItemInnerSpacing.x); ImGui::PushItemWidth(widgetWidth); ImGui::SliderAngle("Y", &m_LocalRotation.y);
			ImGui::SameLine(0, style.ItemInnerSpacing.x); ImGui::PushItemWidth(widgetWidth); ImGui::SliderAngle("Z", &m_LocalRotation.z);

			ImGui::PushItemWidth(widgetWidth); ImGui::Text("Scale");
			ImGui::SameLine(0, style.ItemInnerSpacing.x); ImGui::PushItemWidth(widgetWidth); ImGui::DragFloat("X", &m_LocalScale.x, 0.005f);
			ImGui::SameLine(0, style.ItemInnerSpacing.x); ImGui::PushItemWidth(widgetWidth); ImGui::DragFloat("Y", &m_LocalScale.y, 0.005f);
			ImGui::SameLine(0, style.ItemInnerSpacing.x); ImGui::PushItemWidth(widgetWidth); ImGui::DragFloat("Z", &m_LocalScale.z, 0.005f);
			//entity static or movable?
		}
		*/
	}
#endif

	void Coordinates::Write(std::ostream& /*os*/) const
	{

	}

	void Coordinates::Read(std::ifstream& /*is*/)
	{

	}
}
