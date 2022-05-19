#include <iosfwd>

#include "FightingGame2DGame.h"
#include "Characters/ScriptCharacter.h"
#include "Characters/Player.h"

#include "Animations/Animation2D.h"
#include "Assets/AssetManager.h"

#include "Entities/Components/AnimatedSpriteComponent.h"
#include "Entities/Components/StaticSpriteComponent.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "Game/Input.h"
#include "GameTime.h"

#include "Log/LoggerFile.h"
#include "Maths/Vector3.h"

#include "Physics/PhysicsEngine.h"
#include "Sprite/SpriteTypes.h"
#include <IO/File.h>
#include "../../external/dear-imgui/imgui.h"
#include "Animations/Animation2dLoader.h"
#include "Entities/Components/DebugComponent.h"
#include "Entities/Components/ScriptComponent.h"
#include "Entities/Components/Cameras/Camera2DTargetedComponent.h"
#include "Serializer/Serializer.h"
#include "Sprite/SpriteLoader.h"
#include "Stages/Stage.h"

using namespace CasaEngine;

FightingGame2DGame::FightingGame2DGame() :
	m_pWorld(nullptr)
{
	Logging.AddLogger(new LoggerFile("Out.log"));
}

FightingGame2DGame::~FightingGame2DGame()
{
	
}

void FightingGame2DGame::Initialize()
{
	GetMediaManager().AddSearchPath("../../examples/resources");
	GetMediaManager().AddSearchPath("../../examples/resources/datas");
	GetMediaManager().AddSearchPath("../../examples/resources/textures");
	GetMediaManager().AddSearchPath("../../examples/resources/models");
	GetMediaManager().AddSearchPath("../../examples/resources/shaders");
	GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
	GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet/ryu");
	GetMediaManager().AddSearchPath("../../examples/resources/script");
	GetMediaManager().AddSearchPath("../../examples/resources/fonts");
	GetMediaManager().AddSearchPath("../../examples/resources/tileset");
	GetMediaManager().AddSearchPath("../../examples/resources/fighting_game");

	AddDebugComponents();
	AddUsualComponents();

	Game::Initialize();

	//GetDebugOptions().IsDebugActivated = true;
	//GetDebugOptions().ShowLogInGame = true;
}

void FightingGame2DGame::LoadContent()
{
	Game::LoadContent();
	SpriteLoader::LoadFromFile("sprites.json");
	auto animations = Animation2dLoader::LoadFromFile("animations.json");

	//std::vector<int> animToDelete;
	//
	//for (int i = 0; i < animations.size(); ++i)
	//{
	//	for (const auto& frame : animations[i]._frames)
	//	{
	//		if (GetAssetManager().Contains(frame._spriteId) == false)
	//		{
	//			animToDelete.push_back(i);
	//			break;
	//		}			
	//	}
	//}
	//
	//std::vector<Animation2DData> animValidated;
	//for (int i = 0; i < animations.size(); ++i)
	//{
	//	if (std::find(animToDelete.begin(), animToDelete.end(), i) == animToDelete.end())
	//	{
	//		animValidated.push_back(animations[i]);
	//	}
	//}
	//
	//std::ofstream os("C:\\Users\\casad\\dev\\repo\\casaengine\\examples\\resources\\datas\\animations_cop.json");
	//json j;
	//to_json(j, animValidated, "animations");
	//os << std::setw(4) << j << std::endl; // pretty json

	m_pWorld = new World();
	GetGameInfo().SetWorld(m_pWorld);

	//player 1
	auto* pPlayer1 = new BaseEntity();
	pPlayer1->SetName("player 1");
	pPlayer1->GetCoordinates().SetLocalPosition(Vector3(520, 400, 2.0f));
	auto scale = 2.0f;
	pPlayer1->GetCoordinates().SetLocalScale(Vector3(scale, scale, 0.0f));

	auto* pAnimatedSprite = new AnimatedSpriteComponent(pPlayer1);
	pPlayer1->GetComponentMgr()->AddComponent(pAnimatedSprite);
	for (auto& anim : animations)
	{
		pAnimatedSprite->AddAnimation(new Animation2D(*anim.Copy()));
	}
	pAnimatedSprite->SetCurrentAnimation("idle");
	pAnimatedSprite->SetSpriteEffect(eSpriteEffects::SPRITE_EFFECT_NONE);

	auto* scriptComponent = new ScriptComponent(pPlayer1);
	auto* pScriptCharacter = new ScriptCharacter(pPlayer1, new Player(pPlayer1));
	scriptComponent->SetScriptObject(pScriptCharacter);
	pPlayer1->GetComponentMgr()->AddComponent(scriptComponent);

	auto* debugComponent = new DebugComponent(pPlayer1);
	debugComponent->DisplayAnimation2DCollisions(true);
	debugComponent->DisplayPosition(true);
	pPlayer1->GetComponentMgr()->AddComponent(debugComponent);

	m_pWorld->AddEntity(pPlayer1);

	//player 2
	auto* pPlayer2 = new BaseEntity();
	pPlayer2->SetName("player 2");
	pPlayer2->GetCoordinates().SetLocalPosition(Vector3(820, 400, 2.0f));
	scale = 1.0f;
	pPlayer2->GetCoordinates().SetLocalScale(Vector3(scale, scale, 0.0f));

	pAnimatedSprite = new AnimatedSpriteComponent(pPlayer2);
	pPlayer2->GetComponentMgr()->AddComponent(pAnimatedSprite);
	for (auto& anim : animations)
	{
		pAnimatedSprite->AddAnimation(new Animation2D(*anim.Copy()));
	}
	pAnimatedSprite->SetCurrentAnimation("idle");
	pAnimatedSprite->SetSpriteEffect(eSpriteEffects::SPRITE_EFFECT_FLIP_HORIZONTALLY);

	debugComponent = new DebugComponent(pPlayer2);
	debugComponent->DisplayAnimation2DCollisions(true);
	debugComponent->DisplayPosition(true);
	pPlayer2->GetComponentMgr()->AddComponent(debugComponent);

	m_pWorld->AddEntity(pPlayer2);

	//Camera 2D
	auto* pCamera = new BaseEntity();
	pCamera->SetName("camera 2D");
	auto* m_pCamera2D = new Camera2DTargetedComponent(pCamera);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera2D);
	m_pCamera2D->SetDeadZoneRatio(Vector2(0.7f, 0.7f));
	m_pCamera2D->SetTargetedEntity(pPlayer1);
	m_pCamera2D->SetLimits(CasaEngine::Rectangle(0, 0, 1500, 800));
	m_pWorld->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCamera2D);

	//stage
	auto* pStage = new BaseEntity();
	pStage->SetName("stage");
	pStage->GetCoordinates().SetLocalPosition(Vector3(0, 0, 1.0f));
	auto* stage = new Stage(pStage);
	pStage->GetComponentMgr()->AddComponent(stage);
	m_pWorld->AddEntity(pStage);

	//stage info
	auto* stageInfo = new StageInfo(stage, pPlayer1, pPlayer2);
	stage->SetStageInfo(stageInfo);
	
	m_pWorld->Initialize();
}

void FightingGame2DGame::Update(const GameTime& gameTime_)
{
	Game::Update(gameTime_);
}


void FightingGame2DGame::DisplayUI()
{
	/*
	ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	if (ImGui::Begin("Animation Player"))
	{
		ImGui::BeginChild("Animation List", ImVec2(0, 0));

		ImGui::EndChild();

		ImGui::End();
	}*/
}

void FightingGame2DGame::Draw()
{
	DisplayUI();

	Game::Draw();
}