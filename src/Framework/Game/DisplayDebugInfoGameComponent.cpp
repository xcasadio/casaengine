#include "Base.h"

#include "Game/DisplayDebugInfoGameComponent.h"
#include "Game/Game.h"
#include "GameTime.h"
#include "Graphics/Mesh/Mesh.h"
#include "Maths/Matrix4.h"
#include "GameInfo.h"
#include "Entities/Components/CameraComponent.h"


namespace CasaEngine
{
	void ShowUI4AllComponents(BaseEntity* pEntity);
	void DrawAxis(bgfx::VertexBufferHandle vertexHandle_, bgfx::ProgramHandle program_handle);
	void ShowFPS();
	void ShowDebugWindow();

	DisplayDebugInfoGameComponent::DisplayDebugInfoGameComponent(Game* pGame_) :
		DrawableGameComponent(pGame_),
		m_pProgram(nullptr),
		m_VertexBuffer(),
		m_Vertices{}
	{
		DrawOrder(10);
		UpdateOrder(10);
	}

	DisplayDebugInfoGameComponent::~DisplayDebugInfoGameComponent()
	{
		delete m_pProgram;
		m_pProgram = nullptr;
		bgfx::destroy(m_VertexBuffer);
		m_VertexBuffer = BGFX_INVALID_HANDLE;
	}

	void DisplayDebugInfoGameComponent::OnLoadContent()
	{
		//defined uniq view id 
		bgfx::setViewName(1, "DisplayDebugInfo");
		//bgfx::setView(1, true);

		m_pProgram = new Program("vs_3DLines", "fs_3DLines");

		m_Vertices[0].Position = Vector3::Zero();  m_Vertices[0].Color = Color::Red.ToABGR();
		m_Vertices[1].Position = Vector3::UnitX(); m_Vertices[1].Color = Color::Red.ToABGR();
		m_Vertices[2].Position = Vector3::Zero();  m_Vertices[2].Color = Color::Green.ToABGR();
		m_Vertices[3].Position = Vector3::UnitY(); m_Vertices[3].Color = Color::Green.ToABGR();
		m_Vertices[4].Position = Vector3::Zero();  m_Vertices[4].Color = Color::Blue.ToABGR();
		m_Vertices[5].Position = Vector3::UnitZ(); m_Vertices[5].Color = Color::Blue.ToABGR();

		m_VertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(m_Vertices, 6 * sizeof(VertexPositionColor)), VertexPositionColor::ms_layout);
	}

	void DisplayDebugInfoGameComponent::Update(const GameTime& /*gameTime_*/)
	{
	}

	void DisplayDebugInfoGameComponent::Draw()
	{
		if (Game::Instance().GetDebugOptions().ShowAxis == true)
		{
			DrawAxis(m_VertexBuffer, m_pProgram->Handle());
		}

		if (Game::Instance().GetDebugOptions().ShowFPS == true)
		{
			ShowFPS();
		}

		if (Game::Instance().GetDebugOptions().IsDebugActivated == true)
		{
			ShowDebugWindow();
		}

		if (Game::Instance().GetDebugOptions().ShowLogInGame == true)
		{
			Game::Instance().GetInGameLogger().ShowWindow();
		}
	}


	void DrawAxis(bgfx::VertexBufferHandle vertexHandle_, bgfx::ProgramHandle program_handle)
	{
		CameraComponent* pCamera = Game::Instance().GetGameInfo().GetActiveCamera();
		Viewport& viewport = pCamera->GetViewport();
		Matrix4 matProj, matWorld;

		//matWorld.CreateRotationZ(0.5f * PI);
		//matWorld.CreateTranslation(0.0f, 0.0f, -1.0f);
		//matWorld.CreateScale(1.0f / (float)CA_DEFAULT_WIDTH, 1.0f / (float)CA_DEFAULT_HEIGHT, 1.0f);
		//matWorld.CreateScale(0.989f, 1.0f, 1.0f);
		Vector3 scale(1.0f, 1.0f, 1.0f);
		Quaternion rot;
		rot.FromAxisAngle(Vector3::UnitZ(), 0.5f * PI);
		matWorld.Transformation(
			nullptr, nullptr,
			&scale,
			nullptr,
			&rot, //rotation
			nullptr);

		float left = viewport.X() * Game::Instance().GetWindowSize().x;
		float right = viewport.Width() * Game::Instance().GetWindowSize().x;
		float bottom = viewport.Y() * Game::Instance().GetWindowSize().y;
		float top = viewport.Height() * Game::Instance().GetWindowSize().y;
		matProj = Matrix4::CreateOrthographicOffCenter(left, right, bottom, top, viewport.NearClipPlane(), viewport.FarClipPlane());

		bgfx::setViewTransform(1, nullptr, matProj);
		//bgfx::setViewTransform(1, pCamera->GetViewMatrix(), pCamera->GetProjectionMatrix());

		bgfx::setViewRect(1, left, top, right, bottom);
		bgfx::setTransform(matWorld);

		bgfx::setVertexBuffer(0, vertexHandle_);
		bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_MSAA | BGFX_STATE_PT_LINES);
		bgfx::submit(1, program_handle);
	}

	void ShowFPS()
	{
		ImGui::SetNextWindowPos(ImVec2(10, 10));
		if (ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
		{
			ImGui::Text("%3.1f FPS     ", Game::Instance().GetDebugSystem().GetFPS());
		}

		ImGui::End();
	}

	void ShowDebugWindow()
	{
		ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);

		if (ImGui::Begin("Debug window"))
		{
			ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0)); //-ImGui::GetItemsLineHeightWithSpacing()));
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

			// debug options
			if (ImGui::CollapsingHeader("debug options", ImGuiTreeNodeFlags_CollapsingHeader))
			{
				ImGui::Checkbox("show axis", &Game::Instance().GetDebugOptions().ShowAxis);
				ImGui::Checkbox("show fps", &Game::Instance().GetDebugOptions().ShowFPS);
			}

