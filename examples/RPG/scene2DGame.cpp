#include <string>
#include <iosfwd>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/details/helpers.hpp>
#include <cereal/types/vector.hpp>

#include "scene2DGame.h"

#include "Hero.h"
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
#include "Entities/Components/Physics/Box2DColliderComponent.h"
#include "Entities/Components/ScriptComponent.h"
#include "Entities/Components/StaticSpriteComponent.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Entities/EntityManager.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "Game/Input.h"
#include "GameTime.h"
#include "ScriptCharacter.h"
#include "Animations/AnimationEndEvent.h"
#include "Animations/SetFrameEvent.h"

#include "Graphics/Materials/Material.h"
#include "Graphics/Mesh/Mesh.h"
#include "Graphics/Primitives/BoxPrimitive.h"
#include "Graphics/Primitives/PlanePrimitive.h"
#include "Graphics/Renderer/Enums.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Textures/Texture.h"
#include "Log/LoggerFile.h"
#include "Maths/Math.h"
#include "Maths/Vector3.h"
#include "Maths/Vector4.h"
#include "Memory/MemoryAllocation.h"
#include "Parsers/Xml/tinyxml2.h"
#include "Physics/PhysicsEngine.h"
#include "Resources/ResourceManager.h"
#include "SFML/Window/Mouse.hpp"
#include "Sprite/SpriteTypes.h"
#include "Entities/Components/Physics/RigidBodyComponent.h"
#include "Map2D/AutoTile.h"
#include "Map2D/StaticTile.h"
#include "Map2D/TiledMapComponent.h"
#include "Tools/InGameLogger.h"

#include "load_save_types.h"

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
	GetGameInfo().SetWorld(m_pWorld);
	//m_pWorld->SetPhysicsWorld(PhysicsEngine::Instance().CreateWorld());
	/*
	LoadAssets();
	CreateEntities();
	CreateBackground();
	CreatePlayer();*/

	CreateAssets(Vector2I(48, 48));
	CreateMap(m_pWorld);
	CreateEnnemies(m_pWorld);
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
	//GetGameInfo().GetProjectManager().LoadProject("H:\\Developpement\\CasaEngine2D\\Projects\\LostKingdom\\LostKingdom.xml");
	//m_pModelRenderer = NEW_AO MeshRendererGameComponent(this);
	m_pLine2DRenderer = NEW_AO Line2DRendererComponent(this);
	//m_pLine3DRenderer = NEW_AO Line3DRendererComponent(this);
	m_pSpriteRenderer = NEW_AO SpriteRenderer(this);

	//AddComponent(m_pModelRenderer);
	AddComponent(m_pSpriteRenderer);
	AddComponent(m_pLine2DRenderer);
	//AddComponent(m_pLine3DRenderer);
}

/**
 *
 */
void Scene2DGame::LoadAssets()
{

}

/**
 *
 */
