#include <string>
#include <iosfwd>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

#include "scene2DGame.h"

#include "Player.h"
#include "Enemy.h"
#include "EnemyController.h"
#include "Animations/Animation2D.h"
#include "Assets/AssetManager.h"

#include "Entities/Components/AnimatedSpriteComponent.h"
#include "Entities/Components/Camera3DComponent.h"
#include "Entities/Components/CameraControllers/ArcBallCameraController.h"
#include "Entities/Components/CameraControllers/Camera2DController.h"
#include "Entities/Components/GridComponent.h"
#include "Entities/Components/MeshComponent.h"
#include "Entities/Components/ScriptComponent.h"
#include "Entities/Components/StaticSpriteComponent.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "Game/Input.h"
#include "GameTime.h"
#include "ScriptCharacter.h"

#include "Graphics/Textures/Texture.h"
#include "Log/LoggerFile.h"
#include "Maths/Vector3.h"
#include "Memory/MemoryAllocation.h"
#include "Map2D/AutoTile.h"
#include "Map2D/StaticTile.h"
#include "Map2D/TiledMapComponent.h"

#include "load_save_types.h"
#include "Entities/Components/DebugComponent.h"
#include "Entities/Components/CameraControllers/Camera3DTargetedController.h"
#include "Entities/Components/Physics/Box2DColliderComponent.h"
#include "Entities/Components/Physics/Circle2DColliderComponent.h"

using namespace CasaEngine;

Scene2DGame::Scene2DGame() :
	m_pSpriteRenderer(nullptr),
	m_pAnimatedSprite(nullptr),
	m_pGroundTexture(nullptr),
	m_pLine2DRenderer(nullptr),
	m_pLine3DRenderer(nullptr),
	m_pWorld(nullptr),
	m_pModelRenderer(nullptr)
{
	Logging.AddLogger(NEW_AO LoggerFile("Out.log"));
}

Scene2DGame::~Scene2DGame()
{
	DELETE_AO m_pModelRenderer;
	DELETE_AO m_pSpriteRenderer;
	DELETE_AO m_pLine2DRenderer;
	DELETE_AO m_pLine3DRenderer;
	DELETE_AO m_pGroundTexture;
}

/**
 *
 */
void Scene2DGame::Initialize()
{
	GetMediaManager().AddSearchPath("../../examples/resources");
	GetMediaManager().AddSearchPath("../../examples/resources/datas");
	GetMediaManager().AddSearchPath("../../examples/resources/textures");
	GetMediaManager().AddSearchPath("../../examples/resources/models");
	GetMediaManager().AddSearchPath("../../examples/resources/shaders");
	GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
	GetMediaManager().AddSearchPath("../../examples/resources/script");
	GetMediaManager().AddSearchPath("../../examples/resources/fonts");
	GetMediaManager().AddSearchPath("../../examples/resources/tileset");

	AddGameComponent();

	Game::Initialize();
	//GetDebugOptions().ShowLogInGame = true;
}

/**
 *
 */
void Scene2DGame::LoadContent()
{
	Game::LoadContent();

	m_pWorld = NEW_AO World();
	auto* physicWorld = Game::Instance().GetPhysicsEngine().CreateWorld();
	m_pWorld->SetPhysicsWorld(physicWorld);
	physicWorld->SetGravity(Vector3F::Zero());
	GetGameInfo().SetWorld(m_pWorld);

	CreateAssets(Vector2I(48, 48));
	CreateMap(m_pWorld);
	CreateEnemies(m_pWorld);
	CreateSwordman(m_pWorld);

	m_pWorld->Initialize();
}

/**
 *
 */
void Scene2DGame::Update(const GameTime& gameTime_)
{
	Game::Update(gameTime_);
}

/**
 *
 */
void Scene2DGame::Draw()
{
	Game::Draw();
}

/**
 *
 */
void Scene2DGame::AddGameComponent()
{
	m_pLine2DRenderer = NEW_AO Line2DRendererComponent(this);
	m_pLine3DRenderer = NEW_AO Line3DRendererComponent(this);	
	m_pSpriteRenderer = NEW_AO SpriteRenderer(this);

	//AddComponent(m_pModelRenderer);
	AddComponent(m_pSpriteRenderer);
	AddComponent(m_pLine2DRenderer);
	AddComponent(m_pLine3DRenderer);
}

