#include "CubeGame.h"

#include <bx/math.h>
#include <bx/string.h>
#include <bx/timer.h>

#include "bgfx\bgfx.h"

#include "Entities\Components\Cameras\ArcBallCameraComponent.h"
#include "Entities\Components\MeshComponent.h"
#include "Entities\Components\Transform3DComponent.h"
#include "Game\GameInfo.h"
#include "Game\MeshRendererGameComponent.h"
#include "Graphics\Primitives\BoxPrimitive.h"
#include "Graphics\Primitives\CylinderPrimitive.h"
#include "Graphics\Primitives\PlanePrimitive.h"
#include "Graphics\Primitives\SpherePrimitive.h"
#include "Log\LoggerFile.h"
#include "Log\LogManager.h"
#include "World\World.h"

#include "iconfontheaders/icons_kenney.h"
#include "iconfontheaders/icons_font_awesome.h"

void showExampleDialog(const char* title, const char* _errorText);

CubeGame::CubeGame()
{
	Logging.AddLogger(new LoggerFile("Out.log"));
}

void CubeGame::Initialize()
{
	GetMediaManager().AddSearchPath("../../examples/resources");
	GetMediaManager().AddSearchPath("../../examples/resources/textures");
	GetMediaManager().AddSearchPath("../../examples/resources/models");
	GetMediaManager().AddSearchPath("../../examples/resources/shaders");
	GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
	GetMediaManager().AddSearchPath("../../examples/resources/script");
	GetMediaManager().AddSearchPath("../../examples/resources/fonts");

	AddDebugComponents();
	AddUsualComponents();

	GetDebugOptions().ShowAxis = true;
	GetDebugOptions().ShowFPS = true;
	GetDebugOptions().IsDebugActivated = true;
	GetDebugOptions().ShowLogInGame = true;
	Game::Initialize();
}

void CubeGame::LoadContent()
{
	Game::LoadContent();

	World* m_pWorld = new World();
	Game::Instance().GetGameInfo().SetWorld(m_pWorld);

	m_pProgram = new Program("vs_mesh", "fs_mesh");

	//Camera 3D
	BaseEntity* pCamera = new BaseEntity();
	ArcBallCameraComponent* m_pCamera3D = new ArcBallCameraComponent(pCamera);
	m_pCamera3D->SetCamera(Vector3(0, 20.0f, -50.0f), Vector3::Zero(), Vector3::Up());
	m_pCamera3D->Distance(15.0f);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);
	m_pWorld->AddEntity(pCamera);
	Game::Instance().GetGameInfo().SetActiveCamera(m_pCamera3D);

	const float delta = 3.0f;
	BaseEntity* pEntity;
	Transform3DComponent* pTransform;
	MeshComponent* pModelCpt;
	IPrimitive3D* pPrimitive;
	Mesh* pModel;

	//Cylinder
	pEntity = new BaseEntity();
	pEntity->SetName("cylinder");
	pTransform = new Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3(-delta, 0.5f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	pModelCpt = new MeshComponent(pEntity);
	pPrimitive = new CylinderPrimitive();
	pModel = pPrimitive->CreateModel();
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(pEntity);

	//Box
	pEntity = new BaseEntity();
	pEntity->SetName("box");
	pTransform = new Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3(0.0f, 0.5f, delta));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	pModelCpt = new MeshComponent(pEntity);
	pPrimitive = new BoxPrimitive();
	pModel = pPrimitive->CreateModel();
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(pEntity);

	//Sphere
	pEntity = new BaseEntity();
	pEntity->SetName("sphere");
	pTransform = new Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3(delta, 0.5f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	pModelCpt = new MeshComponent(pEntity);
	pPrimitive = new SpherePrimitive();
	pModel = pPrimitive->CreateModel();
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(pEntity);

	//ground
	pEntity = new BaseEntity();
	pEntity->SetName("ground");
	pTransform = new Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	pModelCpt = new MeshComponent(pEntity);
	pPrimitive = new PlanePrimitive(100.0f, 100.0f);
	pModel = pPrimitive->CreateModel();
	Material* pMat = pModel->GetMaterial()->Clone();
	pModel->SetMaterial(pMat);
	pMat->Texture0(Texture::loadTexture(Game::Instance().GetMediaManager().FindMedia("ceilingMain_DIF.dds"), BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC));
	pMat->Texture0Repeat(Vector2(50, 50));
	//
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(pEntity);

	m_pWorld->Initialize();
}

Vector3 position;
float angle = 0.0f;

void gizmo(const float* _view, const float* _proj)
{
	float mtx[16];
	float scale[3] = { 1.0f, 1.0f, 1.0f };

	ImGuizmo::RecomposeMatrixFromComponents(position, &angle, scale, mtx);

	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

	ImGuizmo::Manipulate(
		_view
		, _proj
		, ImGuizmo::TRANSLATE
		, ImGuizmo::LOCAL
		, mtx
	);

	ImGuizmo::DecomposeMatrixToComponents(mtx, position, &angle, scale);
}

