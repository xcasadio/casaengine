#include <string>
#include <iosfwd>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

#include "RPGGame.h"

#include <BulletCollision/CollisionDispatch/btCollisionObject.h>

#include "Player.h"
#include "Enemy.h"
#include "EnemyController.h"
#include "Animations/Animation2D.h"
#include "Assets/AssetManager.h"

#include "Entities/Components/AnimatedSpriteComponent.h"
#include "Entities/Components/Cameras/ArcBallCameraComponent.h"
#include "Entities/Components/GridComponent.h"
#include "Entities/Components/MeshComponent.h"
#include "Entities/Components/ScriptComponent.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "ScriptCharacter.h"

#include "Graphics/Textures/Texture.h"
#include "Log/LoggerFile.h"
#include "Maths/Vector3.h"

#include "Map2D/AutoTile.h"
#include "Map2D/StaticTile.h"
#include "Map2D/TiledMapComponent.h"

#include "load_save_types.h"
#include "Entities/Components/DebugComponent.h"
#include "Entities/Components/Cameras/Camera2DTargetedComponent.h"
#include "Entities/Components/Cameras/Camera3DTargetedComponent.h"
#include "Entities/Components/Physics/Box2DColliderComponent.h"
#include "Entities/Components/Physics/Circle2DColliderComponent.h"
#include "Physics/Bullet/BulletObjectsContainer.h"

using namespace CasaEngine;

RPGGame::RPGGame() :
	m_pGroundTexture(nullptr),
	m_pEntity(nullptr),
	m_pAnimatedSprite(nullptr),
	m_pCamera3D(nullptr),
	m_pWorld(nullptr)
{
	Logging.AddLogger(new LoggerFile("Out.log"));
}

RPGGame::~RPGGame()
{
	delete m_pGroundTexture;
}

void RPGGame::Initialize()
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

	AddDebugComponents();
	AddUsualComponents();

	Game::Initialize();
	GetDebugOptions().ShowPhysicsDebug = false;
}

void RPGGame::LoadContent()
{
	Game::LoadContent();

	m_pWorld = new World();
	auto* physicWorld = Game::Instance().GetPhysicsEngine().CreateWorld();
	m_pWorld->SetPhysicsWorld(physicWorld);
	physicWorld->SetGravity(Vector3::Zero());
	GetGameInfo().SetWorld(m_pWorld);

	CreateAssets(Vector2I(32, 32));
	CreateMap(m_pWorld);
	CreateEnemies(m_pWorld);
	CreateSwordman(m_pWorld);

	m_pWorld->Initialize();
}

void CreateLayer(const std::vector<int>& tilesId, TiledMapComponent* pMap, float zOffset)
{
	auto* layer = new TiledMapLayer();
	layer->SetZOffset(zOffset);
	std::vector<ITile*> tiles;
	for (int y = 0; y < pMap->GetMapSize().y; ++y)
	{
		for (int x = 0; x < pMap->GetMapSize().x; ++x)
		{
			const auto tile_id = tilesId[y * pMap->GetMapSize().x + x];
			std::ostringstream name;
			name << "tile1_" << (tile_id % 16) << "_" << (int)(tile_id / 16);
			auto* sprite = Game::Instance().GetAssetManager().GetAsset<SpriteData>(name.str());
			auto* tile = new StaticTile(new Sprite(*sprite));
			tiles.push_back(tile);
		}
	}
	layer->SetTiles(tiles);
	pMap->AddLayer(layer);
}

