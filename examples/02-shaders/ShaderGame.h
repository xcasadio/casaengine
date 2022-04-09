#ifndef SHADERGAME_H
#define SHADERGAME_H

#include <Graphics/Textures/Texture.h>
#include "GameTime.h"
#include <Game/Game.h>
#include <Maths/Matrix4.h>
#include <map>
#include "World/World.h"

#include "Entities/Components/Cameras/Camera2DComponent.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Entities/Components/Cameras/ArcBallCameraComponent.h"
#include "Entities/Components/Cameras/Camera3DLookAtComponent.h"
#include "Tools/DebugSystem.h"
#include "Game/Line2DRendererComponent.h"
#include "Game/Line3DRendererComponent.h"
#include "Graphics/Effects/Program.h"
#include "Graphics/Materials/Material.h"
#include "Graphics/Mesh/Mesh.h"

using namespace CasaEngine;

class ShaderGame :
	public Game
{
public:
	ShaderGame();

	void Initialize() override;
	void LoadContent() override;
	void Update(const GameTime& gameTime_) override;

	void ChangeShaders(const std::string& Type);
	void UpdateShadersParams(const GameTime& gameTime_);
	void SetShadersDefaults();

	void LoadModel(const char* Filename);

	typedef std::map<std::string, std::string> TDescTable;

private:
	Mesh* m_Player;         ///< Modèle courant
	Matrix4       m_Rotation;       ///< Matrice de rotation
	Vector3F      m_CameraPos;      ///< Position de la caméra
	Vector3F      m_LightDir;       ///< Direction de la lumière
	Texture* m_pCartoonShading; ///< Texture de lookup pour le rendu cartoon
	std::string         m_ShadersType;    ///< Type des shaders actuellement chargés
	TDescTable          m_ShadersDesc;    ///< Table des descriptions de shaders

	Program* m_pProgram;
	Texture* m_pCartoonShadingTextureHandle;

	DebugSystem* m_pDebugSystem;
	Line2DRendererComponent* m_pLine2DRenderer;
	Line3DRendererComponent* m_pLine3DRenderer;

	BaseEntity* m_pEntity; //, *m_pCamera;
	ArcBallCameraComponent* m_pCamera3D;
	BaseEntity* m_pModelEntity;
	Transform3DComponent* m_pTrans3D;
	World* m_pWorld;
	Material* m_pGroundMaterial;
};

#endif