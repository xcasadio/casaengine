#include "TileMapGame.h"

#include "bgfx\bgfx.h"
#include "Entities\Components\Cameras\Camera2DTargetedComponent.h"

#include "Entities\Components\Cameras\ArcBallCameraComponent.h"
#include "Entities\Components\MeshComponent.h"
#include "GameTime.h"
#include "Serializer/Serializer.h"
#include "Assets/Asset.h"
#include "Assets/AssetManager.h"
#include "Entities/Components/StaticSpriteComponent.h"
#include "Game\GameInfo.h"
#include "Log\LoggerFile.h"
#include "Log\LogManager.h"
#include "World\World.h"
#include "Datas/SpriteData.h"
#include "Entities/Components/DebugComponent.h"
#include "../../external/dear-imgui/imgui.h"
#include "Datas/AutoTileSetData.h"
#include "Map2D/TileData.h"

BaseEntity* s_entity;
Camera2DTargetedComponent* s_pCameraController;


TileMapGame::TileMapGame()
{
	Logging.AddLogger(new LoggerFile("Out.log"));
}

TileMapGame::~TileMapGame()
{
}

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

	AddDebugComponents();
	AddUsualComponents();

	Game::Initialize();
}

void CreateMap(World* pWorld, const int size)
{
	//create autotile set
	auto* autoTileSetData = new AutoTileSetData();
	autoTileSetData->SetName("Outside_A2_2_3");
	int index = 0;
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			std::ostringstream str;
			str << "autoTile_" << x << "_" << y;
			autoTileSetData->spriteIds[index++] = str.str();
		}
	}
	Game::Instance().GetAssetManager().AddAsset(autoTileSetData->GetName(), autoTileSetData);

	// map
	auto* tiledMapParameters = new TiledMapData();

	//tiledMapParameters->mapSize = Vector2I(30, 11);
	//tiledMapParameters->tileSize = Vector2I(size, size);
	//
	//TiledMapLayerData layer;
	//layer.zOffset = 0.0f;
	//for (int y = 0; y < tiledMapParameters->mapSize.y; ++y)
	//{
	//	for (int x = 0; x < tiledMapParameters->mapSize.x; ++x)
	//	{
	//		if (y == 10 || y == 0 || x == 0 || x == 29 ||
	//			x % 2 == 0 && (y == 1 || y == 9) ||
	//			y % 2 == 0 && (x == 1 || x == 28))
	//		{
	//			auto* autoTileParams = new AutoTileData();
	//			autoTileParams->x = x;
	//			autoTileParams->y = y;
	//			autoTileParams->autoTileAssetName = "Outside_A2_2_3";
	//			layer.tiles.push_back(autoTileParams);
	//		}
	//		else
	//		{
	//			auto* staticTileParams = new StaticTileData();
	//			staticTileParams->x = x;
	//			staticTileParams->y = y;
	//			staticTileParams->spriteId = "tile0";
	//			layer.tiles.push_back(staticTileParams);
	//		}
	//	}
	//}
	//tiledMapParameters->layers.push_back(layer);

	//std::ofstream os("C:\\Users\\casad\\dev\\repo\\casaengine\\examples\\resources\\datas\\tileMap.json");
	//json j;
	//to_json(j, *tiledMapParameters);
	////os << j << std::endl;
	//os << std::setw(4) << j << std::endl; // pretty json
	
	std::ifstream i("C:\\Users\\casad\\dev\\repo\\casaengine\\examples\\resources\\datas\\tileMap.json");
	json j2;
	i >> j2;
	TiledMapData t2;
	from_json(j2, *tiledMapParameters);
	//from_json(j2, t2);

	TiledMapCreator::Create(*tiledMapParameters, *pWorld);
}

void TileMapGame::CreateBackground(World* pWorld)
{
	//create all sprites
	constexpr int size = 48; // 32
	auto *pSprite = new SpriteData();
	pSprite->SetAssetFileName("Outside_A2.png");
	pSprite->SetPositionInTexture(CasaEngine::Rectangle(0, 0, size, size));
	pSprite->SetName("tile0");
	GetAssetManager().AddAsset(new Asset(pSprite->GetName(), pSprite));

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			pSprite = new SpriteData();
			pSprite->SetAssetFileName("Outside_A2.png");
			pSprite->SetPositionInTexture(CasaEngine::Rectangle(2 * size + x * size, y * size, size, size));
			std::ostringstream str;
			str << "autoTile_" << x << "_" << y;
			pSprite->SetName(str.str());
			GetAssetManager().AddAsset(new Asset(pSprite->GetName(), pSprite));
		}
	}

	//create anim
	//auto *pAnim2DData = new Animation2DData();
	//pAnim2DData->SetName("anim2D_tile1");
	//auto *pFrameData = new FrameData();
	//pFrameData->SetSpriteId("tile0");
	//pFrameData->SetDuration(2.0f);
	//pAnim2DData->GetFrames().push_back(*pFrameData);
	//pFrameData = new FrameData();
	//pFrameData->SetSpriteId("tile1");
	//pFrameData->SetDuration(2.0f);
	//pAnim2DData->GetFrames().push_back(*pFrameData);
	//pFrameData = new FrameData();
	//pFrameData->SetSpriteId("tile2");
	//pFrameData->SetDuration(2.0f);
	//pAnim2DData->GetFrames().push_back(*pFrameData);
	//pAnim2DData->SetAnimationType(AnimationType::Loop);
	//GetAssetManager().AddAsset(new Asset(pAnim2DData->GetName(), pAnim2DData));
	////
	//pAnim2DData = new Animation2DData();
	//pAnim2DData->SetName("anim2D_tile0");
	//pFrameData = new FrameData();
	//pFrameData->SetSpriteId("tile1");
	//pFrameData->SetDuration(2.0f);
	//pAnim2DData->GetFrames().push_back(*pFrameData);
	//pFrameData = new FrameData();
	//pFrameData->SetSpriteId("tile0");
	//pFrameData->SetDuration(2.0f);
	//pAnim2DData->GetFrames().push_back(*pFrameData);
	//pAnim2DData->SetAnimationType(AnimationType::Loop);
	//GetAssetManager().AddAsset(new Asset(pAnim2DData->GetName(), pAnim2DData));

	CreateMap(pWorld, size);
}

void TileMapGame::LoadContent()
{
	Game::LoadContent();

	auto p_world = new World();
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

	CreateBackground(p_world);

	p_world->Initialize();
}

void TileMapGame::Update(const GameTime& gameTime_)
{
	auto position = s_entity->GetCoordinates().GetLocalPosition();
	const auto speed = 5;

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