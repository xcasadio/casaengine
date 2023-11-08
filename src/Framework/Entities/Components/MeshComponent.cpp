#include  "Entities/BaseEntity.hpp"
#include  "Entities/ComponentTypeEnum.hpp"
#include  "Base.hpp"
#include  "Game/Game.hpp"
#include  "Assets/AssetManager.hpp"
#include  "Maths/Matrix4.hpp"
#include  "MeshComponent.hpp"
#include  "StringUtils.hpp"
#include  "Game/MeshRendererGameComponent.hpp"

namespace CasaEngine
{
	MeshComponent::MeshComponent(BaseEntity* entity)
		: Component(entity, MODEL_3D),
		m_pModel(nullptr),
		m_pProgram(nullptr),
		m_pModelRenderer(nullptr)
	{

	}

	void MeshComponent::Initialize()
	{
		m_pModelRenderer = Game::Instance().GetGameComponent<MeshRendererGameComponent>();
		CA_ASSERT(m_pModelRenderer != nullptr, "MeshComponent::Initialize() can't find the MeshRendererGameComponent.");
	}

	Mesh* MeshComponent::GetModel() const
	{
		return m_pModel;
	}

	void MeshComponent::SetModel(Mesh* val)
	{
		m_pModel = val;
	}

	Program* MeshComponent::GetEffect() const
	{
		return m_pProgram;
	}

	void MeshComponent::SetProgram(Program* pVal_)
	{
		m_pProgram = pVal_;
	}

	void MeshComponent::Update(const GameTime& /*gameTime_*/)
	{
	}

	void MeshComponent::Draw()
	{
		CA_ASSERT(m_pModel != nullptr, "MeshComponent::Draw() : m_pModel is nullptr");
		CA_ASSERT(m_pModelRenderer != nullptr, "MeshComponent::Draw() : m_pModelRenderer is nullptr");

		Matrix4 mat = GetEntity()->GetCoordinates().GetWorldMatrix();
		m_pModelRenderer->AddModel(m_pModel, mat, m_pProgram);
	}

	void MeshComponent::Write(std::ostream& /*os*/) const
	{

	}

	void MeshComponent::Read(std::ifstream& /*is*/)
	{

	}

#if EDITOR
	void MeshComponent::ShowDebugWidget()
	{
		/*
		const ImGuiStyle& style = ImGui::GetStyle();

		if (ImGui::CollapsingHeader("Static Mesh"))
		{
			ImGui::Text("TODO thumbnail");
		}

		if (ImGui::CollapsingHeader("Materials"))
		{
			const float widgetWidth = 50.0f;

			Material *pMat = m_pModel->GetMaterial();

			ImGui::PushItemWidth(widgetWidth); ImGui::Text("Texture 0");
			ImGui::SameLine(0, style.ItemInnerSpacing.x); ImGui::PushItemWidth(widgetWidth); ImGui::Text("TODO thumbnail");
			ImGui::PushItemWidth(widgetWidth); ImGui::Text("Texture 0 rep");
			ImGui::SameLine(0, style.ItemInnerSpacing.x); ImGui::PushItemWidth(widgetWidth); ImGui::DragFloat("U", &pMat->m_Texture0Repeat.x, 0.01f);
			ImGui::SameLine(0, style.ItemInnerSpacing.x); ImGui::PushItemWidth(widgetWidth); ImGui::DragFloat("V", &pMat->m_Texture0Repeat.y, 0.01f);
		}
		*/
	}
#endif
}
