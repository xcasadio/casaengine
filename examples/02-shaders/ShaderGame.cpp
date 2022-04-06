#include "ShaderGame.h"
#include "MD2Loader.h"

#include "Entities/Components/Camera3DComponent.h"
#include "Entities/Components/CameraControllers/ArcBallCameraController.h"
#include "Entities/Components/CameraControllers/Camera2DController.h"
#include "Entities/Components/GridComponent.h"
#include "Entities/Components/MeshComponent.h"
#include "Game/GameInfo.h"
#include "Game/Line2DRendererComponent.h"
#include "Game/Line3DRendererComponent.h"
#include "GameTime.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Graphics/Mesh/Mesh.h"
#include "Graphics/Primitives/BoxPrimitive.h"
#include "Log/LoggerFile.h"
#include "Maths/Math.h"
#include "Maths/Quaternion.h"
#include "UI/imguiAdapter.h"

using namespace CasaEngine;


ShaderGame::ShaderGame() :
	m_pWorld(nullptr)
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

	Game::Initialize();

	m_pLine2DRenderer = new Line2DRendererComponent(this);
	m_pLine3DRenderer = new Line3DRendererComponent(this);

	AddComponent(new MeshRendererGameComponent(this));
	AddComponent(m_pLine2DRenderer);
	AddComponent(m_pLine3DRenderer);

	m_pWorld = new World();
	GetGameInfo().SetWorld(m_pWorld);

	m_LightDir.Set(1.0f, 0.0f, 0.5f);
	m_LightDir.Normalize();
	//Game::Instance().GetMediaManager().RegisterLoader(new CMD2Loader, "md2");

	// Enregistrement des commandes console
	//
	// Les commandes principales sont :
	// --------------------------------
	//
	// > vsparam1 Name x : affecte le flottant x au param�tre ayant le nom Name dans le vertex shader courant
	// > psparam1 Name x : pareil, pour le pixel shader courant
	// > vsparam2 Name x y : affecte le couple de flottants (x, y) au param�tre ayant le nom Name dans le vertex shader courant
	// > psparam2 Name x y : pareil, pour le pixel shader courant
	// > vsparam3 Name x y z : affecte le tripler de flottants (x, y, z) au param�tre ayant le nom Name dans le vertex shader courant
	// > psparam3 Name x y z : pareil, pour le pixel shader courant
	// > shaders Name : Charge les shaders correspondant � l'effet Name ("Name.vcg" et "Name.pcg")
	// > load File : Charge le mod�le nomm� File.md2 du r�pertoire "Mod�les"
	//
	// Exemple de s�quence valide :
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
	// Ici, les casts sont n�cessaires pour lever les ambigu�t�s d�es aux surcharges
	typedef void (Shader::* T1)(const std::string&, float);
	typedef void (Shader::* T2)(const std::string&, const Vector2F&);
	typedef void (Shader::* T3)(const std::string&, const Vector3F&);
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
}

void ShaderGame::LoadContent()
{
	Game::LoadContent();

	//m_CartoonShadingTextureHandle = CreateFromFile("cartoon_shading.dds", PixelFormat::AL_88, TEX_NOMIPMAP);
	Texture::loadTexture(Game::Instance().GetMediaManager().FindMedia("cartoon_shading.dds", true), BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC, 1);
	m_pProgram = new Program("vs_mesh", "fs_mesh");

	//ground
	m_pEntity = new BaseEntity();
	m_pEntity->SetName("ground");
	Transform3DComponent* pTransform = new Transform3DComponent(m_pEntity);
	pTransform->SetLocalPosition(Vector3F(0.0f, -0.5f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
	m_pEntity->GetComponentMgr()->AddComponent(pTransform);
	MeshComponent* pModelCpt = new MeshComponent(m_pEntity);
	BoxPrimitive* pBox = new BoxPrimitive(100.0f, 1.0f, 100.0f);
	Mesh* pModel = pBox->CreateModel();
	//new material
	m_pGroundMaterial = pModel->GetMaterial()->Clone();
	m_pGroundMaterial->Texture0(Texture::loadTexture(Game::Instance().GetMediaManager().FindMedia("ceilingMain_DIF.dds"), BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC));
	m_pGroundMaterial->Texture0Repeat(Vector2F(50, 50));
	pModel->SetMaterial(m_pGroundMaterial);
	//
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);

	m_pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(m_pEntity);

	//Camera 3D
	BaseEntity* pCamera = new BaseEntity();
	m_pCamera3D = new Camera3DComponent(pCamera);
	ArcBallCameraController* pArcBall = new ArcBallCameraController(m_pCamera3D);
	pArcBall->SetCamera(Vector3F(0, 25.0f, -80.0f), Vector3F(0.0f, 1.9f, 0.0f), Vector3F::Up());
	pArcBall->Distance(7.0f);
	m_pCamera3D->CameraController(pArcBall);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);

	m_pWorld->AddEntity(pCamera);
	GetGameInfo().SetActiveCamera(m_pCamera3D);

	//FPS
	/*BaseEntity *pEntity = new BaseEntity();
	pEntity->SetName("FPS Monitoring");
	Transform2DComponent *pTranform2D = new Transform2DComponent(pEntity);
	pTranform2D->SetLocalPosition(Vector2F(10.0f, 10.0f));
	pEntity->GetComponentMgr()->AddComponent(pTranform2D);
	FPSMonitoringComponent *pFPS = new FPSMonitoringComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pFPS);
	pEntity->Initialize();

	m_pWorld->AddEntity(pEntity);
	pEntity->Initialize();*/

	//Mesh
	m_pModelEntity = new BaseEntity();
	m_pModelEntity->SetName("model");
	m_pTrans3D = new Transform3DComponent(m_pModelEntity);
	m_pTrans3D->SetLocalPosition(Vector3F(0.0f, -5.0f, 0.0f));
	m_pTrans3D->SetLocalRotation(0.0f);
	m_pTrans3D->SetLocalScale(Vector3F::One());
	m_pModelEntity->GetComponentMgr()->AddComponent(m_pTrans3D);
	pModelCpt = new MeshComponent(m_pModelEntity);

	CMD2Loader loader;
	IFile* pFile = GetMediaManager().FindMedia("Goblin.md2", (unsigned int)FileMode::READ | (unsigned int)FileMode::BINARY);
	m_Player = loader.LoadFromFile(pFile);
	//
	pModelCpt->SetModel(m_Player);
	pModelCpt->SetProgram(m_pProgram);

	m_pModelEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(m_pModelEntity);

	m_pWorld->Initialize();

	//ChangeShaders("simple");
	//LoadModel("goblin");
}

