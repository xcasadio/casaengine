#ifndef FightingGame2DGAME_H_
#define FightingGame2DGAME_H_

#include "GameTime.h"
#include "Game/Game.h"

#include "Sprite/SpriteRenderer.h"
#include "World/World.h"
#include "Entities/Components/AnimatedSpriteComponent.h"

using namespace CasaEngine;

class FightingGame2DGame :
	public Game
{
public:

	FightingGame2DGame();
	~FightingGame2DGame();

	void Initialize();
	void LoadContent();
	void Update(const CasaEngine::GameTime& gameTime_);
	void Draw();

private:
	void AddGameComponent();
	std::vector<Animation2DData> LoadAnimations();
	void LoadSprites();
	void DisplayGrid();
	void DisplayCollisions();
	void DisplayCollision(BaseEntity* pEntity);
	void DisplayPositions();
	void DisplayPosition(BaseEntity* pEntity);
	void DisplayUI();

private:
	World* m_pWorld;
};

#endif
