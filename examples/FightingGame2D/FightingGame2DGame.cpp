#include <iosfwd>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

#include "FightingGame2DGame.h"

#include "Animations/Animation2D.h"
#include "Assets/AssetManager.h"

#include "Entities/Components/AnimatedSpriteComponent.h"
#include "Entities/Components/CameraControllers/ArcBallCameraController.h"
#include "Entities/Components/CameraControllers/Camera2DController.h"
#include "Entities/Components/GridComponent.h"
#include "Entities/Components/StaticSpriteComponent.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "Game/Input.h"
#include "GameTime.h"

#include "Log/LoggerFile.h"
#include "Maths/Vector3.h"
#include "Memory/MemoryAllocation.h"
#include "Parsers/Xml/tinyxml2.h"
#include "Physics/PhysicsEngine.h"
#include "Sprite/SpriteTypes.h"
#include <IO/File.h>
#include "../../external/dear-imgui/imgui.h"
#include "Entities/Components/Camera2DComponent.h"
#include "Entities/Components/CameraControllers/Camera2DTargetedController.h"

using namespace CasaEngine;

FightingGame2DGame::FightingGame2DGame() :
	m_pWorld(nullptr)
{
	Logging.AddLogger(NEW_AO LoggerFile("Out.log"));
}

FightingGame2DGame::~FightingGame2DGame()
{
	
}

void FightingGame2DGame::Initialize()
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

	//GetDebugOptions().IsDebugActivated = true;
	//GetDebugOptions().ShowLogInGame = true;
}

void FightingGame2DGame::AddGameComponent()
{
	auto line3DRenderer = NEW_AO Line3DRendererComponent(this);
	auto pSpriteRenderer = NEW_AO SpriteRenderer(this);

	AddComponent(pSpriteRenderer);
	AddComponent(line3DRenderer);
}

void FightingGame2DGame::LoadContent()
{
	Game::LoadContent();
	LoadSprites();
	auto animations = LoadAnimations();

	m_pWorld = NEW_AO World();
	GetGameInfo().SetWorld(m_pWorld);

	//player 1
	auto pEntity = NEW_AO BaseEntity();
	pEntity->SetName("player 1");
	auto pTransform = NEW_AO Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3F(520, 400));
	auto scale = 1.0f;
	pTransform->SetLocalScale(Vector3F(scale, scale));
	pEntity->GetComponentMgr()->AddComponent(pTransform);

	auto pAnimatedSprite = NEW_AO AnimatedSpriteComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pAnimatedSprite);
	for (auto& anim : animations)
	{
		pAnimatedSprite->AddAnimation(NEW_AO Animation2D(*anim.Copy()));
	}
	pAnimatedSprite->SetCurrentAnimation(1);
	pAnimatedSprite->SetSpriteEffect(eSpriteEffects::SPRITE_EFFECT_NONE);
	m_pWorld->AddEntity(pEntity);

	//player 2
	auto pPlayer2 = NEW_AO BaseEntity();
	pPlayer2->SetName("player 2");
	pTransform = NEW_AO Transform3DComponent(pPlayer2);
	pTransform->SetLocalPosition(Vector3F(820, 400));
	scale = 1.0f;
	pTransform->SetLocalScale(Vector3F(scale, scale));
	pPlayer2->GetComponentMgr()->AddComponent(pTransform);

	pAnimatedSprite = NEW_AO AnimatedSpriteComponent(pPlayer2);
	pPlayer2->GetComponentMgr()->AddComponent(pAnimatedSprite);
	for (auto& anim : animations)
	{
		pAnimatedSprite->AddAnimation(NEW_AO Animation2D(*anim.Copy()));
	}
	pAnimatedSprite->SetCurrentAnimation(1);
	pAnimatedSprite->SetSpriteEffect(eSpriteEffects::SPRITE_EFFECT_FLIP_HORIZONTALLY);
	m_pWorld->AddEntity(pPlayer2);

	//Camera 2D
	BaseEntity* pCamera = NEW_AO BaseEntity();
	pCamera->SetName("camera 2D");
	Camera2DComponent* m_pCamera2D = NEW_AO Camera2DComponent(pCamera);
	auto camera_controller = new Camera2DTargetedController(m_pCamera2D);
	m_pCamera2D->CameraController(camera_controller);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera2D);
	camera_controller->SetDeadZoneRatio(Vector2F(0.7f, 0.7f));
	camera_controller->SetTargetedEntity(pEntity);
	camera_controller->SetLimits(RectangleI(0, 0, 1500, 800));
	m_pWorld->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCamera2D);

	m_pWorld->Initialize();
}