void CubeGame::Draw()
{
	Game::Draw();

	showExampleDialog("basic demo", "");
	float* _proj = GetGameInfo().GetActiveCamera()->GetProjectionMatrix();
	float* _view = GetGameInfo().GetActiveCamera()->GetViewMatrix();
	gizmo(_view, _proj);
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
		bx::memSet(m_values, 0, sizeof(m_values));

		m_min = 0.0f;
		m_max = 0.0f;
		m_avg = 0.0f;
	}

	void pushSample(float value)
	{
		m_values[m_offset] = value;
		m_offset = (m_offset + 1) % kNumSamples;

		float min = bx::kFloatMax;
		float max = -bx::kFloatMax;
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

static const ImVec4 s_resourceColor(0.5f, 0.5f, 0.5f, 1.0f);

static void resourceBar(const char* _name, const char* _tooltip, uint32_t _num, uint32_t _max, float _maxWidth, float _height)
{
	bool itemHovered = false;

	ImGui::Text("%s: %4d / %4d", _name, _num, _max);
	itemHovered |= ImGui::IsItemHovered();
	ImGui::SameLine();

	const float percentage = float(_num) / float(_max);

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

static bool s_showStats = false;


void showExampleDialog(const char* title, const char* _errorText)
{
	char temp[1024];
	bx::snprintf(temp, BX_COUNTOF(temp), "Example: %s", title);

	ImGui::SetNextWindowPos(
		ImVec2(10.0f, 50.0f)
		, ImGuiCond_FirstUseEver
	);
	ImGui::SetNextWindowSize(
		ImVec2(300.0f, 210.0f)
		, ImGuiCond_FirstUseEver
	);

	ImGui::Begin(temp);

	ImGui::TextWrapped("%s", "description de la demo");

	ImGui::Separator();

	if (nullptr != _errorText)
	{
		const int64_t now = bx::getHPCounter();
		const int64_t freq = bx::getHPFrequency();
		const float   time = float(now % freq) / float(freq);

		bool blink = time > 0.5f;

		ImGui::PushStyleColor(ImGuiCol_Text
			, blink
			? ImVec4(1.0, 0.0, 0.0, 1.0)
			: ImVec4(1.0, 1.0, 1.0, 1.0)
		);
		ImGui::TextWrapped("%s", _errorText);
		ImGui::Separator();
		ImGui::PopStyleColor();
	}

	{
		const bgfx::Caps* caps = bgfx::getCaps();
		if (0 != (caps->supported & BGFX_CAPS_GRAPHICS_DEBUGGER))
		{
			ImGui::SameLine();
			ImGui::Text(ICON_FA_SNOWFLAKE_O);
		}

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(3.0f, 3.0f));

		//if (ImGui::Button(ICON_FA_REPEAT " Restart"))
		//{
		//	cmdExec("app restart");
		//}
		//
		//ImGui::SameLine();
		//if (ImGui::Button(ICON_KI_EXIT " Exit"))
		//{
		//	cmdExec("exit");
		//}

		ImGui::SameLine();
		s_showStats ^= ImGui::Button(ICON_FA_BAR_CHART);

		ImGui::PopStyleVar();
	}

	const bgfx::Stats* stats = bgfx::getStats();
	const double toMsCpu = 1000.0 / stats->cpuTimerFreq;
	const double toMsGpu = 1000.0 / stats->gpuTimerFreq;
	const double frameMs = double(stats->cpuTimeFrame) * toMsCpu;

	s_frameTime.pushSample(float(frameMs));

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
		, double(stats->cpuTimeEnd - stats->cpuTimeBegin) * toMsCpu
		, double(stats->gpuTimeEnd - stats->gpuTimeBegin) * toMsGpu
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

	if (s_showStats)
	{
		ImGui::SetNextWindowSize(
			ImVec2(300.0f, 500.0f)
			, ImGuiCond_FirstUseEver
		);

		if (ImGui::Begin(ICON_FA_BAR_CHART " Stats", &s_showStats))
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
						const double toCpuMs = 1000.0 / double(stats->cpuTimerFreq);
						const double toGpuMs = 1000.0 / double(stats->gpuTimerFreq);
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
									const float cpuMs = float((encoderStats.cpuTimeEnd - encoderStats.cpuTimeBegin) * toCpuMs);
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
									const float cpuTimeElapsed = float((viewStats.cpuTimeEnd - viewStats.cpuTimeBegin) * toCpuMs);
									const float gpuTimeElapsed = float((viewStats.gpuTimeEnd - viewStats.gpuTimeBegin) * toGpuMs);
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
		ImGui::End();
	}

	ImGui::End();
}

