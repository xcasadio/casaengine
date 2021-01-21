#include <string>
#include <iosfwd>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/details/helpers.hpp>
#include <cereal/types/vector.hpp>

#include "Animation2DPlayerGame.h"

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
#include <IO/File.h>
#include <save_load_types.h>

using namespace CasaEngine;

Animation2DPlayerGame::Animation2DPlayerGame() :
	m_pSpriteRenderer(nullptr),
	m_pAnimatedSprite(nullptr),
	m_pWorld(nullptr)
{
	Logging.AddLogger(NEW_AO LoggerFile("Out.log"));
}

Animation2DPlayerGame::~Animation2DPlayerGame()
{
	DELETE_AO m_pSpriteRenderer;
}

/**
 *
 */
void Animation2DPlayerGame::Initialize()
{
	GetMediaManager().AddSearchPath("../../examples/resources");
	GetMediaManager().AddSearchPath("../../examples/resources/datas");
	GetMediaManager().AddSearchPath("../../examples/resources/textures");
	GetMediaManager().AddSearchPath("../../examples/resources/models");
	GetMediaManager().AddSearchPath("../../examples/resources/shaders");
	GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
	GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet/ryu");
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
void Animation2DPlayerGame::LoadContent()
{
	Game::LoadContent();

	m_pWorld = NEW_AO World();
	GetGameInfo().SetWorld(m_pWorld);
	
	//Entity
	auto pEntity = NEW_AO BaseEntity();
	auto pTransform2D = NEW_AO Transform3DComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pTransform2D);

	m_pAnimatedSprite = NEW_AO AnimatedSpriteComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(m_pAnimatedSprite);	
	LoadSprites();
	LoadAnimations(m_pAnimatedSprite);
	m_pAnimatedSprite->SetCurrentAnimation(1);
	m_pWorld->AddEntity(pEntity);

	//Camera 2D
	/*BaseEntity* pCamera = NEW_AO BaseEntity();
	pCamera->SetName("camera 2D");
	Camera2DComponent* m_pCamera2D = NEW_AO Camera2DComponent(pCamera);
	auto camera_controller = new Camera2DTargetedController(m_pCamera2D);
	m_pCamera2D->CameraController(camera_controller);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera2D);
	//camera_controller->SetDeadZoneRatio(Vector2F(0.7f, 0.7f));
	camera_controller->SetTargetedEntity(pEntity);
	//camera_controller->SetLimits(RectangleI(0, 0, 1500, 800));
	m_pWorld->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCamera2D);*/

	//Camera 3D
	BaseEntity* pCamera = NEW_AO BaseEntity();
	Camera3DComponent* m_pCamera3D = NEW_AO Camera3DComponent(pCamera);
	ArcBallCameraController* pArcBall = NEW_AO ArcBallCameraController(m_pCamera3D);
	pArcBall->SetCamera(Vector3F(0, 0.0f, -10.0f), Vector3F::Zero(), -Vector3F::Up());
	pArcBall->Distance(15.0f);
	m_pCamera3D->CameraController(pArcBall);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);
	m_pWorld->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCamera3D);

	m_pWorld->Initialize();
}

void Animation2DPlayerGame::LoadAnimations(AnimatedSpriteComponent *pAnimatedComponent)
{
	auto pFile = GetMediaManager().FindMedia("animations.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	animations animations;
	ar(cereal::make_nvp("animations", animations));

	for (auto animation : animations.animations)
	{
		auto animation2D = NEW_AO Animation2D();
		std::ostringstream number;
		number << animation.Number;
		animation2D->SetName(number.str());
		float time = 0.0f;

		for (auto frame : animation.Frames)
		{
			auto setFrameEvent = NEW_AO SetFrameEvent();
			setFrameEvent->FrameID(frame.SpriteId.c_str());
			setFrameEvent->Time(time);
			time += frame.GameTick * 0.032f;
			animation2D->AddEvent(setFrameEvent);
		}

		GetAssetManager().AddAsset(new Asset(animation2D->GetName(), animation2D));
		pAnimatedComponent->AddAnimation(animation2D->Copy());
	}
}

void Animation2DPlayerGame::LoadSprites()
{
	auto pFile = GetMediaManager().FindMedia("sprites.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	sprites sprites;
	ar(cereal::make_nvp("sprites", sprites));

	for(auto sprite : sprites.sprites)
	{
		auto spritData = NEW_AO SpriteData();
		spritData->SetOrigin(Vector2I(sprite.X, sprite.Y));
		spritData->SetPositionInTexture(RectangleI(0, 0, sprite.SpriteSizeX, sprite.SpriteSizeY));
		std::ostringstream assetName;
		assetName << sprite.Id << ".png";
		spritData->SetAssetFileName(assetName.str());
		GetAssetManager().AddAsset(new Asset(sprite.Id, spritData));
	}
}

static int i;

/**
 *
 */
void Animation2DPlayerGame::Update(const GameTime& gameTime_)
{
	Game::Update(gameTime_);

	if (Game::Instance().GetInput().IsKeyJustDown(sf::Keyboard::Space))
	{
		i++;
		m_pAnimatedSprite->SetCurrentAnimation(i);
	}

	DisplayGrid();
}

void Animation2DPlayerGame::DisplayGrid()
{
	auto halfNumberOfLines = 10 >> 1;
	auto cellWidth = 1.0f;
	auto halfLength = halfNumberOfLines * cellWidth;
	auto gridColor = CColor::DimGray;

	auto line3DRenderer = this->GetGameComponent<Line3DRendererComponent>();
	for (int i = 0; i <= halfNumberOfLines; i++)
	{
		auto coord = cellWidth * i;
		line3DRenderer->AddLine(Vector3F(-halfLength, -coord), gridColor, Vector3F(halfLength, -coord), gridColor);
		line3DRenderer->AddLine(Vector3F(-halfLength, coord), gridColor, Vector3F(halfLength, coord), gridColor);

		line3DRenderer->AddLine(Vector3F(-coord, -halfLength), gridColor, Vector3F(-coord, halfLength), gridColor);
		line3DRenderer->AddLine(Vector3F(coord, -halfLength), gridColor, Vector3F(coord, halfLength), gridColor);
	}
}

/**
 *
 */
void Animation2DPlayerGame::Draw()
{
	Game::Draw();
}


/**
 *
 */
void Animation2DPlayerGame::AddGameComponent()
{
	auto line3DRenderer = NEW_AO Line3DRendererComponent(this);
	m_pSpriteRenderer = NEW_AO SpriteRenderer(this);

	AddComponent(m_pSpriteRenderer);
	AddComponent(line3DRenderer);
}
