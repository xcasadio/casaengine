#ifndef ANIMATION2DPLAYER2DGAME_H_
#define ANIMATION2DPLAYER2DGAME_H_

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

class Animation2DPlayerGame :
	public Game
{
public :

	Animation2DPlayerGame();
	~Animation2DPlayerGame();

	void Initialize();
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
	void DisplayUI();

private:
	SpriteRenderer*	m_pSpriteRenderer;

	BaseEntity * m_pEntity;
	AnimatedSpriteComponent *m_pAnimatedSprite;
	Camera3DComponent *m_pCamera3D;
	World *m_pWorld;

	int m_AnimationIndexSelected, m_LastAnimationIndexSelected;
	int m_FrameIndexSelected, m_LastFrameIndexSelected;
	int m_CollisionIndexSelected, m_LastCollisionIndexSelected;
};

#endif
