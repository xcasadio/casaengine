#pragma once

#include "CA_Export.hpp"

#include  "Graphics/Textures/Texture.hpp"
#include  "Graphics/Materials/Material.hpp"
#include  "Graphics/Vertices/VertexType.hpp"
#include  "Maths/Matrix4.hpp"

#include <bgfx/bgfx.h>

namespace CasaEngine
{
	class CA_EXPORT Mesh
	{
	public:
		Mesh(const VertexPositionNormalTexture* Vertices, unsigned long VerticesCount,
			const unsigned short* Indices = nullptr, unsigned long IndicesCount = 0);
		~Mesh();

		Material* GetMaterial() const;
		void SetMaterial(Material* val);

		void Render(bgfx::ProgramHandle handle_, Matrix4& matWorld_) const;

	private:
		static Texture* m_pDefaultTexture; // default texture if no material

		bgfx::ProgramHandle m_Program;
		bgfx::UniformHandle m_TextureUniform;
		bgfx::VertexBufferHandle m_VertexBuffer;
		bgfx::IndexBufferHandle m_IndexBuffer;
		bgfx::UniformHandle m_TextureRepetitionUniform;
		Material* m_pMaterial;
	};
}
