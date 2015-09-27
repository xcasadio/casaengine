
#include "Base.h"

#include "VertexType.h"


namespace CasaEngine
{
	bgfx::VertexDecl VertexPositionColor::ms_decl;
	void VertexPositionColor::init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,	3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,		4, bgfx::AttribType::Uint8, true)
			.end();
	};

	bgfx::VertexDecl VertexPositionTexture::ms_decl;
	void VertexPositionTexture::init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,	3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0,	2, bgfx::AttribType::Float)
			.end();
	};

	bgfx::VertexDecl VertexPositionColorTexture::ms_decl;
	void VertexPositionColorTexture::init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,	3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0,	2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,		4, bgfx::AttribType::Uint8, true)
			.end();
	};

	bgfx::VertexDecl VertexPositionNormalTexture::ms_decl;
	void VertexPositionNormalTexture::init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,	3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal,		3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0,	2, bgfx::AttribType::Float)
			.end();
	};

	bgfx::VertexDecl VertexPositionColorNormalTexture::ms_decl;
	void VertexPositionColorNormalTexture::init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,	3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal,		3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0,	2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,		4, bgfx::AttribType::Uint8, true)
			.end();
	};

} // namespace CasaEnngine

