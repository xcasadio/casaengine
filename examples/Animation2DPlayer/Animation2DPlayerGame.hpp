#pragma once

#include  "GameTime.hpp"
#include  "Game/Game.hpp"

#include  "World/World.hpp"
#include  "Entities/Components/AnimatedSpriteComponent.hpp"

using namespace CasaEngine;

class Animation2DPlayerGame :
	public Game
{
public:

	Animation2DPlayerGame();
	~Animation2DPlayerGame() override;

	void Initialize() override;
	void LoadContent() override;
	void Update(const CasaEngine::GameTime& gameTime_) override;
	void Draw() override;

private:
	void DisplayUI();

private:
	BaseEntity* m_pEntity;
	AnimatedSpriteComponent* m_pAnimatedSprite;
	World* m_pWorld;

	int m_AnimationSelectedIndex, m_LastAnimationSelectedIndex;
	int m_AnimationTypeSelectedIndex, m_LastAnimationTypeSelectedIndex;
	int m_FrameSelectedIndex, m_LastFrameSelectedIndex;
	int m_CollisionSelectedIndex, m_LastCollisionSelectedIndex;
	int m_CollisionTypeSelectedIndex, m_LastCollisionTypeSelectedIndex;
	bool m_FrameSelectionChanged;
};
