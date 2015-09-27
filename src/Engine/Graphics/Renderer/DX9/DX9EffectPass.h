

#ifndef DX9EFFECTPASS_H
#define DX9EFFECTPASS_H

#include "LibraryEngineExport.h"
#include "Graphics\Effects\IEffectPass.h"

namespace CasaEngine
{
	class DX9Effect;
	class IEffect;

	///
	class LIBRARY_ENGINE_EXPORT DX9EffectPass : public IEffectPass
	{
	public:
		DX9EffectPass(DX9Effect * pEffect_, unsigned int passNum_);
		~DX9EffectPass();
		
		void Begin();
		void End();
		
	private:
		DX9Effect *m_pEffect;
		unsigned int m_PassNum;
	};

}  // namespace CasaEngine

#endif //DX9EFFECTPASS_H