void Scene2DGame::CreateEntities()
{
	//Camera 3D
	BaseEntity* pCamera = NEW_AO BaseEntity();
	m_pCamera3D = NEW_AO Camera3DComponent(pCamera);
	ArcBallCameraController* pArcBall = NEW_AO ArcBallCameraController(m_pCamera3D);
	pArcBall->SetCamera(Vector3F(0, 0.0f, -50.0f), Vector3F::Zero(), Vector3F::Up());
	pArcBall->Distance(7.0f);
	m_pCamera3D->CameraController(pArcBall);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);
	pCamera->Initialize();
	m_pWorld->AddEntity(pCamera);

	GetGameInfo().SetActiveCamera(m_pCamera3D);

	//FPS
	/*BaseEntity *pEntity = NEW_AO BaseEntity();
	Transform2DComponent *pTrans2D = NEW_AO Transform2DComponent(pEntity);
	pTrans2D->SetLocalPosition(Vector2F(10.0f, 10.0f));
	pEntity->GetComponentMgr()->AddComponent(pTrans2D);
	FPSMonitoringComponent *pFPS = NEW_AO FPSMonitoringComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pFPS);
	pEntity->Initialize();
	m_pWorld->AddEntity(pEntity);*/

	//Grid
	BaseEntity* pEntity = NEW_AO BaseEntity();
	GridComponent* pGridComponent = NEW_AO GridComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pGridComponent);
	pEntity->Initialize();
	m_pWorld->AddEntity(pEntity);

	//ground
	/*pEntity = NEW_AO BaseEntity();
	pEntity->SetName("ground");
	Transform3DComponent *pTransform = NEW_AO Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3F(0.0f, -0.2f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	MeshComponent *pModelCpt = NEW_AO MeshComponent(pEntity);
	PlanePrimitive *pPrimitive = NEW_AO PlanePrimitive(100.0f, 100.0f);
	Model *pModel = pPrimitive->CreateModel();
	GetResourceManager().Add("groundModel", pModel);
	DELETE_AO pPrimitive;
	//new material
	Material* pMat = pModel->GetMaterial()->Clone();
	GetResourceManager().Add("groundMaterial", pMat);
	pModel->SetMaterial(pMat);
	m_pGroundTexture = NEW_AO Texture();
	m_pGroundTexture->CreateFromFile("ceilingMain_DIF.png", PixelFormat::ARGB_8888);
	pMat->SetTexture0(m_pGroundTexture);
	pMat->SetTexture0Repeat(Vector2F(50, 50));
	//
	pModelCpt->SetModel(pModel);

	bgfx::ProgramHandle pEffect = IRenderer::Get().CreateEffectFromFile("simple");
	pModelCpt->SetEffect(pEffect);

	pEntity->GetComponentMgr()->AddComponent(pModelCpt);
	pEntity->Initialize();

	m_pWorld->AddEntity(pEntity);*/

	//no physics
	//m_pWorld->GetPhysicsWorld()->SetGravity(Vector3F::Zero());

	//box2d
	/*pEntity = NEW_AO BaseEntity();
	pEntity->SetName("ground");
	Transform3DComponent *pTransform = NEW_AO Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3F(0.0f, -0.2f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
	pEntity->GetComponentMgr()->AddComponent(pTransform);
	MeshComponent *pModelCpt = NEW_AO MeshComponent(pEntity);
	BoxPrimitive *pPrimitive = NEW_AO BoxPrimitive();
	Model *pModel = pPrimitive->CreateModel();
	GetResourceManager().Add("groundModel", pModel);
	DELETE_AO pPrimitive;
	pModelCpt->SetModel(pModel);

	bgfx::ProgramHandle pEffect = IRenderer::Get().CreateEffectFromFile("simple");
	pModelCpt->SetEffect(pEffect);

	pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	Box2DColliderComponent *pBox2D = NEW_AO Box2DColliderComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pBox2D);

	m_pWorld->GetPhysicsWorld()->AddRigidBody(pBox2D);

	//btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(150.),btScalar(50.),btScalar(150.)));

	pEntity->Initialize();
	m_pWorld->AddEntity(pEntity);*/

	/*
	m_collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,-43,0));

	//We can also use DemoApplication::localCreateRigidBody, but for clarity it is provided here:
	{
		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		m_dynamicsWorld->addRigidBody(body);
	}*/
}

/**
 *
 */
