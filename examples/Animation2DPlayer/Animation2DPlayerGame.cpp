#include <string>
#include <iosfwd>

#include "Animation2DPlayerGame.h"

#include "Animations/Animation2D.h"
#include "Assets/AssetManager.h"

#include "Entities/Components/AnimatedSpriteComponent.h"
#include "Entities/Components/GridComponent.h"
#include "Entities/Components/StaticSpriteComponent.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "GameTime.h"

#include "Log/LoggerFile.h"
#include "Maths/Vector3.h"

#include "Physics/PhysicsEngine.h"
#include <IO/File.h>
#include <save_load_types.h>
#include "../../external/dear-imgui/imgui.h"
#include "Entities/Components/DebugComponent.h"
#include "Entities/Components/Cameras/Camera2DComponent.h"
#include "Entities/Components/Cameras/Camera2DTargetedComponent.h"
#include "Serializer/Serializer.h"

using namespace CasaEngine;

std::vector<std::string> last_animation_names;
std::vector<char*> animation_names;

Animation2DPlayerGame::Animation2DPlayerGame() :
	m_pEntity(nullptr),
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
	pEntity->GetCoordinates().SetLocalPosition(Vector3(520, 400, 0.0f));
	const auto scale = 2.0f;
	pEntity->GetCoordinates().SetLocalScale(Vector3(scale, scale, 0.0f));

	m_pAnimatedSprite = new AnimatedSpriteComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(m_pAnimatedSprite);
	LoadSprites();
	LoadAnimations(m_pAnimatedSprite);
	m_pAnimatedSprite->SetCurrentAnimation(1);

	auto* debugComponent = new DebugComponent(pEntity);
	debugComponent->DisplayAnimation2DCollisions(true);
	debugComponent->DisplayPosition(true);
	pEntity->GetComponentMgr()->AddComponent(debugComponent);

	m_pWorld->AddEntity(pEntity);

	//Camera 2D
	auto* pCamera = new BaseEntity();
	pCamera->SetName("camera 2D");
	auto* m_pCamera2D = new Camera2DTargetedComponent(pCamera);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera2D);
	m_pCamera2D->SetDeadZoneRatio(Vector2(0.7f, 0.7f));
	m_pCamera2D->SetTargetedEntity(pEntity);
	m_pCamera2D->SetLimits(CasaEngine::Rectangle(0, 0, 1500, 800));
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
					auto* rect = new Rectangle(coll.X, coll.Y, coll.Width, coll.Height);
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
	std::vector<Animation2DData> anim2DDatas;
	json j;
	is >> j;
	from_json(j["animations"], anim2DDatas);
	
	for (auto& data : anim2DDatas)
	{
		auto* animation = data.Copy();
		GetAssetManager().AddAsset(new Asset(data.GetName(), animation));
		pAnimatedComponent->AddAnimation(new Animation2D(*animation));
	}

	//std::ofstream os("C:\\Users\\casad\\dev\\repo\\casaengine\\examples\\resources\\datas\\animations_cop.json");
	//json j2;
	//to_json(j2, anim2DDatas, "animations");
	//os << std::setw(4) << j2 << std::endl; // pretty json
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
		spriteData->SetPositionInTexture(Rectangle(sprite.posInTextureX, sprite.posInTextureY, sprite.SpriteSizeX, sprite.SpriteSizeY));
		spriteData->SetAssetFileName("ryu.png"); // TODO : read from file
		spriteData->SetName(sprite.Id);
		GetAssetManager().AddAsset(new Asset(sprite.Id, spriteData));

		spriteDatas.push_back(*spriteData);
	}
	*/

	auto* const pFile = GetMediaManager().FindMedia("sprites.json", true);
	std::ifstream is(pFile->Fullname());
	std::vector<SpriteData> spriteDatas;
	json j;
	is >> j;
	from_json(j["sprites"], spriteDatas);

	for (auto& data : spriteDatas)
	{/*
		std::vector<Collision> collisions;

		for (auto& coll : data.GetCollisions())
		{
			auto* rectangle = dynamic_cast<Rectangle *>(coll.GetShape());
			rectangle->x += data.GetOrigin().x;
			rectangle->y += data.GetOrigin().y;
			collisions.push_back(coll);
		}

		data.GetCollisions().clear();

		for (auto& coll : collisions)
		{
			data.GetCollisions().push_back(coll);
		}
		*/
		GetAssetManager().AddAsset(new Asset(data.GetName(), data.Copy()));
	}

	//std::ofstream os("C:\\Users\\casad\\dev\\repo\\casaengine\\examples\\resources\\datas\\sprites_cop.json");
	//json j2;
	//to_json(j2, spriteDatas, "sprites");
	//os << std::setw(4) << j2 << std::endl; // pretty json
}

void Animation2DPlayerGame::Update(const GameTime& gameTime_)
{
	//if (Game::Instance().GetInput().IsKeyJustDown(sf::Keyboard::Space))
	if (m_LastAnimationIndexSelected != m_AnimationIndexSelected)
	{
		m_pAnimatedSprite->SetCurrentAnimation(animation_names[m_AnimationIndexSelected]);
		m_LastAnimationIndexSelected = m_AnimationIndexSelected;
	}

	m_FrameIndexSelected = m_pAnimatedSprite->GetCurrentFrameIndex();

	if (!m_pEntity->IsEnabled())
	{
		m_pEntity->IsEnabled(true);
		m_pEntity->Update(GameTime());
		m_pEntity->IsEnabled(false);
	}

	Game::Update(gameTime_);
}

void Animation2DPlayerGame::RenameAnimation(const char* old_name, const char* new_name)
{
	GetAssetManager().Rename(old_name, new_name);
	copy_animations_name();
}

