#include "ShaderGame.h"
#include "MD2Loader.h"

#include "Entities/Components/Cameras/ArcBallCameraComponent.h"
#include "Entities/Components/MeshComponent.h"
#include "Game/GameInfo.h"
#include "Game/Line2DRendererComponent.h"
#include "Game/Line3DRendererComponent.h"
#include "GameTime.h"
#include "Graphics/Mesh/Mesh.h"
#include "Graphics/Primitives/BoxPrimitive.h"
#include "Log/LoggerFile.h"
#include "Maths/Math.h"
#include "Maths/Quaternion.h"
#include "UI/ImGuiAdapter.h"

using namespace CasaEngine;

ShaderGame::ShaderGame() :
	_world(nullptr)
{
	Logging.AddLogger(new LoggerFile("Out.log"));
}

void ShaderGame::Initialize()
{
	GetMediaManager().AddSearchPath("../../examples/resources");
	GetMediaManager().AddSearchPath("../../examples/resources/textures");
	GetMediaManager().AddSearchPath("../../examples/resources/models");
	GetMediaManager().AddSearchPath("../../examples/resources/shaders");
	GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
	GetMediaManager().AddSearchPath("../../examples/resources/fonts");

	AddDebugComponents();
	AddUsualComponents();

	_lightDirection.Set(1.0f, 0.0f, 0.5f);
	_lightDirection.Normalize();
	//Game::Instance().GetMediaManager().RegisterLoader(new CMD2Loader, "md2");

	// Enregistrement des commandes console
	//
	// Les commandes principales sont :
	// --------------------------------
	//
	// > vsparam1 Name x : affecte le flottant x au paramètre ayant le nom Name dans le vertex shader courant
	// > psparam1 Name x : pareil, pour le pixel shader courant
	// > vsparam2 Name x y : affecte le couple de flottants (x, y) au paramètre ayant le nom Name dans le vertex shader courant
	// > psparam2 Name x y : pareil, pour le pixel shader courant
	// > vsparam3 Name x y z : affecte le tripler de flottants (x, y, z) au paramètre ayant le nom Name dans le vertex shader courant
	// > psparam3 Name x y z : pareil, pour le pixel shader courant
	// > shaders Name : Charge les shaders correspondant à l'effet Name ("Name.vcg" et "Name.pcg")
	// > load File : Charge le modèle nommé File.md2 du répertoire "Modèles"
	//
	// Exemple de séquence valide :
	// ----------------------------
	//
	// > load alien
	// > shaders cartoon
	// > psparam3 color 0.5 0.1 0.5
	// > shaders scale
	// > vsparam1 scale 3
	// > load soldier
	// > exit
	//
	// Ici, les casts sont nécessaires pour lever les ambiguïtés dûes aux surcharges
	typedef void (Shader::* T1)(const std::string&, float);
	typedef void (Shader::* T2)(const std::string&, const Vector2&);
	typedef void (Shader::* T3)(const std::string&, const Vector3&);
	//     Console::Instance().RegisterCommand("vsparam1", Bind(static_cast<T1>(&Shader::SetParameter), m_VertexShader));
	//     Console::Instance().RegisterCommand("psparam1", Bind(static_cast<T1>(&Shader::SetParameter), m_VertexShader));
	//     Console::Instance().RegisterCommand("vsparam2", Bind(static_cast<T2>(&Shader::SetParameter), m_VertexShader));
	//     Console::Instance().RegisterCommand("psparam2", Bind(static_cast<T2>(&Shader::SetParameter), m_VertexShader));
	//     Console::Instance().RegisterCommand("vsparam3", Bind(static_cast<T3>(&Shader::SetParameter), m_VertexShader));
	//     Console::Instance().RegisterCommand("psparam3", Bind(static_cast<T3>(&Shader::SetParameter), m_VertexShader));
	//     Console::Instance().RegisterCommand("shaders",  Bind(&ShaderGame::ChangeShaders,          *this));
	//     Console::Instance().RegisterCommand("load",     Bind(&ShaderGame::LoadModel,              *this));
	//     Console::Instance().RegisterCommand("exit",     Bind(&ShaderGame::Exit,                   *this));

		// Initialisation des descriptions de shaders
	m_ShadersDesc["none"] = "No shader loaded";
	m_ShadersDesc["simple"] = "Display standard model";
	m_ShadersDesc["cartoon"] = "Effect \"cartoon rendering\"";
	m_ShadersDesc["scale"] = "Effect \"lighting by vertex + modify scale\"";
	m_ShadersDesc["negative"] = "Effect \"negative\"";
	m_ShadersDesc["grey"] = "Effect \"grey scale\"";


	Game::Initialize();
}

