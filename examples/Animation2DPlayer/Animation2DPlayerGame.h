#ifndef ANIMATION2DPLAYER2DGAME_H_
#define ANIMATION2DPLAYER2DGAME_H_

#include "GameTime.h"
#include "Game/Game.h"

#include "Sprite/SpriteRenderer.h"
#include "World/World.h"
#include "Entities/Components/Camera3DComponent.h"
#include "Entities/Components/AnimatedSpriteComponent.h"

using namespace CasaEngine;

class Animation2DPlayerGame :
	public Game
{
public:

	Animation2DPlayerGame();
	~Animation2DPlayerGame();

	void Initialize();
	void copy_animations_name();
	void LoadContent();
	void Update(const CasaEngine::GameTime& gameTime_);
	void Draw();

private:
	void AddGameComponent();
	void LoadAnimations(AnimatedSpriteComponent* pAnimatedComponent);
	void LoadSprites();
	void DisplayGrid();
	void DisplayCollisions();
	void DisplayPosition();
	void RenameAnimation(const char* old_name, const char* new_name);
	void DisplayUI();

private:
	SpriteRenderer* m_pSpriteRenderer;

	BaseEntity* m_pEntity;
	AnimatedSpriteComponent* m_pAnimatedSprite;
	Camera3DComponent* m_pCamera3D;
	World* m_pWorld;

	int m_AnimationIndexSelected, m_LastAnimationIndexSelected;
	int m_FrameIndexSelected, m_LastFrameIndexSelected;
	int m_CollisionIndexSelected, m_LastCollisionIndexSelected;
};

#endif
