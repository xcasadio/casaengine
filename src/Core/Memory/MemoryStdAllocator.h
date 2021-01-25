#ifndef _CASAENGINEMemoryStdAllocator_h_
#define _CASAENGINEMemoryStdAllocator_h_

#include "CA_Export.h"
#include <stdlib.h>
#include <limits>

namespace CasaEngine
{
	class CA_EXPORT StdAllocator
	{
	public:
		static inline void* allocateBytes(size_t count)
		{
			return malloc(count);
		}

		static inline void deallocateBytes(void* ptr)
		{
			free(ptr);
		}

		// !!! IF YOU GET AN ERROR HERE:
		// that says something like: "You can't call allocateBytes with 4 arguments",
		// you are using StdAllocator and trying to enable CA_CUSTOM_ALLOCATORS_DEBUG, you
		// have to provide your own custom memory allocator if you want memory debugging.

		/// Get the maximum size of a single allocation
		static inline size_t getMaxAllocationSize()
		{
			return std::numeric_limits<size_t>::max();
		}
	};

	//CASAENGINE_SET_DEFAULT_ALLOCATOR(StdAllocator)
}

#endif	// end of guard _CASAENGINEMemoryStdAllocator_h_
