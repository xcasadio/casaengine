
#ifndef SAMPLECUBEANDROID_H_
#define SAMPLECUBEANDROID_H_

#include "Graphics/Effects/Shader.h"
#include "Graphics/Textures/Texture.h"
#include "Game/GameTime.h"
#include "Game/Game.h"
#include "Singleton.h"
#include "Entities/BaseEntity.h"
#include "Game/ModelRendererGameComponent.h"
#include "World/World.h"

using namespace CasaEngine;

class SampleCubeAndroid :
	public Game
{
public :

	SampleCubeAndroid();
	~SampleCubeAndroid();

	//----------------------------------------------------------
	// Effectue les initialisations
	//----------------------------------------------------------
	void Initialize();

	//----------------------------------------------------------
	// Effectue les initialisations
	//----------------------------------------------------------
	void LoadContent();

	//----------------------------------------------------------
	// Effectue la mise à jour de la scène
	//----------------------------------------------------------
	void Update(const CasaEngine::GameTime& gameTime_);

	//----------------------------------------------------------
	// Effectue le rendu de la scène
	//----------------------------------------------------------
	void Draw();

	//----------------------------------------------------------
	// Données membres
	//----------------------------------------------------------
	//Shader			m_VertexShader;   ///< Vertex shader
	//Shader			m_PixelShader;    ///< Pixel shader

	ModelRendererGameComponent *m_pModelRenderer;

	BaseEntity *m_pEntity, *m_pCamera;
	World *m_pWorld;
};

#endif // SAMPLECUBEANDROID_H_
