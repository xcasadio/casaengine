#pragma once

#include  <Graphics/Textures/Texture.hpp>
#include  "GameTime.hpp"
#include  <Game/Game.hpp>
#include  <Maths/Matrix4.hpp>
#include <map>

#include  "Entities/Components/MeshComponent.hpp"
#include  "World/World.hpp"

#include  "Entities/Components/Cameras/Camera2DComponent.hpp"
#include  "Entities/Components/Cameras/ArcBallCameraComponent.hpp"
#include  "Graphics/Effects/Program.hpp"
#include  "Graphics/Materials/Material.hpp"
#include  "Graphics/Mesh/Mesh.hpp"

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