void Animation2DPlayerGame::DisplayUI()
{
#if EDITOR
	ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_FirstUseEver);
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

		std::ostringstream oss;
		oss << "time (total :" << m_pAnimatedSprite->GetCurrentAnimation()->TotalTime() << " ms)";
		ImGui::SliderFloat(oss.str().c_str(),
			m_pAnimatedSprite->GetCurrentAnimation()->CurrentTimePtr(),
			0.0f,
			m_pAnimatedSprite->GetCurrentAnimation()->TotalTime(), "%.3f", ImGuiSliderFlags_AlwaysClamp);

		ImGui::Separator();

		auto local_scale = m_pEntity->GetCoordinates().GetLocalScale();

		ImGui::Text("Zoom x%d", (int)m_pEntity->GetCoordinates().GetLocalScale().x);
		ImGui::SameLine();

		if (ImGui::Button("+"))
		{
			local_scale.x++;
			local_scale.y++;
			m_pEntity->GetCoordinates().SetLocalScale(local_scale);
		}

		ImGui::SameLine();

		if (ImGui::Button("-"))
		{
			local_scale.x = std::max(--local_scale.x, 1.0f);
			local_scale.y = std::max(--local_scale.y, 1.0f);
			m_pEntity->GetCoordinates().SetLocalScale(local_scale);
		}

		ImGui::Separator();

		ImGui::Combo("Animations", &m_AnimationIndexSelected, &animation_names[0], animation_names.size()/*IM_ARRAYSIZE(items)*/);
		ImGui::SameLine();
		auto editing_animation = ImGui::Button("edit");

		//if (editing_animation)
		{
			if (ImGui::BeginPopupContextItem())
			{
				auto* animation_name = animation_names[m_AnimationIndexSelected];
				ImGui::Text("Edit name:");
				ImGui::InputText("##edit", animation_name, std::strlen(animation_name));
				if (ImGui::Button("Close"))
				{
					RenameAnimation(last_animation_names[m_AnimationIndexSelected].c_str(), animation_names[m_AnimationIndexSelected]);
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}

		std::vector<const char*> frameNames;
		for (const auto& frame : m_pAnimatedSprite->GetCurrentAnimation()->GetAnimation2DData()->_frames)
		{
			auto str = frame._spriteId;
			auto* writable = new char[str.size() + 1];
			std::copy(str.begin(), str.end(), writable);
			writable[str.size()] = '\0';
			frameNames.push_back(writable);
		}

		if (ImGui::BeginCombo("Frames"/*"##combo"*/, m_FrameIndexSelected >= 0 ? frameNames[m_FrameIndexSelected] : nullptr))
		{
			for (int n = 0; n < frameNames.size(); n++)
			{
				if (ImGui::Selectable(frameNames[n], m_FrameIndexSelected == n))
				{
					//m_FrameIndexSelected = frameNames[n];
				}

				if (m_FrameIndexSelected == n)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}
		//ImGui::Combo("Frames", m_FrameIndexSelected >= 0 ? &m_FrameIndexSelected : &defaultIndex, &frameNames[0], frameNames.size());

		std::vector<const char*> collisionNames;
		auto* frames = m_pAnimatedSprite->GetCurrentAnimation();
		auto* spriteData = GetAssetManager().GetAsset<SpriteData>(frames->CurrentFrame());
		auto i = 0;
		for (const auto& collision : spriteData->_collisionShapes)
		{
			auto* rect = dynamic_cast<CasaEngine::Rectangle*>(collision.GetShape());
			std::ostringstream ostr;
			ostr << rect->x << " " << rect->y << " " << rect->w << " " << rect->h;
			auto str = ostr.str();
			auto* writable = new char[str.size() + 1];
			std::copy(str.begin(), str.end(), writable);
			writable[str.size()] = '\0';
			collisionNames.push_back(writable);
		}
		if (ImGui::BeginCombo("Collisions"/*"##combo"*/, m_CollisionIndexSelected >= 0 ? collisionNames[m_CollisionIndexSelected] : nullptr))
		{
			for (int n = 0; n < collisionNames.size(); n++)
			{
				if (ImGui::Selectable(collisionNames[n], m_CollisionIndexSelected == n))
				{
					//m_CollisionIndexSelected = n;
				}

				if (m_CollisionIndexSelected == n)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		ImGui::Text("Move collision"); ImGui::SameLine();
		ImGui::ArrowButton("left", ImGuiDir_::ImGuiDir_Left); ImGui::SameLine();
		ImGui::ArrowButton("right", ImGuiDir_::ImGuiDir_Right); ImGui::SameLine();
		ImGui::ArrowButton("up", ImGuiDir_::ImGuiDir_Up); ImGui::SameLine();
		ImGui::ArrowButton("down", ImGuiDir_::ImGuiDir_Down);

		ImGui::Separator();

		if (ImGui::Button("Save"))
		{
			auto animationsPtr = GetAssetManager().GetAssets<Animation2DData>();
			std::vector<Animation2DData> animationsToSave;
			animationsToSave.resize(animationsPtr.size());
			std::transform(animationsPtr.begin(), animationsPtr.end(), animationsToSave.begin(), [](Animation2DData* x) { return *x; });
			std::ofstream os("C:\\Users\\casad\\dev\\repo\\casaengine\\examples\\resources\\datas\\animations2.json");
			//cereal::JSONOutputArchive ar2(os);
			//ar2(cereal::make_nvp("animations", animationsToSave));
			json j;
			to_json(j, animationsToSave, "animations");
			os << std::setw(4) << j << std::endl; // pretty json
		}

		ImGui::EndChild();
	}

	ImGui::End();
#endif
}


void Animation2DPlayerGame::Draw()
{
	DisplayUI();

	Game::Draw();
}