#include "CubesGame.h"
#include "bgfx.h"

#include "Entities\Components\Camera3DComponent.h"
#include "Entities\Components\CameraControllers\ArcBallCameraController.h"
#include "Entities\Components\MeshComponent.h"
#include "Entities\Components\Transform3DComponent.h"
#include "GameTime.h"
#include "Game\GameInfo.h"
#include "Game\Line2DRendererComponent.h"
#include "Game\Line3DRendererComponent.h"
#include "Game\MeshRendererGameComponent.h"
#include "Graphics\Effects\Shader.h"
#include "Graphics\Primitives\BoxPrimitive.h"
#include "Graphics\Primitives\CylinderPrimitive.h"
#include "Graphics\Primitives\PlanePrimitive.h"
#include "Graphics\Primitives\SpherePrimitive.h"
#include "Graphics\bgfx_utils.h"
#include "Log\LoggerFile.h"
#include "Log\LogManager.h"
#include "Tools\DebugSystem.h"
#include "World\World.h"

/**
 * 
 */
CubesGame::CubesGame()
{
	Logging.AddLogger(NEW_AO LoggerFile("Out.log"));
}

/**
 * 
 */
CubesGame::~CubesGame()
{
	//bgfx::destroyProgram(m_Program);
}

/**
 * 
 */
void CubesGame::Initialize()
{
	Game::Initialize();

	MediaManager::Instance().AddSearchPath("../../examples/resources");
	MediaManager::Instance().AddSearchPath("../../examples/resources/textures");
	MediaManager::Instance().AddSearchPath("../../examples/resources/models");
	MediaManager::Instance().AddSearchPath("../../examples/resources/shaders");
	MediaManager::Instance().AddSearchPath("../../examples/resources/spriteSheet");
	MediaManager::Instance().AddSearchPath("../../examples/resources/script");
	MediaManager::Instance().AddSearchPath("../../examples/resources/fonts");


// 	Line2DRendererComponent *m_pLine2DRenderer = NEW_AO Line2DRendererComponent(this);
// 	Line3DRendererComponent *m_pLine3DRenderer = NEW_AO Line3DRendererComponent(this);
	MeshRendererGameComponent *m_pModelRenderer = NEW_AO MeshRendererGameComponent(this);
	//DebugSystem *m_pDebugSystem = NEW_AO DebugSystem(this);

// 	AddComponent(m_pLine2DRenderer);
// 	AddComponent(m_pLine3DRenderer);	
	AddComponent(m_pModelRenderer);
	//AddComponent(m_pDebugSystem);
}

/**
 * 
 */
void CubesGame::LoadContent()
{
	Game::LoadContent();

	World *m_pWorld = NEW_AO World();
	GameInfo::Instance().SetWorld(m_pWorld);

	m_pProgram = Program::loadProgram("vs_mesh", "fs_mesh");

	//Camera 3D
	BaseEntity *pCamera = NEW_AO BaseEntity();
	Camera3DComponent *m_pCamera3D = NEW_AO Camera3DComponent(pCamera);
	ArcBallCameraController *pArcBall = NEW_AO ArcBallCameraController(m_pCamera3D);
	pArcBall->SetCamera(Vector3F(0, 20.0f, -50.0f), Vector3F::Zero(), Vector3F::Up());
	pArcBall->Distance(15.0f);
	m_pCamera3D->CameraController(pArcBall);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);	
	pCamera->Initialize();
	m_pWorld->AddEntity(pCamera);
	GameInfo::Instance().SetActiveCamera(m_pCamera3D);

	const float delta = 3.0f;

	//Box
	BaseEntity* pEntity = NEW_AO BaseEntity();
	pEntity->SetName("box");
	Transform3DComponent *pTransform = NEW_AO Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3F(0.0f, 0.5f, delta));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	MeshComponent *pModelCpt = NEW_AO MeshComponent(pEntity);
	IPrimitive3D *pPrimitive = NEW_AO BoxPrimitive();
	Mesh *pModel = pPrimitive->CreateModel();
	//ResourceManager::Instance().Add("boxModel", pModel);
	//DELETE_AO pPrimitive;
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);
	pEntity->Initialize();

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
	//ResourceManager::Instance().Add("sphereModel", pModel);
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	//DELETE_AO pPrimitive;
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);
	pEntity->Initialize();

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
	//ResourceManager::Instance().Add("cylinderModel", pModel);
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	//DELETE_AO pPrimitive;
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);
	pEntity->Initialize();

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
	//ResourceManager::Instance().Add("groundModel", pModel);
	//DELETE_AO pPrimitive;
	//new material
	Material* pMat = pModel->GetMaterial()->Clone();
	//ResourceManager::Instance().Add("groundMaterial", pMat);
	pModel->SetMaterial(pMat);
	pMat->Texture0(Texture::loadTexture("ceilingMain_DIF.dds", BGFX_TEXTURE_MIN_ANISOTROPIC | BGFX_TEXTURE_MAG_ANISOTROPIC));
	pMat->Texture0Repeat(Vector2F(50, 50));
	//
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);
	pEntity->GetComponentMgr()->AddComponent(pModelCpt);
	pEntity->Initialize();

	m_pWorld->AddEntity(pEntity);
}

/**
 * 
 */
void CubesGame::Draw()
{
	Game::Draw();
}

/**
 * 
 */
void CubesGame::Update(const GameTime& gameTime_)
{
	Game::Update(gameTime_);
}
