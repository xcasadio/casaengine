#ifndef STEERINGGAME_H_
#define STEERINGGAME_H_

#include "Entities/BaseEntity.h"
#include "Entities/Components/AnimatedSpriteComponent.h"
#include "Entities/Components/Camera3DComponent.h"
#include "Game/Game.h"
#include "Game/Line3DRendererComponent.h"
#include "Game/MeshRendererGameComponent.h"
#include "GameTime.h"
#include "World/World.h"
#include "Graphics/Effects/Program.h"

using namespace CasaEngine;

/**
 * 
 */
class SteeringGame :
	public Game
{
public :

	SteeringGame();
	~SteeringGame();

	void Initialize();
	void LoadContent();
	void Update(const GameTime& gameTime_);
	void Draw();

private:
	void AddGameComponents();
	void CreateEntities();
	void CreateBoids();

private:
	MeshRendererGameComponent *m_pModelRenderer;
	Line3DRendererComponent *m_pLine3DRenderer;

	std::vector<BaseEntity *> m_Entities;
	Camera3DComponent *m_pCamera3D;
	World *m_pWorld;

	Program *m_pProgram;
};

#endif // STEERINGGAME_H_
