#ifndef TILEMAPGAME_H_
#define TILEMAPGAME_H_

#include "Game/Game.h"
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

#endif // TILEMAPGAME_H_
