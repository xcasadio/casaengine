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

#ifndef MD2LOADER_H
#define MD2LOADER_H

//==========================================================
// En-t�tes
//==========================================================
#include <Graphics/Mesh/Mesh.h>
#include <vector>
#include "IO/IFile.h"

////////////////////////////////////////////////////////////
/// Classe prenant en charge l'importation des mod�les MD2
////////////////////////////////////////////////////////////
class CMD2Loader /*:
	public CasaEngine::ILoader<CasaEngine::Mesh>*/
{
public:

	//----------------------------------------------------------
	// Charge un mod�le � partir d'un fichier
	//----------------------------------------------------------
	virtual CasaEngine::Mesh* LoadFromFile(CasaEngine::IFile* pFile_);

private:

	//----------------------------------------------------------
	// Donn�es membres statiques
	//----------------------------------------------------------
	static const int s_MagicId = ('2' << 24) + ('P' << 16) + ('D' << 8) + 'I'; ///< Identifiant magique "IDP2" servant � valider les mod�les
	static const int s_MD2Version = 8;                                            ///< Num�ro de version g�r�
	static const CasaEngine::Vector3F s_NormalTable[];                                  ///< Table des normales pr�calcul�es

#if CA_PLATFORM_WINDOWS

#include <pshpack1.h>

#endif // #if CA_PLATFORM_WINDOWS

	///----------------------------------------------------------
	/// Structure de l'en-t�te des fichiers MD2
	///----------------------------------------------------------
	struct THeader
	{
		int Ident;            ///< Num�ro magique "IDP2"
		int Version;          ///< Version du format
		int TexWidth;         ///< Largeur de la texture
		int TexHeight;        ///< Hauteur de la texture
		int FrameSize;        ///< Taille d'une frame en octets
		int NbTextures;       ///< Nombre de textures
		int NbVertices;       ///< Nombre de vertices par frame
		int NbTexCoords;      ///< Nombre de coordonn�es de texture
		int NbTriangles;      ///< Nombre de triangles
		int NbGLCommands;     ///< Nombre de commandes OpenGL
		int NbFrames;         ///< Nombre de frames
		int OffsetTextures;   ///< Offset donn�es textures
		int OffsetTexCoords;  ///< Offset donn�es coordonn�es de texture
		int OffsetTriangles;  ///< Offset donn�es triangles
		int OffsetFrames;     ///< Offset donn�es frames
		int OffsetGLCommands; ///< Offset donn�es commandes OpenGL
		int OffsetEnd;        ///< Offset fin de fichier
	};

	///----------------------------------------------------------
	/// Structure des sommets
	///----------------------------------------------------------
	struct TPoint
	{
		unsigned char x, y, z; ///< Coordonn�es 3D
		unsigned char n;       ///< Indice de la normale (dans la table des normales pr�calcul�es)
	};

	///----------------------------------------------------------
	/// Structure des coordonn�es de texture
	///----------------------------------------------------------
	struct TTexCoord
	{
		short u, v; ///< Coordonn�es de texture (relatives � la taille de celle-ci)
	};

	///----------------------------------------------------------
	/// Structure des triangles
	///----------------------------------------------------------
	struct TTriangle
	{
		unsigned short Vertices[3];  ///< Indices des 3 sommets du triangle
		unsigned short TexCoords[3]; ///< Indices des coordonn�es de texture des 3 sommets du triangle
	};

	///----------------------------------------------------------
	/// Structure des noms de textures
	///----------------------------------------------------------
	struct TTexture
	{
		char Name[68]; ///< Nom de fichier de la texture
	};

	///----------------------------------------------------------
	/// Structure des frames
	///----------------------------------------------------------
	struct TFrame
	{
		CasaEngine::Vector3F      Scale;     ///< Facteur d'�chelle
		CasaEngine::Vector3F      Translate; ///< Position
		char                Name[16];  ///< Nom de la frame
		std::vector<TPoint> Vertices;  ///< Liste des sommets
	};

#if CA_PLATFORM_WINDOWS

#include <poppack.h>

#endif // #if CA_PLATFORM_WINDOWS
};

#endif // MD2LOADER_H