void RPGGame::CreateMap(World* pWorld)
{
	IFile* pFile = Game::Instance().GetMediaManager().FindMedia("map_1_1.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	_map map_datas;
	ar(cereal::make_nvp("map", map_datas));
	auto tileSize = Vector2I(32, 32);
	//create sprite
	for (int y = 0; y < 6; ++y)
	{
		for (int x = 0; x < 16; ++x)
		{
			auto* pSprite = new SpriteData();
			pSprite->SetName("grass1");
			pSprite->SetPositionInTexture(RectangleI(x * tileSize.x, y * tileSize.y, tileSize.x, tileSize.y));
			pSprite->SetAssetFileName(map_datas.tile_set); //16x6 tiles
			std::ostringstream name;
			name << "tile1_" << x << "_" << y;
			GetAssetManager().AddAsset(new Asset(name.str(), pSprite));
		}
	}

	//create map
	auto* pEntity = new BaseEntity();
	pEntity->SetName("tiled map");
	auto* pTrans3D = new Transform3DComponent(pEntity);
	pTrans3D->SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
	pTrans3D->SetLocalRotation(0.0f);
	//pTrans3D->SetLocalScale(Vector3(48, 48, 1.0));

	auto* pMap = new TiledMapComponent(pEntity);
	pMap->SetMapSize(Vector2I(map_datas.sizeX, map_datas.sizeY));
	pMap->SetTileSize(Vector2I(32, 32));

	//layer 1
	CreateLayer(map_datas.tile_layer_1, pMap, 0);
	CreateLayer(map_datas.tile_layer_2, pMap, 0.01f);
	CreateLayer(map_datas.tile_layer_4, pMap, 1.0f);

	for (int i = 0; i < map_datas.tile_type_layer_1.size(); ++i)
	{
		if (map_datas.tile_type_layer_1[i] == 1)
		{
			pMap->GetLayer(0)->GetTiles()[i]->IsWall(true);
		}
	}

	//TEST create box
	/*
	const auto* shape = new CasaEngine::Rectangle(0, 0, 48, 48);
	//auto *shape = new Circle(m_TileSize.x);
	auto position = Vector3(10, 10, 0.0f);
	auto* collisionShape = Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->CreateCollisionShape(shape, position);
	auto* bullet_collision_object_container = dynamic_cast<BulletCollisionObjectContainer*>(collisionShape);
	bullet_collision_object_container->GetCollisionObject()->setUserPointer(pEntity);
	bullet_collision_object_container->GetCollisionObject()->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->AddCollisionObject(collisionShape);
	*/
	/*
	//layer 2
	layer = new TiledMapLayer();
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
			auto* tile = new StaticTile(new Sprite(*sprite));
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
				auto* tile = new AutoTile(layer, x, y);
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
	*/

	pEntity->GetComponentMgr()->AddComponent(pTrans3D);
	pEntity->GetComponentMgr()->AddComponent(pMap);
	pWorld->AddEntity(pEntity);
}

void RPGGame::CreateAssets(Vector2I tileSize)
{
	//static tile
	//auto texture = Texture::loadTexture(Game::Instance().GetMediaManager().FindMedia("Outside_A2.png"));
	auto* pSprite = new SpriteData();
	pSprite->SetName("grass1");
	pSprite->SetPositionInTexture(RectangleI(0, 0, tileSize.x, tileSize.y));
	pSprite->SetAssetFileName("Outside_A2.png");
	GetAssetManager().AddAsset(new Asset("grass1", pSprite));
	//autotile
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			pSprite = new SpriteData();
			pSprite->SetName("grass1");
			pSprite->SetPositionInTexture(RectangleI(8 * tileSize.x + tileSize.x * x, y * tileSize.y, tileSize.x, tileSize.y));
			//pSprite->SetTexture2D(texture);
			pSprite->SetAssetFileName("Outside_A2.png");
			std::ostringstream name;
			name << "autoGrass2_" << x << "_" << y;
			GetAssetManager().AddAsset(new Asset(name.str(), pSprite));
		}
	}
}

const auto frame_delay = 0.64f * 5.0f;

