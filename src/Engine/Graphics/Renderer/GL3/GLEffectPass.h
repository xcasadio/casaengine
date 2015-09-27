

#ifndef GLEFFECTPASS_H
#define GLEFFECTPASS_H

#include "LibraryEngineExport.h"
#include "Graphics\Effects\IEffectPass.h"
#include "GLShader.h"

namespace CasaEngine
{
	class GLEffect;
	class IEffect;

	///
	class LIBRARY_ENGINE_EXPORT GLEffectPass : public IEffectPass
	{
	public:
		GLEffectPass(GLEffect * pEffect_, GLShader *pShader_);
		~GLEffectPass();
		
		void Begin();
		void End();
		
	private:
		GLEffect *m_pEffect;
		GLShader *m_pShader;
	};

}  // namespace CasaEngine

#endif //GLEFFECTPASS_H