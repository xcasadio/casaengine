#include "TileMapGame.h"

#include "bgfx.h"
#include "CustomCameraController.h"

#include "Entities\Components\Camera3DComponent.h"
#include "Entities\Components\CameraControllers\ArcBallCameraController.h"
#include "Entities\Components\MeshComponent.h"
#include "Entities\Components\Transform3DComponent.h"
#include "GameTime.h"
#include "Animations/AnimationEndEvent.h"
#include "Animations/SetFrameEvent.h"
#include "Assets/Asset.h"
#include "Assets/AssetManager.h"
#include "Entities/Components/Camera2DComponent.h"
#include "Entities/Components/StaticSpriteComponent.h"
#include "Game\GameInfo.h"
#include "Game\Line2DRendererComponent.h"
#include "Graphics\bgfx_utils.h"
#include "Log\LoggerFile.h"
#include "Log\LogManager.h"
#include "Map2D/AutoTile.h"
#include "Map2D/StaticTile.h"
#include "Map2D/TiledMapComponent.h"
#include "Tools\DebugSystem.h"
#include "World\World.h"

Transform3DComponent* s_pTransform;
CustomCameraController* s_pCameraController;

/**
 *
 */
TileMapGame::TileMapGame() :
	m_pSpriteRenderer(nullptr)
{
	Logging.AddLogger(NEW_AO LoggerFile("Out.log"));
}

/**
 *
 */
TileMapGame::~TileMapGame()
{
	DELETE_AO m_pSpriteRenderer;
}

/**
 *
 */
void TileMapGame::Initialize()
{
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/textures");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/models");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/shaders");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/script");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/tileset");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/fonts");

	m_pSpriteRenderer = NEW_AO SpriteRenderer(this);
	AddComponent(m_pSpriteRenderer);

	Game::Initialize();
}

void TileMapGame::CreateBackground(World* pWorld)
{
	//background
	/*Texture* texture = Texture::loadTexture("Tile1.png"); // "space-wallpaper.jpg");
	Sprite *pSprite = NEW_AO Sprite();
	pSprite->SetTexture2D(texture);
	pSprite->SetPositionInTexture(CRectangleI(0, 0, texture->TextureInfo()->width, texture->TextureInfo()->height));
	pSprite->SetName("background");
	Game::Instance().GetAssetManager().AddAsset(NEW_AO Asset(pSprite->GetName(), pSprite));*/

	BaseEntity* pEntity = NEW_AO BaseEntity();
	pEntity->SetName("background");
	Transform3DComponent* pTrans3D = NEW_AO Transform3DComponent(pEntity);
	pTrans3D->SetLocalPosition(Vector3F(0.0f, 0.0f, 1.0f));
	pTrans3D->SetLocalRotation(0.0f);
	/*pTrans3D->SetLocalScale(Vector3F(texture->TextureInfo()->width, texture->TextureInfo()->height, 1.0f));
	pEntity->GetComponentMgr()->AddComponent(pTrans3D);
	StaticSpriteComponent* pStaticSprite = NEW_AO StaticSpriteComponent(pEntity);
	pStaticSprite->SetSpriteID("background");
	pEntity->GetComponentMgr()->AddComponent(pStaticSprite);
	pWorld->AddEntity(pEntity);*/


	//Texture* texture = Texture::loadTexture("Tile1.png");
	Texture* texture = Texture::loadTexture("Outside_A2.png");
	const int size = 48; // 32
	Sprite* pSprite = NEW_AO Sprite();
	pSprite->SetTexture2D(texture);
	//pSprite->SetPositionInTexture(CRectangleI(7 * size, size, size, size));
	pSprite->SetPositionInTexture(CRectangleI(0, 0, size, size));
	pSprite->SetName("tile0");
	Game::Instance().GetAssetManager().AddAsset(NEW_AO Asset(pSprite->GetName(), pSprite));

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			pSprite = NEW_AO Sprite();
			pSprite->SetTexture2D(texture);
			//pSprite->SetPositionInTexture(CRectangleI(12 * size, 4 * size, size, size));
			pSprite->SetPositionInTexture(CRectangleI(2 * size + x * size, y * size, size, size));
			std::ostringstream str;
			str << "autoTile" << (x + y * 2);
			pSprite->SetName(str.str());
			Game::Instance().GetAssetManager().AddAsset(NEW_AO Asset(pSprite->GetName(), pSprite));
		}
	}

	TiledMapComponent* pMap = NEW_AO TiledMapComponent(pEntity);
	pMap->SetMapSize(Vector2I(30, 11));
	pMap->SetTileSize(Vector2I(size, size));
	//create anim
	Animation2D* pAnim = NEW_AO Animation2D();
	SetFrameEvent* pFrameEvent = NEW_AO SetFrameEvent();
	pFrameEvent->FrameID("tile0");
	pFrameEvent->Time(0.0f);
	pAnim->AddEvent(pFrameEvent);
	pFrameEvent = NEW_AO SetFrameEvent();
	pFrameEvent->FrameID("tile1");
	pFrameEvent->Time(2.0f);
	pAnim->AddEvent(pFrameEvent);
	AnimationEndEvent* pEndEvent = NEW_AO AnimationEndEvent();
	pEndEvent->Time(4.0f);
	pAnim->AddEvent(pEndEvent);
	pAnim->SetName("anim2D_tile1");
	pAnim->SetType(Animation2DType::TAnimation2DType::Loop);
	Game::Instance().GetAssetManager().AddAsset(new Asset(pAnim->GetName(), pAnim));
	//
	pAnim = NEW_AO Animation2D();
	pFrameEvent = NEW_AO SetFrameEvent();
	pFrameEvent->FrameID("tile1");
	pFrameEvent->Time(0.0f);
	pAnim->AddEvent(pFrameEvent);
	pFrameEvent = NEW_AO SetFrameEvent();
	pFrameEvent->FrameID("tile0");
	pFrameEvent->Time(2.0f);
	pAnim->AddEvent(pFrameEvent);
	pEndEvent = NEW_AO AnimationEndEvent();
	pEndEvent->Time(4.0f);
	pAnim->AddEvent(pEndEvent);
	pAnim->SetName("anim2D_tile0");
	pAnim->SetType(Animation2DType::TAnimation2DType::Loop);
	Game::Instance().GetAssetManager().AddAsset(new Asset(pAnim->GetName(), pAnim));

	std::vector<ITile*> tiles4AutoTile;
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			std::ostringstream str;
			str << "autoTile" << (x + y * 2);
			auto* staticTile = NEW_AO StaticTile(Game::Instance().GetAssetManager().GetAsset<Sprite>(str.str()));
			tiles4AutoTile.push_back(staticTile);
		}
	}
	
	std::vector<ITile*> tiles;
	for (int y = 0; y < 11; ++y)
	{
		for (int x = 0; x < 30; ++x)
		{
			if (y == 10 || y == 0 || x == 0 || x == 29 ||
				((x % 2 == 0) && (y == 1 || y == 9)) ||
				((y % 2 == 0) && (x == 1 || x == 28)))
			{
				auto* autoTile = NEW_AO AutoTile(pMap, x, y);
				autoTile->setTiles(tiles4AutoTile);
				tiles.push_back(autoTile);
			}
			else
			{
				//tiles.push_back(new AnimatedTile(Game::Instance().GetAssetManager().GetAsset<Animation2D>("anim2D_tile1")->Copy()));
				tiles.push_back(new StaticTile(Game::Instance().GetAssetManager().GetAsset<Sprite>("tile0")));
			}
		}
	}
	pMap->SetTiles(tiles);

	pTrans3D->SetLocalScale(Vector3F(size, size, 1.0));
	pEntity->GetComponentMgr()->AddComponent(pTrans3D);
	pEntity->GetComponentMgr()->AddComponent(pMap);
	pWorld->AddEntity(pEntity);
}

