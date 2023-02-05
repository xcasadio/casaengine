#include "Base.h"

#include "Game/DisplayDebugInfoGameComponent.h"

#include <bx/string.h>
#include <iconfontheaders/icons_font_awesome.h>

#include "Game/Game.h"
#include "GameTime.h"
#include "Graphics/Mesh/Mesh.h"
#include "Maths/Matrix4.h"
#include "GameInfo.h"
#include "Entities/Components/CameraComponent.h"


namespace CasaEngine
{
#if EDITOR
	void ShowUI4AllComponents(BaseEntity* pEntity);
	void DrawGrid(GridOrientation orientation, Line3DRendererComponent* line3DRenderer);
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

		m_Line3DRenderer = GetGame()->GetGameComponent<Line3DRendererComponent>();
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

		if (Game::Instance().GetDebugOptions().ShowGrid == true)
		{
			DrawGrid(m_Orientation, m_Line3DRenderer);
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
		if (ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("%3.1f FPS", Game::Instance().GetDebugSystem().GetFPS());
		}

		ImGui::End();
	}

	struct SampleData
	{
		static constexpr uint32_t kNumSamples = 100;

		SampleData()
		{
			reset();
		}

		void reset()
		{
			m_offset = 0;
			bx::memSet(m_values, 0, sizeof m_values);

			m_min = 0.0f;
			m_max = 0.0f;
			m_avg = 0.0f;
		}

		void pushSample(float value)
		{
			m_values[m_offset] = value;
			m_offset = (m_offset + 1) % kNumSamples;

			float min = MaxFloat;
			float max = -MaxFloat;
			float avg = 0.0f;

			for (uint32_t ii = 0; ii < kNumSamples; ++ii)
			{
				const float val = m_values[ii];
				min = bx::min(min, val);
				max = bx::max(max, val);
				avg += val;
			}

			m_min = min;
			m_max = max;
			m_avg = avg / kNumSamples;
		}

		int32_t m_offset;
		float m_values[kNumSamples];

		float m_min;
		float m_max;
		float m_avg;
	};

	static SampleData s_frameTime;

	static const ImVec4 s_resourceColor(0.5f, 0.5f, 0.5f, 1.0f);

