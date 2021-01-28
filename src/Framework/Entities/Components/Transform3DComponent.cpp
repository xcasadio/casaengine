#include "Entities/BaseEntity.h"

#include "Transform3DComponent.h"
#include "../ComponentTypeEnum.h"
#include "../Events/BaseEntityEvents.h"
#include "EventHandler/Event.h"


namespace CasaEngine
{

Transform3DComponent::Transform3DComponent(BaseEntity* pEntity_) :
	TransformComponent(pEntity_, TRANSFORM_3D),
		m_pParentTransform(nullptr)
{
	m_LocalScale.Set(1.0f, 1.0f, 1.0f);

	m_ParentChangedConnection = pEntity_->subscribeEvent(
		EntityParentChangeEvent::GetEventName(),
		Event::Subscriber(&Transform3DComponent::OnParentChange, this));
}

Transform3DComponent::~Transform3DComponent()
{
	m_ParentChangedConnection->disconnect();
}

void Transform3DComponent::Initialize()
{

}

//all entities must implement an update function
void  Transform3DComponent::Update(const GameTime& /*gameTime_*/)
{

}


void Transform3DComponent::SetLocalMatrix(Matrix4 val) 
{ 
	m_LocalMatrix = val;
	m_LocalMatrixChanged = true;
}

void Transform3DComponent::SetWorldMatrix(Matrix4 val) 
{ 
	m_WorldMatrix = val;
}

Vector3F Transform3DComponent::GetCenterOfRotation() const
{
	return m_LocalCenterOfRotation;
}

void Transform3DComponent::SetCenterOfRotation(Vector3F val)
{
	m_LocalCenterOfRotation = val;
	m_LocalMatrixChanged = true;
}
	
Vector3F Transform3DComponent::GetLocalPosition() const 
{ 
	return m_LocalPosition; 
}

void Transform3DComponent::SetLocalPosition(Vector3F val) 
{ 
	m_LocalPosition = val;
	m_LocalMatrixChanged = true;
}

CasaEngine::Quaternion Transform3DComponent::GetLocalRotation() const
{ 
	return m_LocalRotation; 
}
void Transform3DComponent::SetLocalRotation(Quaternion val)
{ 
	m_LocalRotation = val;
	m_LocalMatrixChanged = true;
}

Vector3F Transform3DComponent::GetLocalScale() const 
{ 
	return m_LocalScale; 
}

void Transform3DComponent::SetLocalScale(Vector3F val) 
{ 
	m_LocalScale = val;
	m_LocalMatrixChanged = true;
}

/**
 * 
 */
Vector3F Transform3DComponent::GetPosition() const 
{ 
	return m_pParentTransform == nullptr ? m_LocalPosition : m_LocalPosition + m_pParentTransform->GetPosition();
}

/**
 * 
 */
CasaEngine::Quaternion Transform3DComponent::GetRotation() const
{ 
	return m_pParentTransform == nullptr ? m_LocalRotation : m_LocalRotation * m_pParentTransform->GetRotation(); 
}

/**
 * 
 */
Vector3F Transform3DComponent::GetScale() const 
{ 
	return m_pParentTransform == nullptr ? m_LocalScale : m_LocalScale + m_pParentTransform->GetScale(); 
}

/*
 *	
 */
bool Transform3DComponent::OnParentChange(const EventArgs &e)
{
	const EntityParentChangeEvent &event = static_cast<const EntityParentChangeEvent &>(e);

	BaseEntity* pParent = event.getParent();

	if (pParent != nullptr)
	{
		m_pParentTransform = pParent->GetComponentMgr()->GetComponent<Transform3DComponent>();
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
void Transform3DComponent::UpdateLocalMatrix()
{
	if (m_LocalMatrixChanged == true)
	{
		m_LocalMatrixChanged = false;

		Matrix4 matS, transCenter, trans;
		trans.SetTranslation(m_LocalPosition);
		transCenter.SetTranslation(m_LocalCenterOfRotation);
		matS.CreateScale(m_LocalScale.x, m_LocalScale.y, m_LocalScale.z);
		Matrix4 matRot = m_LocalRotation.ToMatrix4();

		m_LocalMatrix = transCenter * matS * matRot * trans;
	}
}

/*
 *	
 */
void Transform3DComponent::UpdateWorldMatrix()
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

/**
 * Editor
 */
void Transform3DComponent::ShowDebugWidget()
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

/**
 *
 */
void Transform3DComponent::Write(std::ostream& /*os*/) const
{

}

/**
 * 
 */
void Transform3DComponent::Read (std::ifstream& /*is*/)
{

}



}
