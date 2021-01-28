#include "CubeGame.h"
#include "bgfx\bgfx.h"

#include "Entities\Components\Camera3DComponent.h"
#include "Entities\Components\CameraControllers\ArcBallCameraController.h"
#include "Entities\Components\MeshComponent.h"
#include "Entities\Components\Transform3DComponent.h"
#include "GameTime.h"
#include "Game\GameInfo.h"
#include "Game\MeshRendererGameComponent.h"
#include "Graphics\Primitives\BoxPrimitive.h"
#include "Graphics\Primitives\CylinderPrimitive.h"
#include "Graphics\Primitives\PlanePrimitive.h"
#include "Graphics\Primitives\SpherePrimitive.h"
#include "Log\LoggerFile.h"
#include "Log\LogManager.h"
#include "World\World.h"

/**
 *
 */
CubeGame::CubeGame()
{
	Logging.AddLogger(NEW_AO LoggerFile("Out.log"));
}

/**
 *
 */
CubeGame::~CubeGame()
{
}

/**
 *
 */
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

	MeshRendererGameComponent* m_pModelRenderer = NEW_AO MeshRendererGameComponent(this);

	AddComponent(m_pModelRenderer);

	GetDebugOptions().ShowAxis = true;
	GetDebugOptions().ShowFPS = true;
	GetDebugOptions().IsDebugActivated = true;
	GetDebugOptions().ShowLogInGame = true;
}

/**
 *
 */
void CubeGame::LoadContent()
{
	Game::LoadContent();

	World* m_pWorld = NEW_AO World();
	Game::Instance().GetGameInfo().SetWorld(m_pWorld);

	m_pProgram = NEW_AO Program("vs_mesh", "fs_mesh");

	//Camera 3D
	BaseEntity* pCamera = NEW_AO BaseEntity();
	Camera3DComponent* m_pCamera3D = NEW_AO Camera3DComponent(pCamera);
	ArcBallCameraController* pArcBall = NEW_AO ArcBallCameraController(m_pCamera3D);
	pArcBall->SetCamera(Vector3F(0, 20.0f, -50.0f), Vector3F::Zero(), Vector3F::Up());
	pArcBall->Distance(15.0f);
	m_pCamera3D->CameraController(pArcBall);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);
	m_pWorld->AddEntity(pCamera);
	Game::Instance().GetGameInfo().SetActiveCamera(m_pCamera3D);

	const float delta = 3.0f;

	//Box
	BaseEntity* pEntity = NEW_AO BaseEntity();
	pEntity->SetName("box");
	Transform3DComponent* pTransform = NEW_AO Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3F(0.0f, 0.5f, delta));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	MeshComponent* pModelCpt = NEW_AO MeshComponent(pEntity);
	IPrimitive3D* pPrimitive = NEW_AO BoxPrimitive();
	Mesh* pModel = pPrimitive->CreateModel();
	//Game::Instance().GetResourceManager().Add("boxModel", pModel);
	//DELETE_AO pPrimitive;
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(pEntity);

	//Sphere
	pEntity = NEW_AO BaseEntity();
	pEntity->SetName("sphere");
	pTransform = NEW_AO Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3F(delta, 0.5f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	pModelCpt = NEW_AO MeshComponent(pEntity);
	pPrimitive = NEW_AO SpherePrimitive();
	pModel = pPrimitive->CreateModel();
	//Game::Instance().GetResourceManager().Add("sphereModel", pModel);
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	//DELETE_AO pPrimitive;
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(pEntity);

	//Cylinder
	pEntity = NEW_AO BaseEntity();
	pEntity->SetName("cylinder");
	pTransform = NEW_AO Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3F(-delta, 0.5f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	pModelCpt = NEW_AO MeshComponent(pEntity);
	pPrimitive = NEW_AO CylinderPrimitive();
	pModel = pPrimitive->CreateModel();
	//Game::Instance().GetResourceManager().Add("cylinderModel", pModel);
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	//DELETE_AO pPrimitive;
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(pEntity);

	//ground
	pEntity = NEW_AO BaseEntity();
	pEntity->SetName("ground");
	pTransform = NEW_AO Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3F(0.0f, 0.0f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	pModelCpt = NEW_AO MeshComponent(pEntity);
	pPrimitive = NEW_AO PlanePrimitive(100.0f, 100.0f);
	pModel = pPrimitive->CreateModel();
	//Game::Instance().GetResourceManager().Add("groundModel", pModel);
	//DELETE_AO pPrimitive;
	//new material
	Material* pMat = pModel->GetMaterial()->Clone();
	//Game::Instance().GetResourceManager().Add("groundMaterial", pMat);
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

/**
 *
 */
void CubeGame::Draw()
{
	Game::Draw();
}

/**
 *
 */
void CubeGame::Update(const GameTime& gameTime_)
{
	Game::Update(gameTime_);
}