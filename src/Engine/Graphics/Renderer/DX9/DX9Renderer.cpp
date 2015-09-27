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


#include "DX9Renderer.h"

#include "DX9Declaration.h"
#include "DX9Effect.h"
#include "DX9Enum.h"
#include "DX9Exception.h"
#include "DX9Macro.h"
#include "DX9RenderTargetTexture.h"
#include "DX9Shader.h"
#include "DX9Texture.h"
#include "DxErr.h"
#include "Graphics/Color.h"
#include "Graphics/Vertices/Declaration.h"
#include "Graphics/Vertices/DeclarationElement.h"
#include "Graphics/Viewport.h"
#include "Log/Logger.h"
#include "Util.h"
#include "Win32/Win32Macro.h"
#include "SFML/System/NonCopyable.hpp"
#include "DX9Buffer.h"
#include "Macro.h"
#include "CA_Assert.h"



namespace CasaEngine
{

////////////////////////////////////////////////////////////
// Implémentation des méthodes du singleton
////////////////////////////////////////////////////////////
SINGLETON_IMPL(DX9Renderer)


/////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
////////////////////////////////////////////////////////////
DX9Renderer::DX9Renderer() :
m_MinVertex  (0),
m_VertexCount(0)
{
    for (int i = 0; i < 6; ++i)
        m_Matrices[i].push_back(Matrix4());
}


/////////////////////////////////////////////////////////////
/// Destructeur
///
////////////////////////////////////////////////////////////
DX9Renderer::~DX9Renderer()
{
    //DXCheck(cgD3D9SetDevice(nullptr));
}


////////////////////////////////////////////////////////////
// Renvoie une description du renderer courant
///
/// \return Chaîne de caractère décrivant le renderer et sa version
///
////////////////////////////////////////////////////////////
std::string DX9Renderer::GetRendererDesc() const
{
    return "DirectX 9";
}


/////////////////////////////////////////////////////////////
/// Initialise l'API
///
/// \param Hwnd : Handle du contrôle de rendu
///
////////////////////////////////////////////////////////////
void DX9Renderer::Setup(sf::Window *pWindow_)
{
	HWND Hwnd = reinterpret_cast<HWND>(pWindow_->getSystemHandle());

	CA_ASSERT(Hwnd != nullptr, "DX9Renderer::Setup()");

    // Récupération de l'instance de l'objet D3D9
    if ((m_Direct3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
        throw DX9Exception("Direct3DCreate9", "Initialize");

    // Récupération de la taille de la fenêtre
    RECT Rect;
    Win32Check(GetClientRect(Hwnd, &Rect));

    // Initialisation des paramètres du device
    D3DPRESENT_PARAMETERS PresentParameters;
    ZeroMemory(&PresentParameters, sizeof(D3DPRESENT_PARAMETERS));
    PresentParameters.FullScreen_RefreshRateInHz = 0;
    PresentParameters.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
    PresentParameters.SwapEffect                 = D3DSWAPEFFECT_DISCARD;
    PresentParameters.BackBufferWidth            = Rect.right - Rect.left;
    PresentParameters.BackBufferHeight           = Rect.bottom - Rect.top;
    PresentParameters.BackBufferFormat           = D3DFMT_A8R8G8B8;
    PresentParameters.AutoDepthStencilFormat     = D3DFMT_D24S8;
    PresentParameters.EnableAutoDepthStencil     = true;
    PresentParameters.Windowed                   = true;

    // Création du device
    if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &PresentParameters, &GetPtr(m_Device))))
        throw DX9Exception("CreateDevice", "Initialize");

    // States par défaut
    //fixed pipeline
    DXCheck(m_Device->SetRenderState(D3DRS_LIGHTING,         false));    
    DXCheck(m_Device->SetRenderState(D3DRS_FOGENABLE,        false));
    DXCheck(m_Device->SetRenderState(D3DRS_ALPHATESTENABLE,  false));
    DXCheck(m_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
    //DXCheck(m_Device->SetRenderState(D3DRS_CULLMODE,         D3DCULL_CCW));

	DXCheck(m_Device->SetRenderState(D3DRS_DITHERENABLE,     true));
	DXCheck(m_Device->SetRenderState(D3DRS_ZENABLE,          true));
    DXCheck(m_Device->SetRenderState(D3DRS_STENCILMASK,      0xFF));
    DXCheck(m_Device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xFF));

	SetTextureWrap(TEX_REPEAT);
	SetTextureFilter(TEX_FILTER_3);
	SetTextureAnisotropic(TEX_ANISOTROPY_4);
}


