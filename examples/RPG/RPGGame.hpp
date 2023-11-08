#pragma once

#include  "load_save_types.hpp"
#include  "Graphics/Textures/Texture.hpp"
#include  "Game/Game.hpp"

#include  "World/World.hpp"
#include  "Entities/Components/AnimatedSpriteComponent.hpp"
#include  "Entities/Components/Cameras/ArcBallCameraComponent.hpp"

using namespace CasaEngine;

class RPGGame :
	public Game
{
public:

	RPGGame();
	~RPGGame() override;

	void Initialize() override;
	void LoadContent() override;

private:
	void CreateMap(World* pWorld);
	void CreateEnemies(World* pWorld);
	void CreateSwordman(World* pWorld);

private:
	Texture* m_pGroundTexture;

	BaseEntity* m_pEntity;
	AnimatedSpriteComponent* m_pAnimatedSprite;
	ArcBallCameraComponent* m_pCamera3D;
	World* m_pWorld;
};
