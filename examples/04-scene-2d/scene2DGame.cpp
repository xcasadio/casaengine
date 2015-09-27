#include <string>
#include <iosfwd>

#include "scene2DGame.h"

#include "Animations/Animation2D.h"
#include "Assets/AssetManager.h"
#include "EngineInfo.h"
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
#include "Entities/DebugTools/FPSMonitoringComponent.h"
#include "Entities/EntityManager.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "Game/Input.h"
#include "GameTime.h"


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
	if (m_pModelRenderer != nullptr) DELETE_AO m_pModelRenderer;
	if (m_pSpriteRenderer != nullptr) DELETE_AO m_pSpriteRenderer;
	if (m_pLine2DRenderer != nullptr) DELETE_AO m_pLine2DRenderer;
	if (m_pLine3DRenderer != nullptr) DELETE_AO m_pLine3DRenderer;

	if (m_pGroundTexture != nullptr) DELETE_AO m_pGroundTexture;

	EntityMgr.Clear();

	PhysicsEngine::Destroy();
}

/**
 * 
 */
void Scene2DGame::Initialize()
{
	MediaManager::Instance().AddSearchPath("../../examples/resources");
	MediaManager::Instance().AddSearchPath("../../examples/resources/textures");
	MediaManager::Instance().AddSearchPath("../../examples/resources/models");
	MediaManager::Instance().AddSearchPath("../../examples/resources/shaders");
	MediaManager::Instance().AddSearchPath("../../examples/resources/spriteSheet");
	MediaManager::Instance().AddSearchPath("../../examples/resources/script");
	MediaManager::Instance().AddSearchPath("../../examples/resources/fonts");

	AddGameComponent();

	Game::Initialize();
}

/**
 * 
 */
void Scene2DGame::LoadContent()
{
	Game::LoadContent();

	m_pWorld = NEW_AO World();
	GameInfo::Instance().SetWorld(m_pWorld);
	m_pWorld->SetPhysicsWorld(PhysicsEngine::Instance().CreateWorld());

	LoadAssets();

	CreateEntities();
	CreateBackground();
	CreatePlayer();
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
	//GameInfo::Instance().GetProjectManager().LoadProject("H:\\Developpement\\CasaEngine2D\\Projects\\LostKingdom\\LostKingdom.xml");
	m_pModelRenderer = NEW_AO MeshRendererGameComponent(this);
	m_pLine2DRenderer = NEW_AO Line2DRendererComponent(this);
	m_pLine3DRenderer = NEW_AO Line3DRendererComponent(this);
	m_pSpriteRenderer = NEW_AO SpriteRenderer(this);

	AddComponent(m_pModelRenderer);
	AddComponent(m_pSpriteRenderer);
	AddComponent(m_pLine2DRenderer);
	AddComponent(m_pLine3DRenderer);
}

/**
 * 
 */
void Scene2DGame::LoadAssets()
{
	tinyxml2::XMLDocument *xmlDoc = ::new tinyxml2::XMLDocument();
	tinyxml2::XMLError error = xmlDoc->LoadFile("../../examples/resources/spriteSheet/assets.xml"); // TODO : xmlDoc->Parse()

	const tinyxml2::XMLElement *pElem;

	//load animations
	pElem = xmlDoc->FirstChildElement("Assets")->FirstChildElement("AnimationList")->FirstChildElement("Animation2D");

	while (pElem != nullptr)
	{
		Animation2D *pAnim = NEW_AO Animation2D();
		pAnim->Read(*pElem);
		AssetManager::Instance().AddAsset(NEW_AO Asset(pAnim->GetName(), pAnim));
		pElem = pElem->NextSiblingElement();
	}

	//load sprite
	pElem = xmlDoc->FirstChildElement("Assets")->FirstChildElement("SpriteList")->FirstChildElement("Sprite2D");

	while (pElem != nullptr)
	{
		Sprite *pSprite = NEW_AO Sprite();
		pSprite->Read(*pElem);

		AssetManager::Instance().AddAsset(NEW_AO Asset(pSprite->GetName(), pSprite));
		pElem = pElem->NextSiblingElement();
	}

	delete xmlDoc;
}

/**
 * 
 */
