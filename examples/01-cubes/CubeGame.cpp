#include "CubeGame.h"
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

	Game::Initialize();

	MeshRendererGameComponent* m_pModelRenderer = new MeshRendererGameComponent(this);

	AddComponent(m_pModelRenderer);

	GetDebugOptions().ShowAxis = true;
	GetDebugOptions().ShowFPS = true;
	GetDebugOptions().IsDebugActivated = true;
	GetDebugOptions().ShowLogInGame = true;
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
	m_pCamera3D->SetCamera(Vector3F(0, 20.0f, -50.0f), Vector3F::Zero(), Vector3F::Up());
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
	pTransform->SetLocalPosition(Vector3F(-delta, 0.5f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
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
	pTransform->SetLocalPosition(Vector3F(0.0f, 0.5f, delta));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
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
	pTransform->SetLocalPosition(Vector3F(delta, 0.5f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
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
	pTransform->SetLocalPosition(Vector3F(0.0f, 0.0f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	pModelCpt = new MeshComponent(pEntity);
	pPrimitive = new PlanePrimitive(100.0f, 100.0f);
	pModel = pPrimitive->CreateModel();
	Material* pMat = pModel->GetMaterial()->Clone();
	pModel->SetMaterial(pMat);
	pMat->Texture0(Texture::loadTexture(Game::Instance().GetMediaManager().FindMedia("ceilingMain_DIF.dds"), BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC));
	pMat->Texture0Repeat(Vector2F(50, 50));
	//
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(pEntity);

	m_pWorld->Initialize();
}