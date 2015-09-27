#include "Base.h"

#include "Maths/Matrix4.h"
#include "Graphics/Mesh/Mesh.h"
#include "Graphics/Renderer/Renderer.h"
#include "Exceptions.h"

#include <string>

#include "Resources/ResourceManager.h"
#include "Log/LogManager.h"
#include "Log/LogVerbose.h"
#include "CA_Assert.h"
#include "Graphics/bgfx_utils.h"


namespace CasaEngine
{

Texture *Mesh::m_pDefaultTexture = nullptr;

// bgfx::TextureHandle genMissingTexture(uint32_t _width, uint32_t _height, float _lineWidth = 0.02f)
// {
// 	const bgfx::Memory* mem = bgfx::alloc(_width*_height*4);
// 	uint32_t* bgra8 = (uint32_t*)mem->data;
// 
// 	const float sx = 0.70710677f;
// 	const float cx = 0.70710677f;
// 
// 	for (uint32_t yy = 0; yy < _height; ++yy)
// 	{
// 		for (uint32_t xx = 0; xx < _width; ++xx)
// 		{
// 			float px = xx / float(_width)  * 2.0f - 1.0f;
// 			float py = yy / float(_height) * 2.0f - 1.0f;
// 
// 			float sum = bx::fpulse(px * cx - py * sx, _lineWidth, -_lineWidth)
// 				+ bx::fpulse(px * sx + py * cx, _lineWidth, -_lineWidth)
// 				;
// 			*bgra8++ = sum >= 1.0f ? 0xffff0000 : 0xffffffff;
// 		}
// 	}
// 
// 	return bgfx::createTexture2D(uint16_t(_width), uint16_t(_height), 0, bgfx::TextureFormat::BGRA8, 0, mem);
// }

/**
 * 
 */
Mesh::Mesh(const VertexPositionNormalTexture* Vertices, unsigned long VerticesCount, const unsigned short* Indices, unsigned long IndicesCount) :
	m_pMaterial(nullptr)
{
	if (m_pDefaultTexture == nullptr)
	{
		//Todo : create it programmatically
		m_pDefaultTexture = Texture::loadTexture("checkboard.dds", BGFX_TEXTURE_NONE);
	}

    CA_ASSERT(Vertices != nullptr, "Mesh::Mesh() : Vertices is nullptr");
    CA_ASSERT(Indices != nullptr, "Mesh::Mesh() : Indices is nullptr");

	m_VertexBuffer = bgfx::createVertexBuffer(
		bgfx::makeRef((uint8_t *)Vertices, VerticesCount * sizeof(VertexPositionNormalTexture)), 
		VertexPositionNormalTexture::ms_decl);

	m_IndexBuffer = bgfx::createIndexBuffer(
		bgfx::makeRef((uint8_t *)Indices, IndicesCount * sizeof(short)));

	m_TextureRepitionUniform = bgfx::createUniform("u_texcoord0rep", bgfx::UniformType::Vec4);
	m_TextureUniform = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);	

	const char *materialName = "internal_default_material";
	m_pMaterial = ResourceManager::Instance().Get<Material>(materialName);

	if (nullptr == m_pMaterial)
	{
		m_pMaterial = NEW_AO Material();
		m_pMaterial->Texture0(m_pDefaultTexture);
		ResourceManager::Instance().Add(materialName, m_pMaterial);
	}
}

/**
 * 
 */
Mesh::~Mesh()
{
	if (nullptr != m_pMaterial)
	{
		m_pMaterial->Release();
	}

	bgfx::destroyIndexBuffer(m_IndexBuffer);
	bgfx::destroyVertexBuffer(m_VertexBuffer);
}

/**
 * 
 */
Material* Mesh::GetMaterial() const
{
	return m_pMaterial;
}

/**
 * 
 */
void Mesh::SetMaterial(Material* val)
{
// 	if (nullptr != m_pMaterial)
// 	{
// 		m_pMaterial->Release();
// 	}

	m_pMaterial = val;
}

/**
 * 
 */
void Mesh::Render(bgfx::ProgramHandle handle_, Matrix4 &matWorld_) const
{
	bgfx::setTransform(matWorld_);

	bgfx::setVertexBuffer(m_VertexBuffer);
	bgfx::setIndexBuffer(m_IndexBuffer);

	bgfx::TextureHandle texture = m_pMaterial->Texture0() != nullptr ? m_pMaterial->Texture0()->Handle() : m_pDefaultTexture->Handle();
	bgfx::setTexture(0, m_TextureUniform, bgfx::isValid(texture) ? texture : m_pDefaultTexture->Handle());

	bgfx::setUniform(m_TextureRepitionUniform,  Vector4F(m_pMaterial->Texture0Repeat().x, m_pMaterial->Texture0Repeat().y, 1.0f, 1.0f));
	bgfx::setState(BGFX_STATE_DEFAULT);
	bgfx::submit(0, handle_);
}

} // namespace CasaEngine