void Scene2DGame::CreateEntities()
{
	//Camera 3D
	BaseEntity *pCamera = NEW_AO BaseEntity();
	m_pCamera3D = NEW_AO Camera3DComponent(pCamera);
	ArcBallCameraController *pArcBall = NEW_AO ArcBallCameraController(m_pCamera3D);
	pArcBall->SetCamera(Vector3F(0, 0.0f, -50.0f), Vector3F::Zero(), Vector3F::Up());
	pArcBall->Distance(7.0f);
	m_pCamera3D->CameraController(pArcBall);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);	
	pCamera->Initialize();
	m_pWorld->AddEntity(pCamera);

	GameInfo::Instance().SetActiveCamera(m_pCamera3D);

	//FPS
	BaseEntity *pEntity = NEW_AO BaseEntity();
	Transform2DComponent *pTrans2D = NEW_AO Transform2DComponent(pEntity);
	pTrans2D->SetLocalPosition(Vector2F(10.0f, 10.0f));
	pEntity->GetComponentMgr()->AddComponent(pTrans2D);
	FPSMonitoringComponent *pFPS = NEW_AO FPSMonitoringComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pFPS);
	pEntity->Initialize();
	m_pWorld->AddEntity(pEntity);

	//Grid
	pEntity = NEW_AO BaseEntity();
	GridComponent *pGridComponent = NEW_AO GridComponent(pEntity);
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
	ResourceManager::Instance().Add("groundModel", pModel);
	DELETE_AO pPrimitive;
	//new material
	Material* pMat = pModel->GetMaterial()->Clone();
	ResourceManager::Instance().Add("groundMaterial", pMat);
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


	m_pWorld->GetPhysicsWorld()->SetGravity(Vector3F::Zero());

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
	ResourceManager::Instance().Add("groundModel", pModel);
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
	BaseEntity *pEntity = NEW_AO BaseEntity();
	Transform3DComponent *pTrans3D = NEW_AO Transform3DComponent(pEntity);
	pTrans3D->SetLocalPosition(Vector3F(0.0f, 20.0f, 0.0f));
	pEntity->GetComponentMgr()->AddComponent(pTrans3D);

	m_pAnimatedSprite = NEW_AO AnimatedSpriteComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(m_pAnimatedSprite);

	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("Anim_belrick_idle_r"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("Anim_belrick_idle_l"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("Anim_belrick_idle_u"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("Anim_belrick_idle_d"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("Anim_belrick_idle_ur"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("Anim_belrick_idle_dr"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("Anim_belrick_idle_ul"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("Anim_belrick_idle_dl"));

	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_run_r"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_run_l"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_run_u"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_run_d"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_run_ur"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_run_dr"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_run_ul"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_run_dl"));

	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_01_r"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_01_l"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_01_u"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_01_d"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_01_ur"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_01_dr"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_01_ul"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_01_dl"));
	
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_02_r"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_02_l"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_02_u"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_02_d"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_02_ur"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_02_dr"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_02_ul"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_02_dl"));
	
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_03_r"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_03_l"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_03_u"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_03_d"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_03_ur"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_03_dr"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_03_ul"));
	m_pAnimatedSprite->AddAnimation(AssetManager::Instance().GetAsset<Animation2D>("anim_belrick_attack_03_dl"));

	m_pAnimatedSprite->SetCurrentAnimation(0); // Anim_belrick_idle_r

// 	Box2DColliderComponent *pBox2D = NEW_AO Box2DColliderComponent(pEntity);
// 	dynamic_cast<Box2D *>(pBox2D->GetShape())->Size(Vector2F(0.5f, 0.5f));
// 	pBox2D->Mass(1.0f);
// 	pEntity->GetComponentMgr()->AddComponent(pBox2D);

	Box2D box2D;
	box2D.Size(Vector2F(0.5f, 0.5f));
	RigidBodyComponent *pRigidBodyCpt = NEW_AO RigidBodyComponent(pEntity);
	RigidBody &body = pRigidBodyCpt->GetRigidBody();
	body.pCollisionShape = &box2D;
	body.mass = 1.0f;
	pEntity->GetComponentMgr()->AddComponent(pRigidBodyCpt);

	ScriptComponent *pScriptComponent = NEW_AO ScriptComponent(pEntity);
	pScriptComponent->SetObjectClassID(0xC299A4EE);
	//pScriptComponent->SetScriptFile("test.lua");
	pEntity->GetComponentMgr()->AddComponent(pScriptComponent);

	pEntity->Initialize();	
	m_pWorld->AddEntity(pEntity);
}


/**
 * 
 */
void Scene2DGame::CreateBackground()
{
	BaseEntity *pEntity = NEW_AO BaseEntity();
	Transform3DComponent *pTrans3D = NEW_AO Transform3DComponent(pEntity);
	pTrans3D->SetLocalPosition(Vector3F(0.0f, 0.0f, -1.0f));
	pEntity->GetComponentMgr()->AddComponent(pTrans3D);

	StaticSpriteComponent *pStaticSprite = NEW_AO StaticSpriteComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pStaticSprite);
	pStaticSprite->SpriteID("1");

	pEntity->Initialize();	
	m_pWorld->AddEntity(pEntity);
}
