#pragma once

#include "CA_Export.hpp"
#include  "Textures/Texture.hpp"
#include  "RenderTarget.hpp"

namespace CasaEngine
{
	class CA_EXPORT TextureTarget : public RenderTarget
	{
	public:
		 //virtual void Create(const Vector2I& Size, PixelFormat::TPixelFormat Format) = 0;
		virtual Texture* GetTexture() = 0;
	};
}
