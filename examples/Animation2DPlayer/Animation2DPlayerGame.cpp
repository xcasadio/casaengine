#include <string>
#include <iosfwd>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

#include "Animation2DPlayerGame.h"

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
#include <IO/File.h>
#include <save_load_types.h>
#include "../../external/dear-imgui/imgui.h"
#include "Entities/Components/Camera2DComponent.h"
#include "Entities/Components/CameraControllers/Camera2DTargetedController.h"

using namespace CasaEngine;

Animation2DPlayerGame::Animation2DPlayerGame() :
	m_pSpriteRenderer(nullptr),
	m_pAnimatedSprite(nullptr),
	m_pWorld(nullptr),
	m_AnimationIndexSelected(0),
	m_LastAnimationIndexSelected(0),
	m_FrameIndexSelected(0),
	m_LastFrameIndexSelected(0)
{
	Logging.AddLogger(NEW_AO LoggerFile("Out.log"));
}

Animation2DPlayerGame::~Animation2DPlayerGame()
{
	DELETE_AO m_pSpriteRenderer;
}

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

	//GetDebugOptions().IsDebugActivated = true;
	//GetDebugOptions().ShowLogInGame = true;
}

void Animation2DPlayerGame::LoadContent()
{
	Game::LoadContent();

	m_pWorld = NEW_AO World();
	GetGameInfo().SetWorld(m_pWorld);

	//Entity
	auto pEntity = NEW_AO BaseEntity();
	m_pEntity = pEntity;
	auto pTransform = NEW_AO Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3F(520, 400));
	auto scale = 1.0f;
	pTransform->SetLocalScale(Vector3F(scale, scale));
	pEntity->GetComponentMgr()->AddComponent(pTransform);

	m_pAnimatedSprite = NEW_AO AnimatedSpriteComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(m_pAnimatedSprite);
	LoadSprites();
	LoadAnimations(m_pAnimatedSprite);
	m_pAnimatedSprite->SetCurrentAnimation(1);
	m_pWorld->AddEntity(pEntity);

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

	//Camera 3D
	/*BaseEntity* pCamera = NEW_AO BaseEntity();
	Camera3DComponent* m_pCamera3D = NEW_AO Camera3DComponent(pCamera);
	ArcBallCameraController* pArcBall = NEW_AO ArcBallCameraController(m_pCamera3D);
	//TODO : why we need to have -Up in order to have the sprite oriented well
	pArcBall->SetCamera(Vector3F(0, 0.0f, -10.0f), Vector3F::Zero(), -Vector3F::Up());
	pArcBall->Distance(15.0f);
	m_pCamera3D->CameraController(pArcBall);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);
	m_pWorld->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCamera3D);*/

	m_pWorld->Initialize();
}