////////////////////////////////////////////////////////////
/// Vérifie les fonctionnalités supportées et met à jour
/// la table des fonctionnalités
///
////////////////////////////////////////////////////////////
void DX9Renderer::CheckCaps()
{
    // Récupération des caps Dx9
    D3DCAPS9 caps;
    DXCheck(m_Device->GetDeviceCaps(&caps));

    // Support de la génération de mipmaps hardware
    m_Capabilities[Capability::HardwareMipmapping] = (caps.Caps2 & D3DCAPS2_CANAUTOGENMIPMAP) != 0;

    // Support de la compression de texture
    m_Capabilities[Capability::DXTCompression] = CheckFormat(D3DFMT_DXT1, D3DRTYPE_TEXTURE) &&
                                          CheckFormat(D3DFMT_DXT3, D3DRTYPE_TEXTURE) &&
                                          CheckFormat(D3DFMT_DXT5, D3DRTYPE_TEXTURE);

    // Support des dimensions de texture non-puissances de 2
	m_Capabilities[Capability::TextureNonPowerOf2] = !(caps.TextureCaps & D3DPTEXTURECAPS_POW2) ||
						(caps.TextureCaps & D3DPTEXTURECAPS_NONPOW2CONDITIONAL);

	m_Capabilities[Capability::ScissorTest] = caps.RasterCaps && D3DPRASTERCAPS_SCISSORTEST;

	m_MaxTextureSize.x = caps.MaxTextureWidth;
	m_MaxTextureSize.y = caps.MaxTextureHeight;
}


////////////////////////////////////////////////////////////
/// Indique si un format de pixel donné est supporté
///
/// \param Format :       Format à tester
/// \param ResourceType : Type de ressource (texture, surface, ...)
/// \param Usage :        Usage (0 par défaut)
///
/// \return True si le format est supporté
///
////////////////////////////////////////////////////////////
bool DX9Renderer::CheckFormat(D3DFORMAT Format, D3DRESOURCETYPE ResourceType, unsigned long Usage)
{
    CA_ASSERT(m_Direct3D != nullptr, "DX9Renderer::CheckFormat()");

    return SUCCEEDED(m_Direct3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8,
                                                   Usage, ResourceType, Format));
}

/**
 * 
 */
const char * DX9Renderer::GetShaderFileExtension() const
{
	return ".fx";
}

/////////////////////////////////////////////////////////////
/// Démarre le rendu de la scène
///
////////////////////////////////////////////////////////////
void DX9Renderer::BeginScene()
{
    //DXCheck(m_Device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
	//	ConvertColor(CColor::CornflowerBlue), 1.0f, 0x00));
    DXCheck(m_Device->BeginScene());
}


/////////////////////////////////////////////////////////////
/// Termine le rendu de la scène
///
////////////////////////////////////////////////////////////
void DX9Renderer::EndScene()
{
	HRESULT hr;

    DXCheck(m_Device->EndScene());
    DXCheck((hr = m_Device->Present(nullptr, nullptr, nullptr, nullptr)));

	if (hr == D3DERR_DEVICELOST)
	{
		SetDeviceLost();
	}
}

/**
 * 
 */
void DX9Renderer::Clear(unsigned int flags)
{
	unsigned int f = 0;

	if ((flags & RenderParameter::Color) == RenderParameter::Color)
	{
		f |= D3DCLEAR_TARGET;
	}

	if ((flags & RenderParameter::ZBuffer) == RenderParameter::ZBuffer)
	{
		f |= D3DCLEAR_ZBUFFER;
	}

	if ((flags & RenderParameter::Stencil) == RenderParameter::Stencil)
	{
		f |= D3DCLEAR_STENCIL;
	}

	DXCheck(m_Device->Clear(0, nullptr, f,
		ConvertColor(GetClearColor()), 1.0f, 0x00));
}



/**
 * Create a vertex Buffer
 * 
 * \param Size :   Nombre d'éléments
 * \param Stride : Taille d'un élément
 * \param Flags :  Options de création
 * 
 * \return Pointeur sur le nouveau buffer
 * 
 */
IBufferBase* DX9Renderer::CreateVB(unsigned long Size, unsigned long Stride, unsigned long Flags) const
{
	LPDIRECT3DVERTEXBUFFER9 VertexBuffer;
    DXCheck(m_Device->CreateVertexBuffer(
		Size * Stride, 
		DX9Enum::BufferFlags(Flags), 0, D3DPOOL_DEFAULT, &VertexBuffer, nullptr));

    return NEW_AO DX9VertexBuffer(Size, VertexBuffer);
}

/**
 * Create a index Buffer
 * 
 * \param Size :   Nombre d'éléments
 * \param Stride : Taille d'un élément
 * \param Flags :  Options de création
 * 
 * \return Pointeur sur le nouveau buffer
 * 
 */
IBufferBase* DX9Renderer::CreateIB(unsigned long Size, unsigned long Stride, unsigned long Flags) const
{
    LPDIRECT3DINDEXBUFFER9 IndexBuffer;
    DXCheck((m_Device->CreateIndexBuffer(
		Size * Stride, 
		DX9Enum::BufferFlags(Flags), 
		Stride == 2 ? D3DFMT_INDEX16 : D3DFMT_INDEX32, D3DPOOL_DEFAULT, 
		&IndexBuffer, nullptr)));

    return NEW_AO DX9IndexBuffer(Size, IndexBuffer);
}