/**
 *
 */
void TileMapGame::LoadContent()
{
	Game::LoadContent();

	World* p_world = NEW_AO World();
	Game::Instance().GetGameInfo().SetWorld(p_world);

	auto texture = Texture::loadTexture("vegeta.png");
	auto pSprite = NEW_AO Sprite();
	pSprite->SetTexture2D(texture);
	pSprite->SetPositionInTexture(CRectangleI(0, 0, texture->TextureInfo()->width, texture->TextureInfo()->height));
	pSprite->SetName("sprite");
	//pSprite->SetAssetFileName("vegeta.png");
	Game::Instance().GetAssetManager().AddAsset(NEW_AO Asset(pSprite->GetName(), pSprite));

	BaseEntity* pEntity = NEW_AO BaseEntity();
	pEntity->SetName("vegeta");
	Transform3DComponent* pTransform = NEW_AO Transform3DComponent(pEntity);
	s_pTransform = pTransform;
	pTransform->SetLocalPosition(Vector3F(500.0f, 250.0f, 2.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F(texture->TextureInfo()->width, texture->TextureInfo()->height, 1.0f));
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	auto pStaticSprite = NEW_AO StaticSpriteComponent(pEntity);
	pStaticSprite->SetSpriteID("sprite");
	pEntity->GetComponentMgr()->AddComponent(pStaticSprite);
	p_world->AddEntity(pEntity);

	//Camera 2D
	BaseEntity* pCamera = NEW_AO BaseEntity();
	pCamera->SetName("camera 2D");
	Camera2DComponent* m_pCamera2D = NEW_AO Camera2DComponent(pCamera);
	auto custom_camera_controller = new CustomCameraController(m_pCamera2D);
	s_pCameraController = custom_camera_controller;
	m_pCamera2D->CameraController(custom_camera_controller);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera2D);
	custom_camera_controller->SetDeadZoneRatio(Vector2F(0.7f, 0.7f));
	custom_camera_controller->SetTargetedEntity(pEntity);
	custom_camera_controller->SetLimits(CRectangleI(0, 0, 1500, 800));
	p_world->AddEntity(pCamera);
	Game::Instance().GetGameInfo().SetActiveCamera(m_pCamera2D);


	CreateBackground(p_world);

	p_world->Initialize();
}

/**
 *
 */
void TileMapGame::Update(const GameTime& gameTime_)
{
	auto position = s_pTransform->GetLocalPosition();
	const auto speed = 5;

	if (std::abs(GetInput().GetJoystickLeftStickY(0)) > 20)
	{
		position.y += speed * (GetInput().GetJoystickLeftStickY(0) > 0 ? 1 : -1);
	}

	if (std::abs(GetInput().GetJoystickLeftStickX(0)) > 20)
	{
		position.x += speed * (GetInput().GetJoystickLeftStickX(0) > 0 ? 1 : -1);
	}

	s_pTransform->SetLocalPosition(position);

	Game::Update(gameTime_);
}

/**
 *
 */
void TileMapGame::Draw()
{
	bgfx::dbgTextClear();
	bgfx::dbgTextPrintf(0, 0, 0x0f, "player position: %.0f, %.0f", s_pTransform->GetPosition().x, s_pTransform->GetPosition().y);
	bgfx::dbgTextPrintf(0, 1, 0x0f, "camera offset: %d, %d", s_pCameraController->GetOffset().x, s_pCameraController->GetOffset().y);


	Game::Draw();
}

