
#include "Base.h"
#include "Graphics\Effects\IEffectPass.h"
#include "Graphics\Effects\IEffect.h"
#include "DX9Effect.h"
#include "DX9Macro.h"

namespace CasaEngine
{

	/**
	 *
	 */
	DX9EffectPass::DX9EffectPass(DX9Effect * pEffect_, unsigned int passNum_) :
		IEffectPass(pEffect_), 
		m_PassNum(passNum_)
	{
		m_pEffect =  pEffect_;
		IEffectPass::SetShader(pEffect_->GetShader());
	}

	/**
	 *
	 */
	DX9EffectPass::~DX9EffectPass()
	{
	}

	/**
	 * 
	 */
	void DX9EffectPass::Begin()
	{		
		DXCheck(m_pEffect->GetShader()->D3DXEffect()->BeginPass(m_PassNum));
	}

	/**
	 * 
	 */
	void DX9EffectPass::End()
	{
		DXCheck(m_pEffect->GetShader()->D3DXEffect()->EndPass());
	}

} // namespace CasaEngine
