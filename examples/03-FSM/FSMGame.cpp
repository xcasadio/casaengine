#include "FSMGame.h"

#include <string>
#include <iosfwd>

#include "Entities/Components/Camera2DComponent.h"
#include "Entities/Components/CameraControllers/ArcBallCameraController.h"
#include "Entities/Components/FSMComponent.h"
#include "Entities/EntityManager.h"
#include "Game/GameInfo.h"
#include "Graphics/Renderer/Renderer.h"
#include "Log/LoggerFile.h"
#include "Maths/Math.h"
#include "Maths/Vector4.h"
#include "Sprite/SpriteTypes.h"
#include "WestWorldWithMessaging/MinerComponent.h"
#include "WestWorldWithMessaging/MinersWifeComponent.h"


using namespace CasaEngine;

/**
 * 
 */
FSMGame::FSMGame()
{
	Logging.AddLogger(NEW_AO LoggerFile("Out.log"));
}

/**
 * 
 */
FSMGame::~FSMGame()
{
	delete m_pElsa;
	delete m_pBob;
}

/**
 * 
 */
void FSMGame::Initialize()
{
	MediaManager::Instance().AddSearchPath("../../examples/resources");
	MediaManager::Instance().AddSearchPath("../../examples/resources/textures");
	MediaManager::Instance().AddSearchPath("../../examples/resources/models");
	MediaManager::Instance().AddSearchPath("../../examples/resources/shaders");
	MediaManager::Instance().AddSearchPath("../../examples/resources/spriteSheet");
	MediaManager::Instance().AddSearchPath("../../examples/resources/fonts");
}

/**
 * 
 */
void FSMGame::LoadContent()
{
	Game::LoadContent();

	GameInfo::Instance().SetWorld(NEW_AO World());

	// Définition arbitraire des paramètres de caméra et de lumière
	m_CameraPos.Set(0, 0, -40);

	// Initialisation des matrices de transformation 3D
	Matrix4 MatView, MatProj, MatRotY, MatRotZ;
	MatRotY.CreateRotationY(-MATH_PI_DIV_2, Vector3F(0, 0, 0));
	MatRotZ.CreateRotationZ(-MATH_PI_DIV_2, Vector3F(0, 0, 0));
	m_MatView3D.LookAt(m_CameraPos, m_CameraPos + Vector3F(0.0f, 0.0f, 1.0f));
	m_MatView3D = MatRotY * MatRotZ * m_MatView3D;
	m_MatProj3D.PerspectiveFOV(MATH_PI_DIV_2, 640.0f / 480.0f, 1.0f, 200.0f);

	//Camera 3D
	BaseEntity *pCamera = NEW_AO BaseEntity();
	m_pCamera3D = NEW_AO Camera3DComponent(pCamera);
	ArcBallCameraController *pArcBall = NEW_AO ArcBallCameraController(m_pCamera3D);
	pArcBall->SetCamera(Vector3F(0, 0.0f, -50.0f), Vector3F::Zero(), Vector3F::Up());
	pArcBall->Distance(7.0f);
	m_pCamera3D->CameraController(pArcBall);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);	
	pCamera->Initialize();
	GameInfo::Instance().GetWorld()->AddEntity(pCamera);	
	GameInfo::Instance().SetActiveCamera(m_pCamera3D);

	//
	m_pBob = NEW_AO BaseEntity();
	MinerComponent* pMiner = NEW_AO MinerComponent(m_pBob);
	m_pBob->GetComponentMgr()->AddComponent(pMiner);
	GameInfo::Instance().GetWorld()->AddEntity(m_pBob);

	m_pElsa = NEW_AO BaseEntity();
	MinersWifeComponent* pMinersWife = NEW_AO MinersWifeComponent(m_pElsa);
	m_pElsa->GetComponentMgr()->AddComponent(pMinersWife);
	GameInfo::Instance().GetWorld()->AddEntity(m_pElsa);

	m_pBob->SetName("Miner");
	m_pElsa->SetName("Miner's wife");

	pMiner->SetWifeID(m_pElsa->ID());
	pMinersWife->SetMinerID(m_pBob->ID());

	Game::Initialize();

	Game::Instance()->GetDebugOptions().ShowLogInGame = true;
}