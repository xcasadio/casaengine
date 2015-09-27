
#include "Base.h"
#include "Graphics\Effects\IEffectPass.h"
#include "Graphics\Effects\IEffect.h"
#include "GLEffect.h"
#include "GLMacro.h"
#include "GLShader.h"

namespace CasaEngine
{

	/**
	 *
	 */
	GLEffectPass::GLEffectPass(GLEffect * pEffect_, GLShader *pShader_) :
		IEffectPass(pEffect_), 
		m_pShader(pShader_)
	{
		m_pEffect =  pEffect_;

		IEffectPass::SetShader(pShader_);
	}

	/**
	 *
	 */
	GLEffectPass::~GLEffectPass()
	{
	}

	/**
	 * 
	 */
	void GLEffectPass::Begin()
	{
		glUseProgram(m_pShader->ProgramID());
	}

	/**
	 * 
	 */
	void GLEffectPass::End()
	{
		glUseProgram(0);
		//Do nothing ?
	}

} // namespace CasaEngine