void Scene2DGame::CreateMap(World* pWorld)
{
	auto* pEntity = NEW_AO BaseEntity();
	pEntity->SetName("tiled map");
	auto* pTrans3D = NEW_AO Transform3DComponent(pEntity);
	pTrans3D->SetLocalPosition(Vector3F(0.0f, 0.0f, 1.0f));
	pTrans3D->SetLocalRotation(0.0f);
	//pTrans3D->SetLocalScale(Vector3F(48, 48, 1.0));

	auto* pMap = NEW_AO TiledMapComponent(pEntity);
	pMap->SetMapSize(Vector2I(30, 11));
	pMap->SetTileSize(Vector2I(48, 48));

	//layer 1
	auto* layer = NEW_AO TiledMapLayer();
	std::vector<ITile*> tiles;
	for (int y = 0; y < pMap->GetMapSize().y; ++y)
	{
		for (int x = 0; x < pMap->GetMapSize().x; ++x)
		{
			auto* sprite = GetAssetManager().GetAsset<SpriteData>("grass1");
			auto* tile = NEW_AO StaticTile(NEW_AO Sprite(*sprite));
			tiles.push_back(tile);
		}
	}
	layer->SetTiles(tiles);
	pMap->AddLayer(layer);

	for (int x = 0; x < 5; ++x)
	{
		tiles[4 + pMap->GetMapSize().x * x]->IsWall(true);
	}
	
	//wall
	/*for (int x = 0; x < pMap->GetMapSize().x; ++x)
	{
		tiles[x + pMap->GetMapSize().x * 6]->IsWall(true);
	}*/

	//layer 2
	layer = NEW_AO TiledMapLayer();
	tiles.clear();
	//create tile for autotile
	std::vector<ITile*> autoTiles;
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			std::ostringstream name;
			name << "autoGrass2_" << x << "_" << y;
			auto* sprite = GetAssetManager().GetAsset<SpriteData>(name.str());
			auto* tile = NEW_AO StaticTile(NEW_AO Sprite(*sprite));
			autoTiles.push_back(tile);
		}
	}
	for (int y = 0; y < pMap->GetMapSize().y; ++y)
	{
		for (int x = 0; x < pMap->GetMapSize().x; ++x)
		{
			if (y > 2 && y < pMap->GetMapSize().y - 2
				&& x > 5 && x < pMap->GetMapSize().x - 5)
			{
				auto* tile = NEW_AO AutoTile(layer, x, y);
				tile->setTiles(autoTiles);
				tiles.push_back(tile);
			}
			else
			{
				tiles.push_back(nullptr);
			}
		}
	}
	layer->SetTiles(tiles);
	pMap->AddLayer(layer);

	//layer 3
	/*layer = new TiledMapLayer();
	layer->SetTiles(tiles);
	pMap->AddLayer(layer);*/

	pEntity->GetComponentMgr()->AddComponent(pTrans3D);
	pEntity->GetComponentMgr()->AddComponent(pMap);
	pWorld->AddEntity(pEntity);
}

void Scene2DGame::CreateAssets(Vector2I tileSize)
{
	//static tile
	//auto texture = Texture::loadTexture(Game::Instance().GetMediaManager().FindMedia("Outside_A2.png"));
	auto* pSprite = NEW_AO SpriteData();
	pSprite->SetName("grass1");
	pSprite->SetPositionInTexture(RectangleI(0, 0, tileSize.x, tileSize.y));
	pSprite->SetAssetFileName("Outside_A2.png");
	GetAssetManager().AddAsset(NEW_AO Asset("grass1", pSprite));
	//autotile
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			pSprite = NEW_AO SpriteData();
			pSprite->SetName("grass1");
			pSprite->SetPositionInTexture(RectangleI(8 * tileSize.x + tileSize.x * x, y * tileSize.y, tileSize.x, tileSize.y));
			//pSprite->SetTexture2D(texture);
			pSprite->SetAssetFileName("Outside_A2.png");
			std::ostringstream name;
			name << "autoGrass2_" << x << "_" << y;
			GetAssetManager().AddAsset(NEW_AO Asset(name.str(), pSprite));
		}
	}
}

