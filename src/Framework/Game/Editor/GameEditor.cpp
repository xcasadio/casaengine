#include "Base.h"
#include "GameEditor.h"
#include "Game/Game.h"

#include "Entities/BaseEntity.h"
#include "Entities/Components/Cameras/Camera3DComponent.h"
#include "Entities/Components/Cameras/ArcBallCameraComponent.h"
#include "World/World.h"
#include "Game/GameInfo.h"
#include "Maths/Vector3.h"
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
		//m_pLineRenderer = new Line3DRendererComponent(this);
		//AddComponent(m_pLineRenderer);
		//m_SpriteRenderer = new SpriteRenderer(this);
		//AddComponent(m_SpriteRenderer);

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
		//BaseEntity *pEntity = new BaseEntity();
		//GridComponent *pGridComponent = new GridComponent(pEntity);
		//pEntity->GetComponentMgr()->AddComponent(pGridComponent);
		//pEntity->Initialize();
	
		//m_pWorld->AddEntity(pEntity);

		Game::Initialize();
	}

	void GameEditor::LoadContent()
	{
		Game::LoadContent();

		//Camera 3D
		BaseEntity *pCamera = new BaseEntity();
		ArcBallCameraComponent *m_pCamera3D = new ArcBallCameraComponent(pCamera);
		m_pCamera3D->SetCamera(Vector3(0, 10.0f, -50.0f), Vector3::Zero(), Vector3::Up());
		m_pCamera3D->Distance(7.0f);
		pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);	
		pCamera->Initialize();
		Game::Instance().GetGameInfo().GetWorld()->AddEntity(pCamera);

		Game::Instance().GetGameInfo().SetActiveCamera(m_pCamera3D);
	}
}
