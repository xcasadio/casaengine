#ifndef _CASAENGINEMemoryDebugAllocator_h_
#define _CASAENGINEMemoryDebugAllocator_h_

#include "CA_Export.h"

namespace CasaEngine
{
	class CA_EXPORT DebugAllocator
	{
	public:
		/**
		 *
		 */
		static void* allocateBytes(size_t size, const char* file, int line, const char* func);

		/**
		 *
		 */
		static void deallocateBytes(void* ptr);

		/// Get the maximum size of a single allocation
		static size_t getMaxAllocationSize();
	};

	//TODO why bug ??
	//CA_SET_DEFAULT_ALLOCATOR(DebugAllocator)

	template<typename T>
	struct AllocatorConfig
	{
		typedef DebugAllocator Allocator;
	};
}

#endif	// end of guard _CASAENGINEMemoryDebugAllocator_h_
