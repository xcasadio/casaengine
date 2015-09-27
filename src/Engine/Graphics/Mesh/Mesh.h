#ifndef MESH_H
#define MESH_H

#include "CA_Export.h"

#include "Resources/Resource.h"


#include "Graphics/Textures/Texture.h"

#include "Maths/Vector2.h"
#include "Maths/Vector3.h"
#include "Graphics/Materials/Material.h"

#include "Graphics/Vertices/VertexType.h"
#include "bgfx.h"
#include "Maths/Matrix4.h"


namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    /// Classe manipulant les modèles
    ////////////////////////////////////////////////////////////
    class CA_EXPORT Mesh :
		public IResource
    {
    public :

        /**
         * 
         */
        Mesh(const VertexPositionNormalTexture* Vertices, unsigned long VerticesCount, 
			const unsigned short* Indices = nullptr, unsigned long IndicesCount = 0);

		/**
		 * 
		 */
		~Mesh();

		/**
		 * 
		 */
		Material* GetMaterial() const;

		/**
		 * 
		 */
		void SetMaterial(Material* val);

        /**
         * 
         */
        void Render(bgfx::ProgramHandle handle_, Matrix4 &matWorld_) const;

    private :
		static Texture *m_pDefaultTexture; // default texture if no material

		bgfx::ProgramHandle m_Program;
		bgfx::UniformHandle m_TextureUniform;
        bgfx::VertexBufferHandle m_VertexBuffer;
        bgfx::IndexBufferHandle m_IndexBuffer;
		bgfx::UniformHandle m_TextureRepitionUniform;
		Material* m_pMaterial;

	};

} // namespace CasaEngine


#endif // MESH_H
