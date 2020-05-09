#include "ShaderGame.h"
#include "MD2Loader.h"

#include "Entities/Components/Camera3DComponent.h"
#include "Entities/Components/CameraControllers/ArcBallCameraController.h"
#include "Entities/Components/CameraControllers/Camera2DController.h"
#include "Entities/Components/GridComponent.h"
#include "Entities/Components/MeshComponent.h"
#include "Entities/Components/Transform2DComponent.h"
#include "Entities/EntityManager.h"
#include "Game/GameInfo.h"
#include "Game/Line2DRendererComponent.h"
#include "Game/Line3DRendererComponent.h"
#include "GameTime.h"
#include "Graphics/Mesh/Mesh.h"
#include "Graphics/Primitives/BoxPrimitive.h"
#include "Graphics/Renderer/Renderer.h"
#include "Log/LoggerFile.h"
#include "Maths/Math.h"
#include "Maths/Quaternion.h"
#include "Maths/Vector4.h"
#include "UI/imguiAdapter.h"

using namespace CasaEngine;

/**
 * 
 */
ShaderGame::ShaderGame() :
	m_pWorld(nullptr)
{
	Logging.AddLogger(NEW_AO LoggerFile("Out.log"));
}

/**
 * 
 */
void ShaderGame::Initialize()
{
	Game::Initialize();

 	m_pLine2DRenderer = NEW_AO Line2DRendererComponent(this);
 	m_pLine3DRenderer = NEW_AO Line3DRendererComponent(this);

	AddComponent(NEW_AO MeshRendererGameComponent(this));
 	AddComponent(m_pLine2DRenderer);
 	AddComponent(m_pLine3DRenderer);

	m_pWorld = NEW_AO World();
	Game::Instance().GetGameInfo().SetWorld(m_pWorld);

    m_LightDir.Set(1.0f, 0.0f, 0.5f);
    m_LightDir.Normalize();

	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/textures");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/models");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/shaders");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/spriteSheet");
	Game::Instance().GetMediaManager().AddSearchPath("../../examples/resources/fonts");
    //Game::Instance().GetMediaManager().RegisterLoader(NEW_AO CMD2Loader, "md2");

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
    typedef void (Shader::*T1)(const std::string&, float);
    typedef void (Shader::*T2)(const std::string&, const Vector2F&);
    typedef void (Shader::*T3)(const std::string&, const Vector3F&);
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
    m_ShadersDesc["none"]     = "No shader loaded";
    m_ShadersDesc["simple"]   = "Display standard model";
    m_ShadersDesc["cartoon"]  = "Effect \"cartoon rendering\"";
    m_ShadersDesc["scale"]    = "Effect \"lighting by vertex + modify scale\"";
    m_ShadersDesc["negative"] = "Effect \"negative\"";
    m_ShadersDesc["grey"]     = "Effect \"grey scale\"";
}

/**
 * 
 */
