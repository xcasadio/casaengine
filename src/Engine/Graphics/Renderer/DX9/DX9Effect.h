

#ifndef DX9EFFECT_H
#define DX9EFFECT_H

#include "LibraryEngineExport.h"
#include "Graphics\Effects\IEffect.h"
#include "DX9EffectPass.h"
#include <vector>
#include "Graphics\Model\Model.h"
#include "DX9Shader.h"

namespace CasaEngine
{
	/**
	 * 
	 */
	class LIBRARY_ENGINE_EXPORT DX9Effect : public IEffect
	{
	public:
		DX9Effect();
		~DX9Effect();

		void CreatePassFromShader(DX9Shader *pShader_);
		DX9Shader * GetShader() const;
		
	protected:
		void Begin();
		void End();

	private:
		DX9Shader *m_pShader;
	};

}  // namespace CasaEngine

#endif //DX9EFFECT_H