std::vector<Animation2DData> FightingGame2DGame::LoadAnimations()
{
	auto pFile = GetMediaManager().FindMedia("animations.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	std::vector<Animation2DData> anim2DDatas;
	ar(cereal::make_nvp("animations", anim2DDatas));

	for (auto& data : anim2DDatas)
	{
		auto* animation = data.Copy();
		GetAssetManager().AddAsset(NEW_AO Asset(data.GetName(), animation));
	}

	return anim2DDatas;
}

void FightingGame2DGame::LoadSprites()
{
	auto pFile = GetMediaManager().FindMedia("sprites.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	std::vector<SpriteData> spriteDatas;
	ar(cereal::make_nvp("sprites", spriteDatas));

	for (auto& data : spriteDatas)
	{
		GetAssetManager().AddAsset(NEW_AO Asset(data.GetName(), data.Copy()));
	}
}

void FightingGame2DGame::Update(const GameTime& gameTime_)
{
	Game::Update(gameTime_);

	DisplayCollisions();
	DisplayPositions();
}

void FightingGame2DGame::DisplayCollisions()
{
	DisplayCollision(m_pWorld->GetEntityByName("player 1"));
	DisplayCollision(m_pWorld->GetEntityByName("player 2"));
}

void FightingGame2DGame::DisplayCollision(BaseEntity* pEntity)
{
	auto* const anim = pEntity->GetComponentMgr()->GetComponent<AnimatedSpriteComponent>()->GetCurrentAnimation();
	if (anim != nullptr)
	{
		//anim->GetName()
		if (GetAssetManager().Contains(anim->CurrentFrame()))
		{
			auto* spriteData = GetAssetManager().GetAsset<SpriteData>(anim->CurrentFrame());
			auto* line3DRenderer = this->GetGameComponent<Line3DRendererComponent>();
			auto* const transform = pEntity->GetComponentMgr()->GetComponent<Transform3DComponent>();

			for (const auto& coll : spriteData->GetCollisions())
			{
				if (coll.GetShape()->Type() == ShapeType::RECTANGLE)
				{
					auto* rect = dynamic_cast<RectangleI*>(coll.GetShape());
					auto color = coll.GetType() == CollisionType::Defense ? CColor::Blue : CColor::Red;
					auto pos = transform->GetLocalPosition();
					const auto scaleX = transform->GetLocalScale().x;
					const auto scaleY = transform->GetLocalScale().y;
					auto rectScaled = RectangleI(rect->x * scaleX, rect->y * scaleY, rect->w * scaleX, rect->h * scaleY);

					auto leftTop = Vector3F(rectScaled.Left(), rectScaled.Top()) + pos;
					auto leftBottom = Vector3F(rectScaled.Left(), rectScaled.Bottom()) + pos;
					auto rightTop = Vector3F(rectScaled.Right(), rectScaled.Top()) + pos;
					auto rightBottom = Vector3F(rectScaled.Right(), rectScaled.Bottom()) + pos;

					line3DRenderer->AddLine(leftTop, rightTop, color);
					line3DRenderer->AddLine(leftBottom, rightBottom, color);
					line3DRenderer->AddLine(leftTop, leftBottom, color);
					line3DRenderer->AddLine(rightTop, rightBottom, color);
				}
			}
		}
	}
}

void FightingGame2DGame::DisplayPositions()
{
	DisplayPosition(m_pWorld->GetEntityByName("player 1"));
	DisplayPosition(m_pWorld->GetEntityByName("player 2"));
}

void FightingGame2DGame::DisplayPosition(BaseEntity *pEntity)
{
	auto line3DRenderer = this->GetGameComponent<Line3DRendererComponent>();
	auto position = pEntity->GetComponentMgr()->GetComponent<Transform3DComponent>()->GetLocalPosition();
	auto color = CColor::Green;
	auto size = 50 / 2.0f;

	line3DRenderer->AddLine(Vector3F(position.x + size, position.y), Vector3F(position.x - size, position.y), color);
	line3DRenderer->AddLine(Vector3F(position.x, position.y + size), Vector3F(position.x, position.y - size), color);
}

void FightingGame2DGame::DisplayUI()
{
	/*
	ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	if (ImGui::Begin("Animation Player"))
	{
		ImGui::BeginChild("Animation List", ImVec2(0, 0));

		ImGui::EndChild();

		ImGui::End();
	}*/
}

void FightingGame2DGame::DisplayGrid()
{
	/*
	auto halfNumberOfLines = 100 >> 1;
	auto cellWidth = 10.0f;
	auto halfLength = halfNumberOfLines * cellWidth;
	auto gridColor = CColor::DimGray;

	auto line3DRenderer = this->GetGameComponent<Line3DRendererComponent>();
	for (int i = 0; i <= halfNumberOfLines; i++)
	{
		auto coord = cellWidth * i;
		line3DRenderer->AddLine(Vector3F(-halfLength, -coord), Vector3F(halfLength, -coord), gridColor);
		line3DRenderer->AddLine(Vector3F(-halfLength, coord), Vector3F(halfLength, coord), gridColor);

		line3DRenderer->AddLine(Vector3F(-coord, -halfLength), Vector3F(-coord, halfLength), gridColor);
		line3DRenderer->AddLine(Vector3F(coord, -halfLength), Vector3F(coord, halfLength), gridColor);
	}
	*/
}

void FightingGame2DGame::Draw()
{
	Game::Draw();

	DisplayUI();
}