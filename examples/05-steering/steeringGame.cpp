#include <string>

#include "steeringGame.h"

#include <bgfx/defines.h>

#include "Entities/Components/AnimatedSpriteComponent.h"
#include "Entities/Components/Camera3DComponent.h"
#include "Entities/Components/CameraControllers/ArcBallCameraController.h"
#include "Entities/Components/MeshComponent.h"
#include "Entities/Components/Physics/RigidBodyComponent.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "Game/Input.h"
#include "GameTime.h"
#include "Graphics/Materials/Material.h"
#include "Graphics/Mesh/Mesh.h"
#include "Graphics/Primitives/BoxPrimitive.h"
#include "Graphics/Primitives/PlanePrimitive.h"
#include "Graphics/Textures/Texture.h"
#include "Log/LoggerFile.h"
#include "Maths/Vector3.h"

#include "Entities/Components/MovingEntity2DComponent.h"
#include "Entities/Components/SteeringBehaviorComponent.h"

using namespace CasaEngine;

/**
 *
 */
SteeringGame::SteeringGame() :
	m_pLine3DRenderer(nullptr),
	m_pWorld(nullptr),
	m_pModelRenderer(nullptr)
{
	Logging.AddLogger(new LoggerFile("Out.log"));
}

/**
 *
 */
SteeringGame::~SteeringGame()
{
	if (m_pModelRenderer != nullptr) delete m_pModelRenderer;
	if (m_pLine3DRenderer != nullptr) delete m_pLine3DRenderer;

	//Game::Instance().GetEntityManager().Clear();
	//PhysicsEngine::Destroy();
}

/**
 *
 */
void SteeringGame::Initialize()
{
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/textures");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/models");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/shaders");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/script");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/fonts");

	AddGameComponents();

	Game::Initialize();
}

/**
 *
 */
void SteeringGame::LoadContent()
{
	Game::LoadContent();

	m_pWorld = new World();
	Game::Instance().GetGameInfo().SetWorld(m_pWorld);
	//m_pWorld->SetPhysicsWorld(PhysicsEngine::Instance().CreateWorld());

	CreateEntities();
	CreateBoids();
}

/**
 *
 */
void SteeringGame::Update(const GameTime& gameTime_)
{
	Game::Update(gameTime_);
}

/**
 *
 */
void SteeringGame::Draw()
{
	Game::Draw();
}

/**
 *
 */
void SteeringGame::AddGameComponents()
{
	m_pModelRenderer = new MeshRendererGameComponent(this);
	m_pLine3DRenderer = new Line3DRendererComponent(this);

	AddComponent(m_pModelRenderer);
	AddComponent(m_pLine3DRenderer);
}

/**
 *
 */
void SteeringGame::CreateEntities()
{
	m_pProgram = new Program("vs_mesh", "fs_mesh");

	//////////////////////////////////////////////////////////////////////////
	// Camera 3D
	BaseEntity* pCamera = new BaseEntity();
	m_pCamera3D = new Camera3DComponent(pCamera);
	ArcBallCameraController* pArcBall = new ArcBallCameraController(m_pCamera3D);
	pArcBall->SetCamera(Vector3F(0, 20.0f, -50.0f), Vector3F::Zero(), Vector3F::Up());
	pArcBall->Distance(15.0f);
	m_pCamera3D->CameraController(pArcBall);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);
	pCamera->Initialize();
	m_pWorld->AddEntity(pCamera);
	Game::Instance().GetGameInfo().SetActiveCamera(m_pCamera3D);

	//////////////////////////////////////////////////////////////////////////
	// ground
	BaseEntity* pEntity = new BaseEntity();
	pEntity->SetName("ground");
	Transform3DComponent* pTransform = new Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3F(0.0f, -0.5f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	MeshComponent* pModelCpt = new MeshComponent(pEntity);
	BoxPrimitive* pBox = new BoxPrimitive(100.0f, 1.0f, 100.0f);
	Mesh* pModel = pBox->CreateModel();
	//new material
	Material* pMat = pModel->GetMaterial()->Clone();
	pMat->Texture0(Texture::loadTexture(Game::Instance().GetMediaManager().FindMedia("ceilingMain_DIF.dds"), BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC));
	pMat->Texture0Repeat(Vector2F(50, 50));
	pModel->SetMaterial(pMat);
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
void SteeringGame::CreateBoids()
{
	BaseEntity* pEntity = new BaseEntity();
	Transform3DComponent* pTrans3D = new Transform3DComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pTrans3D);

	MovingEntity2DComponent* pMovingCpnt = new MovingEntity2DComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pMovingCpnt);

	SteeringBehaviorComponent* pSteeringCpnt = new SteeringBehaviorComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pSteeringCpnt);

	pEntity->Initialize();
	m_pWorld->AddEntity(pEntity);

	m_Entities.push_back(pEntity);
}