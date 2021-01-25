#ifndef GAME2DDEMOGAME_H_
#define GAME2DDEMOGAME_H_

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

class Scene2DGame :
	public Game
{
public:

	Scene2DGame();
	~Scene2DGame();

	void Initialize();
	void LoadContent();
	void Update(const CasaEngine::GameTime& gameTime_);
	void Draw();

private:
	void AddGameComponent();
	void CreateEntities();
	void CreatePlayer();
	void LoadAssets();

	void CreateMap(World* pWorld);
	void CreateAssets(Vector2I tileSize);
	void CreateEnnemies(World* pWorld);
	void CreateSwordman(World* pWorld);

private:
	Texture* m_pGroundTexture;

	MeshRendererGameComponent* m_pModelRenderer;
	SpriteRenderer* m_pSpriteRenderer;
	Line2DRendererComponent* m_pLine2DRenderer;
	Line3DRendererComponent* m_pLine3DRenderer;

	BaseEntity* m_pEntity;
	AnimatedSpriteComponent* m_pAnimatedSprite;
	Camera3DComponent* m_pCamera3D;
	World* m_pWorld;
};

#endif
