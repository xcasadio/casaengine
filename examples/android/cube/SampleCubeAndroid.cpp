#include "SampleCubeAndroid.h"
#include "Log/LogManager.h"
#include "EngineInfo.h"
#include "Entities/BaseEntity.h"
#include "Entities/Components/Camera3DComponent.h"
#include "Entities/Components/CameraControllers/ArcBallCameraController.h"
#include "Entities/Components/Model3DComponent.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Entities/EntityManager.h"
#include "Game/GameInfo.h"
#include "Game/Line3DRendererComponent.h"
#include "Game/ModelRendererGameComponent.h"
#include "Graphics/Model/Model.h"
#include "Graphics/Primitives/BoxPrimitive.h"
#include "Maths/Math.h"
#include "Maths/Vector2.h"
#include "Maths/Vector3.h"
#include "Tools/DebugSystem.h"
#include <Game/GameTime.h>
#include <Graphics/Renderer/Renderer.h>
#include <Maths/Vector4.h>
#include "Game/Line2DRendererComponent.h"
#include "Entities/Components/Transform2DComponent.h"
#include "Entities/Components/GridComponent.h"
#include "Entities/DebugTools/FPSMonitoringComponent.h"

#include <vector>
#include <iosfwd>
#include <string>


using namespace CasaEngine;


SampleCubeAndroid::SampleCubeAndroid() :
		m_pModelRenderer(NULL),
		m_pEntity(NULL),
		m_pWorld(NULL)
{
}

SampleCubeAndroid::~SampleCubeAndroid()
{
	/*if (m_pModelRenderer != NULL)
	{
		delete m_pModelRenderer;
	}

	if (m_pEntity != NULL)
	{
		delete m_pEntity;
	}*/

	if (m_pWorld != NULL)
	{
		delete m_pWorld;
	}

	EntityManager::Instance().Clear();
}


/////////////////////////////////////////////////////////////
/// Effectue les initialisations
///
////////////////////////////////////////////////////////////
void SampleCubeAndroid::Initialize()
{
	AddComponent(NEW_AO InputManagerComponent(this));
	AddComponent(NEW_AO Line2DRendererComponent(this));
	AddComponent(NEW_AO Line3DRendererComponent(this));

	m_pModelRenderer = NEW_AO ModelRendererGameComponent(this);
	AddComponent(m_pModelRenderer);

	DebugSystem *pDebugSystem = NEW_AO DebugSystem(this);
	AddComponent(pDebugSystem);

	// Ajout des chemins prédéfinis
	MediaManager::Instance().AddSearchPath("");
	//MediaManager::Instance().AddSearchPath("assets");

	m_pWorld = NEW_AO World();
	GameInfo::Instance().SetWorld(m_pWorld);
	
	//Box
	m_pEntity = NEW_AO BaseEntity();
	Transform2DComponent *pTransform = NEW_AO Transform2DComponent(m_pEntity);
	pTransform->SetLocalPosition(Vector2F::Zero());
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector2F::One());
	m_pEntity->GetComponentMgr()->AddComponent(pTransform);
	Model3DComponent *pModelCpt = NEW_AO Model3DComponent(m_pEntity);
	BoxPrimitive *pBox = NEW_AO BoxPrimitive();
	Model *pModel = pBox->CreateModel();
	pModelCpt->SetModel(pModel);
	IEffect *pEffect = IRenderer::Get().CreateEffectFromFile("simple");
	pModelCpt->SetEffect(pEffect);

	m_pEntity->GetComponentMgr()->AddComponent(pModelCpt);
	EntityMgr.RegisterEntity(m_pEntity);
	m_pEntity->Initialize();
	
	m_pWorld->AddEntity(m_pEntity);

	//camera
	m_pCamera = NEW_AO BaseEntity();
	Camera3DComponent *pCamera3DComponent = NEW_AO Camera3DComponent(m_pCamera);
	ArcBallCameraController *pArcBall = NEW_AO ArcBallCameraController(pCamera3DComponent);
	pArcBall->SetCamera(Vector3F(0, 20.0f, -50.0f), Vector3F::Zero(), Vector3F::Up());
	pArcBall->Distance(7.0f);
	pCamera3DComponent->FOV(MATH_PI_DIV_2);
	pCamera3DComponent->CameraController(pArcBall);
	m_pCamera->GetComponentMgr()->AddComponent(pCamera3DComponent);
	EntityMgr.RegisterEntity(m_pCamera);
	m_pCamera->Initialize();

	m_pWorld->AddEntity(m_pCamera);

	//Grid
	BaseEntity *pEntity = NEW_AO BaseEntity();
	GridComponent *pGridComponent = NEW_AO GridComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pGridComponent);
	EntityMgr.RegisterEntity(pEntity);
	pEntity->Initialize();

	m_pWorld->AddEntity(pEntity);

	//FPS
	/*pEntity = new BaseEntity();
	Transform2DComponent *pTrans2D = new Transform2DComponent(pEntity);
	pTrans2D->SetLocalPosition(Vector2F(10.0f, 10.0f));
	pEntity->GetComponentMgr()->AddComponent(pTrans2D);
	FPSMonitoringComponent *pFPS = new FPSMonitoringComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pFPS);
	pEntity->Initialize();
	pDebugSystem->AddObserver(pEntity);

	m_pWorld->AddEntity(pEntity);*/

	GameInfo::Instance().SetActiveCamera(pCamera3DComponent);
	Game::Initialize();
}

/////////////////////////////////////////////////////////////
/// 
///
////////////////////////////////////////////////////////////
void SampleCubeAndroid::LoadContent()
{
	Game::LoadContent();
}


/////////////////////////////////////////////////////////////
/// Effectue la mise à jour de la scène
///
////////////////////////////////////////////////////////////
void SampleCubeAndroid::Update(const GameTime& gameTime_)
{
	Game::Update(gameTime_);
}


/////////////////////////////////////////////////////////////
/// Effectue le rendu de la scène
///
////////////////////////////////////////////////////////////
void SampleCubeAndroid::Draw()
{
	IRenderer::Get().Clear(RenderParameter::Color | RenderParameter::ZBuffer | RenderParameter::Stencil);
	Game::Draw();
}