void ShaderGame::Update(const GameTime& gameTime_)
{
	Game::Update(gameTime_);

	Quaternion q1, q2;
	q1.FromAxisAngle(Vector3F::UnitX(), -MATH_PI_DIV_2);
	q2.FromAxisAngle(Vector3F::UnitZ(), gameTime_.TotalTime() * 0.005f * Pi);

	m_pTrans3D->SetLocalPosition(Vector3F(0.0f, 2.4f, 0.0f));
	m_pTrans3D->SetLocalRotation(q1 * q2);
	m_pTrans3D->SetLocalScale(Vector3F(0.1f, 0.1f, 0.1f));

	//UpdateShadersParams(gameTime_);
}

void ShaderGame::ChangeShaders(const std::string& Type)
{
	//     if (m_ShadersDesc.find(Type) == m_ShadersDesc.end())
	//         throw CException("Type de shader inconnu");
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
	//     // Mise � jour du message d'aide
	//     m_Help.Text = m_ShadersDesc[Type];
	//     m_Help.Align(ALIGN_BOTTOM, CRectangle(5, 5, 635, 475));
	//
	//     m_ShadersType = Type;
	//
	//     SetShadersDefaults();
}

void ShaderGame::UpdateShadersParams(const GameTime& gameTime_)
{
	//     Matrix4 ModelView = m_Rotation * Game::Instance().GetGameInfo().GetActiveCamera()->GetViewMatrix();
	//     Matrix4 ModelViewProj = ModelView * Game::Instance().GetGameInfo().GetActiveCamera()->GetProjectionMatrix();
	//
	//     if (m_ShadersType == "cartoon")
	//     {
	//         m_VertexShader.SetParameter("ModelViewProj", ModelViewProj);
	//         m_VertexShader.SetParameter("ModelView",     ModelView);
	//         m_VertexShader.SetParameter("LightDir",      m_LightDir);
	//         m_VertexShader.SetParameter("CameraPos",     Game::Instance().GetGameInfo().GetActiveCamera()->GetViewMatrix().GetTranslation());
	//     }
	//     else if (m_ShadersType == "scale")
	//     {
	//         m_VertexShader.SetParameter("ModelViewProj", ModelViewProj);
	//         m_VertexShader.SetParameter("ModelView",     ModelView);
	//         m_VertexShader.SetParameter("LightDir",      m_LightDir);
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
	//         //m_PixelShader.SetParameter("color", CColor::White);
	// 		m_VertexShader.SetParameter("color", CColor::White);
	//     }
	//     else if (m_ShadersType == "scale")
	//     {
	//         m_VertexShader.SetParameter("scale", 1.5f);
	//     }
}

void ShaderGame::LoadModel(const char* Filename)
{
	static CMD2Loader loader;

	IFile* pFile = Game::Instance().GetMediaManager().FindMedia((std::string(Filename) + ".md2").c_str(), (unsigned int)FileMode::READ | (unsigned int)FileMode::BINARY);
	m_Player = loader.LoadFromFile(pFile);
}