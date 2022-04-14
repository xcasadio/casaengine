#include <string>
#include <iosfwd>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

#include "Animation2DPlayerGame.h"

#include "Animations/Animation2D.h"
#include "Assets/AssetManager.h"

#include "Entities/Components/AnimatedSpriteComponent.h"
#include "Entities/Components/GridComponent.h"
#include "Entities/Components/StaticSpriteComponent.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "GameTime.h"

#include "Log/LoggerFile.h"
#include "Maths/Vector3.h"

#include "Physics/PhysicsEngine.h"
#include <IO/File.h>
#include <save_load_types.h>
#include "../../external/dear-imgui/imgui.h"
#include "Entities/Components/Cameras/Camera2DComponent.h"
#include "Entities/Components/Cameras/Camera2DTargetedComponent.h"

using namespace CasaEngine;

std::vector<std::string> last_animation_names;
std::vector<char*> animation_names;

Animation2DPlayerGame::Animation2DPlayerGame() :
	m_pAnimatedSprite(nullptr),
	m_pWorld(nullptr),
	m_AnimationIndexSelected(0),
	m_LastAnimationIndexSelected(0),
	m_FrameIndexSelected(0),
	m_LastFrameIndexSelected(0),
	m_CollisionIndexSelected(0),
	m_LastCollisionIndexSelected(0)
{
	Logging.AddLogger(new LoggerFile("Out.log"));
}

Animation2DPlayerGame::~Animation2DPlayerGame()
{
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

	AddDebugComponents();
	AddUsualComponents();

	Game::Initialize();

	//GetDebugOptions().IsDebugActivated = true;
	//GetDebugOptions().ShowLogInGame = true;
}

void Animation2DPlayerGame::copy_animations_name()
{
	last_animation_names.resize(animation_names.size());
	std::copy(animation_names.begin(), animation_names.end(), last_animation_names.begin());
}

void Animation2DPlayerGame::LoadContent()
{
	Game::LoadContent();

	m_pWorld = new World();
	GetGameInfo().SetWorld(m_pWorld);

	//Entity
	auto* pEntity = new BaseEntity();
	m_pEntity = pEntity;
	auto* pTransform = new Transform3DComponent(pEntity);
	pTransform->SetLocalPosition(Vector3(520, 400, 1.0f));
	const auto scale = 1.0f;
	pTransform->SetLocalScale(Vector3(scale, scale, 0.0f));
	pEntity->GetComponentMgr()->AddComponent(pTransform);

	m_pAnimatedSprite = new AnimatedSpriteComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(m_pAnimatedSprite);
	LoadSprites();
	LoadAnimations(m_pAnimatedSprite);
	m_pAnimatedSprite->SetCurrentAnimation(1);
	m_pWorld->AddEntity(pEntity);

	//Camera 2D
	auto* pCamera = new BaseEntity();
	pCamera->SetName("camera 2D");
	auto* m_pCamera2D = new Camera2DTargetedComponent(pCamera);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera2D);
	m_pCamera2D->SetDeadZoneRatio(Vector2(0.7f, 0.7f));
	m_pCamera2D->SetTargetedEntity(pEntity);
	m_pCamera2D->SetLimits(RectangleI(0, 0, 1500, 800));
	m_pWorld->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCamera2D);

	//Camera 3D
	/*BaseEntity* pCamera = new BaseEntity();
	Camera3DComponent* m_pCamera3D = new Camera3DComponent(pCamera);
	ArcBallCameraComponent* pArcBall = new ArcBallCameraComponent(m_pCamera3D);
	//TODO : why we need to have -Up in order to have the sprite oriented well
	pArcBall->SetCamera(Vector3(0, 0.0f, -10.0f), Vector3::Zero(), -Vector3::Up());
	pArcBall->Distance(15.0f);
	m_pCamera3D->CameraController(pArcBall);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);
	m_pWorld->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCamera3D);*/

	m_pWorld->Initialize();

	auto animation_datas = GetAssetManager().GetAssets<AnimationData>();

	for (auto* anim : animation_datas)
	{
		auto str = anim->GetName();
		auto* writable = new char[str.size() + 1];
		std::copy(str.begin(), str.end(), writable);
		writable[str.size()] = '\0';
		animation_names.push_back(writable);
	}

	copy_animations_name();
}

