
#include "Base.h"

#include "TextureTarget.h"
#include "Maths\Matrix4.h"
#include "Maths\Vector3.h"
#include "EngineInfo.h"

#include "Memory/DebugNew.h"
#include "Renderer/Renderer.h"

namespace CasaEngine
{
	/**
	 * 
	 */
	TargetTexture::TargetTexture() :
		m_pTexture(NULL)
	{
	}

	/**
	 * 
	 */
	const TargetTexture& TargetTexture::operator=( const TargetTexture& /*rsh_*/ )
	{
		return *this;
	}

	/**
	 * 
	 */
	TargetTexture::~TargetTexture()
	{
		delete m_pTexture;
	}

	/**
	 *
	 */
	void TargetTexture::Create(const Vector2I& Size, PixelFormat::TPixelFormat Format)
	{
		m_pTexture = IRenderer::Get().CreateTexture(Size, Format);

	}

	/**
	 * 
	 */
	void TargetTexture::Activate()
	{
		m_pOldRenderTarget = IRenderer::Get().GetRenderTarget();
		IRenderer::Get().SetRenderTarget(this);
	}

	/**
	 * 
	 */
	void TargetTexture::Deactivate()
	{
		IRenderer::Get().SetRenderTarget(m_pOldRenderTarget);
	}

	/**
	 * 
	 */
	ITextureBase *TargetTexture::GetTexture()
	{
		return m_pTexture;
	}

	/**
	 * 
	 */
	bool TargetTexture::IsImageryCache() const
	{

	}

} // namespace CasaEngine
