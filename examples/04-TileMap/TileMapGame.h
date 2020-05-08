#ifndef HELLOWORLDGAME_H_
#define HELLOWORLDGAME_H_

#include "Entities/Components/StaticSpriteComponent.h"
#include "Entities/Components/CameraControllers/CameraController.h"
#include "Game/Game.h"
#include "Graphics/Effects/Program.h"
#include "Sprite/SpriteRenderer.h"
#include "World/World.h"

using namespace CasaEngine;

/**
 * 
 */
class TileMapGame :
	public Game
{
public:
	TileMapGame();
	~TileMapGame();

	virtual void Initialize();
	void CreateBackground(World* pWorld);
	virtual void LoadContent();
	virtual void Draw();
	virtual void Update(const GameTime& gameTime_);

private:
	SpriteRenderer* m_pSpriteRenderer;
};

#endif // HELLOWORLDGAME_H_
