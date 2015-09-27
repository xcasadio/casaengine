

#ifndef GLEFFECT_H
#define GLEFFECT_H

#include "LibraryEngineExport.h"
#include "Graphics\Effects\IEffect.h"
#include "GLEffectPass.h"
#include <vector>
#include "Graphics\Model\Model.h"
#include "GLShader.h"

namespace CasaEngine
{
	/**
	 * 
	 */
	class LIBRARY_ENGINE_EXPORT GLEffect : public IEffect
	{
	public:
		GLEffect();
		~GLEffect();

		void AddPass(GLShader *pShader_);
		GLShader *GetShader() const;
		
	protected:
		void Begin();
		void End();

	private:
		GLShader *m_pShader;
	};

}  // namespace CasaEngine

#endif //GLEFFECT_H