/////////////////////////////////////////////////////////////
/// Crée une déclaration de vertex
///
/// \param Elements : Description de la déclaration
/// \param Count :    Nombre d'éléments dans le tableau
///
/// \return Pointeur sur la déclaration créée
///
////////////////////////////////////////////////////////////
IDeclaration* DX9Renderer::CreateDeclaration(const DeclarationElement::TDeclarationElement* Elements, std::size_t Count) const
{
    // Création du tableau de D3DVERTEXELEMENT9 à partir des TDeclarationElement
    std::vector<D3DVERTEXELEMENT9> DxElements;
    std::vector<int> Offset(Count, 0);

    // Parcours des éléments de la déclaration et conversion en élément Dx9
    for (const DeclarationElement::TDeclarationElement* Elt = Elements; Elt < Elements + Count; ++Elt)
    {
        // Construction d'un élément temporaire
        D3DVERTEXELEMENT9 CurrentElement;

        // Stream, offset et méthode
		CurrentElement.Stream = static_cast<unsigned short>(Elt->Stream);
        CurrentElement.Offset = static_cast<unsigned short>(Offset[Elt->Stream]);
        CurrentElement.Method = D3DDECLMETHOD_DEFAULT;

        // Usage
        switch (Elt->Usage)
        {
            case DeclarationElement::Position :  CurrentElement.Usage = D3DDECLUSAGE_POSITION; CurrentElement.UsageIndex = 0; break;
            case DeclarationElement::Normal :    CurrentElement.Usage = D3DDECLUSAGE_NORMAL;   CurrentElement.UsageIndex = 0; break;
            case DeclarationElement::Diffuse :   CurrentElement.Usage = D3DDECLUSAGE_COLOR;    CurrentElement.UsageIndex = 0; break;
            case DeclarationElement::TexCoord0 : CurrentElement.Usage = D3DDECLUSAGE_TEXCOORD; CurrentElement.UsageIndex = 0; break;
            case DeclarationElement::TexCoord1 : CurrentElement.Usage = D3DDECLUSAGE_TEXCOORD; CurrentElement.UsageIndex = 1; break;
			case DeclarationElement::TexCoord2 : CurrentElement.Usage = D3DDECLUSAGE_TEXCOORD; CurrentElement.UsageIndex = 2; break;
			case DeclarationElement::TexCoord3 : CurrentElement.Usage = D3DDECLUSAGE_TEXCOORD; CurrentElement.UsageIndex = 3; break;
        }

        // Type et incrémentation de l'offset
        switch (Elt->DataType)
        {
            case DeclarationElement::Float1 : CurrentElement.Type = D3DDECLTYPE_FLOAT1;   Offset[Elt->Stream] += 4;  break;
            case DeclarationElement::Float2 : CurrentElement.Type = D3DDECLTYPE_FLOAT2;   Offset[Elt->Stream] += 8;  break;
            case DeclarationElement::Float3 : CurrentElement.Type = D3DDECLTYPE_FLOAT3;   Offset[Elt->Stream] += 12; break;
            case DeclarationElement::Float4 : CurrentElement.Type = D3DDECLTYPE_FLOAT4;   Offset[Elt->Stream] += 16; break;
            case DeclarationElement::Color :  CurrentElement.Type = D3DDECLTYPE_D3DCOLOR; Offset[Elt->Stream] += 4;  break;
        }

        // Ajout de l'élément courant
	    DxElements.push_back(CurrentElement);
    }

    // Ajout de l'élément marquant la fin du tableau
    D3DVERTEXELEMENT9 EndElement = D3DDECL_END();
	DxElements.push_back(EndElement);

    // Création de la déclaration
    LPDIRECT3DVERTEXDECLARATION9 Declaration = nullptr;
    DXCheck(m_Device->CreateVertexDeclaration(&DxElements[0], &Declaration));

    return NEW_AO DX9Declaration(Declaration);
}


/////////////////////////////////////////////////////////////
/// Change le vertex buffer courant
///
/// \param Stream :    Numéro du stream
/// \param Buffer :    Pointeur sur le buffer
/// \param Stride :    Taille des vertices
/// \param MinVertex : Indice de vertex minimum
/// \param MaxVertex : Indice de vertex maximum
///
////////////////////////////////////////////////////////////
void DX9Renderer::SetVB(unsigned int Stream, const IBufferBase* Buffer, unsigned long Stride, unsigned long MinVertex, unsigned long MaxVertex)
{
    // Récupération du buffer Dx
    const DX9VertexBuffer* VertexBuffer = static_cast<const DX9VertexBuffer*>(Buffer);

    // Envoi à l'API
    DXCheck(m_Device->SetStreamSource(Stream, VertexBuffer ? VertexBuffer->GetBuffer() : nullptr, 0, Stride));

    // Sauvegarde des MinVertex et VertexCount
    m_MinVertex   = MinVertex;
    m_VertexCount = MaxVertex - MinVertex + 1;
}


