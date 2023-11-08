#pragma once

#include  "Maths/Vector2.hpp"
#include  "Maths/Vector3.hpp"
#include  "Maths/Vector4.hpp"
#include  "Graphics/Color.hpp"
#include "CA_Export.hpp"

#include  "Maths/Matrix4.hpp"
#include  "Graphics/Textures/Texture.hpp"
#include <bgfx/bgfx.h>
#include  "Shader.hpp"

namespace CasaEngine
{
	class CA_EXPORT Program
	{
	public:
		Program(const char* _vsName, const char* _fsName);
		Program(bgfx::ProgramHandle handle_);

		virtual ~Program();

		void SetParameter(const char* pName, float Value);
		void SetParameter(const char* pName, const Vector2& Value);
		void SetParameter(const char* pName, const Vector3& Value);
		void SetParameter(const char* pName, const Vector4& Value);
		void SetParameter(const char* pName, const Matrix4& Value);
		void SetParameter(const char* pName, const Color& Value);
		void SetParameter(const char* pName, const Texture* Value);

		bgfx::ProgramHandle Handle() const;

	private:
		bgfx::ProgramHandle m_Handle;
		Shader* m_pVs, * m_pFs;
	};
}
