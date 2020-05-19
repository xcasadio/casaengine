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
}

/**
 * 
 */
void FSMGame::Initialize()
{
	GetMediaManager().AddSearchPath("../../examples/resources");
	GetMediaManager().AddSearchPath("../../examples/resources/textures");
	GetMediaManager().AddSearchPath("../../examples/resources/models");
	GetMediaManager().AddSearchPath("../../examples/resources/shaders");
	GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
	GetMediaManager().AddSearchPath("../../examples/resources/fonts");

	GetGameInfo().SetWorld(NEW_AO World());

	m_pBob = NEW_AO BaseEntity();
	MinerComponent* pMiner = NEW_AO MinerComponent(m_pBob);
	m_pBob->GetComponentMgr()->AddComponent(pMiner);
	Game::Instance().GetGameInfo().GetWorld()->AddEntity(m_pBob);

	m_pElsa = NEW_AO BaseEntity();
	MinersWifeComponent* pMinersWife = NEW_AO MinersWifeComponent(m_pElsa);
	m_pElsa->GetComponentMgr()->AddComponent(pMinersWife);
	Game::Instance().GetGameInfo().GetWorld()->AddEntity(m_pElsa);

	m_pBob->SetName("Miner");
	m_pElsa->SetName("Miner's wife");

	pMiner->SetWifeID(m_pElsa->ID());
	pMinersWife->SetMinerID(m_pBob->ID());

	GetDebugOptions().ShowLogInGame = true;

	Game::Initialize();
}