#pragma once

#include <Graphics/Textures/Texture.h>
#include "GameTime.h"
#include <Game/Game.h>
#include <Maths/Matrix4.h>
#include <map>
#include "World/World.h"

#include "Entities/Components/Cameras/Camera2DComponent.h"
#include "Entities/Components/Cameras/ArcBallCameraComponent.h"
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
	Mesh* m_Player;
	Matrix4       m_Rotation;
	Vector3      m_CameraPos;
	Vector3      m_LightDir;
	Texture* m_pCartoonShading;
	std::string         m_ShadersType;
	TDescTable          m_ShadersDesc;

	Program* m_pProgram;
	Texture* m_pCartoonShadingTextureHandle;

	BaseEntity* m_pEntity; //, *m_pCamera;
	ArcBallCameraComponent* m_pCamera3D;
	BaseEntity* m_pModelEntity;
	World* m_pWorld;
	Material* m_pGroundMaterial;
};