#ifdef EDITOR
			if (ImGui::CollapsingHeader("entities", ImGuiTreeNodeFlags_OpenOnArrow))
			{
				// left
				static int selected = 0;
				ImGui::BeginChild("entities list", ImVec2(150, 0), true);

				EntityManager::EntityIterator it;

				for (it = Game::Instance().GetEntityManager().cbegin(); it != Game::Instance().GetEntityManager().cend(); ++it)
				{
					char label[128];
					sprintf(label, "%s (%d)", it->second->GetName(), it->first);
					ImGui::Selectable(label, &it->second->m_IsSelected); //ImGui::SameLine(100); ImGui::Text(" 2,345 bytes");
				}
				ImGui::EndChild();
				ImGui::SameLine();

				// right
				ImGui::BeginGroup();
				BaseEntity* pEntity = Game::Instance().GetEntityManager().GetFirstSelectedEntity();

				if (pEntity != nullptr)
				{
					ImGui::BeginChild("item view", ImVec2(0, ImGui::GetTextLineHeightWithSpacing())); // Leave room for 1 line below us
					ImGui::Text("Object selected : %s (%d)", pEntity->GetName(), pEntity->ID());
					ImGui::Separator();

					ShowUI4AllComponents(pEntity);

					ImGui::EndChild();

					//Used to detect bug : button are cut at the bottom
					ImGui::BeginChild("buttons");
					if (ImGui::Button("Revert")) {}
					ImGui::EndChild();
				}

				ImGui::EndGroup();
			}
#endif

			ImGui::PopStyleVar();
			ImGui::EndChild();
		}

		ImGui::End();
	}

	void ShowUI4AllComponents(BaseEntity* pEntity)
	{
		const std::vector<Component*>& cpts = pEntity->GetComponentMgr()->Components();

		for (auto it = cpts.cbegin();
			it != cpts.cend();
			++it)
		{
			(*it)->ShowDebugWidget();
		}
	}
}
