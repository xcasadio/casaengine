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
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	GameEditor::GameEditor(sf::WindowHandle handle_) :
		Game(handle_)
	{
		Logging.AddLogger(NEW_AO LoggerFile("Out.log"));
	}

	GameEditor::~GameEditor()
	{
		if (nullptr != m_pLineRenderer) DELETE_AO m_pLineRenderer;
		if (nullptr != m_SpriteRenderer) DELETE_AO m_SpriteRenderer;
	}

	void GameEditor::Initialize()
	{
		m_pLineRenderer = NEW_AO Line3DRendererComponent(this);
		AddComponent(m_pLineRenderer);
		m_SpriteRenderer = NEW_AO SpriteRenderer(this);
		AddComponent(m_SpriteRenderer);

		m_pWorld = NEW_AO World();
		Game::Instance().GetGameInfo().SetWorld(m_pWorld);

		// Ajout des chemins prédéfinis
		Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources");
		Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/textures");
		Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/models");
		Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/shaders");
		Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
		Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/fonts");

		//Grid
		BaseEntity *pEntity = NEW_AO BaseEntity();
		GridComponent *pGridComponent = NEW_AO GridComponent(pEntity);
		pEntity->GetComponentMgr()->AddComponent(pGridComponent);
		pEntity->Initialize();
	
		m_pWorld->AddEntity(pEntity);

		Game::Initialize();
	}

	void GameEditor::LoadContent()
	{
		Game::LoadContent();

		//Camera 3D
		BaseEntity *pCamera = NEW_AO BaseEntity();
		Camera3DComponent *m_pCamera3D = NEW_AO Camera3DComponent(pCamera);
		ArcBallCameraController *pArcBall = NEW_AO ArcBallCameraController(m_pCamera3D);
		pArcBall->SetCamera(Vector3F(0, 10.0f, -50.0f), Vector3F::Zero(), Vector3F::Up());
		pArcBall->Distance(7.0f);
		m_pCamera3D->CameraController(pArcBall);
		pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);	
		pCamera->Initialize();
		Game::Instance().GetGameInfo().GetWorld()->AddEntity(pCamera);

		Game::Instance().GetGameInfo().SetActiveCamera(m_pCamera3D);
	}

	void GameEditor::Update( const GameTime& gameTime_)
	{
		Game::Update(gameTime_);
	}

	void GameEditor::Draw()
	{
		Game::Draw();
	}

}
