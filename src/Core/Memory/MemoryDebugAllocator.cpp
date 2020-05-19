#include "MemoryDebugAllocator.h"
#include <iomanip>
#include <iostream>
#include "MemoryReport.h"
#include <limits>

namespace CasaEngine
{
	void* DebugAllocator::allocateBytes(size_t size, const char* file, int line, const char* func)
	{
		void* ptr = malloc(size);
		MemoryReport::Instance().Allocate(ptr, size, file, line);
		return ptr;
	}

	void DebugAllocator::deallocateBytes(void* ptr)
	{
		MemoryReport::Instance().Deallocate(ptr);
		free(ptr);
	}

	size_t DebugAllocator::getMaxAllocationSize()
	{
		return std::numeric_limits<size_t>::max();
	}
}
