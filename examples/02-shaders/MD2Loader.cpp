#include "MD2Loader.h"
#include <fstream>

#include "Graphics/Vertices/VertexType.h"
#include "Game/Game.h"

using namespace CasaEngine;

////////////////////////////////////////////////////////////
/// Charge un modèle à partir d'un fichier
///
/// \param Filename : Chemin complet du fichier à charger
///
/// \return Pointeur sur le modèle créé
///
////////////////////////////////////////////////////////////
Mesh* CMD2Loader::LoadFromFile(IFile* pFile_)
{
	// Les méthodes utilisées ici ne sont pas portables (problèmes d'endianness et de taille des types primitifs).
	// Il faudrait, pour bien faire, tout charger dans des tableaux d'octet et tout réassembler.
	// ...A faire quand j'aurai le temps :)

	THeader Header;
	pFile_->Read(reinterpret_cast<char*>(&Header), sizeof(Header));

	if (Header.Ident != s_MagicId)
		throw CLoadingFailed(pFile_->Filename(), "Le fichier n'est pas un modèle MD2 valide");

	if (Header.Version != s_MD2Version)
		throw CLoadingFailed(pFile_->Filename(), "Le modèle possède une version différente de celle requise (v.8)");

	std::vector<TTexture>  Textures(Header.NbTextures);
	std::vector<TTexCoord> TexCoords(Header.NbTexCoords);
	std::vector<TTriangle> Triangles(Header.NbTriangles);
	std::vector<TFrame>    Frames(Header.NbFrames);

	// Lecture des noms de textures
	pFile_->Seek(Header.OffsetTextures, SeekDir::SEEKDIR_SET);
	pFile_->Read(reinterpret_cast<char*>(&Textures[0]), sizeof(TTexture) * Header.NbTextures);

	// Lecture des coordonnées de texture
	pFile_->Seek(Header.OffsetTexCoords, SeekDir::SEEKDIR_SET);
	pFile_->Read(reinterpret_cast<char*>(&TexCoords[0]), sizeof(TTexCoord) * Header.NbTexCoords);

	// Lecture des triangles
	pFile_->Seek(Header.OffsetTriangles, SeekDir::SEEKDIR_SET);
	pFile_->Read(reinterpret_cast<char*>(&Triangles[0]), sizeof(TTriangle) * Header.NbTriangles);

	// Lecture des frames (on ne lit que la première pour le moment -- on ne gère pas les animations)
	pFile_->Seek(Header.OffsetFrames, SeekDir::SEEKDIR_SET);
	Frames[0].Vertices.resize(Header.NbVertices);
	pFile_->Read(reinterpret_cast<char*>(&Frames[0].Scale), sizeof(Frames[0].Scale));
	pFile_->Read(reinterpret_cast<char*>(&Frames[0].Translate), sizeof(Frames[0].Translate));
	pFile_->Read(reinterpret_cast<char*>(&Frames[0].Name), sizeof(Frames[0].Name));
	pFile_->Read(reinterpret_cast<char*>(&Frames[0].Vertices[0]), sizeof(TPoint) * Header.NbVertices);

	// Transformation des données (aucune optimisation au niveau du stockage des vertices)
	std::vector<VertexPositionNormalTexture> Vertices;
	std::vector<unsigned short>  Indices;
	for (int i = 0; i < Header.NbTriangles; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			// Récupération des informations sur le sommet courant
			VertexPositionNormalTexture v;
			const TPoint& Vert = Frames[0].Vertices[Triangles[i].Vertices[j]];
			const TTexCoord& TexC = TexCoords[Triangles[i].TexCoords[j]];

			// Construction du vertex
			v.Position.x = Vert.x * Frames[0].Scale.x + Frames[0].Translate.x;
			v.Position.y = Vert.y * Frames[0].Scale.y + Frames[0].Translate.y;
			v.Position.z = Vert.z * Frames[0].Scale.z + Frames[0].Translate.z;
			v.Normal = s_NormalTable[Vert.n];
			//v.Color       = IRenderer::Get().ConvertColor(CColor::White);
			v.TexCoords.x = TexC.u / static_cast<float>(Header.TexWidth);
			v.TexCoords.y = TexC.v / static_cast<float>(Header.TexHeight);

			// Ajout au vertex buffer et à l'index buffer
			Vertices.push_back(v);
			Indices.push_back(i * 3 + j);
		}
	}

	VertexPositionNormalTexture* pVerts = ::new VertexPositionNormalTexture[(int)Vertices.size()];
	memcpy(pVerts, Vertices.data(), Vertices.size() * sizeof(VertexPositionNormalTexture));

	unsigned short* pIndices = ::new unsigned short[(int)Indices.size()];
	memcpy(pIndices, Indices.data(), Indices.size() * sizeof(unsigned short));

	Mesh* pModel = NEW_AO Mesh(pVerts, (int)Vertices.size(), pIndices, (int)Indices.size());
	Material* pMaterial = pModel->GetMaterial()->Clone();
	pMaterial->Texture0(Texture::loadTexture(
		Game::Instance().GetMediaManager().FindMedia(Textures[0].Name, true),
		BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC));
	pModel->SetMaterial(pMaterial);

	// 	Texture* pTexture = Game::Instance().GetResourceManager().Get<Texture>(Textures[0].Name);
	//
	// 	if (nullptr == pTexture)
	// 	{
	// 		pTexture = IRenderer::Get().loadTexture(Textures[0].Name, BGFX_TEXTURE_MIN_ANISOTROPIC | BGFX_TEXTURE_MAG_ANISOTROPIC);
	// 		Game::Instance().GetResourceManager().Add(Textures[0].Name, pTexture);
	// 	}

	return pModel;
}

