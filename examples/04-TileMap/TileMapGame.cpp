#include "TileMapGame.h"

#include "GameTime.h"
#include "../../external/dear-imgui/imgui.h"
#include "Assets/Asset.h"
#include "Assets/AssetManager.h"
#include "Datas/SpriteData.h"
#include "Entities/Components/DebugComponent.h"
#include "Entities/Components/ScriptComponent.h"
#include "Entities/Components/StaticSpriteComponent.h"
#include "Entities\Components\Cameras\ArcBallCameraComponent.h"
#include "Entities\Components\Cameras\Camera2DTargetedComponent.h"
#include "Game\GameInfo.h"
#include "Log\LoggerFile.h"
#include "Log\LogManager.h"
#include "Map2D/AutoTile.h"
#include "Map2D/TiledMapCreator.h"
#include "Serializer/Serializer.h"
#include "Sprite/SpriteLoader.h"
#include "World\World.h"

BaseEntity* s_entity;
Camera2DTargetedComponent* s_pCameraController;


TileMapGame::TileMapGame()
{
	Logging.AddLogger(new LoggerFile("Out.log"));
}

TileMapGame::~TileMapGame() = default;

void TileMapGame::Initialize()
{
	GetMediaManager().AddSearchPath("../../examples/resources");
	GetMediaManager().AddSearchPath("../../examples/resources/textures");
	GetMediaManager().AddSearchPath("../../examples/resources/models");
	GetMediaManager().AddSearchPath("../../examples/resources/shaders");
	GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
	GetMediaManager().AddSearchPath("../../examples/resources/script");
	GetMediaManager().AddSearchPath("../../examples/resources/tileset");
	GetMediaManager().AddSearchPath("../../examples/resources/fonts");
	GetMediaManager().AddSearchPath("../../examples/resources/datas");

	AddDebugComponents();
	AddUsualComponents();

	Game::Initialize();
}

void TileMapGame::LoadContent()
{
	Game::LoadContent();

	auto* p_world = new World();
	GetGameInfo().SetWorld(p_world);

	//create perso
	auto pSprite = new SpriteData();
	pSprite->SetAssetFileName("vegeta.png");
	pSprite->SetPositionInTexture(CasaEngine::Rectangle(0, 0, 43, 76));
	pSprite->SetName("sprite");
	GetAssetManager().AddAsset(new Asset(pSprite->GetName(), pSprite));

	s_entity = new BaseEntity();
	s_entity->SetName("vegeta");
	s_entity->GetCoordinates().SetLocalPosition(Vector3(500.0f, 250.0f, 1.5f));
	auto pStaticSprite = new StaticSpriteComponent(s_entity);
	pStaticSprite->SetSpriteID("sprite");
	s_entity->GetComponentMgr()->AddComponent(pStaticSprite);
	auto* debugComponent = new DebugComponent(s_entity);
	debugComponent->DisplayPosition(true);
	s_entity->GetComponentMgr()->AddComponent(debugComponent);
	p_world->AddEntity(s_entity);

	//Camera 2D
	auto pCamera = new BaseEntity();
	pCamera->SetName("camera 2D");
	s_pCameraController = new Camera2DTargetedComponent(pCamera);
	pCamera->GetComponentMgr()->AddComponent(s_pCameraController);
	s_pCameraController->SetDeadZoneRatio(Vector2(0.7f, 0.7f));
	s_pCameraController->SetTargetedEntity(s_entity);
	s_pCameraController->SetLimits(CasaEngine::Rectangle(0, 0, 1500, 800));
	p_world->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(s_pCameraController);

	//map
	SpriteLoader::LoadFromFile("Outside_A2_sprites.json");
	TiledMapCreator::LoadMapFromFile("tileMap.json", *p_world);

	p_world->Initialize();
}

void TileMapGame::Update(const GameTime & gameTime_)
{
	auto position = s_entity->GetCoordinates().GetLocalPosition();
	constexpr auto speed = 5;

	if (std::abs(GetInput().GetJoystickLeftStickY(0)) > 20)
	{
		position.y += speed * (GetInput().GetJoystickLeftStickY(0) > 0 ? 1 : -1);
	}
	else if (GetInput().IsKeyDown(sf::Keyboard::Up))
	{
		position.y += speed * -1;
	}
	else if (GetInput().IsKeyDown(sf::Keyboard::Down))
	{
		position.y += speed * 1;
	}

	if (std::abs(GetInput().GetJoystickLeftStickX(0)) > 20)
	{
		position.x += speed * (GetInput().GetJoystickLeftStickX(0) > 0 ? 1 : -1);
	}
	else if (GetInput().IsKeyDown(sf::Keyboard::Right))
	{
		position.x += speed * 1;
	}
	else if (GetInput().IsKeyDown(sf::Keyboard::Left))
	{
		position.x += speed * -1;
	}

	s_entity->GetCoordinates().SetLocalPosition(position);

	Game::Update(gameTime_);
}

void TileMapGame::Draw()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10));

	if (ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::Text("player position : % .0f, % .0f", s_entity->GetCoordinates().GetPosition().x, s_entity->GetCoordinates().GetPosition().y);
		ImGui::Text("camera offset: %d, %d", s_pCameraController->GetOffset().x, s_pCameraController->GetOffset().y);
	}

	ImGui::End();
}