	static bool bar(float _width, float _maxWidth, float _height, const ImVec4& _color)
	{
		const ImGuiStyle& style = ImGui::GetStyle();

		ImVec4 hoveredColor(
			_color.x + _color.x * 0.1f
			, _color.y + _color.y * 0.1f
			, _color.z + _color.z * 0.1f
			, _color.w + _color.w * 0.1f
		);

		ImGui::PushStyleColor(ImGuiCol_Button, _color);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoveredColor);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, _color);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, style.ItemSpacing.y));

		bool itemHovered = false;

		ImGui::Button("##", ImVec2(_width, _height));
		itemHovered |= ImGui::IsItemHovered();

		ImGui::SameLine();
		ImGui::InvisibleButton("##", ImVec2(bx::max(1.0f, _maxWidth - _width), _height));
		itemHovered |= ImGui::IsItemHovered();

		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(3);

		return itemHovered;
	}

	static void resourceBar(const char* _name, const char* _tooltip, uint32_t _num, uint32_t _max, float _maxWidth, float _height)
	{
		bool itemHovered = false;

		ImGui::Text("%s: %4d / %4d", _name, _num, _max);
		itemHovered |= ImGui::IsItemHovered();
		ImGui::SameLine();

		const float percentage = static_cast<float>(_num) / static_cast<float>(_max);

		itemHovered |= bar(bx::max(1.0f, percentage * _maxWidth), _maxWidth, _height, s_resourceColor);
		ImGui::SameLine();

		ImGui::Text("%5.2f%%", percentage * 100.0f);

		if (itemHovered)
		{
			ImGui::SetTooltip("%s %5.2f%%"
				, _tooltip
				, percentage * 100.0f
			);
		}
	}

	void DisplayResources(const bgfx::Stats* stats)
	{
		if (ImGui::CollapsingHeader(ICON_FA_PUZZLE_PIECE " Resources"))
		{
			const bgfx::Caps* caps = bgfx::getCaps();

			const float itemHeight = ImGui::GetTextLineHeightWithSpacing();
			const float maxWidth = 90.0f;

			ImGui::PushFont(ImGui::Font::Mono);
			ImGui::Text("Res: Num  / Max");
			resourceBar("DIB", "Dynamic index buffers", stats->numDynamicIndexBuffers, caps->limits.maxDynamicIndexBuffers, maxWidth, itemHeight);
			resourceBar("DVB", "Dynamic vertex buffers", stats->numDynamicVertexBuffers, caps->limits.maxDynamicVertexBuffers, maxWidth, itemHeight);
			resourceBar(" FB", "Frame buffers", stats->numFrameBuffers, caps->limits.maxFrameBuffers, maxWidth, itemHeight);
			resourceBar(" IB", "Index buffers", stats->numIndexBuffers, caps->limits.maxIndexBuffers, maxWidth, itemHeight);
			resourceBar(" OQ", "Occlusion queries", stats->numOcclusionQueries, caps->limits.maxOcclusionQueries, maxWidth, itemHeight);
			resourceBar("  P", "Programs", stats->numPrograms, caps->limits.maxPrograms, maxWidth, itemHeight);
			resourceBar("  S", "Shaders", stats->numShaders, caps->limits.maxShaders, maxWidth, itemHeight);
			resourceBar("  T", "Textures", stats->numTextures, caps->limits.maxTextures, maxWidth, itemHeight);
			resourceBar("  U", "Uniforms", stats->numUniforms, caps->limits.maxUniforms, maxWidth, itemHeight);
			resourceBar(" VB", "Vertex buffers", stats->numVertexBuffers, caps->limits.maxVertexBuffers, maxWidth, itemHeight);
			resourceBar(" VL", "Vertex layouts", stats->numVertexLayouts, caps->limits.maxVertexLayouts, maxWidth, itemHeight);
			ImGui::PopFont();
		}
	}

	void DisplayProfilersInfo(const bgfx::Stats* stats)
	{
		if (ImGui::CollapsingHeader(ICON_FA_CLOCK_O " Profiler"))
		{
			if (0 == stats->numViews)
			{
				ImGui::Text("Profiler is not enabled.");
			}
			else
			{
				if (ImGui::BeginChild("##view_profiler", ImVec2(0.0f, 0.0f)))
				{
					ImGui::PushFont(ImGui::Font::Mono);

					ImVec4 cpuColor(0.5f, 1.0f, 0.5f, 1.0f);
					ImVec4 gpuColor(0.5f, 0.5f, 1.0f, 1.0f);

					const float itemHeight = ImGui::GetTextLineHeightWithSpacing();
					const float itemHeightWithSpacing = ImGui::GetFrameHeightWithSpacing();
					const double toCpuMs = 1000.0 / static_cast<double>(stats->cpuTimerFreq);
					const double toGpuMs = 1000.0 / static_cast<double>(stats->gpuTimerFreq);
					const float  scale = 3.0f;

					if (ImGui::BeginListBox("Encoders", ImVec2(ImGui::GetWindowWidth(), stats->numEncoders * itemHeightWithSpacing)))
					{
						ImGuiListClipper clipper;
						clipper.Begin(stats->numEncoders, itemHeight);

						while (clipper.Step())
						{
							for (int32_t pos = clipper.DisplayStart; pos < clipper.DisplayEnd; ++pos)
							{
								const bgfx::EncoderStats& encoderStats = stats->encoderStats[pos];

								ImGui::Text("%3d", pos);
								ImGui::SameLine(64.0f);

								const float maxWidth = 30.0f * scale;
								const float cpuMs = static_cast<float>((encoderStats.cpuTimeEnd - encoderStats.cpuTimeBegin) * toCpuMs);
								const float cpuWidth = bx::clamp(cpuMs * scale, 1.0f, maxWidth);

								if (bar(cpuWidth, maxWidth, itemHeight, cpuColor))
								{
									ImGui::SetTooltip("Encoder %d, CPU: %f [ms]"
										, pos
										, cpuMs
									);
								}
							}
						}

						ImGui::EndListBox();
					}

					ImGui::Separator();

					if (ImGui::BeginListBox("Views", ImVec2(ImGui::GetWindowWidth(), stats->numViews * itemHeightWithSpacing)))
					{
						ImGuiListClipper clipper;
						clipper.Begin(stats->numViews, itemHeight);

						while (clipper.Step())
						{
							for (int32_t pos = clipper.DisplayStart; pos < clipper.DisplayEnd; ++pos)
							{
								const bgfx::ViewStats& viewStats = stats->viewStats[pos];

								ImGui::Text("%3d %3d %s", pos, viewStats.view, viewStats.name);

								const float maxWidth = 30.0f * scale;
								const float cpuTimeElapsed = static_cast<float>((viewStats.cpuTimeEnd - viewStats.cpuTimeBegin) * toCpuMs);
								const float gpuTimeElapsed = static_cast<float>((viewStats.gpuTimeEnd - viewStats.gpuTimeBegin) * toGpuMs);
								const float cpuWidth = bx::clamp(cpuTimeElapsed * scale, 1.0f, maxWidth);
								const float gpuWidth = bx::clamp(gpuTimeElapsed * scale, 1.0f, maxWidth);

								ImGui::SameLine(64.0f);

								if (bar(cpuWidth, maxWidth, itemHeight, cpuColor))
								{
									ImGui::SetTooltip("View %d \"%s\", CPU: %f [ms]"
										, pos
										, viewStats.name
										, cpuTimeElapsed
									);
								}

								ImGui::SameLine();
								if (bar(gpuWidth, maxWidth, itemHeight, gpuColor))
								{
									ImGui::SetTooltip("View: %d \"%s\", GPU: %f [ms]"
										, pos
										, viewStats.name
										, gpuTimeElapsed
									);
								}
							}
						}

						ImGui::EndListBox();
					}

					ImGui::PopFont();
				}

				ImGui::EndChild();
			}
		}
	}

	void DisplayFrame(const bgfx::Stats* stats)
	{
		const double toMsCpu = 1000.0 / stats->cpuTimerFreq;
		const double toMsGpu = 1000.0 / stats->gpuTimerFreq;
		const double frameMs = static_cast<double>(stats->cpuTimeFrame) * toMsCpu;

		s_frameTime.pushSample(static_cast<float>(frameMs));

		char frameTextOverlay[256];
		bx::snprintf(frameTextOverlay, BX_COUNTOF(frameTextOverlay), "%s%.3fms, %s%.3fms\nAvg: %.3fms, %.1f FPS"
			, ICON_FA_ARROW_DOWN
			, s_frameTime.m_min
			, ICON_FA_ARROW_UP
			, s_frameTime.m_max
			, s_frameTime.m_avg
			, 1000.0f / s_frameTime.m_avg
		);

		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImColor(0.0f, 0.5f, 0.15f, 1.0f).Value);
		ImGui::PlotHistogram("Frame"
			, s_frameTime.m_values
			, SampleData::kNumSamples
			, s_frameTime.m_offset
			, frameTextOverlay
			, 0.0f
			, 60.0f
			, ImVec2(0.0f, 45.0f)
		);
		ImGui::PopStyleColor();

		ImGui::Text("Submit CPU %0.3f, GPU %0.3f (L: %d)"
			, static_cast<double>(stats->cpuTimeEnd - stats->cpuTimeBegin) * toMsCpu
			, static_cast<double>(stats->gpuTimeEnd - stats->gpuTimeBegin) * toMsGpu
			, stats->maxGpuLatency
		);

		if (-INT64_MAX != stats->gpuMemoryUsed)
		{
			char tmp0[64];
			bx::prettify(tmp0, BX_COUNTOF(tmp0), stats->gpuMemoryUsed);

			char tmp1[64];
			bx::prettify(tmp1, BX_COUNTOF(tmp1), stats->gpuMemoryMax);

			ImGui::Text("GPU mem: %s / %s", tmp0, tmp1);
		}
	}

	void ShowDebugWindow()
	{
		ImGui::SetNextWindowPos(ImVec2(10.0f, 50.0f), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);

		if (ImGui::Begin("Debug window"))
		{
			ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0)); //-ImGui::GetItemsLineHeightWithSpacing()));
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

			const bgfx::Stats* stats = bgfx::getStats();

			DisplayFrame(stats);

			if (ImGui::CollapsingHeader("Debug options", ImGuiTreeNodeFlags_CollapsingHeader))
			{
				ImGui::Checkbox("Show axis", &Game::Instance().GetDebugOptions().ShowAxis);
				ImGui::Checkbox("Show FPS", &Game::Instance().GetDebugOptions().ShowFPS);
			}

			const bgfx::Caps* caps = bgfx::getCaps();
			if (0 != (caps->supported & BGFX_CAPS_GRAPHICS_DEBUGGER))
			{
				ImGui::SameLine();
				ImGui::Text(ICON_FA_SNOWFLAKE_O);
			}

			DisplayResources(stats);
			DisplayProfilersInfo(stats);