void Scene2DGame::CreateEnemies(World* pWorld)
{
	IFile* pFile = Game::Instance().GetMediaManager().FindMedia("octopus.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	_ennemi ennemi_datas;
	ar(cereal::make_nvp("octopus", ennemi_datas));

	auto* pEntity = NEW_AO BaseEntity();
	pEntity->SetName("octopus 1");
	auto* pTrans3D = NEW_AO Transform3DComponent(pEntity);
	pTrans3D->SetLocalPosition(Vector3F(100.0f, 100.0f, 0.2f));
	pTrans3D->SetLocalRotation(0.0f);
	//pTrans3D->SetLocalScale(Vector3F(32, 32, 1.0));
	pEntity->GetComponentMgr()->AddComponent(pTrans3D);

	//load texture
	//auto texture = Texture::loadTexture(ennemi_datas.tile_set.c_str());
	//load sprite
	int id = 0;
	for (auto& sprite : ennemi_datas.sprites)
	{
		auto* pSprite = NEW_AO SpriteData();
		std::ostringstream name;
		name << "octopus_" << sprite.id;
		id++;
		pSprite->SetName(name.str());
		pSprite->SetPositionInTexture(RectangleI(sprite.x, sprite.y, sprite.w, sprite.h));
		pSprite->SetOrigin(Vector2I(12, 20));
		pSprite->SetAssetFileName(ennemi_datas.tile_set);
		GetAssetManager().AddAsset(NEW_AO Asset(name.str(), pSprite));
	}

	auto* pAnimatedComponent = NEW_AO AnimatedSpriteComponent(pEntity);
	//load anim
	for (auto& anim : ennemi_datas.animations)
	{
		auto* pAnim = NEW_AO Animation2DData();
		pAnim->SetAnimationType(AnimationType::Loop);
		pAnim->SetName(anim.name);
		const auto frame_delay = 0.64f;

		for (auto& frame : anim.frames)
		{
			auto* frameData = NEW_AO FrameData(); 
			std::ostringstream spriteName;
			spriteName << "octopus_" << frame.sprite_id;
			frameData->SetSpriteId(spriteName.str());
			frameData->SetDuration(frame_delay);
			pAnim->AddFrame(*frameData);
		}

		GetAssetManager().AddAsset(NEW_AO Asset(pAnim->GetName(), pAnim));
		pAnimatedComponent->AddAnimation(NEW_AO Animation2D(*pAnim));
	}

	pEntity->GetComponentMgr()->AddComponent(pAnimatedComponent);
	//pAnimatedComponent->SetCurrentAnimation(0);

	auto* scriptComponent = NEW_AO ScriptComponent(pEntity);
	auto* pScriptCharacter = NEW_AO ScriptCharacter(pEntity, NEW_AO Enemy(pEntity));
	scriptComponent->SetScriptObject(pScriptCharacter);
	pEntity->GetComponentMgr()->AddComponent(scriptComponent);

	auto* debugComponent = NEW_AO DebugComponent(pEntity);
	debugComponent->DisplayPosition(true);
	pEntity->GetComponentMgr()->AddComponent(debugComponent);

	//collision
	//auto *colliderComponent = new Circle2DColliderComponent(pPlayerEntity);
	//colliderComponent->SetCenter(Vector3F::Zero());
	//colliderComponent->SetRadius(10.0f);
	auto* colliderComponent = NEW_AO Box2DColliderComponent(pEntity);
	colliderComponent->Set(0, 0, 10, 10);
	pEntity->GetComponentMgr()->AddComponent(colliderComponent);

	pWorld->AddEntity(pEntity);
}

void Scene2DGame::CreateSwordman(World* pWorld)
{
	//player
	const auto tileWidth = 48, tileHeight = 48;
	auto* pPlayerEntity = NEW_AO BaseEntity();
	pPlayerEntity->SetName("player 1");
	auto* pTrans3D = NEW_AO Transform3DComponent(pPlayerEntity);
	pTrans3D->SetLocalPosition(Vector3F(50.0f, 150.0f, 0.2f));
	pTrans3D->SetLocalRotation(0.0f);
	//pTrans3D->SetLocalScale(Vector3F(tileWidth, tileHeight, 1.0));
	pPlayerEntity->GetComponentMgr()->AddComponent(pTrans3D);

	//textures
	IFile* pFile = Game::Instance().GetMediaManager().FindMedia("player.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	_joueur player_datas;
	ar(cereal::make_nvp("swordman", player_datas));

	//create sprite
	//auto texture = Texture::loadTexture(player_datas.tile_set.c_str());
	//load sprite
	int id = 0;
	for (auto& sprite : player_datas.sprites)
	{
		auto* pSprite = NEW_AO SpriteData();
		std::ostringstream name;
		name << "player_" << sprite.id;
		id++;
		pSprite->SetName(name.str());
		pSprite->SetPositionInTexture(RectangleI(sprite.x, sprite.y, sprite.w, sprite.h));
		pSprite->SetOrigin(Vector2I(24, 38));
		pSprite->SetAssetFileName(player_datas.tile_set);
		GetAssetManager().AddAsset(NEW_AO Asset(name.str(), pSprite));
	}

	//load anim
	auto* pAnimatedComponent = NEW_AO AnimatedSpriteComponent(pPlayerEntity);
	for (auto& anim : player_datas.animations)
	{
		auto* pAnim = NEW_AO Animation2DData();
		pAnim->SetAnimationType(AnimationType::Loop);
		pAnim->SetName(anim.name);
		const auto frame_delay = 0.64f;

		for (auto& frame : anim.frames)
		{
			auto* frameData = NEW_AO FrameData();
			std::ostringstream spriteName;
			spriteName << "player_" << frame.sprite_id;
			frameData->SetSpriteId(spriteName.str());
			frameData->SetDuration(frame_delay);
			pAnim->AddFrame(*frameData);
		}

		GetAssetManager().AddAsset(NEW_AO Asset(pAnim->GetName(), pAnim));
		pAnimatedComponent->AddAnimation(NEW_AO Animation2D(*pAnim));
	}

	pPlayerEntity->GetComponentMgr()->AddComponent(pAnimatedComponent);
	//pAnimatedComponent->SetCurrentAnimation("stand_down");
	pWorld->AddEntity(pPlayerEntity);

	auto* scriptComponent = NEW_AO ScriptComponent(pPlayerEntity);
	auto* pScriptCharacter = NEW_AO ScriptCharacter(pPlayerEntity, NEW_AO Player(pPlayerEntity));
	scriptComponent->SetScriptObject(pScriptCharacter);
	pPlayerEntity->GetComponentMgr()->AddComponent(scriptComponent);

	//collision
	//auto *colliderComponent = new Circle2DColliderComponent(pPlayerEntity);
	//colliderComponent->SetCenter(Vector3F::Zero());
	//colliderComponent->SetRadius(10.0f);
	auto* colliderComponent = NEW_AO Box2DColliderComponent(pPlayerEntity);
	colliderComponent->Set(0, 0, 10, 10);
	pPlayerEntity->GetComponentMgr()->AddComponent(colliderComponent);

	//debug
	auto* debugComponent = NEW_AO DebugComponent(pPlayerEntity);
	debugComponent->DisplayPosition(true);
	pPlayerEntity->GetComponentMgr()->AddComponent(debugComponent);
	
	//Camera 2D
	auto* pCamera = NEW_AO BaseEntity();
	pCamera->SetName("camera 2D");
	auto* m_pCamera2D = NEW_AO Camera3DComponent(pCamera);
	auto* custom_camera_controller = NEW_AO Camera3DTargetedController(m_pCamera2D);
	m_pCamera2D->CameraController(custom_camera_controller);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera2D);
	custom_camera_controller->SetDeadZoneRatio(Vector2F(0.7f, 0.7f));
	custom_camera_controller->SetTargetedEntity(pPlayerEntity);
	custom_camera_controller->SetLimits(RectangleI(0, 0, 1500, 800));
	pWorld->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCamera2D);


	//Camera 3D
	pCamera = NEW_AO BaseEntity();
	m_pCamera3D = NEW_AO Camera3DComponent(pCamera);
	auto* pArcBall = NEW_AO ArcBallCameraController(m_pCamera3D);
	pArcBall->SetCamera(Vector3F(0, 0.0f, -50.0f), Vector3F::Zero(), -Vector3F::Up());
	pArcBall->Distance(70.0f);
	pArcBall->InputDistanceRate(4.0f);
	pArcBall->InputDisplacementRate(30.0f);
	m_pCamera3D->CameraController(pArcBall);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);
	pCamera->Initialize();
	m_pWorld->AddEntity(pCamera);

	GetGameInfo().SetActiveCamera(m_pCamera3D);
}