void ShaderGame::CreateGround()
{
	auto* entity = new BaseEntity();
	entity->SetName("ground");
	entity->GetCoordinates().SetLocalPosition(Vector3(0.0f, -0.5f, 0.0f));
	entity->GetCoordinates().SetLocalRotation(0.0f);
	entity->GetCoordinates().SetLocalScale(Vector3::One());
	auto* meshComponent = new MeshComponent(entity);
	auto* box = new BoxPrimitive(100.0f, 1.0f, 100.0f);
	Mesh* mesh = box->CreateMesh();
	//new material
	_groundMaterial = mesh->GetMaterial()->Clone();
	_groundMaterial->Texture0(Texture::loadTexture(Instance().GetMediaManager().FindMedia("ceilingMain_DIF.dds"), BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC));
	_groundMaterial->Texture0Repeat(Vector2(50, 50));
	mesh->SetMaterial(_groundMaterial);
	//
	meshComponent->SetModel(mesh);
	meshComponent->SetProgram(_program);

	entity->GetComponentMgr()->AddComponent(meshComponent);

	_world->AddEntity(entity);
}

void ShaderGame::CreateCamera()
{
	auto* cameraEntity = new BaseEntity();
	auto* arcBallCamera = new ArcBallCameraComponent(cameraEntity);
	arcBallCamera->SetCamera(Vector3(0, 25.0f, -80.0f), Vector3(0.0f, 1.9f, 0.0f), Vector3::Up());
	arcBallCamera->Distance(7.0f);
	cameraEntity->GetComponentMgr()->AddComponent(arcBallCamera);

	GetGameInfo().SetActiveCamera(arcBallCamera);
}

void ShaderGame::CreateMesh()
{
	_entity = new BaseEntity();
	_entity->SetName("model");
	_entity->GetCoordinates().SetLocalPosition(Vector3(0.0f, -5.0f, 0.0f));
	_entity->GetCoordinates().SetLocalRotation(0.0f);
	_entity->GetCoordinates().SetLocalScale(Vector3::One());
	auto* meshComponent = new MeshComponent(_entity);

	CMD2Loader loader;
	IFile* file = GetMediaManager().FindMedia("Goblin.md2", (unsigned int)FileMode::READ | (unsigned int)FileMode::BINARY);
	_mesh = loader.LoadFromFile(file);
	//
	meshComponent->SetModel(_mesh);
	meshComponent->SetProgram(_program);

	_entity->GetComponentMgr()->AddComponent(meshComponent);

	_world->AddEntity(_entity);
}

void ShaderGame::LoadContent()
{
	Game::LoadContent();

	_world = new World();
	GetGameInfo().SetWorld(_world);

	//m_CartoonShadingTextureHandle = CreateFromFile("cartoon_shading.dds", PixelFormat::AL_88, TEX_NOMIPMAP);
	//m_pCartoonShading = Texture::loadTexture(Instance().GetMediaManager().FindMedia("cartoon_shading.dds", true), BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC, 1);

	_program = new Program("vs_mesh", "fs_mesh");

	CreateGround();
	CreateCamera();
	CreateMesh();

	_world->Initialize();
}

void ShaderGame::Update(const GameTime& gameTime_)
{
	Game::Update(gameTime_);

	Quaternion q1, q2;
	q1.FromAxisAngle(Vector3::UnitX(), -Math::PI_OVER_2);
	q2.FromAxisAngle(Vector3::UnitZ(), gameTime_.TotalTime() * 0.1f * Math::Pi);

	_entity->GetCoordinates().SetLocalPosition(Vector3(0.0f, 2.4f, 0.0f));
	_entity->GetCoordinates().SetLocalRotation(q1 * q2);
	_entity->GetCoordinates().SetLocalScale(Vector3(0.1f, 0.1f, 0.1f));

	//UpdateShadersParams(gameTime_);
}