#ifdef EDITOR
			if (ImGui::CollapsingHeader("entities", ImGuiTreeNodeFlags_OpenOnArrow))
			{
				// left
				static int selected = 0;
				ImGui::BeginChild("entities list", ImVec2(150, 0), true);

				for (auto it = Game::Instance().GetEntityManager().begin(); it != Game::Instance().GetEntityManager().end(); ++it)
				{
					char label[128];
					sprintf(label, "%s (%d)", it->second->GetName(), it->first);
					ImGui::Selectable(label, &it->second->_isSelected); //ImGui::SameLine(100); ImGui::Text(" 2,345 bytes");
				}
				ImGui::EndChild();
				ImGui::SameLine();

				// right
				ImGui::BeginGroup();
				BaseEntity* pEntity = Game::Instance().GetEntityManager().GetFirstSelectedEntity();

				if (pEntity != nullptr)
				{
					ImGui::BeginChild("item view", ImVec2(0, ImGui::GetTextLineHeightWithSpacing())); // Leave room for 1 line below us
					ImGui::Text("Object selected : %s (%d)", pEntity->GetName(), pEntity->Id());
					ImGui::Separator();

					ShowUI4AllComponents(pEntity);

					ImGui::EndChild();

					//Used to detect bug : button are cut at the bottom
					ImGui::BeginChild("buttons");
					if (ImGui::Button("Revert"))
					{

					}
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

	void DrawGrid(GridOrientation orientation, Line3DRendererComponent* line3DRenderer)
	{
		constexpr auto halfNumberOfLines = 100 >> 1;
		constexpr auto cellWidth = 10.0f;
		constexpr auto halfLength = halfNumberOfLines * cellWidth;
		const auto gridColor = Color::DimGray;

		for (auto i = 0; i <= halfNumberOfLines; i++)
		{
			const auto coord = cellWidth * i;

			switch (orientation)
			{
			case GridOrientation::XY:
				line3DRenderer->AddLine(Vector3(-halfLength, -coord, 0.0f), Vector3(halfLength, -coord, 0.0f), gridColor);
				line3DRenderer->AddLine(Vector3(-halfLength, coord, 0.0f), Vector3(halfLength, coord, 0.0f), gridColor);
				line3DRenderer->AddLine(Vector3(-coord, -halfLength, 0.0f), Vector3(-coord, halfLength, 0.0f), gridColor);
				line3DRenderer->AddLine(Vector3(coord, -halfLength, 0.0f), Vector3(coord, halfLength, 0.0f), gridColor);
				break;
			case GridOrientation::XZ:
				line3DRenderer->AddLine(Vector3(-halfLength, 0.0f, -coord), Vector3(halfLength, 0.0f, -coord), gridColor);
				line3DRenderer->AddLine(Vector3(-halfLength, 0.0f, coord), Vector3(halfLength, 0.0f, coord), gridColor);
				line3DRenderer->AddLine(Vector3(-coord, 0.0f, -halfLength), Vector3(-coord, 0.0f, halfLength), gridColor);
				line3DRenderer->AddLine(Vector3(coord, 0.0f, -halfLength), Vector3(coord, 0.0f, halfLength), gridColor);
				break;
			case GridOrientation::YZ:
				line3DRenderer->AddLine(Vector3(0.0f, -halfLength, -coord), Vector3(0.0f, halfLength, -coord), gridColor);
				line3DRenderer->AddLine(Vector3(0.0f, -halfLength, coord), Vector3(0.0f, halfLength, coord), gridColor);
				line3DRenderer->AddLine(Vector3(0.0f, -coord, -halfLength), Vector3(0.0f, -coord, halfLength), gridColor);
				line3DRenderer->AddLine(Vector3(0.0f, coord, -halfLength), Vector3(0.0f, coord, halfLength), gridColor);
				break;
			}
		}
		/*
		m_Line3DRenderer->AddLine(Vector3::Zero(), Color::Red, Vector3::UnitX(), Color::Red);
		m_Line3DRenderer->AddLine(Vector3::Zero(), Color::Green, Vector3::UnitY(), Color::Green);
		m_Line3DRenderer->AddLine(Vector3::Zero(), Color::Blue, Vector3::UnitZ(), Color::Blue);
		*/
	}
#endif
}