/////////////////////////////////////////////////////////////
/// Change l'index buffer courant
///
/// \param Buffer : Pointeur sur le buffer
/// \param Stride : Taille des indices
///
////////////////////////////////////////////////////////////
void DX9Renderer::SetIB(const IBufferBase* Buffer, unsigned long /*Stride*/)
{
    const DX9IndexBuffer* IndexBuffer = static_cast<const DX9IndexBuffer*>(Buffer);
    DXCheck(m_Device->SetIndices(IndexBuffer ? IndexBuffer->GetBuffer() : nullptr));
}


/////////////////////////////////////////////////////////////
/// Change la déclaration de vertex courante
///
/// \param Declaration : Nouvelle déclaration
///
////////////////////////////////////////////////////////////
void DX9Renderer::SetDeclaration(const IDeclaration* Declaration)
{
    // Récupération de la déclaration Dx
    const DX9Declaration* DxDeclaration = static_cast<const DX9Declaration*>(Declaration);

    // Envoi à l'API
    DXCheck(m_Device->SetVertexDeclaration(DxDeclaration ? DxDeclaration->GetDeclaration() : nullptr));
}


/////////////////////////////////////////////////////////////
/// Affiche des primitives
///
/// \param Type :        Type de primitives
/// \param FirstVertex : Position du premier vertex
/// \param Count :       Nombre de triangles
///
////////////////////////////////////////////////////////////
void DX9Renderer::DrawPrimitives(PrimitiveType::TPrimitiveType Type, unsigned long FirstVertex, unsigned long Count) const
{
    DXCheck(m_Device->DrawPrimitive(DX9Enum::Get(Type), FirstVertex, Count));
}


/////////////////////////////////////////////////////////////
/// Affiche des primitives indicées
///
/// \param Type :       Type de primitives
/// \param FirstIndex : Position du premier indice
/// \param Count :      Nombre de triangles
///
////////////////////////////////////////////////////////////
void DX9Renderer::DrawIndexedPrimitives(PrimitiveType::TPrimitiveType Type, unsigned long FirstIndex, unsigned long Count) const
{
    DXCheck(m_Device->DrawIndexedPrimitive(DX9Enum::Get(Type), 0, m_MinVertex, m_VertexCount, FirstIndex, Count));
}

/////////////////////////////////////////////////////////////
/// Affiche des primitives
///
/// \param Type :        Type de primitives
/// \param FirstVertex : Position du premier vertex
/// \param Count :       Nombre de triangles
///
////////////////////////////////////////////////////////////
void DX9Renderer::DrawPrimitivesInstanced(PrimitiveType::TPrimitiveType Type, unsigned long FirstVertex, unsigned long Count, unsigned long /*nbElt_*/) const
{
	DXCheck(m_Device->DrawPrimitive(DX9Enum::Get(Type), FirstVertex, Count));
}


/////////////////////////////////////////////////////////////
/// Affiche des primitives indicées
///
/// \param Type :       Type de primitives
/// \param FirstIndex : Position du premier indice
/// \param Count :      Nombre de triangles
///
////////////////////////////////////////////////////////////
void DX9Renderer::DrawIndexedPrimitivesInstanced(PrimitiveType::TPrimitiveType Type, unsigned long FirstIndex, unsigned long Count, unsigned long /*nbElt_*/) const
{
	DXCheck(m_Device->DrawIndexedPrimitive(DX9Enum::Get(Type), 0, m_MinVertex, m_VertexCount, FirstIndex, Count));
}


