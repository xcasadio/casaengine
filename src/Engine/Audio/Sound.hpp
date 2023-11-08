
#ifndef SOUND_H_
#define SOUND_H_

#include "LibraryEngineExport.h"
#include "Memory\MemoryAllocation.h"


namespace CasaEngine
{
	/**
	 *	
	 */
	class LIBRARY_ENGINE_EXPORT Sound :
		public AllocatedObject<Sound>
	{
	public:
		Sound();
		~Sound();

	private:

	};

} // namespace CasaEngine

#endif // SOUND_H_
