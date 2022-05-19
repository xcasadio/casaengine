#pragma once

#include "CA_Export.h"

#include "Maths/Vector3.h"
#include "Maths/Vector2.h"

#include <bgfx/bgfx.h>

namespace CasaEngine
{
	struct CA_EXPORT VertexPositionColor
	{
		Vector3     Position;  
		unsigned int Color;     

		static void init();
		static bgfx::VertexLayout ms_layout;
	};

	struct CA_EXPORT VertexPositionTexture
	{
		Vector3     Position;  
		Vector2     TexCoords; 

		static void init();
		static bgfx::VertexLayout ms_layout;
	};

	struct CA_EXPORT VertexPositionColorTexture
	{
		Vector3     Position;  
		Vector2     TexCoords; 
		unsigned int Color;     

		static void init();
		static bgfx::VertexLayout ms_layout;
	};

	struct CA_EXPORT VertexPositionNormalTexture
	{
		Vector3     Position;  
		Vector3     Normal;    
		Vector2     TexCoords; 

		static void init();
		static bgfx::VertexLayout ms_layout;
	};

	struct CA_EXPORT VertexPositionColorNormalTexture
	{
		Vector3     Position;  
		Vector3     Normal;    
		Vector2     TexCoords; 
		unsigned int Color{};   

		static void init();
		static bgfx::VertexLayout ms_layout;
	};
}
