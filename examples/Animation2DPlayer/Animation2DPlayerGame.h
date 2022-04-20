#pragma once

#include "GameTime.h"
#include "Game/Game.h"

#include "World/World.h"
#include "Entities/Components/AnimatedSpriteComponent.h"

using namespace CasaEngine;

class Animation2DPlayerGame :
	public Game
{
public:

	Animation2DPlayerGame();
	~Animation2DPlayerGame() override;

	void Initialize() override;
	void copy_animations_name();
	void LoadContent() override;
	void Update(const CasaEngine::GameTime& gameTime_) override;
	void Draw() override;

private:
	void LoadAnimations(AnimatedSpriteComponent* pAnimatedComponent);
	void LoadSprites();
	void DisplayCollisions();
	void DisplayPosition();
	void RenameAnimation(const char* old_name, const char* new_name);
	void DisplayUI();

private:
	BaseEntity* m_pEntity;
	AnimatedSpriteComponent* m_pAnimatedSprite;
	World* m_pWorld;

	int m_AnimationIndexSelected, m_LastAnimationIndexSelected;
	int m_FrameIndexSelected, m_LastFrameIndexSelected;
	int m_CollisionIndexSelected, m_LastCollisionIndexSelected;
};
