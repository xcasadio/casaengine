#pragma once

#include "load_save_types.h"
#include "Graphics/Textures/Texture.h"
#include "Game/Game.h"

#include "World/World.h"
#include "Entities/Components/AnimatedSpriteComponent.h"
#include "Entities/Components/Cameras/ArcBallCameraComponent.h"

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
