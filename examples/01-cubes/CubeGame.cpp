#include  "CubeGame.hpp"

#include <bx/math.h>
#include <bx/timer.h>

#include  "Entities/Components/Cameras/ArcBallCameraComponent.hpp"
#include  "Entities/Components/MeshComponent.hpp"
#include  "Game/GameInfo.hpp"
#include  "Game/MeshRendererGameComponent.hpp"
#include  "Graphics/Primitives/BoxPrimitive.hpp"
#include  "Graphics/Primitives/CylinderPrimitive.hpp"
#include  "Graphics/Primitives/PlanePrimitive.hpp"
#include  "Graphics/Primitives/SpherePrimitive.hpp"
#include  "Log/LoggerFile.hpp"
#include  "Log/LogManager.hpp"
#include  "World/World.hpp"

Matrix4 entityMatrix;

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
	MeshComponent* pModelCpt;
	IPrimitive3D* pPrimitive;
	Mesh* pModel;

	//Cylinder
	pEntity = new BaseEntity();
	pEntity->SetName("cylinder");
	pEntity->GetCoordinates().SetLocalPosition(Vector3(-delta, 0.5f, 0.0f));
	pEntity->GetCoordinates().SetLocalRotation(0.0f);
	pEntity->GetCoordinates().SetLocalScale(Vector3::One());
	pModelCpt = new MeshComponent(pEntity);
	pPrimitive = new CylinderPrimitive();
	pModel = pPrimitive->CreateMesh();
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(pEntity);

	//Box
	pEntity = new BaseEntity();
	pEntity->SetName("box");
	pEntity->GetCoordinates().SetLocalPosition(Vector3(0.0f, 0.5f, delta));
	pEntity->GetCoordinates().SetLocalRotation(0.0f);
	pEntity->GetCoordinates().SetLocalScale(Vector3::One());
	entityMatrix = pEntity->GetCoordinates().GetLocalMatrix();
	pModelCpt = new MeshComponent(pEntity);
	pPrimitive = new BoxPrimitive();
	pModel = pPrimitive->CreateMesh();
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(pEntity);

	//Sphere
	pEntity = new BaseEntity();
	pEntity->SetName("sphere");
	pEntity->GetCoordinates().SetLocalPosition(Vector3(delta, 0.5f, 0.0f));
	pEntity->GetCoordinates().SetLocalRotation(0.0f);
	pEntity->GetCoordinates().SetLocalScale(Vector3::One());
	pModelCpt = new MeshComponent(pEntity);
	pPrimitive = new SpherePrimitive();
	pModel = pPrimitive->CreateMesh();
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(pEntity);

	//ground
	pEntity = new BaseEntity();
	pEntity->SetName("ground");
	pEntity->GetCoordinates().SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
	pEntity->GetCoordinates().SetLocalRotation(0.0f);
	pEntity->GetCoordinates().SetLocalScale(Vector3::One());
	pModelCpt = new MeshComponent(pEntity);
	pPrimitive = new PlanePrimitive(100.0f, 100.0f);
	pModel = pPrimitive->CreateMesh();
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

void gizmo(const float* _view, const float* _proj, BaseEntity* entity)
{
	//float* entityMatrix = entity->GetCoordinates().GetLocalMatrix();

	//Vector3 position = transform_3d_component->GetLocalPosition();
	//float rotation[3] = { 0.0f, 0.0f, 0.0f };
	//float mtx[16];
	//float scale[3] = { 1.0f, 1.0f, 1.0f };
	//ImGuizmo::RecomposeMatrixFromComponents(position, rotation, scale, mtx);

	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

	//auto* camera = dynamic_cast<ArcBallCameraComponent*>(Game::Instance().GetGameInfo().GetActiveCamera());

	//float view[16];
	//auto position = camera->Position();
	//auto target = camera->Target();
	//auto up = camera->Up();
	//bx::mtxLookAt(view,
	//	bx::Vec3(position.x, position.y, position.z),
	//	bx::Vec3(target.x, target.y, target.z),
	//	bx::Vec3(up.x, up.y, up.z));

	//auto& viewport = camera->GetViewport();
	//float ratio = viewport.Width() * Game::Instance().GetWindowSize().x / (viewport.Height() * Game::Instance().GetWindowSize().y);
	//float proj[16];
	//bx::mtxProj(proj, ToDegree(camera->FOV()), ratio, viewport.NearClipPlane(), viewport.FarClipPlane(), false, bx::Handness::Left);

	//std::ostringstream oss;
	//oss << "Casaengine" << std::endl;
	//for (int y = 0; y < 4; y++)
	//{
	//	for (int x = 0; x < 4; x++)
	//	{
	//		oss << _proj[x + y * 4] << " ";
	//	}
	//
	//	oss << std::endl;
	//}
	//oss << "bx" << std::endl;
	//for (int y = 0; y < 4; y++)
	//{
	//	for (int x = 0; x < 4; x++)
	//	{
	//		oss << proj[x + y * 4] << " ";
	//	}
	//
	//	oss << std::endl;
	//}
	//
	//OutputDebugStringA(oss.str().c_str());


	//std::ostringstream oss;
	//oss << "Before" << std::endl;
	//for (int y = 0; y < 4; y++)
	//{
	//	for (int x = 0; x < 4; x++)
	//	{
	//		oss << entityMatrix[x + y * 4] << " ";
	//	}
	//
	//	oss << std::endl;
	//}

	if (ImGuizmo::Manipulate(
		_view
		,
		_proj
		, ImGuizmo::TRANSLATE
		, ImGuizmo::LOCAL
		, entityMatrix))
	{
		//OutputDebugStringA("manipulated\n");
		entity->GetCoordinates().SetLocalPosition(entityMatrix.Translation());
	}

	//oss << "After" << std::endl;
	//for (int y = 0; y < 4; y++)
	//{
	//	for (int x = 0; x < 4; x++)
	//	{
	//		oss << entityMatrix[x + y * 4] << " ";
	//	}
	//
	//	oss << std::endl;
	//}
	//OutputDebugStringA(oss.str().c_str());

	//ImGuizmo::DecomposeMatrixToComponents(mtx, position, &angle, scale);
}

void CubeGame::Draw()
{
	float* _proj = GetGameInfo().GetActiveCamera()->GetProjectionMatrix();
	float* _view = GetGameInfo().GetActiveCamera()->GetViewMatrix();
	gizmo(_view, _proj, this->GetEntityManager().GetEntityFromName("box"));

	Game::Draw();
}
