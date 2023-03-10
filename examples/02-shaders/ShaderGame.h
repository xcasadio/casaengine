#pragma once

#include <Graphics/Textures/Texture.h>
#include "GameTime.h"
#include <Game/Game.h>
#include <Maths/Matrix4.h>
#include <map>

#include "Entities/Components/MeshComponent.h"
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
	void Draw() override;

	void ChangeShaders(const std::string& Type);
	void UpdateShadersParams(const GameTime& gameTime_);
	void SetShadersDefaults();

	void LoadModel(const char* Filename);

	typedef std::map<std::string, std::string> TDescTable;

private:
	void CreateGround();
	void CreateCamera();
	void CreateMesh();

	Mesh* _mesh;
	Matrix4       _matRotation;
	Vector3      _cameraPosition;
	Vector3      _lightDirection;
	Texture* m_pCartoonShading;
	std::string         m_ShadersType;
	TDescTable          m_ShadersDesc;

	Program* _program;
	Texture* _cartoonShadingTextureHandle;

	BaseEntity* _entity;
	World* _world;
	Material* _groundMaterial;
};
