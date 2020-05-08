
#ifndef _RenderTargetTexture_H_
#define _RenderTargetTexture_H_

#include "CA_Export.h"
#include "Maths/Vector3.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector2.h"
#include "Renderer/Enums.h"
#include "Textures/Texture.h"
#include "RenderTarget.h"
#include "Graphics/Textures/Texture.h"

namespace CasaEngine
{
	///
	class CA_EXPORT TextureTarget : public RenderTarget
	{
	public:
		/**
		 *
		 */
		//virtual void Create(const Vector2I& Size, PixelFormat::TPixelFormat Format) = 0;

		/**
		 * 
		 */
		virtual Texture *GetTexture() = 0;
	};

} 

#endif //_RenderTargetTexture_H_
