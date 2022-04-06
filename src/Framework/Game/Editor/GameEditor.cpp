#include "Base.h"
#include "GameEditor.h"
#include "Game/Game.h"

#include "Entities/BaseEntity.h"
#include "Entities/Components/Camera3DComponent.h"
#include "Entities/Components/CameraControllers/ArcBallCameraController.h"
#include "World/World.h"
#include "Game/GameInfo.h"
#include "Maths/Vector3.h"
#include "Entities/Components/GridComponent.h"
#include "Log/LoggerFile.h"


namespace CasaEngine
{
	GameEditor::GameEditor(sf::WindowHandle handle_) :
		Game(handle_)
	{
		Logging.AddLogger(new LoggerFile("Out.log"));
	}

	GameEditor::~GameEditor()
	{
		delete m_pLineRenderer;
		delete m_SpriteRenderer;
	}

	void GameEditor::Initialize()
	{
		m_pLineRenderer = new Line3DRendererComponent(this);
		AddComponent(m_pLineRenderer);
		m_SpriteRenderer = new SpriteRenderer(this);
		AddComponent(m_SpriteRenderer);

		m_pWorld = new World();
		Game::Instance().GetGameInfo().SetWorld(m_pWorld);

		// Ajout des chemins prédéfinis
		Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources");
		Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/textures");
		Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/models");
		Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/shaders");
		Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
		Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/fonts");

		//Grid
		BaseEntity *pEntity = new BaseEntity();
		GridComponent *pGridComponent = new GridComponent(pEntity);
		pEntity->GetComponentMgr()->AddComponent(pGridComponent);
		pEntity->Initialize();
	
		m_pWorld->AddEntity(pEntity);

		Game::Initialize();
	}

	void GameEditor::LoadContent()
	{
		Game::LoadContent();

		//Camera 3D
		BaseEntity *pCamera = new BaseEntity();
		Camera3DComponent *m_pCamera3D = new Camera3DComponent(pCamera);
		ArcBallCameraController *pArcBall = new ArcBallCameraController(m_pCamera3D);
		pArcBall->SetCamera(Vector3F(0, 10.0f, -50.0f), Vector3F::Zero(), Vector3F::Up());
		pArcBall->Distance(7.0f);
		m_pCamera3D->CameraController(pArcBall);
		pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);	
		pCamera->Initialize();
		Game::Instance().GetGameInfo().GetWorld()->AddEntity(pCamera);

		Game::Instance().GetGameInfo().SetActiveCamera(m_pCamera3D);
	}
}