void Animation2DPlayerGame::LoadAnimations(AnimatedSpriteComponent* pAnimatedComponent)
{
	/*
	auto* pFile = GetMediaManager().FindMedia("ryu_animations.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	animations animations;
	ar(cereal::make_nvp("animations", animations));

	std::vector<Animation2DData> anims;

	for (auto animation : animations.animations)
	{
		auto* animation2D = new Animation2DData();
		std::ostringstream number;
		number << animation.Number;
		animation2D->SetName(number.str());
		animation2D->SetAnimationType(AnimationType::Loop);

		for (auto frame : animation.Frames)
		{
			if (GetAssetManager().Contains(frame.SpriteId))
			{
				auto* sprite = GetAssetManager().GetAsset<SpriteData>(frame.SpriteId);
				for (auto& coll : frame.Collisions)
				{
					auto* collision = new Collision();
					collision->SetType(coll.ClsnType == 1 ? CollisionType::Attack : CollisionType::Defense);
					auto* rect = new RectangleI(coll.X, coll.Y, coll.Width, coll.Height);
					collision->SetShape(rect);
					sprite->GetCollisions().push_back(*collision);
				}
			}

			auto* frameData = new FrameData();
			frameData->SetSpriteId(frame.SpriteId.c_str());
			frameData->SetDuration(frame.GameTick * 0.16f); // 0.048f;
			animation2D->AddFrame(*frameData);
		}

		GetAssetManager().AddAsset(new Asset(animation2D->GetName(), animation2D));
		pAnimatedComponent->AddAnimation(new Animation2D(*animation2D));

		anims.push_back(*animation2D);
	}
	*/
	
	//save sprites and animations
	/*
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
	*/

	auto* const pFile = GetMediaManager().FindMedia("animations.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	std::vector<Animation2DData> anim2DDatas;
	ar(cereal::make_nvp("animations", anim2DDatas));

	for (auto& data : anim2DDatas)
	{
		auto* animation = data.Copy();
		GetAssetManager().AddAsset(new Asset(data.GetName(), animation));
		pAnimatedComponent->AddAnimation(new Animation2D(*animation));
	}
}

void Animation2DPlayerGame::LoadSprites()
{
	/*
	auto* pFile = GetMediaManager().FindMedia("ryu_sprites.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	sprites sprites;
	ar(cereal::make_nvp("sprites", sprites));

	std::vector<SpriteData> spriteDatas;

	for (auto sprite : sprites.sprites)
	{
		auto* spriteData = new SpriteData();
		spriteData->SetOrigin(Vector2I(sprite.X, sprite.Y));
		spriteData->SetPositionInTexture(RectangleI(sprite.posInTextureX, sprite.posInTextureY, sprite.SpriteSizeX, sprite.SpriteSizeY));
		spriteData->SetAssetFileName("ryu.png"); // TODO : read from file
		spriteData->SetName(sprite.Id);
		GetAssetManager().AddAsset(new Asset(sprite.Id, spriteData));

		spriteDatas.push_back(*spriteData);
	}
	*/

	auto* const pFile = GetMediaManager().FindMedia("sprites.json", true);
	std::ifstream is(pFile->Fullname());
	cereal::JSONInputArchive ar(is);
	std::vector<SpriteData> spriteDatas;
	ar(cereal::make_nvp("sprites", spriteDatas));

	for (auto& data : spriteDatas)
	{
		GetAssetManager().AddAsset(new Asset(data.GetName(), data.Copy()));
	}
}

void Animation2DPlayerGame::Update(const GameTime& gameTime_)
{
	//if (Game::Instance().GetInput().IsKeyJustDown(sf::Keyboard::Space))
	if (m_LastAnimationIndexSelected != m_AnimationIndexSelected)
	{
		m_pAnimatedSprite->SetCurrentAnimation(animation_names[m_AnimationIndexSelected]);
		m_LastAnimationIndexSelected = m_AnimationIndexSelected;
	}

	Game::Update(gameTime_);

	//DisplayGrid();
	DisplayCollisions();
	DisplayPosition();
}

void Animation2DPlayerGame::DisplayCollisions()
{
	auto* anim = m_pAnimatedSprite->GetCurrentAnimation();
	if (anim != nullptr)
	{
		//anim->GetName()
		if (GetAssetManager().Contains(anim->CurrentFrame()))
		{
			auto* spriteData = GetAssetManager().GetAsset<SpriteData>(anim->CurrentFrame());
			auto* line3DRenderer = this->GetGameComponent<Line3DRendererComponent>();
			auto* transform = m_pEntity->GetComponentMgr()->GetComponent<Transform3DComponent>();

			for (auto coll : spriteData->GetCollisions())
			{
				if (coll.GetShape()->Type() == ShapeType::RECTANGLE)
				{
					auto* rect = dynamic_cast<RectangleI*>(coll.GetShape());
					auto color = coll.GetType() == CollisionType::Defense ? Color::Blue : Color::Red;
					auto pos = transform->GetLocalPosition();
					const auto scaleX = transform->GetLocalScale().x;
					const auto scaleY = transform->GetLocalScale().y;
					auto rectScaled = RectangleI(rect->x * scaleX, rect->y * scaleY, rect->w * scaleX, rect->h * scaleY);

					auto leftTop = Vector3(rectScaled.Left(), rectScaled.Top(), 0.0f) + pos;
					auto leftBottom = Vector3(rectScaled.Left(), rectScaled.Bottom(), 0.0f) + pos;
					auto rightTop = Vector3(rectScaled.Right(), rectScaled.Top(), 0.0f) + pos;
					auto rightBottom = Vector3(rectScaled.Right(), rectScaled.Bottom(), 0.0f) + pos;

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
	auto* line3DRenderer = this->GetGameComponent<Line3DRendererComponent>();
	const auto position = m_pEntity->GetComponentMgr()->GetComponent<Transform3DComponent>()->GetLocalPosition();
	const auto color = Color::Green;
	const auto size = 500 / 2.0f;

	line3DRenderer->AddLine(Vector3(position.x + size, position.y, 0.0f), Vector3(position.x - size, position.y, 0.0f), color);
	line3DRenderer->AddLine(Vector3(position.x, position.y + size, 0.0f), Vector3(position.x, position.y - size, 0.0f), color);
}

void Animation2DPlayerGame::RenameAnimation(const char* old_name, const char* new_name)
{
	GetAssetManager().Rename(old_name, new_name);
	copy_animations_name();
}

void Animation2DPlayerGame::DisplayUI()
{
	ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	if (ImGui::Begin("Animation Player"))
	{
		ImGui::BeginChild("Animation List", ImVec2(0, 0));

		if (ImGui::Button("Play"))
		{
			m_pEntity->IsEnabled(true);
		}
		ImGui::SameLine();
		if (ImGui::Button("Stop"))
		{
			m_pEntity->IsEnabled(false);
		}

		ImGui::Combo("Animations", &m_AnimationIndexSelected, &animation_names[0], animation_names.size()/*IM_ARRAYSIZE(items)*/);
		ImGui::SameLine();
		auto editing_animation = ImGui::Button("edit");

		//if (editing_animation)
		{
			if (ImGui::BeginPopupContextItem())
			{
				auto* animation_name = animation_names[m_AnimationIndexSelected];
				ImGui::Text("Edit name:");
				ImGui::InputText("##edit", animation_name, IM_ARRAYSIZE(animation_name));
				if (ImGui::Button("Close"))
				{
					RenameAnimation(last_animation_names[m_AnimationIndexSelected].c_str(), animation_names[m_AnimationIndexSelected]);
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}

		ImGui::Combo("Frames", &m_FrameIndexSelected, new const char* [] { "test" }, 1);

		std::vector<const char*> collisionNames;
		auto* frames = m_pAnimatedSprite->GetCurrentAnimation();
		auto* spriteData = GetAssetManager().GetAsset<SpriteData>(frames->CurrentFrame());
		auto i = 0;
		for (const auto& collision : spriteData->GetCollisions())
		{
			auto* rect = dynamic_cast<RectangleI*>(collision.GetShape());
			std::ostringstream ostr;
			ostr << rect->x << " " << rect->y << " " << rect->w << " " << rect->h;
			auto str = ostr.str();
			auto* writable = new char[str.size() + 1];
			std::copy(str.begin(), str.end(), writable);
			writable[str.size()] = '\0';
			collisionNames.push_back(writable);
		}
		ImGui::Combo("Collisions", &m_CollisionIndexSelected, &collisionNames[0], spriteData->GetCollisions().size());

		ImGui::Button("+");
		ImGui::SameLine();
		ImGui::Button("-");

		ImGui::ArrowButton("left", ImGuiDir_::ImGuiDir_Left); ImGui::SameLine();
		ImGui::ArrowButton("right", ImGuiDir_::ImGuiDir_Right); ImGui::SameLine();
		ImGui::ArrowButton("up", ImGuiDir_::ImGuiDir_Up); ImGui::SameLine();
		ImGui::ArrowButton("down", ImGuiDir_::ImGuiDir_Down);

		if (ImGui::Button("Save"))
		{
			auto animationsPtr = GetAssetManager().GetAssets<Animation2DData>();
			std::vector<Animation2DData> animationsToSave;
			animationsToSave.resize(animationsPtr.size());
			std::transform(animationsPtr.begin(), animationsPtr.end(), animationsToSave.begin(), [](Animation2DData* x) { return *x; });
			std::ofstream os("C:\\Users\\casad\\dev\\repo\\casaengine\\examples\\resources\\datas\\animations.json");
			cereal::JSONOutputArchive ar2(os);
			ar2(cereal::make_nvp("animations", animationsToSave));
		}

		ImGui::EndChild();
	}

	ImGui::End();
}

void Animation2DPlayerGame::DisplayGrid()
{
	const auto halfNumberOfLines = 100 >> 1;
	const auto cellWidth = 10.0f;
	const auto halfLength = halfNumberOfLines * cellWidth;
	const auto gridColor = Color::DimGray;

	auto* line3DRenderer = this->GetGameComponent<Line3DRendererComponent>();
	for (auto i = 0; i <= halfNumberOfLines; i++)
	{
		const auto coord = cellWidth * i;
		line3DRenderer->AddLine(Vector3(-halfLength, -coord, 0.0f), Vector3(halfLength, -coord, 0.0f), gridColor);
		line3DRenderer->AddLine(Vector3(-halfLength, coord, 0.0f), Vector3(halfLength, coord, 0.0f), gridColor);

		line3DRenderer->AddLine(Vector3(-coord, -halfLength, 0.0f), Vector3(-coord, halfLength, 0.0f), gridColor);
		line3DRenderer->AddLine(Vector3(coord, -halfLength, 0.0f), Vector3(coord, halfLength, 0.0f), gridColor);
	}
	/*
	line3DRenderer->AddLine(Vector3::Zero(), Color::Red, Vector3::UnitX(), Color::Red);
	line3DRenderer->AddLine(Vector3::Zero(), Color::Green, Vector3::UnitY(), Color::Green);
	line3DRenderer->AddLine(Vector3::Zero(), Color::Blue, Vector3::UnitZ(), Color::Blue);
	*/
}

void Animation2DPlayerGame::Draw()
{
	Game::Draw();

	DisplayUI();
}