void ShaderGame::Draw()
{
	Game::Draw();


}

void ShaderGame::ChangeShaders(const std::string& Type)
{
	//     if (m_ShadersDesc.find(Type) == m_ShadersDesc.end())
	//         throw Exception("Type de shader inconnu");
	//
	//     if (Type == "none")
	//     {
	//         m_pEffect = nullptr;
	//         m_VertexShader.Unload();
	//         //m_PixelShader.Unload();
	//     }
	//     else
	//     {
	// 		m_pEffect = IRenderer::Get().CreateEffectFromFile(Type);
	//
	// 		//m_VertexShader.LoadFromFile(Type);
	//
	//         //m_VertexShader.LoadFromFile(Type + ".vcg");
	//         //m_PixelShader.LoadFromFile(Type + ".pcg");
	//     }
	//
	//     // Mise à jour du message d'aide
	//     m_Help.Text = m_ShadersDesc[Type];
	//     m_Help.Align(ALIGN_BOTTOM, CRectangle(5, 5, 635, 475));
	//
	//     m_ShadersType = Type;
	//
	//     SetShadersDefaults();
}

void ShaderGame::UpdateShadersParams(const GameTime& gameTime_)
{
	//     Matrix4 ModelView = _matRotation * Game::Instance().GetGameInfo().GetActiveCamera()->GetViewMatrix();
	//     Matrix4 ModelViewProj = ModelView * Game::Instance().GetGameInfo().GetActiveCamera()->GetProjectionMatrix();
	//
	//     if (m_ShadersType == "cartoon")
	//     {
	//         m_VertexShader.SetParameter("ModelViewProj", ModelViewProj);
	//         m_VertexShader.SetParameter("ModelView",     ModelView);
	//         m_VertexShader.SetParameter("LightDir",      _lightDirection);
	//         m_VertexShader.SetParameter("CameraPos",     Game::Instance().GetGameInfo().GetActiveCamera()->GetViewMatrix().GetTranslation());
	//     }
	//     else if (m_ShadersType == "scale")
	//     {
	//         m_VertexShader.SetParameter("ModelViewProj", ModelViewProj);
	//         m_VertexShader.SetParameter("ModelView",     ModelView);
	//         m_VertexShader.SetParameter("LightDir",      _lightDirection);
	//     }
	//     else if (m_ShadersType == "simple")
	//     {
	//         m_VertexShader.SetParameter("ModelViewProj", ModelViewProj);
	//     }
	//     else if (m_ShadersType == "negative")
	//     {
	//         m_VertexShader.SetParameter("ModelViewProj", ModelViewProj);
	// 		m_VertexShader.SetParameter("Factor", std::cos(gameTime_.TotalTime()) * 0.5f + 0.5f);
	//         //m_PixelShader.SetParameter("Factor",         cosf(GetTickCount() / 1000.0f) * 0.5f + 0.5f);
	//     }
	//     else if (m_ShadersType == "grey")
	//     {
	//         m_VertexShader.SetParameter("ModelViewProj", ModelViewProj);
	//     }
}

void ShaderGame::SetShadersDefaults()
{
	//     if (m_ShadersType == "cartoon")
	//     {
	//         //m_PixelShader.SetParameter("color", Color::White);
	// 		m_VertexShader.SetParameter("color", Color::White);
	//     }
	//     else if (m_ShadersType == "scale")
	//     {
	//         m_VertexShader.SetParameter("scale", 1.5f);
	//     }
}

void ShaderGame::LoadModel(const char* Filename)
{
	static CMD2Loader loader;

	IFile* pFile = Instance().GetMediaManager().FindMedia((std::string(Filename) + ".md2").c_str(), (unsigned int)FileMode::READ | (unsigned int)FileMode::BINARY);
	_mesh = loader.LoadFromFile(pFile);
}