/////////////////////////////////////////////////////////////
/// Empile la matrice courante
///
/// \param Type : Type de la matrice
///
////////////////////////////////////////////////////////////
/*void DX9Renderer::PushMatrix(MatrixType::TMatrixType Type)
{
    m_Matrices[Type].push_back(m_Matrices[Type].back());
}


/////////////////////////////////////////////////////////////
/// Dépile la matrice en haut de la pile
///
/// \param Type : Type de la matrice
///
////////////////////////////////////////////////////////////
void DX9Renderer::PopMatrix(MatrixType::TMatrixType Type)
{
    m_Matrices[Type].pop_back();

    DXCheck(m_Device->SetTransform(DX9Enum::Get(Type), (D3DMATRIX*)&m_Matrices[Type].back()));
}


/////////////////////////////////////////////////////////////
/// Charge une matrice
///
/// \param Type :   Type de la matrice
/// \param Matrix : Nouvelle matrice
///
////////////////////////////////////////////////////////////
void DX9Renderer::LoadMatrix(MatrixType::TMatrixType Type, const Matrix4& Matrix)
{
    m_Matrices[Type].back() = Matrix;

    DXCheck(m_Device->SetTransform(DX9Enum::Get(Type), (D3DMATRIX*)&Matrix));
}


/////////////////////////////////////////////////////////////
/// Charge une matrice en la multipliant avec la précédente
///
/// \param Type :   Type de la matrice
/// \param Matrix : Nouvelle matrice
///
////////////////////////////////////////////////////////////
void DX9Renderer::LoadMatrixMult(MatrixType::TMatrixType Type, const Matrix4& Matrix)
{
    m_Matrices[Type].back() = Matrix * m_Matrices[Type].back();

    DXCheck(m_Device->SetTransform(DX9Enum::Get(Type), (D3DMATRIX*)&m_Matrices[Type].back()));
}


/////////////////////////////////////////////////////////////
/// Récupère la matrice courante
///
/// \param  Type :   Type de la matrice
/// \param Matrix : Matrice de destination
///
////////////////////////////////////////////////////////////
void DX9Renderer::GetMatrix(MatrixType::TMatrixType Type, Matrix4& Matrix) const
{
    Matrix = m_Matrices[Type].back();
}*/


/////////////////////////////////////////////////////////////
/// Convertit une couleur dans le format pris en charge par l'API
///
/// \param Color : Couleur à convertir
///
/// \return Couleur convertie sous forme d'unsigned long
///
////////////////////////////////////////////////////////////
unsigned long DX9Renderer::ConvertColor(const CColor& Color) const
{
    return Color.ToARGB();
}


/////////////////////////////////////////////////////////////
/// Change une texture
///
/// \param Unit :    Unité de texture
/// \param Texture : Nouvelle texture
///
////////////////////////////////////////////////////////////
void DX9Renderer::SetTexture(unsigned int Unit, const ITextureBase* Texture) const
{
    const DX9Texture* DxTexture = static_cast<const DX9Texture*>(Texture);
    DXCheck(m_Device->SetTexture(Unit, DxTexture ? DxTexture->GetDxTexture() : nullptr));
}


/////////////////////////////////////////////////////////////
/// Crée une nouvelle texture
///
/// \param Size :   Taille de la texture
/// \param Format : Format de pixel de la texture
/// \param Flags :  Options de création
///
/// \return Pointeur sur la texture créée
///
////////////////////////////////////////////////////////////
ITextureBase* DX9Renderer::CreateTexture(
	const Vector2I& Size, 
	const PixelFormat::TPixelFormat Format,
	const unsigned char *data_,
	const unsigned long Flags) const
{
    // Détection du nombre de niveaux de mips et du mipmapping automatique
    bool HasMipmaps  = (Flags & TEX_NOMIPMAP) != 0;
    bool AutoMipmaps = HasCapability(Capability::HardwareMipmapping) &&
                       DXCheck(m_Direct3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8,
                                                     D3DUSAGE_AUTOGENMIPMAP, D3DRTYPE_TEXTURE,
                                                     DX9Enum::Get(Format))) == D3D_OK;

    // Ajustement de l'usage
    unsigned long Usage = AutoMipmaps ? D3DUSAGE_AUTOGENMIPMAP : 0;

    // Création de la texture Dx9
    LPDIRECT3DTEXTURE9 Texture = nullptr;
    DXCheck((D3DXCreateTexture(m_Device, Size.x, Size.y, 0, Usage, DX9Enum::Get(Format), D3DPOOL_MANAGED, &Texture)));
    return NEW_AO DX9Texture(Size, Format, HasMipmaps, AutoMipmaps, Texture, data_);
}


/**
 * 
 */
void DX9Renderer::SetTextureWrap(const unsigned long Flags) const
{
	if (Flags & TEX_CLAMP )
	{
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_ADDRESSU,  D3DTADDRESS_CLAMP));
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_ADDRESSV,  D3DTADDRESS_CLAMP));
	}
	else if (Flags & TEX_BORDER )
	{
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_ADDRESSU,  D3DTADDRESS_BORDER));
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_ADDRESSV,  D3DTADDRESS_BORDER));
	}
	else if (Flags & TEX_MIRROR )
	{
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_ADDRESSU,  D3DTADDRESS_MIRROR));
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_ADDRESSV,  D3DTADDRESS_MIRROR));	
	}
	else if (Flags & TEX_REPEAT )
	{
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_ADDRESSU,  D3DTADDRESS_WRAP));
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_ADDRESSV,  D3DTADDRESS_WRAP));
	}
	else if (Flags & TEX_MIRROR_ONCE )
	{
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_ADDRESSU,  D3DTADDRESS_MIRRORONCE));
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_ADDRESSV,  D3DTADDRESS_MIRRORONCE));
	}
}

/**
 * 
 */
