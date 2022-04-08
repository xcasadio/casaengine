#include "TileMapGame.h"

#include "bgfx\bgfx.h"
#include "Entities\Components\CameraControllers\Camera2DTargetedController.h"

#include "Entities\Components\Camera3DComponent.h"
#include "Entities\Components\CameraControllers\ArcBallCameraController.h"
#include "Entities\Components\MeshComponent.h"
#include "Entities\Components\Transform3DComponent.h"
#include "GameTime.h"
#include "Animations/SetFrameEvent.h"
#include "Assets/Asset.h"
#include "Assets/AssetManager.h"
#include "Entities/Components/Camera2DComponent.h"
#include "Entities/Components/StaticSpriteComponent.h"
#include "Game\GameInfo.h"
#include "Game\Line2DRendererComponent.h"
#include "Log\LoggerFile.h"
#include "Log\LogManager.h"
#include "Map2D/AutoTile.h"
#include "Map2D/StaticTile.h"
#include "Map2D/TiledMapComponent.h"
#include "World\World.h"
#include "Datas/SpriteData.h"
#include "Entities/Components/DebugComponent.h"
#include "../../external/dear-imgui/imgui.h"

Transform3DComponent* s_pTransform;
Camera2DTargetedController* s_pCameraController;


TileMapGame::TileMapGame() :
	m_pSpriteRenderer(nullptr)
{
	Logging.AddLogger(new LoggerFile("Out.log"));
}

TileMapGame::~TileMapGame()
{
	delete m_pSpriteRenderer;
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

	m_pSpriteRenderer = new SpriteRenderer(this);
	AddComponent(m_pSpriteRenderer);
	AddComponent(new Line3DRendererComponent(this));

	Game::Initialize();
}

void TileMapGame::CreateBackground(World* pWorld)
{
	auto *pEntity = new BaseEntity();
	pEntity->SetName("background");
	auto *pTrans3D = new Transform3DComponent(pEntity);
	pTrans3D->SetLocalPosition(Vector3F(0.0f, 0.0f, 1.0f));
	pTrans3D->SetLocalRotation(0.0f);

	//Texture* texture = Texture::loadTexture("Outside_A2.png");
	constexpr int size = 48; // 32
	auto *pSprite = new SpriteData();
	pSprite->SetAssetFileName("Outside_A2.png");
	//pSprite->SetTexture2D(texture);
	pSprite->SetPositionInTexture(RectangleI(0, 0, size, size));
	pSprite->SetName("tile0");
	Game::Instance().GetAssetManager().AddAsset(new Asset(pSprite->GetName(), pSprite));

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			pSprite = new SpriteData();
			pSprite->SetAssetFileName("Outside_A2.png");
			//pSprite->SetTexture2D(texture);
			pSprite->SetPositionInTexture(RectangleI(2 * size + x * size, y * size, size, size));
			std::ostringstream str;
			str << "autoTile" << x + y * 2;
			pSprite->SetName(str.str());
			Game::Instance().GetAssetManager().AddAsset(new Asset(pSprite->GetName(), pSprite));
		}
	}

	auto *pMap = new TiledMapComponent(pEntity);
	pMap->SetMapSize(Vector2I(30, 11));
	pMap->SetTileSize(Vector2I(size, size));
	//create anim
	auto *pAnim2DData = new Animation2DData();
	pAnim2DData->SetName("anim2D_tile1");
	auto *pFrameData = new FrameData();
	pFrameData->SetSpriteId("tile0");
	pFrameData->SetDuration(2.0f);
	pAnim2DData->GetFrames().push_back(*pFrameData);
	pFrameData = new FrameData();
	pFrameData->SetSpriteId("tile1");
	pFrameData->SetDuration(2.0f);
	pAnim2DData->GetFrames().push_back(*pFrameData);
	pFrameData = new FrameData();
	pFrameData->SetSpriteId("tile2");
	pFrameData->SetDuration(2.0f);
	pAnim2DData->GetFrames().push_back(*pFrameData);
	pAnim2DData->SetAnimationType(AnimationType::Loop);
	Game::Instance().GetAssetManager().AddAsset(new Asset(pAnim2DData->GetName(), pAnim2DData));
	//
	pAnim2DData = new Animation2DData();
	pAnim2DData->SetName("anim2D_tile0");
	pFrameData = new FrameData();
	pFrameData->SetSpriteId("tile1");
	pFrameData->SetDuration(2.0f);
	pAnim2DData->GetFrames().push_back(*pFrameData);
	pFrameData = new FrameData();
	pFrameData->SetSpriteId("tile0");
	pFrameData->SetDuration(2.0f);
	pAnim2DData->GetFrames().push_back(*pFrameData);
	pAnim2DData->SetAnimationType(AnimationType::Loop);
	Game::Instance().GetAssetManager().AddAsset(new Asset(pAnim2DData->GetName(), pAnim2DData));

	std::vector<ITile*> tiles4AutoTile;
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			std::ostringstream str;
			str << "autoTile" << x + y * 2;
			auto* staticTile = new StaticTile(new Sprite(*GetAssetManager().GetAsset<SpriteData>(str.str())));
			tiles4AutoTile.push_back(staticTile);
		}
	}

	auto* layer = new TiledMapLayer();

	std::vector<ITile*> tiles;
	for (int y = 0; y < 11; ++y)
	{
		for (int x = 0; x < 30; ++x)
		{
			if (y == 10 || y == 0 || x == 0 || x == 29 ||
				x % 2 == 0 && (y == 1 || y == 9) ||
				y % 2 == 0 && (x == 1 || x == 28))
			{
				auto* autoTile = new AutoTile(layer, x, y);
				autoTile->setTiles(tiles4AutoTile);
				tiles.push_back(autoTile);
			}
			else
			{
				//tiles.push_back(new AnimatedTile(Game::Instance().GetAssetManager().GetAsset<Animation2D>("anim2D_tile1")->Copy()));
				tiles.push_back(new StaticTile(new Sprite(*Game::Instance().GetAssetManager().GetAsset<SpriteData>("tile0"))));
			}
		}
	}

	layer->SetTiles(tiles);
	pMap->AddLayer(layer);
	
	pEntity->GetComponentMgr()->AddComponent(pTrans3D);
	pEntity->GetComponentMgr()->AddComponent(pMap);
	pWorld->AddEntity(pEntity);
}