////////////////////////////////////////////////////////////
// Table des normales précalculées
////////////////////////////////////////////////////////////
const Vector3F CMD2Loader::s_NormalTable[] =
{
	Vector3F(-0.525731f,  0.000000f,  0.850651f),
	Vector3F(-0.442863f,  0.238856f,  0.864188f),
	Vector3F(-0.295242f,  0.000000f,  0.955423f),
	Vector3F(-0.309017f,  0.500000f,  0.809017f),
	Vector3F(-0.162460f,  0.262866f,  0.951056f),
	Vector3F(0.000000f,  0.000000f,  1.000000f),
	Vector3F(0.000000f,  0.850651f,  0.525731f),
	Vector3F(-0.147621f,  0.716567f,  0.681718f),
	Vector3F(0.147621f,  0.716567f,  0.681718f),
	Vector3F(0.000000f,  0.525731f,  0.850651f),
	Vector3F(0.309017f,  0.500000f,  0.809017f),
	Vector3F(0.525731f,  0.000000f,  0.850651f),
	Vector3F(0.295242f,  0.000000f,  0.955423f),
	Vector3F(0.442863f,  0.238856f,  0.864188f),
	Vector3F(0.162460f,  0.262866f,  0.951056f),
	Vector3F(-0.681718f,  0.147621f,  0.716567f),
	Vector3F(-0.809017f,  0.309017f,  0.500000f),
	Vector3F(-0.587785f,  0.425325f,  0.688191f),
	Vector3F(-0.850651f,  0.525731f,  0.000000f),
	Vector3F(-0.864188f,  0.442863f,  0.238856f),
	Vector3F(-0.716567f,  0.681718f,  0.147621f),
	Vector3F(-0.688191f,  0.587785f,  0.425325f),
	Vector3F(-0.500000f,  0.809017f,  0.309017f),
	Vector3F(-0.238856f,  0.864188f,  0.442863f),
	Vector3F(-0.425325f,  0.688191f,  0.587785f),
	Vector3F(-0.716567f,  0.681718f, -0.147621f),
	Vector3F(-0.500000f,  0.809017f, -0.309017f),
	Vector3F(-0.525731f,  0.850651f,  0.000000f),
	Vector3F(0.000000f,  0.850651f, -0.525731f),
	Vector3F(-0.238856f,  0.864188f, -0.442863f),
	Vector3F(0.000000f,  0.955423f, -0.295242f),
	Vector3F(-0.262866f,  0.951056f, -0.162460f),
	Vector3F(0.000000f,  1.000000f,  0.000000f),
	Vector3F(0.000000f,  0.955423f,  0.295242f),
	Vector3F(-0.262866f,  0.951056f,  0.162460f),
	Vector3F(0.238856f,  0.864188f,  0.442863f),
	Vector3F(0.262866f,  0.951056f,  0.162460f),
	Vector3F(0.500000f,  0.809017f,  0.309017f),
	Vector3F(0.238856f,  0.864188f, -0.442863f),
	Vector3F(0.262866f,  0.951056f, -0.162460f),
	Vector3F(0.500000f,  0.809017f, -0.309017f),
	Vector3F(0.850651f,  0.525731f,  0.000000f),
	Vector3F(0.716567f,  0.681718f,  0.147621f),
	Vector3F(0.716567f,  0.681718f, -0.147621f),
	Vector3F(0.525731f,  0.850651f,  0.000000f),
	Vector3F(0.425325f,  0.688191f,  0.587785f),
	Vector3F(0.864188f,  0.442863f,  0.238856f),
	Vector3F(0.688191f,  0.587785f,  0.425325f),
	Vector3F(0.809017f,  0.309017f,  0.500000f),
	Vector3F(0.681718f,  0.147621f,  0.716567f),
	Vector3F(0.587785f,  0.425325f,  0.688191f),
	Vector3F(0.955423f,  0.295242f,  0.000000f),
	Vector3F(1.000000f,  0.000000f,  0.000000f),
	Vector3F(0.951056f,  0.162460f,  0.262866f),
	Vector3F(0.850651f, -0.525731f,  0.000000f),
	Vector3F(0.955423f, -0.295242f,  0.000000f),
	Vector3F(0.864188f, -0.442863f,  0.238856f),
	Vector3F(0.951056f, -0.162460f,  0.262866f),
	Vector3F(0.809017f, -0.309017f,  0.500000f),
	Vector3F(0.681718f, -0.147621f,  0.716567f),
	Vector3F(0.850651f,  0.000000f,  0.525731f),
	Vector3F(0.864188f,  0.442863f, -0.238856f),
	Vector3F(0.809017f,  0.309017f, -0.500000f),
	Vector3F(0.951056f,  0.162460f, -0.262866f),
	Vector3F(0.525731f,  0.000000f, -0.850651f),
	Vector3F(0.681718f,  0.147621f, -0.716567f),
	Vector3F(0.681718f, -0.147621f, -0.716567f),
	Vector3F(0.850651f,  0.000000f, -0.525731f),
	Vector3F(0.809017f, -0.309017f, -0.500000f),
	Vector3F(0.864188f, -0.442863f, -0.238856f),
	Vector3F(0.951056f, -0.162460f, -0.262866f),
	Vector3F(0.147621f,  0.716567f, -0.681718f),
	Vector3F(0.309017f,  0.500000f, -0.809017f),
	Vector3F(0.425325f,  0.688191f, -0.587785f),
	Vector3F(0.442863f,  0.238856f, -0.864188f),
	Vector3F(0.587785f,  0.425325f, -0.688191f),
	Vector3F(0.688191f,  0.587785f, -0.425325f),
	Vector3F(-0.147621f,  0.716567f, -0.681718f),
	Vector3F(-0.309017f,  0.500000f, -0.809017f),
	Vector3F(0.000000f,  0.525731f, -0.850651f),
	Vector3F(-0.525731f,  0.000000f, -0.850651f),
	Vector3F(-0.442863f,  0.238856f, -0.864188f),
	Vector3F(-0.295242f,  0.000000f, -0.955423f),
	Vector3F(-0.162460f,  0.262866f, -0.951056f),
	Vector3F(0.000000f,  0.000000f, -1.000000f),
	Vector3F(0.295242f,  0.000000f, -0.955423f),
	Vector3F(0.162460f,  0.262866f, -0.951056f),
	Vector3F(-0.442863f, -0.238856f, -0.864188f),
	Vector3F(-0.309017f, -0.500000f, -0.809017f),
	Vector3F(-0.162460f, -0.262866f, -0.951056f),
	Vector3F(0.000000f, -0.850651f, -0.525731f),
	Vector3F(-0.147621f, -0.716567f, -0.681718f),
	Vector3F(0.147621f, -0.716567f, -0.681718f),
	Vector3F(0.000000f, -0.525731f, -0.850651f),
	Vector3F(0.309017f, -0.500000f, -0.809017f),
	Vector3F(0.442863f, -0.238856f, -0.864188f),
	Vector3F(0.162460f, -0.262866f, -0.951056f),
	Vector3F(0.238856f, -0.864188f, -0.442863f),
	Vector3F(0.500000f, -0.809017f, -0.309017f),
	Vector3F(0.425325f, -0.688191f, -0.587785f),
	Vector3F(0.716567f, -0.681718f, -0.147621f),
	Vector3F(0.688191f, -0.587785f, -0.425325f),
	Vector3F(0.587785f, -0.425325f, -0.688191f),
	Vector3F(0.000000f, -0.955423f, -0.295242f),
	Vector3F(0.000000f, -1.000000f,  0.000000f),
	Vector3F(0.262866f, -0.951056f, -0.162460f),
	Vector3F(0.000000f, -0.850651f,  0.525731f),
	Vector3F(0.000000f, -0.955423f,  0.295242f),
	Vector3F(0.238856f, -0.864188f,  0.442863f),
	Vector3F(0.262866f, -0.951056f,  0.162460f),
	Vector3F(0.500000f, -0.809017f,  0.309017f),
	Vector3F(0.716567f, -0.681718f,  0.147621f),
	Vector3F(0.525731f, -0.850651f,  0.000000f),
	Vector3F(-0.238856f, -0.864188f, -0.442863f),
	Vector3F(-0.500000f, -0.809017f, -0.309017f),
	Vector3F(-0.262866f, -0.951056f, -0.162460f),
	Vector3F(-0.850651f, -0.525731f,  0.000000f),
	Vector3F(-0.716567f, -0.681718f, -0.147621f),
	Vector3F(-0.716567f, -0.681718f,  0.147621f),
	Vector3F(-0.525731f, -0.850651f,  0.000000f),
	Vector3F(-0.500000f, -0.809017f,  0.309017f),
	Vector3F(-0.238856f, -0.864188f,  0.442863f),
	Vector3F(-0.262866f, -0.951056f,  0.162460f),
	Vector3F(-0.864188f, -0.442863f,  0.238856f),
	Vector3F(-0.809017f, -0.309017f,  0.500000f),
	Vector3F(-0.688191f, -0.587785f,  0.425325f),
	Vector3F(-0.681718f, -0.147621f,  0.716567f),
	Vector3F(-0.442863f, -0.238856f,  0.864188f),
	Vector3F(-0.587785f, -0.425325f,  0.688191f),
	Vector3F(-0.309017f, -0.500000f,  0.809017f),
	Vector3F(-0.147621f, -0.716567f,  0.681718f),
	Vector3F(-0.425325f, -0.688191f,  0.587785f),
	Vector3F(-0.162460f, -0.262866f,  0.951056f),
	Vector3F(0.442863f, -0.238856f,  0.864188f),
	Vector3F(0.162460f, -0.262866f,  0.951056f),
	Vector3F(0.309017f, -0.500000f,  0.809017f),
	Vector3F(0.147621f, -0.716567f,  0.681718f),
	Vector3F(0.000000f, -0.525731f,  0.850651f),
	Vector3F(0.425325f, -0.688191f,  0.587785f),
	Vector3F(0.587785f, -0.425325f,  0.688191f),
	Vector3F(0.688191f, -0.587785f,  0.425325f),
	Vector3F(-0.955423f,  0.295242f,  0.000000f),
	Vector3F(-0.951056f,  0.162460f,  0.262866f),
	Vector3F(-1.000000f,  0.000000f,  0.000000f),
	Vector3F(-0.850651f,  0.000000f,  0.525731f),
	Vector3F(-0.955423f, -0.295242f,  0.000000f),
	Vector3F(-0.951056f, -0.162460f,  0.262866f),
	Vector3F(-0.864188f,  0.442863f, -0.238856f),
	Vector3F(-0.951056f,  0.162460f, -0.262866f),
	Vector3F(-0.809017f,  0.309017f, -0.500000f),
	Vector3F(-0.864188f, -0.442863f, -0.238856f),
	Vector3F(-0.951056f, -0.162460f, -0.262866f),
	Vector3F(-0.809017f, -0.309017f, -0.500000f),
	Vector3F(-0.681718f,  0.147621f, -0.716567f),
	Vector3F(-0.681718f, -0.147621f, -0.716567f),
	Vector3F(-0.850651f,  0.000000f, -0.525731f),
	Vector3F(-0.688191f,  0.587785f, -0.425325f),
	Vector3F(-0.587785f,  0.425325f, -0.688191f),
	Vector3F(-0.425325f,  0.688191f, -0.587785f),
	Vector3F(-0.425325f, -0.688191f, -0.587785f),
	Vector3F(-0.587785f, -0.425325f, -0.688191f),
	Vector3F(-0.688191f, -0.587785f, -0.425325f)
};