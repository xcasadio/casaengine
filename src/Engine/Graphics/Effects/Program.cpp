#include "Base.h"

#include "Program.h"
#include "Shader.h"

namespace CasaEngine
{
	void Program::SetParameter(const char* pName, float Value)
	{
	}

	void Program::SetParameter(const char* pName, const Vector2F& Value)
	{
	}

	void Program::SetParameter(const char* pName, const Vector3F& Value)
	{
	}

	void Program::SetParameter(const char* pName, const Vector4F& Value)
	{
	}

	void Program::SetParameter(const char* pName, const Matrix4& Value)
	{
	}

	void Program::SetParameter(const char* pName, const CColor& Value)
	{
	}

	Program::Program(const char* _vsName, const char* _fsName)
	{
		m_pVs = Shader::loadShader(_vsName);
		m_pFs = Shader::loadShader(_fsName);
		CA_ASSERT(m_pVs != nullptr, "Can't load the vertex shader '%s'", _vsName);
		CA_ASSERT(m_pFs != nullptr, "Can't load the fragment shader '%s'", _fsName);
		m_Handle = createProgram(m_pVs->Handle(), m_pFs->Handle(), false);
	}

	Program::Program(bgfx::ProgramHandle handle_)
	{
		m_Handle = handle_;
	}

	Program::~Program()
	{
		destroy(m_Handle);
		DELETE_AO m_pVs;
		DELETE_AO m_pFs;
	}

	bgfx::ProgramHandle Program::Handle() const
	{
		return m_Handle;
	}
}