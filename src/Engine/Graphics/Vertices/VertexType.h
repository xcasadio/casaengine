#ifndef VERTEXTYPE_H_
#define VERTEXTYPE_H_

#include "CA_Export.h"

#include "Maths/Vector3.h"
#include "Maths/Vector2.h"
#include "Memory/MemoryAllocation.h"
#include <bgfx/bgfx.h>

namespace CasaEngine
{
	/**
	 *
	 */
	struct CA_EXPORT VertexPositionColor :
		public AllocatedObject<VertexPositionColor>
	{
		Vector3F     Position;  ///< Position
		unsigned int Color;     ///< ABGR

		static void init();
		static bgfx::VertexLayout ms_layout;
	};
	
	/**
	 *
	 */
	struct CA_EXPORT VertexPositionTexture :
		public AllocatedObject<VertexPositionTexture>
	{
		Vector3F     Position;  ///< Position
		Vector2F     TexCoords; ///< Coordonnées de texture

		static void init();
		static bgfx::VertexLayout ms_layout;
	};

	/**
	 *
	 */
	struct CA_EXPORT VertexPositionColorTexture :
		public AllocatedObject<VertexPositionColorTexture>
	{
		Vector3F     Position;  ///< Position		
		Vector2F     TexCoords; ///< Coordonnées de texture
		unsigned int Color;     ///< ABGR

		static void init();
		static bgfx::VertexLayout ms_layout;
	};
	
	/**
	 *
	 */
	struct CA_EXPORT VertexPositionNormalTexture :
		public AllocatedObject<VertexPositionNormalTexture>
	{
		Vector3F     Position;  ///< Position
		Vector3F     Normal;    ///< Vecteur normal
		Vector2F     TexCoords; ///< Coordonnées de texture

		static void init();
		static bgfx::VertexLayout ms_layout;
	};
	
	/**
	 *
	 */
	struct CA_EXPORT VertexPositionColorNormalTexture :
		public AllocatedObject<VertexPositionColorNormalTexture>
	{
		Vector3F     Position;  ///< Position
		Vector3F     Normal;    ///< Vecteur normal		
		Vector2F     TexCoords; ///< Coordonnées de texture
		unsigned int Color;     ///< ABGR

		static void init();
		static bgfx::VertexLayout ms_layout;
	};

}

#endif // VERTEXTYPE_H_