void DX9Renderer::SetTextureFilter(const unsigned long Flags) const
{
	if (Flags & TEX_FILTER_0 )
	{
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT));
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT));
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT)); // D3DTEXF_NONE ?
	}
	else if (Flags & TEX_FILTER_1 )
	{
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT));
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT));
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR));
	}
	else if (Flags & TEX_FILTER_2 )
	{
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR));
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR));
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT));
	}
	else if (Flags & TEX_FILTER_3 )
	{
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR));
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR));
		DXCheck(m_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR));
	}
}

/**
 * 
 */
void DX9Renderer::SetTextureAnisotropic(const unsigned long Flags) const
{
	int value = 0;

	if (Flags & TEX_ANISOTROPY_1 )
	{
		value = 1;
	}
	else if (Flags & TEX_ANISOTROPY_2)
	{
		value = 2;
	}
	else if (Flags & TEX_ANISOTROPY_4)
	{
		value = 4;
	}
	else if (Flags & TEX_ANISOTROPY_8)
	{
		value = 8;
	}
	else if (Flags & TEX_ANISOTROPY_16)
	{
		value = 16;
	}

	DXCheck(m_Device->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, value));
}



/////////////////////////////////////////////////////////////
/// Paramètre l'alpha-blending
///
/// \param Src :  Paramètre source
/// \param Dest : Paramètre destination
///
////////////////////////////////////////////////////////////
void DX9Renderer::SetupAlphaBlending(Blend::TBlend Src, Blend::TBlend Dest) const
{
	DXCheck(m_Device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, FALSE));
    DXCheck(m_Device->SetRenderState(D3DRS_SRCBLEND,  DX9Enum::Get(Src)));
    DXCheck(m_Device->SetRenderState(D3DRS_DESTBLEND, DX9Enum::Get(Dest)));
}

/**
 * 
 */
void DX9Renderer::SetupAlphaBlending(Blend::TBlend Src, Blend::TBlend SrcAlpha, Blend::TBlend Dest, Blend::TBlend DestAlpha) const
{
	DXCheck(m_Device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE));
	DXCheck(m_Device->SetRenderState(D3DRS_SRCBLEND,  DX9Enum::Get(Src)));
	DXCheck(m_Device->SetRenderState(D3DRS_SRCBLENDALPHA, DX9Enum::Get(SrcAlpha)));
	DXCheck(m_Device->SetRenderState(D3DRS_DESTBLEND, DX9Enum::Get(Dest)));
	DXCheck(m_Device->SetRenderState(D3DRS_DESTBLENDALPHA, DX9Enum::Get(DestAlpha)));
}

/////////////////////////////////////////////////////////////
/// Paramètre les opérations d'une unité de texture
///
/// \param Unit : Unité de texture
/// \param Op :   Opérateur
/// \param Arg1 : Argument 1
/// \param Arg2 : Argument 2
/// \param Constant : Constante, dans le cas où un argument est TXA_CONSTANT
///
////////////////////////////////////////////////////////////
void DX9Renderer::SetupTextureUnit(unsigned int Unit, TextureOperation::TTextureOp Op, TTextureArg Arg1, TTextureArg Arg2, const CColor& Constant) const
{
    // Opérateur et arguments
    if (Op < TextureOperation::AlphaFirstArg)
    {
        DXCheck(m_Device->SetTextureStageState(Unit, D3DTSS_COLOROP,   DX9Enum::Get(Op)));
        DXCheck(m_Device->SetTextureStageState(Unit, D3DTSS_COLORARG1, DX9Enum::Get(Arg1)));
        DXCheck(m_Device->SetTextureStageState(Unit, D3DTSS_COLORARG2, DX9Enum::Get(Arg2)));
    }
    else
    {
        DXCheck(m_Device->SetTextureStageState(Unit, D3DTSS_ALPHAOP,   DX9Enum::Get(Op)));
        DXCheck(m_Device->SetTextureStageState(Unit, D3DTSS_ALPHAARG1, DX9Enum::Get(Arg1)));
        DXCheck(m_Device->SetTextureStageState(Unit, D3DTSS_ALPHAARG2, DX9Enum::Get(Arg2)));
    }

    // Constante
    if ((Arg1 == TXA_CONSTANT) || (Arg2 == TXA_CONSTANT))
    {
        DXCheck(m_Device->SetRenderState(D3DRS_TEXTUREFACTOR, ConvertColor(Constant)));
    }
}

//----------------------------------------------------------
// define the scissor box
//----------------------------------------------------------
void DX9Renderer::SetScissorRect(const CRectangle* pRect_)
{
	RECT rect;
	rect.left = pRect_->Left();
	rect.top = pRect_->Top();
	rect.right = pRect_->Right();
	rect.bottom = pRect_->Bottom();

	DXCheck(m_Device->SetScissorRect(&rect)); 
}

