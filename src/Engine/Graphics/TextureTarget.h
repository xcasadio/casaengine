#pragma once

#include "CA_Export.h"
#include "Textures/Texture.h"
#include "RenderTarget.h"

namespace CasaEngine
{
	class CA_EXPORT TextureTarget : public RenderTarget
	{
	public:
		 //virtual void Create(const Vector2I& Size, PixelFormat::TPixelFormat Format) = 0;
		virtual Texture* GetTexture() = 0;
	};
}
