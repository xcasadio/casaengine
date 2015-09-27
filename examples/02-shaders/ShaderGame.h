//==========================================================
// CasaEngine - Free C++ 3D engine
//
// Copyright (C) 2004-2005 Laurent Gomila
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc.,
// 59 Temple Place - Suite 330,
// Boston, MA  02111-1307, USA.
//
// E-mail : laurent.gom@gmail.com
//==========================================================

#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H


#include <Graphics/Effects/Shader.h>
#include <Graphics/Textures/Texture.h>
#include "GameTime.h"
#include <Game/Game.h>
#include <Maths/Matrix4.h>
#include <Singleton.h>
#include <map>
#include "Entities/BaseEntity.h"
#include "World/World.h"

#include "Entities/Components/Camera3DComponent.h"
#include "Entities/Components/Camera2DComponent.h"
#include "Tools/DebugSystem.h"
#include "Game/Line2DRendererComponent.h"
#include "Game/Line3DRendererComponent.h"
#include "bgfx.h"
#include "Graphics/Effects/Program.h"

using namespace CasaEngine;

////////////////////////////////////////////////////////////
// Classe principale de la démo
////////////////////////////////////////////////////////////
class ShaderGame : 
	public Game
{
public :

	ShaderGame();

    //----------------------------------------------------------
    // Effectue les initialisations
    //----------------------------------------------------------
    void Initialize();

	void LoadContent();

    //----------------------------------------------------------
    // Effectue la mise à jour de la scène
    //----------------------------------------------------------
    void Update(const GameTime& gameTime_);

    //----------------------------------------------------------
    // Effectue le rendu de la scène
    //----------------------------------------------------------
    void Draw();

    //----------------------------------------------------------
    // Change de type de shaders
    //----------------------------------------------------------
    void ChangeShaders(const std::string& Type);

    //----------------------------------------------------------
    // Met à jour les paramètres des shaders
    //----------------------------------------------------------
    void UpdateShadersParams(const GameTime& gameTime_);

    //----------------------------------------------------------
    // Initialise les valeurs par défaut des paramètres des shaders
    //----------------------------------------------------------
    void SetShadersDefaults();

    //----------------------------------------------------------
    // Charge un autre modèle
    //----------------------------------------------------------
    void LoadModel(const char *Filename);

	void EndRun();

    //----------------------------------------------------------
    // Types
    //----------------------------------------------------------
    typedef std::map<std::string, std::string> TDescTable;

private:

    //----------------------------------------------------------
    // Données membres
    //----------------------------------------------------------
	Mesh		  *m_Player;         ///< Modèle courant
	Matrix4       m_Rotation;       ///< Matrice de rotation
	Vector3F      m_CameraPos;      ///< Position de la caméra
	Vector3F      m_LightDir;       ///< Direction de la lumière
	Texture       *m_pCartoonShading; ///< Texture de lookup pour le rendu cartoon
    std::string         m_ShadersType;    ///< Type des shaders actuellement chargés
    TDescTable          m_ShadersDesc;    ///< Table des descriptions de shaders

	Program *m_pProgram;
	Texture *m_pCartoonShadingTextureHandle;

	DebugSystem *m_pDebugSystem;
	Line2DRendererComponent *m_pLine2DRenderer;
	Line3DRendererComponent *m_pLine3DRenderer;

	BaseEntity *m_pEntity; //, *m_pCamera;
	Camera3DComponent *m_pCamera3D;
	Camera2DComponent *m_pCamera2D;
	BaseEntity *m_pModelEntity;
	Transform3DComponent *m_pTrans3D;
	World *m_pWorld;
	Material *m_pGroundMaterial;
};


#endif // MYAPPLICATION_H