//----------------------------------------------------------
// Get the scissor box
//----------------------------------------------------------
void DX9Renderer::GetScissorRect(CRectangle *pRect_) const
{
	CA_ASSERT(pRect_ != nullptr, "DX9Renderer::GetScissorRect()");

	RECT rect;
	DXCheck(m_Device->GetScissorRect(&rect) );

	pRect_->Set(rect.left, rect.top, rect.right - rect.left, rect.top - rect.bottom);
}

/////////////////////////////////////////////////////////////
/// Active / désactive un paramètre de rendu
///
/// \param Param : Paramètre de rendu
/// \param Value : Valeur (actif / inactif)
///
////////////////////////////////////////////////////////////
void DX9Renderer::Enable(RenderParameter::TRenderParameter Param, unsigned int Value) const
{
	switch (Param)
	{
	case RenderParameter::CullFace:
		switch(Value)
		{
		case RenderParameter::CULLFACE_NONE:
			Value = D3DCULL_NONE;
			break;

		case RenderParameter::CULLFACE_CW:
			Value = D3DCULL_CCW; // inverted relative to OpenGL
			break;

		case RenderParameter::CULLFACE_CCW:
			Value = D3DCULL_CW; // inverted relative to OpenGL
			break;
		}
		break;

	case RenderParameter::StencilFail :
	case RenderParameter::StencilZFail :
	case RenderParameter::StencilPass :	
		Value = DX9Enum::Get(static_cast<RenderParameter::TStencilOperation>(Value));
		break;

	case RenderParameter::StencilFunc :
		Value = DX9Enum::Get(static_cast<TCompareFunction>(Value));
		break;
	}

    DXCheck(m_Device->SetRenderState(DX9Enum::Get(Param), Value));
}


////////////////////////////////////////////////////////////
/// Crée un shader à partir d'un programme Cg
///
/// \param Program : Programme Cg
/// \param Type :    Type du shader
///
/// \return Shader créé et chargé
///
////////////////////////////////////////////////////////////
IShaderBase* DX9Renderer::CreateShader(IFile *pFile_) const
{
	/*
	#define D3DXSHADER_DEBUG                          (1 << 0)
	#define D3DXSHADER_SKIPVALIDATION                 (1 << 1)
	#define D3DXSHADER_SKIPOPTIMIZATION               (1 << 2)
	#define D3DXSHADER_PACKMATRIX_ROWMAJOR            (1 << 3)
	#define D3DXSHADER_PACKMATRIX_COLUMNMAJOR         (1 << 4)
	#define D3DXSHADER_PARTIALPRECISION               (1 << 5)
	#define D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT        (1 << 6)
	#define D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT        (1 << 7)
	#define D3DXSHADER_NO_PRESHADER                   (1 << 8)
	#define D3DXSHADER_AVOID_FLOW_CONTROL             (1 << 9)
	#define D3DXSHADER_PREFER_FLOW_CONTROL            (1 << 10)
	#define D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY (1 << 12)
	#define D3DXSHADER_IEEE_STRICTNESS                (1 << 13)
	#define D3DXSHADER_USE_LEGACY_D3DX9_31_DLL        (1 << 16)


	// optimization level flags
	#define D3DXSHADER_OPTIMIZATION_LEVEL0            (1 << 14)
	#define D3DXSHADER_OPTIMIZATION_LEVEL1            0
	#define D3DXSHADER_OPTIMIZATION_LEVEL2            ((1 << 14) | (1 << 15))
	#define D3DXSHADER_OPTIMIZATION_LEVEL3            (1 << 15)
	 */

	//LPDIRECT3DVERTEXSHADER9         vertexShader   = nullptr; // VS
	//LPDIRECT3DPIXELSHADER9          pixelShader    = nullptr; // PS

	LPD3DXEFFECT pEffect;
	SmartPtr<ID3DXBuffer, CResourceCOM> pErrMsg;
	DWORD dwShaderFlags = 0;

	//dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
	//dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
	//dwShaderFlags |= D3DXSHADER_NO_PRESHADER;
	dwShaderFlags |= D3DXSHADER_DEBUG;
	dwShaderFlags |= D3DXSHADER_SKIPOPTIMIZATION;

	LPCVOID pBuffer = pFile_->GetBuffer();

	HRESULT hr = DXCheck( D3DXCreateEffect(
		m_Device,
		pBuffer, 
		pFile_->GetBufferLength(),
		nullptr, //CONST D3DXMACRO* pDefines,
		nullptr, // LPD3DXINCLUDE pInclude,
		dwShaderFlags,
		nullptr, // LPD3DXEFFECTPOOL
		&pEffect,
		&GetPtr(pErrMsg) ));

	/*HRESULT hr = DXCheck( D3DXCreateEffectFromFile(
		m_Device,
		fileName_.c_str(),
		nullptr, //CONST D3DXMACRO* pDefines,
		nullptr, // LPD3DXINCLUDE pInclude,
		dwShaderFlags,
		nullptr, // LPD3DXEFFECTPOOL
		&pEffect,
		&GetPtr(pErrMsg) ));*/

	if(FAILED(hr))
	{
		char *ErrMsg = (char *)(pErrMsg ? pErrMsg->GetBufferPointer() : DXGetErrorDescription(hr));
		CA_ERROR(ErrMsg);
		return nullptr;
	}

    return NEW_AO DX9Shader(pEffect);
}


