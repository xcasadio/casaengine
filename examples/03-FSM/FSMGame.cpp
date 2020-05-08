#include <string>

#include "FSMGame.h"
#include "Entities/Components/Camera2DComponent.h"
#include "Entities/Components/CameraControllers/ArcBallCameraController.h"
#include "Entities/EntityManager.h"
#include "Game/GameInfo.h"
#include "Graphics/Renderer/Renderer.h"
#include "Log/LoggerFile.h"
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

	GameInfo::Instance().SetWorld(NEW_AO World());

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

	GetDebugOptions().ShowLogInGame = true;

	Game::Initialize();
}