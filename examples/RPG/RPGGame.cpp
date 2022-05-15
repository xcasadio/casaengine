#include <string>
#include <iosfwd>

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
#include "Entities/Components/ScriptComponent.h"
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
#include "Map2D/TileSetData.h"
#include "Physics/Bullet/BulletObjectsContainer.h"
#include "Serializer/Serializer.h"

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
	GetDebugOptions().ShowPhysicsDebug = true;
}

void RPGGame::LoadContent()
{
	Game::LoadContent();

	m_pWorld = new World();
	auto* physicWorld = GetPhysicsEngine().CreateWorld();
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

void CreateLayerNew(const std::vector<int>& tile_ids, TiledMapData& tiled_map_parameters, float zOffset)
{
	TiledMapLayerData layer;
	layer.zOffset = zOffset;
	int index = 0;

	for (const int tile_id : tile_ids)
	{
		std::ostringstream name;
		name << "tile1_" << (tile_id % 16) << "_" << (int)(tile_id / 16);
		auto* tileParams = new StaticTileData();
		tileParams->spriteId = name.str();
		tileParams->x = (index % tiled_map_parameters.mapSize.x);
		tileParams->y = (int)(index / tiled_map_parameters.mapSize.x);
		layer.tiles.push_back(tileParams);

		index++;
	}

	tiled_map_parameters.layers.push_back(layer);
}

void CreateTileSet(Vector2I tileSize, const std::string& tileSetAssetFileName)
{
	for (int y = 0; y < 6; ++y)
	{
		for (int x = 0; x < 16; ++x)
		{
			auto* pSprite = new SpriteData();
			pSprite->SetPositionInTexture(CasaEngine::Rectangle(x * tileSize.x, y * tileSize.y, tileSize.x, tileSize.y));
			pSprite->SetAssetFileName(tileSetAssetFileName); //16x6 tiles
			std::ostringstream name;
			name << "tile1_" << x << "_" << y;
			pSprite->SetName(name.str());
			Game::Instance().GetAssetManager().AddAsset(new Asset(name.str(), pSprite));
		}
	}
}

void RPGGame::CreateMap(World* pWorld)
{
	_map map_datas;

	{
		IFile* pFile = GetMediaManager().FindMedia("map_1_1.json", true);
		std::ifstream is(pFile->Fullname());
		json j;
		is >> j;
		from_json(j["map"], map_datas);
	}

	auto tileSize = Vector2I(32, 32);
	auto tileSetAssetFileName = map_datas.tile_set;

	CreateTileSet(tileSize, tileSetAssetFileName);

	TiledMapData tiled_map_parameters;

	{
		IFile* pFile = GetMediaManager().FindMedia("map_1_1_tile_set.json", true);
		std::ifstream is(pFile->Fullname());
		json j;
		is >> j;
		from_json(j, tiled_map_parameters);
	}

	//{
	//	tiled_map_parameters.tileSize = tileSize;
	//	tiled_map_parameters.mapSize = Vector2I(map_datas.sizeX, map_datas.sizeY);
	//	CreateLayerNew(map_datas.tile_layer_1, tiled_map_parameters, 0.0f);
	//	CreateLayerNew(map_datas.tile_layer_2, tiled_map_parameters, 0.1f);
	//	CreateLayerNew(map_datas.tile_layer_4, tiled_map_parameters, 1.0f);
	//	std::ofstream os("C:\\Users\\casad\\dev\\repo\\casaengine\\examples\\resources\\datas\\map_1_1_tile_set.json");
	//	json j2;
	//	to_json(j2, tiled_map_parameters);
	//	os << std::setw(4) << j2 << std::endl; // pretty json
	//}

	TiledMapCreator::Create(tiled_map_parameters, *pWorld);

	//create map
	//auto* pEntity = new BaseEntity();
	//pEntity->SetName("tiled map");
	//pEntity->GetCoordinates().SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
	//pEntity->GetCoordinates().SetLocalRotation(0.0f);
	//
	//
	//auto* pMap = new TiledMapComponent(pEntity);
	//pMap->SetMapSize(Vector2I(map_datas.sizeX, map_datas.sizeY));
	//pMap->SetTileSize(Vector2I(32, 32));
	//
	////layer 1
	//CreateLayer(map_datas.tile_layer_1, pMap, 0);
	//CreateLayer(map_datas.tile_layer_2, pMap, 0.01f);
	//CreateLayer(map_datas.tile_layer_4, pMap, 1.0f);
	//
	//for (int i = 0; i < map_datas.tile_type_layer_1.size(); ++i)
	//{
	//	if (map_datas.tile_type_layer_1[i] == 1)
	//	{
	//		pMap->GetLayer(0)->GetTiles()[i]->IsWall(true);
	//	}
	//}
	//
	//pEntity->GetComponentMgr()->AddComponent(pMap);
	//pWorld->AddEntity(pEntity);
}

void RPGGame::CreateAssets(Vector2I tileSize)
{
	TileSetData tileSetData;
	tileSetData.tileSize = Vector2I(32, 32);
	tileSetData.spriteSheetFileName = "Tile1.png";

	//auto* pSprite = new SpriteData();
	//pSprite->SetName("grass1");
	//pSprite->SetPositionInTexture(CasaEngine::Rectangle(0, 0, tileSize.x, tileSize.y));
	//pSprite->SetAssetFileName("Outside_A2.png");
	//GetAssetManager().AddAsset(new Asset("grass1", pSprite));
	//
	//for (int y = 0; y < 3; ++y)
	//{
	//	for (int x = 0; x < 2; ++x)
	//	{
	//		pSprite = new SpriteData();
	//		pSprite->SetName("grass1");
	//		pSprite->SetPositionInTexture(CasaEngine::Rectangle(8 * tileSize.x + tileSize.x * x, y * tileSize.y, tileSize.x, tileSize.y));
	//		pSprite->SetAssetFileName("Outside_A2.png");
	//		std::ostringstream name;
	//		name << "autoGrass2_" << x << "_" << y;
	//		GetAssetManager().AddAsset(new Asset(name.str(), pSprite));
	//	}
	//}


}

void CreateSprite(const std::string tileSetName, const std::vector<_sprite>& sprites, const char* prefix)
{
	int id = 0;

	for (auto& sprite : sprites)
	{
		auto* pSprite = new SpriteData();
		std::ostringstream name;
		name << prefix << sprite.id;
		id++;
		pSprite->SetName(name.str());
		pSprite->SetPositionInTexture(CasaEngine::Rectangle(sprite.x, sprite.y, sprite.w, sprite.h));
		pSprite->SetOrigin(Vector2I(sprite.px, sprite.py));

		for (auto& coll : sprite.att)
		{
			Collision collision;
			collision.SetType(CollisionHitType::Attack);
			collision.SetShape(new CasaEngine::Rectangle(coll.x /* - sprite.px*/, coll.y /* - sprite.py*/, coll.w, coll.h));
			pSprite->_collisionShapes.push_back(collision);
		}

		for (auto& coll : sprite.def)
		{
			Collision collision;
			collision.SetType(CollisionHitType::Defense);
			collision.SetShape(new CasaEngine::Rectangle(coll.x /* - sprite.px */ , coll.y /* - sprite.py */ , coll.w, coll.h));
			pSprite->_collisionShapes.push_back(collision);
		}

		pSprite->SetAssetFileName(tileSetName);
		Game::Instance().GetAssetManager().AddAsset(new Asset(name.str(), pSprite));
	}
}

void CreateAnimations(const char* prefix, AnimatedSpriteComponent* pAnimatedComponent, const std::vector<animation>& animations)
{
	for (auto& anim : animations)
	{
		auto* pAnim = new Animation2DData();
		pAnim->SetName(anim.name);
		pAnim->_animationType = Loop;

		for (auto& frame : anim.frames)
		{
			auto* frameData = new FrameData();
			std::ostringstream spriteName;
			spriteName << prefix << frame.sprite_id;
			frameData->_spriteId = spriteName.str();
			frameData->_duration = frame.delay;
			pAnim->_frames.push_back(*frameData);
		}

		Game::Instance().GetAssetManager().AddAsset(new Asset(pAnim->GetName(), pAnim));
		pAnimatedComponent->AddAnimation(new Animation2D(*pAnim));
	}
}

void RPGGame::CreateEnemies(World* pWorld)
{
	IFile* pFile = GetMediaManager().FindMedia("octopus.json", true);
	std::ifstream is(pFile->Fullname());
	_ennemi ennemi_datas;
	json j;
	is >> j;
	from_json(j["octopus"], ennemi_datas);

	auto* pEntity = new BaseEntity();
	pEntity->SetName("octopus 1");
	pEntity->GetCoordinates().SetLocalPosition(Vector3(100.0f, 100.0f, 0.1f));
	pEntity->GetCoordinates().SetLocalRotation(0.0f);

	CreateSprite(ennemi_datas.tile_set, ennemi_datas.sprites, "octopus_");

	auto* pAnimatedComponent = new AnimatedSpriteComponent(pEntity);
	CreateAnimations("octopus_", pAnimatedComponent, ennemi_datas.animations);
	
	pEntity->GetComponentMgr()->AddComponent(pAnimatedComponent);

	auto* scriptComponent = new ScriptComponent(pEntity);
	auto* pScriptCharacter = new ScriptCharacter(pEntity, new Enemy(pEntity));
	scriptComponent->SetScriptObject(pScriptCharacter);
	pEntity->GetComponentMgr()->AddComponent(scriptComponent);

	auto* debugComponent = new DebugComponent(pEntity);
	debugComponent->DisplayPosition(false);
	debugComponent->DisplayAnimation2DCollisions(true);
	pEntity->GetComponentMgr()->AddComponent(debugComponent);

	//collision
	auto* colliderComponent = new Circle2DColliderComponent(pEntity);
	colliderComponent->SetCenter(Vector3::Zero());
	colliderComponent->SetRadius(10.0f);
	colliderComponent->AxisConstraint(AxisConstraints::XY);
	//auto* colliderComponent = new Box2DColliderComponent(pEntity);
	//colliderComponent->Set(0, 0, 10, 10);
	pEntity->GetComponentMgr()->AddComponent(colliderComponent);

	pWorld->AddEntity(pEntity);
}

void RPGGame::CreateSwordman(World* pWorld)
{
	//create weapon
	auto* weaponEntity = new BaseEntity();
	weaponEntity->SetName("sword");
	auto* debugComponent = new DebugComponent(weaponEntity);
	debugComponent->DisplayPosition(false);
	debugComponent->DisplayAnimation2DCollisions(true);
	weaponEntity->GetComponentMgr()->AddComponent(debugComponent);

	IFile* pFile = GetMediaManager().FindMedia("baton.json", true);
	_weapon weapon_data;

	{
		std::ifstream is(pFile->Fullname());
		json j;
		is >> j;
		from_json(j["weapon"], weapon_data);
	}

	CreateSprite(weapon_data.tile_set, weapon_data.sprites, "sword_");

	auto* pAnimatedComponent = new AnimatedSpriteComponent(weaponEntity);
	CreateAnimations("sword_", pAnimatedComponent, weapon_data.animations);

	weaponEntity->GetComponentMgr()->AddComponent(pAnimatedComponent);
	weaponEntity->IsEnabled(false);
	weaponEntity->IsVisible(false);
	pWorld->AddEntity(weaponEntity);

	//auto* scriptComponent = new ScriptComponent(weaponEntity);
	//auto weapon = new Weapon(weaponEntity);
	//auto* pScriptCharacter = new ScriptCharacter(weaponEntity, player);
	//scriptComponent->SetScriptObject(pScriptCharacter);
	//weaponEntity->GetComponentMgr()->AddComponent(scriptComponent);

	////////////////////////////////////////////////////////////
	//player
	constexpr auto tileWidth = 48, tileHeight = 48;
	auto* pPlayerEntity = new BaseEntity();
	pPlayerEntity->SetName("player 1");
	pPlayerEntity->GetCoordinates().SetLocalPosition(Vector3(50.0f, 150.0f, 0.1f));
	pPlayerEntity->GetCoordinates().SetLocalRotation(0.0f);

	//read file
	pFile = GetMediaManager().FindMedia("player.json", true);
	std::ifstream is(pFile->Fullname());
	_joueur player_datas;
	json j;
	is >> j;
	from_json(j["swordman"], player_datas);

	//create sprite
	CreateSprite(player_datas.tile_set, player_datas.sprites, "player_");

	pAnimatedComponent = new AnimatedSpriteComponent(pPlayerEntity);
	CreateAnimations("player_", pAnimatedComponent, player_datas.animations);

	pPlayerEntity->GetComponentMgr()->AddComponent(pAnimatedComponent);
	pWorld->AddEntity(pPlayerEntity);

	auto* scriptComponent = new ScriptComponent(pPlayerEntity);
	auto player = new Player(pPlayerEntity);
	player->SetWeapon(weaponEntity);
	player->Speed(50.0f);
	auto* pScriptCharacter = new ScriptCharacter(pPlayerEntity, player);
	scriptComponent->SetScriptObject(pScriptCharacter);
	pPlayerEntity->GetComponentMgr()->AddComponent(scriptComponent);

	//collision
	auto* colliderComponent = new Circle2DColliderComponent(pPlayerEntity);
	colliderComponent->SetCenter(Vector3::Zero());
	colliderComponent->SetRadius(10.0f);
	colliderComponent->AxisConstraint(AxisConstraints::XY);
	//auto* colliderComponent = new Box2DColliderComponent(pPlayerEntity);
	//colliderComponent->Set(0, 0, 10, 10);
	pPlayerEntity->GetComponentMgr()->AddComponent(colliderComponent);

	//debug
	debugComponent = new DebugComponent(pPlayerEntity);
	debugComponent->DisplayPosition(false);
	debugComponent->DisplayAnimation2DCollisions(true);
	pPlayerEntity->GetComponentMgr()->AddComponent(debugComponent);

	//Camera 2D
	auto* pCamera = new BaseEntity();
	pCamera->SetName("camera targeted");
	//auto* m_pCameraTargeted = new Camera2DTargetedComponent(pCamera);
	auto* m_pCameraTargeted = new Camera3DTargetedComponent(pCamera);
	pCamera->GetComponentMgr()->AddComponent(m_pCameraTargeted);
	m_pCameraTargeted->SetDeadZoneRatio(Vector2(0.7f, 0.7f));
	m_pCameraTargeted->SetTargetedEntity(pPlayerEntity);
	m_pCameraTargeted->SetLimits(CasaEngine::Rectangle(0, 0, 1500, 800));
	pWorld->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCameraTargeted);

	//Camera 3D
	pCamera = new BaseEntity();
	m_pCamera3D = new ArcBallCameraComponent(pCamera);
	m_pCamera3D->SetCamera(Vector3(0, 0.0f, -50.0f), Vector3(0, 10.0f, 0.0f), -Vector3::Up());
	m_pCamera3D->Distance(70.0f);
	m_pCamera3D->InputDistanceRate(4.0f);
	m_pCamera3D->InputDisplacementRate(30.0f);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);
	pCamera->Initialize();
	m_pWorld->AddEntity(pCamera);

	//GetGameInfo().SetActiveCamera(m_pCamera3D);
}