void ShaderGame::LoadContent()
{
	Game::LoadContent();

	//m_CartoonShadingTextureHandle = CreateFromFile("cartoon_shading.dds", PixelFormat::AL_88, TEX_NOMIPMAP);
	Texture::loadTexture("cartoon_shading.dds", BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC, 1);
	m_pProgram = NEW_AO Program("vs_mesh", "fs_mesh");

	//ground
	m_pEntity = NEW_AO BaseEntity();
	m_pEntity->SetName("ground");
	Transform3DComponent* pTransform = NEW_AO Transform3DComponent(m_pEntity);
	pTransform->SetLocalPosition(Vector3F(0.0f, -0.5f, 0.0f));
	pTransform->SetLocalRotation(0.0f);
	pTransform->SetLocalScale(Vector3F::One());
	m_pEntity->GetComponentMgr()->AddComponent(pTransform);
	MeshComponent* pModelCpt = NEW_AO MeshComponent(m_pEntity);
	BoxPrimitive *pBox = NEW_AO BoxPrimitive(100.0f, 1.0f, 100.0f);
	Mesh* pModel = pBox->CreateModel();
	//new material
	m_pGroundMaterial = pModel->GetMaterial()->Clone();
	m_pGroundMaterial->Texture0(Texture::loadTexture("ceilingMain_DIF.dds", BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC));
	m_pGroundMaterial->Texture0Repeat(Vector2F(50, 50));
	pModel->SetMaterial(m_pGroundMaterial);
	//
	pModelCpt->SetModel(pModel);
	pModelCpt->SetProgram(m_pProgram);

	m_pEntity->GetComponentMgr()->AddComponent(pModelCpt);

	m_pWorld->AddEntity(m_pEntity);

	//Camera 3D
	BaseEntity *pCamera = NEW_AO BaseEntity();
	m_pCamera3D = NEW_AO Camera3DComponent(pCamera);
	ArcBallCameraController *pArcBall = NEW_AO ArcBallCameraController(m_pCamera3D);
	pArcBall->SetCamera(Vector3F(0, 25.0f, -80.0f), Vector3F(0.0f, 1.9f, 0.0f), Vector3F::Up());
	pArcBall->Distance(7.0f);
	m_pCamera3D->CameraController(pArcBall);
	pCamera->GetComponentMgr()->AddComponent(m_pCamera3D);

	m_pWorld->AddEntity(pCamera);
	Game::Instance().GetGameInfo().SetActiveCamera(m_pCamera3D);

	//FPS
	/*BaseEntity *pEntity = NEW_AO BaseEntity();
	pEntity->SetName("FPS Monitoring");
	Transform2DComponent *pTranform2D = NEW_AO Transform2DComponent(pEntity);
	pTranform2D->SetLocalPosition(Vector2F(10.0f, 10.0f));
	pEntity->GetComponentMgr()->AddComponent(pTranform2D);
	FPSMonitoringComponent *pFPS = NEW_AO FPSMonitoringComponent(pEntity);
	pEntity->GetComponentMgr()->AddComponent(pFPS);
	pEntity->Initialize();

	m_pWorld->AddEntity(pEntity);
	pEntity->Initialize();*/

	//Mesh
	m_pModelEntity = NEW_AO BaseEntity();
	m_pModelEntity->SetName("model");
	m_pTrans3D = NEW_AO Transform3DComponent(m_pModelEntity);
	m_pTrans3D->SetLocalPosition(Vector3F(0.0f, -5.0f, 0.0f));
	m_pTrans3D->SetLocalRotation(0.0f);
	m_pTrans3D->SetLocalScale(Vector3F::One());
	m_pModelEntity->GetComponentMgr()->AddComponent(m_pTrans3D);
	pModelCpt = NEW_AO MeshComponent(m_pModelEntity);

	CMD2Loader loader;
	CasaEngine::IFile* pFile = CasaEngine::Game::Instance().GetMediaManager().FindMedia("Goblin.md2", CasaEngine::FileMode::READ | FileMode::BINARY);
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

/**
 * 
 */
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

/**
 * 
 */
void ShaderGame::Draw()
{
	Game::Draw();
}

/**
 * 
 */
void ShaderGame::EndRun()
{
	
}

/**
 * 
 */
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
//     // Mise à jour du message d'aide
//     m_Help.Text = m_ShadersDesc[Type];
//     m_Help.Align(ALIGN_BOTTOM, CRectangle(5, 5, 635, 475));
// 
//     m_ShadersType = Type;
// 
//     SetShadersDefaults();
}

/**
 * 
 */
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

/**
 * 
 */
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

/**
 * 
 */
void ShaderGame::LoadModel(const char *Filename)
{
	static CMD2Loader loader;

	CasaEngine::IFile* pFile = CasaEngine::Game::Instance().GetMediaManager().FindMedia((std::string(Filename) + ".md2").c_str(), CasaEngine::FileMode::READ | FileMode::BINARY);
	m_Player = loader.LoadFromFile(pFile);
}