void Animation2DPlayerGame::LoadAnimations(AnimatedSpriteComponent* pAnimatedComponent)
{
	auto pFile = GetMediaManager().FindMedia("ryu_animations.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	animations animations;
	ar(cereal::make_nvp("animations", animations));

	std::vector<Animation2DData> anims;

	for (auto animation : animations.animations)
	{
		auto animation2D = NEW_AO Animation2DData();
		std::ostringstream number;
		number << animation.Number;
		animation2D->SetName(number.str());
		animation2D->SetAnimationType(AnimationType::Loop);
		float time = 0.0f;

		for (auto frame : animation.Frames)
		{
			if (GetAssetManager().Contains(frame.SpriteId))
			{
				auto sprite = GetAssetManager().GetAsset<SpriteData>(frame.SpriteId);
				for (auto& coll : frame.Collisions)
				{
					auto collision = NEW_AO Collision();
					collision->SetType(coll.ClsnType == 1 ? CollisionType::Attack : CollisionType::Defense);
					auto rect = NEW_AO RectangleI(coll.X, coll.Y, coll.Width, coll.Height);
					collision->SetShape(rect);
					sprite->GetCollisions().push_back(*collision);
				}
			}

			auto frameData = NEW_AO FrameData();
			frameData->SetSpriteId(frame.SpriteId.c_str());
			frameData->SetDuration(frame.GameTick * 0.16f); // 0.048f;
			animation2D->AddFrame(*frameData);
		}

		GetAssetManager().AddAsset(new Asset(animation2D->GetName(), animation2D));
		pAnimatedComponent->AddAnimation(NEW_AO Animation2D(*animation2D));

		anims.push_back(*animation2D);
	}

	std::ofstream os("C:\\Users\\casad\\dev\\repo\\casaengine\\examples\\resources\\datas\\animations.json");
	cereal::JSONOutputArchive ar2(os);
	ar2(cereal::make_nvp("animations", anims));


	auto spriteDatasPtr = GetAssetManager().GetAssets<SpriteData>();
	std::vector<SpriteData> spriteDatas;
	spriteDatas.resize(spriteDatasPtr.size());
	std::transform(spriteDatasPtr.begin(), spriteDatasPtr.end(), spriteDatas.begin(), [](SpriteData* x) { return *x; });
	std::ofstream spritesStream("C:\\Users\\casad\\dev\\repo\\casaengine\\examples\\resources\\datas\\sprites.json");
	cereal::JSONOutputArchive arSprites(spritesStream);
	arSprites(cereal::make_nvp("sprites", spriteDatas));
}

void Animation2DPlayerGame::LoadSprites()
{
	auto pFile = GetMediaManager().FindMedia("ryu_sprites.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	sprites sprites;
	ar(cereal::make_nvp("sprites", sprites));

	std::vector<SpriteData> spriteDatas;

	for (auto sprite : sprites.sprites)
	{
		auto spriteData = NEW_AO SpriteData();
		spriteData->SetOrigin(Vector2I(sprite.X, sprite.Y));
		spriteData->SetPositionInTexture(RectangleI(sprite.posInTextureX, sprite.posInTextureY, sprite.SpriteSizeX, sprite.SpriteSizeY));
		spriteData->SetAssetFileName("ryu.png"); // TODO : read from file
		spriteData->SetName(sprite.Id);
		GetAssetManager().AddAsset(new Asset(sprite.Id, spriteData));

		spriteDatas.push_back(*spriteData);
	}
}

void Animation2DPlayerGame::Update(const GameTime& gameTime_)
{
	Game::Update(gameTime_);

	//if (Game::Instance().GetInput().IsKeyJustDown(sf::Keyboard::Space))
	if (m_LastAnimationIndexSelected != m_AnimationIndexSelected)
	{
		m_pAnimatedSprite->SetCurrentAnimation(m_AnimationIndexSelected);
		m_LastAnimationIndexSelected = m_AnimationIndexSelected;
	}

	//DisplayGrid();
	DisplayCollisions();
	DisplayPosition();
}

void Animation2DPlayerGame::DisplayCollisions()
{
	auto anim = m_pAnimatedSprite->GetCurrentAnimation();
	if (anim != nullptr)
	{
		//anim->GetName()
		if (GetAssetManager().Contains(anim->CurrentFrame()))
		{
			auto spriteData = GetAssetManager().GetAsset<SpriteData>(anim->CurrentFrame());
			auto line3DRenderer = this->GetGameComponent<Line3DRendererComponent>();
			auto transform = m_pEntity->GetComponentMgr()->GetComponent<Transform3DComponent>();

			for (auto coll : spriteData->GetCollisions())
			{
				if (coll.GetShape()->Type() == ShapeType::RECTANGLE)
				{
					auto rect = dynamic_cast<RectangleI*>(coll.GetShape());
					auto color = coll.GetType() == CollisionType::Defense ? CColor::Blue : CColor::Red;
					auto pos = transform->GetLocalPosition();
					auto scaleX = transform->GetLocalScale().x;
					auto scaleY = transform->GetLocalScale().y;
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

void Animation2DPlayerGame::DisplayPosition()
{
	auto line3DRenderer = this->GetGameComponent<Line3DRendererComponent>();
	auto position = m_pEntity->GetComponentMgr()->GetComponent<Transform3DComponent>()->GetLocalPosition();
	auto color = CColor::Green;
	auto size = 500 / 2.0f;

	line3DRenderer->AddLine(Vector3F(position.x + size, position.y), Vector3F(position.x - size, position.y), color);
	line3DRenderer->AddLine(Vector3F(position.x, position.y + size), Vector3F(position.x, position.y - size), color);
}

void Animation2DPlayerGame::DisplayUI()
{
	ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	if (ImGui::Begin("Animation Player"))
	{
		ImGui::BeginChild("Animation List", ImVec2(0, 0));

		ImGui::Button("Play");
		ImGui::Button("Stop");

		const char** items = new const char* [m_pAnimatedSprite->GetAnimations().size()];
		int index = 0;
		std::vector<const char*> names;
		for (auto anim : m_pAnimatedSprite->GetAnimations())
		{
			std::string str = anim->GetAnimationData()->GetName();
			char* writable = new char[str.size() + 1];
			std::copy(str.begin(), str.end(), writable);
			writable[str.size()] = '\0';
			names.push_back(writable);
		}
		ImGui::Combo("Animations", &m_AnimationIndexSelected, &names[0], m_pAnimatedSprite->GetAnimations().size()/*IM_ARRAYSIZE(items)*/);

		/*auto frames = m_pAnimatedSprite->GetCurrentAnimation();
		GetAssetManager().GetAsset<>(frames->CurrentFrame())

		for (auto anim : m_pAnimatedSprite->GetAnimations())
		{
			std::string str = anim->GetName();
			char* writable = new char[str.size() + 1];
			std::copy(str.begin(), str.end(), writable);
			writable[str.size()] = '\0';
			names.push_back(writable);
		}*/
		ImGui::Combo("Frames", &m_AnimationIndexSelected, new const char* [] { "test" }, 1);

		std::vector<const char*> collisionNames;
		auto frames = m_pAnimatedSprite->GetCurrentAnimation();
		auto spriteData = GetAssetManager().GetAsset<SpriteData>(frames->CurrentFrame());
		int i = 0;
		for (auto collision : spriteData->GetCollisions())
		{
			auto rect = dynamic_cast<RectangleI*>(collision.GetShape());
			std::ostringstream ostr;
			ostr << rect->x << " " << rect->y << " " << rect->w << " " << rect->h;
			std::string str = ostr.str();
			char* writable = new char[str.size() + 1];
			std::copy(str.begin(), str.end(), writable);
			writable[str.size()] = '\0';
			collisionNames.push_back(writable);
		}
		ImGui::Combo("Collisions", &m_CollisionIndexSelected, &collisionNames[0], spriteData->GetCollisions().size());

		ImGui::Button("+");
		ImGui::Button("-");

		ImGui::ArrowButton("left", ImGuiDir_::ImGuiDir_Left);
		ImGui::ArrowButton("right", ImGuiDir_::ImGuiDir_Right);
		ImGui::ArrowButton("up", ImGuiDir_::ImGuiDir_Up);
		ImGui::ArrowButton("down", ImGuiDir_::ImGuiDir_Down);

		ImGui::Button("Save");

		ImGui::EndChild();

		ImGui::End();
	}
}

void Animation2DPlayerGame::DisplayGrid()
{
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
	/*
	line3DRenderer->AddLine(Vector3F::Zero(), CColor::Red, Vector3F::UnitX(), CColor::Red);
	line3DRenderer->AddLine(Vector3F::Zero(), CColor::Green, Vector3F::UnitY(), CColor::Green);
	line3DRenderer->AddLine(Vector3F::Zero(), CColor::Blue, Vector3F::UnitZ(), CColor::Blue);
	*/
}

void Animation2DPlayerGame::Draw()
{
	Game::Draw();

	DisplayUI();
}

void Animation2DPlayerGame::AddGameComponent()
{
	auto line3DRenderer = NEW_AO Line3DRendererComponent(this);
	m_pSpriteRenderer = NEW_AO SpriteRenderer(this);

	AddComponent(m_pSpriteRenderer);
	AddComponent(line3DRenderer);
}