void TileMapGame::LoadContent()
{
	Game::LoadContent();

	auto p_world = new World();
	Game::Instance().GetGameInfo().SetWorld(p_world);

	auto pSprite = new SpriteData();
	pSprite->SetAssetFileName("vegeta.png");
	pSprite->SetPositionInTexture(RectangleI(0, 0, 43, 76));
	pSprite->SetName("sprite");
	GetAssetManager().AddAsset(new Asset(pSprite->GetName(), pSprite));

	auto pEntity = new BaseEntity();
	pEntity->SetName("vegeta");
	auto pTransform = new Transform3DComponent(pEntity);
	s_pTransform = pTransform;
	pTransform->SetLocalPosition(Vector3F(500.0f, 250.0f, 1.5f));
	//pTransform->SetLocalRotation(0.0f);
	//pTransform->SetLocalScale(Vector3F(43, 76, 1.0f));
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	auto pStaticSprite = new StaticSpriteComponent(pEntity);
	pStaticSprite->SetSpriteID("sprite");
	pEntity->GetComponentMgr()->AddComponent(pStaticSprite);
	auto* debugComponent = new DebugComponent(pEntity);
	debugComponent->DisplayPosition(true);
	pEntity->GetComponentMgr()->AddComponent(debugComponent);
	p_world->AddEntity(pEntity);

	//Camera 2D
	auto pCamera = new BaseEntity();
	pCamera->SetName("camera 2D");
	auto m_pCamera2D = new Camera2DComponent(pCamera);
	auto custom_camera_controller = new Camera2DTargetedController(m_pCamera2D);
	s_pCameraController = custom_camera_controller;
	m_pCamera2D->CameraController(custom_camera_controller);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera2D);
	custom_camera_controller->SetDeadZoneRatio(Vector2F(0.7f, 0.7f));
	custom_camera_controller->SetTargetedEntity(pEntity);
	custom_camera_controller->SetLimits(RectangleI(0, 0, 1500, 800));
	p_world->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCamera2D);

	CreateBackground(p_world);

	p_world->Initialize();
}

void TileMapGame::Update(const GameTime& gameTime_)
{
	auto position = s_pTransform->GetLocalPosition();
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

	s_pTransform->SetLocalPosition(position);

	Game::Update(gameTime_);
}

void TileMapGame::Draw()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10));

	if (ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::Text("player position : % .0f, % .0f", s_pTransform->GetPosition().x, s_pTransform->GetPosition().y);
		ImGui::Text("camera offset: %d, %d", s_pCameraController->GetOffset().x, s_pCameraController->GetOffset().y);
	}

	ImGui::End();
}