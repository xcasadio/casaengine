#include "Base.h"

#include "Program.h"
#include "Shader.h"

namespace CasaEngine
{

/**
 * 
 */
Program *Program::loadProgram(const char* _vsName, const char* _fsName)
{
	Shader *pVs = Shader::loadShader(_vsName);
	Shader *pFs = Shader::loadShader(_fsName);
	return NEW_AO Program(bgfx::createProgram(pVs->Handle(), pFs->Handle(), false));
}

/**
 *  
 */
void Program::SetParameter(const char *pName, float Value)
{
    
}

/**
 *  
 */
void Program::SetParameter(const char *pName, const Vector2F& Value)
{
    
}

/**
 *  
 */
void Program::SetParameter(const char *pName, const Vector3F& Value)
{
    
}

/**
 *  
 */
void Program::SetParameter(const char *pName, const Vector4F& Value)
{
    
}

/**
 *  
 */
void Program::SetParameter(const char *pName, const Matrix4& Value)
{
    
}

/**
 *  
 */
void Program::SetParameter(const char *pName, const CColor& Value)
{
    
}


/**
 * 
 */
Program::Program(bgfx::ProgramHandle handle_)
{
	m_Handle = handle_;
}

/**
 * 
 */
Program::~Program()
{
	bgfx::destroyProgram(m_Handle);
}

/**
 * 
 */
bgfx::ProgramHandle Program::Handle() const
{
	return m_Handle;
}

} // namespace CasaEngine
