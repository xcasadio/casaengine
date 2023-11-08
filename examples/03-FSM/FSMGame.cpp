#include  "FSMGame.hpp"
#include  "Game/GameInfo.hpp"
#include  "Log/LoggerFile.hpp"
#include  "WestWorldWithMessaging/MinerComponent.hpp"
#include  "WestWorldWithMessaging/MinersWifeComponent.hpp"

using namespace CasaEngine;


FSMGame::FSMGame()
{
	Logging.AddLogger(new LoggerFile("Out.log"));
}

FSMGame::~FSMGame()
{
}

void FSMGame::Initialize()
{
	GetMediaManager().AddSearchPath("../../examples/resources");
	GetMediaManager().AddSearchPath("../../examples/resources/textures");
	GetMediaManager().AddSearchPath("../../examples/resources/models");
	GetMediaManager().AddSearchPath("../../examples/resources/shaders");
	GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
	GetMediaManager().AddSearchPath("../../examples/resources/fonts");

	AddDebugComponents();
	AddUsualComponents();

	GetGameInfo().SetWorld(new World());

	m_pBob = new BaseEntity();
	MinerComponent* pMiner = new MinerComponent(m_pBob);
	m_pBob->GetComponentMgr()->AddComponent(pMiner);
	Game::Instance().GetGameInfo().GetWorld()->AddEntity(m_pBob);

	m_pElsa = new BaseEntity();
	MinersWifeComponent* pMinersWife = new MinersWifeComponent(m_pElsa);
	m_pElsa->GetComponentMgr()->AddComponent(pMinersWife);
	Game::Instance().GetGameInfo().GetWorld()->AddEntity(m_pElsa);

	m_pBob->SetName("Miner");
	m_pElsa->SetName("Miner's wife");

	pMiner->SetWifeID(m_pElsa->Id());
	pMinersWife->SetMinerID(m_pBob->Id());

	GetDebugOptions().ShowLogInGame = true;

	Game::Initialize();
}