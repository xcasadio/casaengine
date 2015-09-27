
#include "Base.h"
#include "DX9Effect.h"
#include "Graphics\Model\Model.h"
#include "DX9EffectPass.h"
#include "DX9Shader.h"
#include "Macro.h"
#include "DX9Macro.h"
#include "CA_Assert.h"

namespace CasaEngine
{

	/**
	 *
	 */
	DX9Effect::DX9Effect() :
		m_pShader(nullptr)
	{
		
	}

	/**
	 *
	 */
	DX9Effect::~DX9Effect()
	{
	}

	/**
	 * 
	 */
	void DX9Effect::Begin()
	{
		unsigned int passes = 0;
		DXCheck(m_pShader->D3DXEffect()->Begin(&passes, D3DXFX_DONOTSAVESTATE ));
	}

	/**
	 * 
	 */
	void DX9Effect::End()
	{
		DXCheck(m_pShader->D3DXEffect()->End());
	}

	/**
	 * 
	 */	
	void DX9Effect::CreatePassFromShader(DX9Shader *pShader_)
	{
		CA_ASSERT(pShader_ != nullptr, "DX9Effect::CreatePassFromShader() is nullptr");

		m_pShader = pShader_;
		ID3DXEffect *pEffect = m_pShader->D3DXEffect();

		/*D3DXEFFECT_DESC *pDesc;
		DXCheck(pEffect->GetDesc(pDesc));
		unsigned int nbTech = pDesc->Techniques;*/

		D3DXTECHNIQUE_DESC pTechDesc;
		DXCheck(pEffect->GetTechniqueDesc(pEffect->GetTechnique(0), &pTechDesc));
		
		for (unsigned int i=0; i < pTechDesc.Passes; i++)
		{
			AddPass(NEW_AO DX9EffectPass(this, i));
		}

		//DXCheck(pEffect->Begin(&m_NbPass, m_Flags));

		//D3DXHANDLE mhTech = pEffect->GetTechniqueByName("Simple");
		//DXCheck(pEffect->SetTechnique(mhTech));
	}

	/**
	 * 
	 */
	DX9Shader * DX9Effect::GetShader() const
	{
		return m_pShader;
	}

} // namespace CasaEngine
