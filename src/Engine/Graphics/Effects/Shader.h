#ifndef SHADER_H
#define SHADER_H

#include "CA_Export.h"
#include <bgfx/bgfx.h>

namespace CasaEngine
{
	class CA_EXPORT Shader
	{
	public:
		static Shader* loadShader(const char* name_);

	public:
		Shader(bgfx::ShaderHandle handle_);
		virtual ~Shader();
		bgfx::ShaderHandle Handle() const;

	private:
		bgfx::ShaderHandle m_Handle;
	};
}

#endif
