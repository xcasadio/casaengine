
#include "DX9RenderTargetTexture.h"
#include "DX9Enum.h"
#include "DX9Exception.h"
#include "Graphics/PixelUtils.h"
#include "DX9Macro.h"
#include "CA_Assert.h"




namespace CasaEngine
{

DX9RenderTargetTexture::DX9RenderTargetTexture() :
	m_pSurface(nullptr),
	m_pDX9Texture(nullptr),
	m_pDirect3DTexture9(nullptr),
	m_pTexture(nullptr)
{
	CA_TRACE("DX9RenderTargetTexture(%p) created\n", this);
}

/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Size :        Dimensions de la texture
/// \param Format :      Format de pixel de la texture
/// \param HasMipmaps :  Indique si la texture a des niveaux de mip
/// \param AutoMipmaps : Indique si la texture peut générer ses mips en HW
/// \param Texture :     ID de la texture Dx
///
////////////////////////////////////////////////////////////
DX9RenderTargetTexture::DX9RenderTargetTexture(const Vector2I& Size, PixelFormat::TPixelFormat Format) :
	m_pSurface(nullptr),
	m_pDX9Texture(nullptr),
	m_pDirect3DTexture9(nullptr),
	m_pTexture(nullptr)
{
	CA_TRACE("DX9RenderTargetTexture(%p) created\n", this);
	Create(Size, Format);
}


DX9RenderTargetTexture::~DX9RenderTargetTexture()
{
	Release();
}


/////////////////////////////////////////////////////////////
/// Renvoie la texture Dx9
///
/// \return Pointeur sur la texture Dx9
///
////////////////////////////////////////////////////////////
IDirect3DTexture9* DX9RenderTargetTexture::GetDxTexture() const
{
    return m_pDirect3DTexture9;
}

/**
 * 
 */
void DX9RenderTargetTexture::Release()
{
	CA_TRACE("DX9RenderTargetTexture(%p) released\n", this);

	if (m_pSurface)
	{
		m_pSurface->Release();
		m_pSurface = nullptr;
	}

	if (m_pTexture)
	{
		// this will destroy m_pDX9Texture because it is a IResource
		DELETE_AO m_pTexture; 
		m_pTexture = nullptr;
	}
}

/**
 * 
 */
void DX9RenderTargetTexture::Create(const Vector2I& Size, PixelFormat::TPixelFormat Format)
{
	Release();

	CA_TRACE("DX9RenderTargetTexture(%p) initialized\n", this);

	DX9Renderer::Instance().GetDevice()->CreateTexture(static_cast<UINT>(Size.x),
                            static_cast<UINT>(Size.y),
                            1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
                            D3DPOOL_DEFAULT, &m_pDirect3DTexture9, 0);

    m_pDirect3DTexture9->GetSurfaceLevel(0, &m_pSurface);

	m_pDX9Texture = NEW_AO DX9Texture(Size, Format, false, false, m_pDirect3DTexture9);
	m_pTexture = NEW_AO Texture();
	m_pTexture->CreateFromTexture(m_pDX9Texture);

	SetArea(CRectangle(0, 0,  Size.x,  Size.y));
}

/**
 * 
 */
void DX9RenderTargetTexture::Activate()
{
	//CA_TRACE("DX9RenderTargetTexture(%p) activated\n", this);

	LPDIRECT3DSURFACE9 oldSurface = 0;
	DX9Renderer::Instance().GetDevice()->GetRenderTarget(0, &oldSurface);

	if (oldSurface && oldSurface != m_pSurface)
	{
		m_pPrevColourSurface = oldSurface;
		DX9Renderer::Instance().GetDevice()->SetRenderTarget(0, m_pSurface);
	}
	else if (oldSurface)
		oldSurface->Release();
}

/**
 * 
 */
void DX9RenderTargetTexture::Deactivate()
{
	//CA_TRACE("DX9RenderTargetTexture(%p) deactivated\n", this);

	DX9Renderer::Instance().GetDevice()->SetRenderTarget(0, m_pPrevColourSurface);

	if (m_pPrevColourSurface)
	{
		m_pPrevColourSurface->Release();
		m_pPrevColourSurface = 0;
	}
}

/**
 *
 */
Texture * DX9RenderTargetTexture::GetTexture()
{
	return m_pTexture;
}

/**
 * 
 */
bool DX9RenderTargetTexture::IsImageryCache() const
{
	return true;
}

/**
 * 
 */
bool DX9RenderTargetTexture::IsRenderingInverted() const
{
	return false;
}

} // namespace CasaEngine