////////////////////////////////////////////////////////////
/// Change le vertex shader courant
///
/// \param Shader : Nouveau shader
///
////////////////////////////////////////////////////////////
/*void DX9Renderer::SetVertexShader(const IShaderBase* Shader)
{
    const DX9Shader* DxShader = static_cast<const DX9Shader*>(Shader);

    if (DxShader)
    {
		throw CException("DX9IRenderer::Get().SetVertexShader : NotImplemented");

        //if (DxShader->GetType() != ShaderType::Vertex)
        //    throw CException("Type de shader incorrect : pixel shader reçu dans SetVertexShader");
				

		//DXCheck(m_Device->SetVertexShader(DxShader->Effect()) );
        //DXCheck(cgD3D9BindProgram(DxShader->GetProgram()));
    }
    else
    {
        DXCheck(m_Device->SetVertexShader(nullptr));
    }
}


////////////////////////////////////////////////////////////
/// Change le pixel shader courant
///
/// \param Shader : Nouveau shader
///
////////////////////////////////////////////////////////////
void DX9Renderer::SetPixelShader(const IShaderBase* Shader)
{
    const DX9Shader* DxShader = static_cast<const DX9Shader*>(Shader);

    if (DxShader)
    {
		throw CException("DX9IRenderer::Get().SetVertexShader : NotImplemented");

        //if (DxShader->GetType() != ShaderType::Pixel)
        //    throw CException("Type de shader incorrect : vertex shader reçu dans SetPixelShader");

        //DXCheck(cgD3D9BindProgram(DxShader->GetProgram()));
    }
    else
    {
        DXCheck(m_Device->SetPixelShader(nullptr));
    }
}*/


/**
 * 
 */
IEffect *DX9Renderer::CreateEffectFromShader(IShaderBase *pShader_) const
{
	DX9Shader *pDXShader = dynamic_cast<DX9Shader *>(pShader_);

	CA_ASSERT(pDXShader != nullptr, "DX9Renderer::CreateEffectFromShader() is nullptr");

	DX9Effect *pEffect = NEW_AO DX9Effect();
	pEffect->CreatePassFromShader(pDXShader);
	return pEffect; 
}

/**
 * TODO : Delete
 */
IDirect3DDevice9* DX9Renderer::GetDevice() const
{
	return m_Device;
}

/**
 * 
 */
TextureTarget* DX9Renderer::CreateTextureTarget(const Vector2I &size, PixelFormat::TPixelFormat format )
{
	return NEW_AO DX9RenderTargetTexture(size, format);
}

/**
 * 
 */
void DX9Renderer::Resize(unsigned int width_, unsigned height_)
{
	CA_UNUSED(width_, height_)
	/*/D3DVIEWPORT9 dx9vp;
	m_Device->GetViewport(&dx9vp);
	dx9vp.X = vp_.X();
	dx9vp.Y = vp_.Y();
	dx9vp.Width = vp_.Width();
	dx9vp.Height = vp_.Height();
	dx9vp.MinZ = vp_.NearClipPlane();
	dx9vp.MaxZ = vp_.FarClipPlane();
	m_Device->SetViewport(&dx9vp);*/
}

/**
 * 
 */
Viewport DX9Renderer::GetViewport() const
{
	D3DVIEWPORT9 dx9vp;
	m_Device->GetViewport(&dx9vp);
	Viewport vp;
	vp.X(static_cast<float>(dx9vp.X));
	vp.Y(static_cast<float>(dx9vp.Y));
	vp.Width(static_cast<float>(dx9vp.Width));
	vp.Height(static_cast<float>(dx9vp.Height));
	vp.NearClipPlane(dx9vp.MinZ);
	vp.FarClipPlane(dx9vp.MaxZ);

	return vp;
}

/**
 * 
 */
void DX9Renderer::SetViewport(const Viewport &vp_)
{
	//CA_TRACE("Viewport %f %f %f %f\n", 
	//	vp_.X(), vp_.Y(), vp_.Width(), vp_.Height());

	D3DVIEWPORT9 dx9vp;
	dx9vp.X = static_cast<DWORD>(vp_.X());
	dx9vp.Y = static_cast<DWORD>(vp_.Y());
	dx9vp.Width = static_cast<DWORD>(vp_.Width());
	dx9vp.Height = static_cast<DWORD>(vp_.Height());
	dx9vp.MinZ = 0.0f;
	dx9vp.MaxZ = 1.0f;
	DXCheck(m_Device->SetViewport(&dx9vp));
}

} // namespace CasaEngine
