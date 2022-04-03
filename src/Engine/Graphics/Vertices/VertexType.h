#ifndef VERTEXTYPE_H_
#define VERTEXTYPE_H_

#include "CA_Export.h"

#include "Maths/Vector3.h"
#include "Maths/Vector2.h"
#include "Memory/MemoryAllocation.h"
#include <bgfx/bgfx.h>

namespace CasaEngine
{
	struct CA_EXPORT VertexPositionColor :
		AllocatedObject<VertexPositionColor>
	{
		Vector3F     Position;  
		unsigned int Color;     

		static void init();
		static bgfx::VertexLayout ms_layout;
	};

	struct CA_EXPORT VertexPositionTexture :
		AllocatedObject<VertexPositionTexture>
	{
		Vector3F     Position;  
		Vector2F     TexCoords; 

		static void init();
		static bgfx::VertexLayout ms_layout;
	};

	struct CA_EXPORT VertexPositionColorTexture :
		AllocatedObject<VertexPositionColorTexture>
	{
		Vector3F     Position;  
		Vector2F     TexCoords; 
		unsigned int Color;     

		static void init();
		static bgfx::VertexLayout ms_layout;
	};

	struct CA_EXPORT VertexPositionNormalTexture :
		AllocatedObject<VertexPositionNormalTexture>
	{
		Vector3F     Position;  
		Vector3F     Normal;    
		Vector2F     TexCoords; 

		static void init();
		static bgfx::VertexLayout ms_layout;
	};

	struct CA_EXPORT VertexPositionColorNormalTexture :
		AllocatedObject<VertexPositionColorNormalTexture>
	{
		Vector3F     Position;  
		Vector3F     Normal;    
		Vector2F     TexCoords; 
		unsigned int Color{};   

		static void init();
		static bgfx::VertexLayout ms_layout;
	};
}

#endif