void RPGGame::CreateEnemies(World* pWorld)
{
	IFile* pFile = Game::Instance().GetMediaManager().FindMedia("octopus.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	_ennemi ennemi_datas;
	ar(cereal::make_nvp("octopus", ennemi_datas));

	auto* pEntity = new BaseEntity();
	pEntity->SetName("octopus 1");
	auto* pTrans3D = new Transform3DComponent(pEntity);
	pTrans3D->SetLocalPosition(Vector3(100.0f, 100.0f, 0.1f));
	pTrans3D->SetLocalRotation(0.0f);
	//pTrans3D->SetLocalScale(Vector3(32, 32, 1.0));
	pEntity->GetComponentMgr()->AddComponent(pTrans3D);

	//load texture
	//auto texture = Texture::loadTexture(ennemi_datas.tile_set.c_str());
	//load sprite
	int id = 0;
	for (auto& sprite : ennemi_datas.sprites)
	{
		auto* pSprite = new SpriteData();
		std::ostringstream name;
		name << "octopus_" << sprite.id;
		id++;
		pSprite->SetName(name.str());
		pSprite->SetPositionInTexture(RectangleI(sprite.x, sprite.y, sprite.w, sprite.h));
		pSprite->SetOrigin(Vector2I(12, 20));
		pSprite->SetAssetFileName(ennemi_datas.tile_set);
		GetAssetManager().AddAsset(new Asset(name.str(), pSprite));
	}

	auto* pAnimatedComponent = new AnimatedSpriteComponent(pEntity);
	//load anim
	for (auto& anim : ennemi_datas.animations)
	{
		auto* pAnim = new Animation2DData();
		pAnim->SetAnimationType(AnimationType::Loop);
		pAnim->SetName(anim.name);

		for (auto& frame : anim.frames)
		{
			auto* frameData = new FrameData();
			std::ostringstream spriteName;
			spriteName << "octopus_" << frame.sprite_id;
			frameData->SetSpriteId(spriteName.str());
			frameData->SetDuration(frame_delay);
			pAnim->AddFrame(*frameData);
		}

		GetAssetManager().AddAsset(new Asset(pAnim->GetName(), pAnim));
		pAnimatedComponent->AddAnimation(new Animation2D(*pAnim));
	}

	pEntity->GetComponentMgr()->AddComponent(pAnimatedComponent);
	//pAnimatedComponent->SetCurrentAnimation(0);

	auto* scriptComponent = new ScriptComponent(pEntity);
	auto* pScriptCharacter = new ScriptCharacter(pEntity, new Enemy(pEntity));
	scriptComponent->SetScriptObject(pScriptCharacter);
	pEntity->GetComponentMgr()->AddComponent(scriptComponent);

	auto* debugComponent = new DebugComponent(pEntity);
	debugComponent->DisplayPosition(true);
	pEntity->GetComponentMgr()->AddComponent(debugComponent);

	//collision
	auto* colliderComponent = new Circle2DColliderComponent(pEntity);
	colliderComponent->SetCenter(Vector3::Zero());
	colliderComponent->SetRadius(10.0f);
	//auto* colliderComponent = new Box2DColliderComponent(pEntity);
	//colliderComponent->Set(0, 0, 10, 10);
	pEntity->GetComponentMgr()->AddComponent(colliderComponent);

	pWorld->AddEntity(pEntity);
}

void RPGGame::CreateSwordman(World* pWorld)
{
	//player
	constexpr auto tileWidth = 48, tileHeight = 48;
	auto* pPlayerEntity = new BaseEntity();
	pPlayerEntity->SetName("player 1");
	auto* pTrans3D = new Transform3DComponent(pPlayerEntity);
	pTrans3D->SetLocalPosition(Vector3(50.0f, 150.0f, 0.1f));
	pTrans3D->SetLocalRotation(0.0f);
	//pTrans3D->SetLocalScale(Vector3(tileWidth, tileHeight, 1.0));
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
		auto* pSprite = new SpriteData();
		std::ostringstream name;
		name << "player_" << sprite.id;
		id++;
		pSprite->SetName(name.str());
		pSprite->SetPositionInTexture(RectangleI(sprite.x, sprite.y, sprite.w, sprite.h));
		pSprite->SetOrigin(Vector2I(24, 38));
		pSprite->SetAssetFileName(player_datas.tile_set);
		GetAssetManager().AddAsset(new Asset(name.str(), pSprite));
	}

	//load anim
	auto* pAnimatedComponent = new AnimatedSpriteComponent(pPlayerEntity);
	for (auto& anim : player_datas.animations)
	{
		auto* pAnim = new Animation2DData();
		pAnim->SetAnimationType(AnimationType::Loop);
		pAnim->SetName(anim.name);

		for (auto& frame : anim.frames)
		{
			auto* frameData = new FrameData();
			std::ostringstream spriteName;
			spriteName << "player_" << frame.sprite_id;
			frameData->SetSpriteId(spriteName.str());
			frameData->SetDuration(frame_delay);
			pAnim->AddFrame(*frameData);
		}

		GetAssetManager().AddAsset(new Asset(pAnim->GetName(), pAnim));
		pAnimatedComponent->AddAnimation(new Animation2D(*pAnim));
	}

	pPlayerEntity->GetComponentMgr()->AddComponent(pAnimatedComponent);
	//pAnimatedComponent->SetCurrentAnimation("stand_down");
	pWorld->AddEntity(pPlayerEntity);

	auto* scriptComponent = new ScriptComponent(pPlayerEntity);
	auto* pScriptCharacter = new ScriptCharacter(pPlayerEntity, new Player(pPlayerEntity));
	scriptComponent->SetScriptObject(pScriptCharacter);
	pPlayerEntity->GetComponentMgr()->AddComponent(scriptComponent);

	//collision
	auto* colliderComponent = new Circle2DColliderComponent(pPlayerEntity);
	colliderComponent->SetCenter(Vector3::Zero());
	colliderComponent->SetRadius(10.0f);
	//auto* colliderComponent = new Box2DColliderComponent(pPlayerEntity);
	//colliderComponent->Set(0, 0, 10, 10);
	pPlayerEntity->GetComponentMgr()->AddComponent(colliderComponent);

	//debug
	auto* debugComponent = new DebugComponent(pPlayerEntity);
	debugComponent->DisplayPosition(true);
	pPlayerEntity->GetComponentMgr()->AddComponent(debugComponent);

	//Camera 2D
	auto* pCamera = new BaseEntity();
	pCamera->SetName("camera targeted");
	//auto* m_pCameraTargeted = new Camera2DTargetedComponent(pCamera);
	auto* m_pCameraTargeted = new Camera3DTargetedComponent(pCamera);
	pCamera->GetComponentMgr()->AddComponent(m_pCameraTargeted);
	m_pCameraTargeted->SetDeadZoneRatio(Vector2(0.7f, 0.7f));
	m_pCameraTargeted->SetTargetedEntity(pPlayerEntity);
	m_pCameraTargeted->SetLimits(RectangleI(0, 0, 1500, 800));
	pWorld->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCameraTargeted);

	//Camera 3D
	pCamera = new BaseEntity();
	m_pCamera3D = new ArcBallCameraComponent(pCamera);
	m_pCamera3D->SetCamera(Vector3(0, 0.0f, -50.0f), Vector3(0, 10.0f, 0.0f), Vector3::Up());
	m_pCamera3D->Distance(70.0f);
	m_pCamera3D->InputDistanceRate(4.0f);
	m_pCamera3D->InputDisplacementRate(30.0f);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);
	pCamera->Initialize();
	m_pWorld->AddEntity(pCamera);

	//GetGameInfo().SetActiveCamera(m_pCamera3D);
}