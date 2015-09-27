
#include "Base.h"
#include "GLEffect.h"
#include "Graphics\Model\Model.h"
#include "GLEffectPass.h"
#include "GLShader.h"
#include "CA_Assert.h"
#include "GLMacro.h"
#include "Graphics\Effects\IEffectPass.h"

namespace CasaEngine
{

	/**
	 *
	 */
	GLEffect::GLEffect() :
		m_pShader(nullptr)
	{
		
	}

	/**
	 *
	 */
	GLEffect::~GLEffect()
	{
	}

	/**
	 * 
	 */
	void GLEffect::Begin()
	{
		
	}

	/**
	 * 
	 */
	void GLEffect::End()
	{
		
	}

	/**
	 * Call this function with the right order
	 */	
	void GLEffect::AddPass(GLShader *pShader_)
	{
		IEffect::AddPass(NEW_AO GLEffectPass(this, pShader_));
	}

	/**
	 * 
	 */
	GLShader * GLEffect::GetShader() const
	{
		return m_pShader;
	}

} // namespace CasaEngine
