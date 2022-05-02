#include <iosfwd>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

#include "FightingGame2DGame.h"
#include "Characters/ScriptCharacter.h"
#include "Characters/Player.h"

#include "Animations/Animation2D.h"
#include "Assets/AssetManager.h"

#include "Entities/Components/AnimatedSpriteComponent.h"
#include "Entities/Components/GridComponent.h"
#include "Entities/Components/StaticSpriteComponent.h"
#include "Entities/Components/Transform3DComponent.h"
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
#include "Entities/Components/DebugComponent.h"
#include "Entities/Components/ScriptComponent.h"
#include "Entities/Components/Cameras/Camera2DTargetedComponent.h"
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
	LoadSprites();
	auto animations = LoadAnimations();

	m_pWorld = new World();
	GetGameInfo().SetWorld(m_pWorld);

	Transform3DComponent* pTransform = nullptr;

	//player 1
	auto* pPlayer1 = new BaseEntity();
	pPlayer1->SetName("player 1");
	pTransform = new Transform3DComponent(pPlayer1);
	pTransform->SetLocalPosition(Vector3(520, 400, 2.0f));
	auto scale = 2.0f;
	pTransform->SetLocalScale(Vector3(scale, scale, 0.0f));
	pPlayer1->GetComponentMgr()->AddComponent(pTransform);

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
	pTransform = new Transform3DComponent(pPlayer2);
	pTransform->SetLocalPosition(Vector3(820, 400, 2.0f));
	scale = 1.0f;
	pTransform->SetLocalScale(Vector3(scale, scale, 0.0f));
	pPlayer2->GetComponentMgr()->AddComponent(pTransform);

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
	m_pCamera2D->SetLimits(RectangleI(0, 0, 1500, 800));
	m_pWorld->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCamera2D);

	//stage
	auto* pStage = new BaseEntity();
	pStage->SetName("stage");
	pTransform = new Transform3DComponent(pStage);
	pTransform->SetLocalPosition(Vector3(0, 0, 1.0f));
	pStage->GetComponentMgr()->AddComponent(pTransform);
	auto* stage = new Stage(pStage);
	pStage->GetComponentMgr()->AddComponent(stage);
	m_pWorld->AddEntity(pStage);

	//stage info
	auto* stageInfo = new StageInfo(stage, pPlayer1, pPlayer2);
	stage->SetStageInfo(stageInfo);
	
	m_pWorld->Initialize();
}

std::vector<Animation2DData> FightingGame2DGame::LoadAnimations()
{
	auto* const pFile = GetMediaManager().FindMedia("animations.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	std::vector<Animation2DData> anim2DDatas;
	ar(cereal::make_nvp("animations", anim2DDatas));

	for (auto& data : anim2DDatas)
	{
		auto* animation = data.Copy();
		GetAssetManager().AddAsset(new Asset(data.GetName(), animation));
	}

	return anim2DDatas;
}

void FightingGame2DGame::LoadSprites()
{
	auto* const pFile = GetMediaManager().FindMedia("sprites.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	std::vector<SpriteData> spriteDatas;
	ar(cereal::make_nvp("sprites", spriteDatas));

	for (auto& data : spriteDatas)
	{
		GetAssetManager().AddAsset(new Asset(data.GetName(), data.Copy()));
	}
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