void Scene2DGame::CreatePlayer()
{
	BaseEntity* pEntity = NEW_AO BaseEntity();
	Transform3DComponent* pTrans3D = NEW_AO Transform3DComponent(pEntity);
	pTrans3D->SetLocalPosition(Vector3F(0.0f, 20.0f, 0.0f));
	pEntity->GetComponentMgr()->AddComponent(pTrans3D);

	m_pAnimatedSprite = NEW_AO AnimatedSpriteComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(m_pAnimatedSprite);

	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("Anim_belrick_idle_r"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("Anim_belrick_idle_l"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("Anim_belrick_idle_u"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("Anim_belrick_idle_d"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("Anim_belrick_idle_ur"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("Anim_belrick_idle_dr"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("Anim_belrick_idle_ul"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("Anim_belrick_idle_dl"));

	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_run_r"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_run_l"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_run_u"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_run_d"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_run_ur"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_run_dr"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_run_ul"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_run_dl"));

	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_01_r"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_01_l"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_01_u"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_01_d"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_01_ur"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_01_dr"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_01_ul"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_01_dl"));

	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_02_r"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_02_l"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_02_u"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_02_d"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_02_ur"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_02_dr"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_02_ul"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_02_dl"));

	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_03_r"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_03_l"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_03_u"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_03_d"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_03_ur"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_03_dr"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_03_ul"));
	m_pAnimatedSprite->AddAnimation(GetAssetManager().GetAsset<Animation2D>("anim_belrick_attack_03_dl"));

	m_pAnimatedSprite->SetCurrentAnimation(0); // Anim_belrick_idle_r

// 	Box2DColliderComponent *pBox2D = NEW_AO Box2DColliderComponent(pEntity);
// 	dynamic_cast<Box2D *>(pBox2D->GetShape())->Size(Vector2F(0.5f, 0.5f));
// 	pBox2D->Mass(1.0f);
// 	pEntity->GetComponentMgr()->AddComponent(pBox2D);

	RectangleF box2D;
	box2D.Set(0, 0, 0.5f, 0.5f);
	//RigidBodyComponent *pRigidBodyCpt = NEW_AO RigidBodyComponent(pEntity);
	//RigidBody &body = pRigidBodyCpt->GetRigidBody();
	//body.pCollisionShape = &box2D;
	//body.mass = 1.0f;
	//pEntity->GetComponentMgr()->AddComponent(pRigidBodyCpt);

	//ScriptComponent *pScriptComponent = NEW_AO ScriptComponent(pEntity);
	//pEntity->GetComponentMgr()->AddComponent(pScriptComponent);

	pEntity->Initialize();
	m_pWorld->AddEntity(pEntity);
}

void Scene2DGame::CreateMap(World *pWorld)
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
	auto* layer = new TiledMapLayer();
	std::vector<ITile*> tiles;
	for (int y = 0; y < pMap->GetMapSize().y; ++y)
	{
		for (int x = 0; x < pMap->GetMapSize().x; ++x)
		{
			auto* sprite = GetAssetManager().GetAsset<SpriteData>("grass1");
			auto* tile = new StaticTile(Sprite::CreateFromSpriteData(*sprite));
			tiles.push_back(tile);
		}
	}
	layer->SetTiles(tiles);
	pMap->AddLayer(layer);

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
			auto* tile = new StaticTile(Sprite::CreateFromSpriteData(*sprite));
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
	auto pSprite = new SpriteData();
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

