#ifndef FSMGAME_H_
#define FSMGAME_H_

#include "GameTime.h"
#include "Game/Game.h"
#include "Maths/Matrix4.h"
#include "Entities/BaseEntity.h"
#include "Entities/Components/Camera3DComponent.h"

using namespace CasaEngine;

/**
 * 
 */
class FSMGame :
	public Game
{
public:
	/**
	 * 
	 */
	FSMGame();

	/**
	 * 
	 */
	~FSMGame();

	/**
	 * 
	 */
	void Initialize();

	/**
	 * 
	 */
	void LoadContent();

private :
	Matrix4			m_MatView3D;      ///< Matrice de vue pour le mode 3D
	Matrix4			m_MatProj3D;      ///< Matrice de projection pour le mode 3D
	Matrix4			m_Rotation;       ///< Matrice de rotation
	Vector3F		m_CameraPos;      ///< Position de la caméra

	BaseEntity* m_pBob, *m_pElsa;

	Camera3DComponent *m_pCamera3D;
};

#endif // FSMGAME_H_
