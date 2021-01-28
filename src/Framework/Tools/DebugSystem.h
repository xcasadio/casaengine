#ifndef _DEBUGSYSTEM_H_
#define _DEBUGSYSTEM_H_

#include "CA_Export.h"
#include "GameTime.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
    /**
     *  
     */
    class CA_EXPORT DebugSystem :
		public AllocatedObject<DebugSystem>
    {
	public :
		DebugSystem();
		~DebugSystem();

		void Initialize();
		void Update(const GameTime& gameTime_);

		int GetFPS() const;
		
	private:
		float m_fFPSTime;
		int m_iFPSCount;
		float m_fFPSLastDelta;
		int m_iLastFPSCount;
	};

}


#endif // _DEBUGSYSTEM_H_