void Scene2DGame::CreateEnnemies(World* pWorld)
{
	IFile* pFile = Game::Instance().GetMediaManager().FindMedia("octopus.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	_ennemi ennemi_datas;
	ar(cereal::make_nvp("octopus", ennemi_datas));

	auto* pEntity = NEW_AO BaseEntity();
	pEntity->SetName("octopus 1");
	auto* pTrans3D = NEW_AO Transform3DComponent(pEntity);
	pTrans3D->SetLocalPosition(Vector3F(100.0f, 100.0f, 1.0f));
	pTrans3D->SetLocalRotation(0.0f);
	//pTrans3D->SetLocalScale(Vector3F(32, 32, 1.0));
	pEntity->GetComponentMgr()->AddComponent(pTrans3D);

	//load texture
	//auto texture = Texture::loadTexture(ennemi_datas.tile_set.c_str());
	//load sprite
	int id = 0;
	for (auto& sprite : ennemi_datas.sprites)
	{
		SpriteData* pSprite = new SpriteData();
		std::ostringstream name;
		name << "octopus_" << sprite.id;
		id++;
		pSprite->SetName(name.str());
		pSprite->SetPositionInTexture(RectangleI(sprite.x, sprite.y, sprite.w, sprite.h));
		//pSprite->SetTexture2D(texture);
		pSprite->SetAssetFileName(ennemi_datas.tile_set.c_str());
		GetAssetManager().AddAsset(new Asset(name.str(), pSprite));
	}
	
	auto pAnimatedComponent = NEW_AO AnimatedSpriteComponent(pEntity);
	//load anim
	for (auto& anim : ennemi_datas.animations)
	{
		Animation2D* pAnim = new Animation2D();
		pAnim->SetType(Animation2DType::Loop);
		pAnim->SetName(anim.name);
		int i = 0;
		const auto frame_delay = 0.64f;

		for (auto& frame : anim.frames)
		{
			SetFrameEvent* pFrameEvent = new SetFrameEvent();
			std::ostringstream spriteName;
			spriteName << "octopus_" << frame.sprite_id;
			pFrameEvent->FrameID(spriteName.str().c_str());
			pFrameEvent->Time(frame_delay * i);
			pAnim->AddEvent(pFrameEvent);
			i++;
		}
		auto* end_event = new AnimationEndEvent();
		end_event->Time(anim.frames.size() * frame_delay);
		pAnim->AddEvent(end_event);

		GetAssetManager().AddAsset(new Asset(pAnim->GetName(), pAnim));
		pAnimatedComponent->AddAnimation(pAnim->Copy());
	}
	
	pEntity->GetComponentMgr()->AddComponent(pAnimatedComponent);
	//pAnimatedComponent->SetCurrentAnimation(0);

	auto scriptComponent = new ScriptComponent(pEntity);
	auto* pScriptCharacter = new ScriptCharacter(pEntity, new Enemy(pEntity));
	scriptComponent->SetScriptObject(pScriptCharacter);	
	pEntity->GetComponentMgr()->AddComponent(scriptComponent);

	pWorld->AddEntity(pEntity);	
}

void Scene2DGame::CreateSwordman(World* pWorld)
{
	//player
	const auto tileWidth = 48, tileHeight = 48;
	auto* pPlayerEntity = NEW_AO BaseEntity();
	pPlayerEntity->SetName("player 1");
	auto* pTrans3D = NEW_AO Transform3DComponent(pPlayerEntity);
	pTrans3D->SetLocalPosition(Vector3F(50.0f, 50.0f, 1.0f));
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
		auto pSprite = new SpriteData();
		std::ostringstream name;
		name << "player_" << sprite.id;
		id++;
		pSprite->SetName(name.str());
		pSprite->SetPositionInTexture(RectangleI(sprite.x, sprite.y, sprite.w, sprite.h));
		//pSprite->SetTexture2D(texture);
		pSprite->SetAssetFileName(player_datas.tile_set.c_str());
		GetAssetManager().AddAsset(new Asset(name.str(), pSprite));
	}

	//load anim
	auto pAnimatedComponent = NEW_AO AnimatedSpriteComponent(pPlayerEntity);
	for (auto& anim : player_datas.animations)
	{
		Animation2D* pAnim = new Animation2D();
		pAnim->SetType(Animation2DType::Loop);
		pAnim->SetName(anim.name);
		int i = 0;
		const auto frame_delay = 0.64f;

		for (auto& frame : anim.frames)
		{
			SetFrameEvent* pFrameEvent = new SetFrameEvent();
			std::ostringstream spriteName;
			spriteName << "player_" << frame.sprite_id;
			pFrameEvent->FrameID(spriteName.str().c_str());
			pFrameEvent->Time(frame_delay * i);
			pAnim->AddEvent(pFrameEvent);
			i++;
		}
		auto* end_event = new AnimationEndEvent();
		end_event->Time(anim.frames.size() * frame_delay);
		pAnim->AddEvent(end_event);

		GetAssetManager().AddAsset(new Asset(pAnim->GetName(), pAnim));
		pAnimatedComponent->AddAnimation(pAnim->Copy());
	}

	pPlayerEntity->GetComponentMgr()->AddComponent(pAnimatedComponent);
	//pAnimatedComponent->SetCurrentAnimation("stand_down");
	pWorld->AddEntity(pPlayerEntity);

	auto scriptComponent = new ScriptComponent(pPlayerEntity);
	auto* pScriptCharacter = new ScriptCharacter(pPlayerEntity, new Hero(pPlayerEntity));
	scriptComponent->SetScriptObject(pScriptCharacter);
	pPlayerEntity->GetComponentMgr()->AddComponent(scriptComponent);

	//Camera 2D
	BaseEntity* pCamera = NEW_AO BaseEntity();
	pCamera->SetName("camera 2D");
	Camera2DComponent* m_pCamera2D = NEW_AO Camera2DComponent(pCamera);
	auto custom_camera_controller = new Camera2DTargetedController(m_pCamera2D);
	m_pCamera2D->CameraController(custom_camera_controller);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera2D);
	custom_camera_controller->SetDeadZoneRatio(Vector2F(0.7f, 0.7f));
	custom_camera_controller->SetTargetedEntity(pPlayerEntity);
	custom_camera_controller->SetLimits(RectangleI(0, 0, 1500, 800));
	pWorld->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCamera2D);
}
