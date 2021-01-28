#ifndef FightingGame2DGAME_H_
#define FightingGame2DGAME_H_

#include "Graphics/Effects/Shader.h"
#include "Graphics/Textures/Texture.h"
#include "GameTime.h"
#include "Game/Game.h"
#include "Maths/Matrix4.h"

#include "Sprite/Sprite.h"
#include "Sprite/SpriteRenderer.h"
#include "Game/Input.h"
#include "Entities/BaseEntity.h"
#include "Tools/DebugSystem.h"
#include "Game/Line2DRendererComponent.h"
#include "Game/Line3DRendererComponent.h"
#include "World/World.h"
#include "Entities/Components/Camera3DComponent.h"
#include "Entities/Components/Camera2DComponent.h"
#include "Entities/Components/AnimatedSpriteComponent.h"
#include "Entities/Components/CameraControllers/Camera2DTargetedController.h"
#include "Game/MeshRendererGameComponent.h"

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
