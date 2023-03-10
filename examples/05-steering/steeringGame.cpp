#include <string>

#include "steeringGame.h"

#include <bgfx/defines.h>

#include "Entities/Components/AnimatedSpriteComponent.h"
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
#include "Entities/Components/Cameras/ArcBallCameraComponent.h"

using namespace CasaEngine;

SteeringGame::SteeringGame()
{
	Logging.AddLogger(new LoggerFile("Out.log"));
}

SteeringGame::~SteeringGame()
{
}

void SteeringGame::Initialize()
{
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/textures");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/models");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/shaders");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/script");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/fonts");

	AddDebugComponents();
	AddUsualComponents();

	Game::Initialize();
}

void SteeringGame::LoadContent()
{
	Game::LoadContent();

	m_pWorld = new World();
	Game::Instance().GetGameInfo().SetWorld(m_pWorld);
	//m_pWorld->SetPhysicsWorld(PhysicsEngine::Instance().CreateWorld());

	CreateEntities();
	CreateBoids();
}

void SteeringGame::Update(const GameTime& gameTime_)
{
	Game::Update(gameTime_);
}

void SteeringGame::Draw()
{
	Game::Draw();
}

void SteeringGame::CreateEntities()
{
	m_pProgram = new Program("vs_mesh", "fs_mesh");

	//////////////////////////////////////////////////////////////////////////
	// Camera 3D
	BaseEntity* pCamera = new BaseEntity();
	m_pCamera3D = new ArcBallCameraComponent(pCamera);
	m_pCamera3D->SetCamera(Vector3(0, 20.0f, -50.0f), Vector3::Zero(), Vector3::Up());
	m_pCamera3D->Distance(15.0f);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);
	pCamera->Initialize();
	m_pWorld->AddEntity(pCamera);
	Game::Instance().GetGameInfo().SetActiveCamera(m_pCamera3D);

	//////////////////////////////////////////////////////////////////////////
	// ground
	BaseEntity* pEntity = new BaseEntity();
	pEntity->SetName("ground");
	Transform3DComponent* pTransform = new Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3(0.0f, -0.5f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	MeshComponent* pModelCpt = new MeshComponent(pEntity);
	BoxPrimitive* pBox = new BoxPrimitive(100.0f, 1.0f, 100.0f);
	Mesh* pModel = pBox->CreateMesh();
	//new material
	Material* pMat = pModel->GetMaterial()->Clone();
	pMat->Texture0(Texture::loadTexture(Game::Instance().GetMediaManager().FindMedia("ceilingMain_DIF.dds"), BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC));
	pMat->Texture0Repeat(Vector2(50, 50));
	pModel->SetMaterial(pMat);
	//
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);

	pEntity->GetComponentMgr()->AddComponent(pModelCpt);
	pEntity->Initialize();

	m_pWorld->AddEntity(pEntity);
}

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