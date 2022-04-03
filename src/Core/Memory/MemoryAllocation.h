#ifndef _CASAENGINEMemoryAllocation_h_
#define _CASAENGINEMemoryAllocation_h_

#include "CompilationConfig.h"

#ifdef CA_DEBUG_MEMORY
#	define CA_CUSTOM_ALLOCATORS
#	define CA_CUSTOM_ALLOCATORS_DEBUG
#endif

#ifdef CA_CUSTOM_ALLOCATORS

namespace CasaEngine
{
	// stub classes uses for allocator configuration
	class STLAllocator {};
	class BufferAllocator {};

	// borrowed from Ogre, used to construct arrays
	template<typename T>
	T* constructN(T* basePtr, size_t count)
	{
		for (size_t i = 0; i < count; ++i)
		{
			new (static_cast<void*>(basePtr + i)) T();
		}
		return basePtr;
	}

	// ogre doesn't do this template but I added it because it works even for types without
	// destructors where I was getting syntax errors with just the macro
	template<typename T>
	void destructN(T* basePtr, size_t count)
	{
		// iterate in reverse for consistency with delete []
		for (size_t i = count - 1; i-- > 0;)
		{
			basePtr[i].~T();
		}
	}
}

#ifndef CA_CUSTOM_ALLOCATORS_DEBUG
#   define NEW_AO new
#   define DELETE_AO delete
// for primitive types, types not inherited from AllocatedObject
#   define NEW_PT(T, A) new (::CasaEngine::AllocatorConfig<A>::Allocator::allocateBytes(sizeof(T))) T
#   define NEW_ARRAY_PT(T, count, A) ::CasaEngine::constructN(static_cast<T*>(::CasaEngine::AllocatorConfig<A>::Allocator::allocateBytes(sizeof(T)*(count))), count)
#   define DELETE_PT(ptr, T, A) do{if(ptr){(ptr)->~T(); ::CasaEngine::AllocatorConfig<A>::Allocator::deallocateBytes((void*)ptr);}}while(0)
#   define DELETE_ARRAY_PT(ptr, T, count, A) do{if(ptr){ ::CasaEngine::destructN(static_cast<T*>(ptr), count); ::CasaEngine::AllocatorConfig<A>::Allocator::deallocateBytes((void*)ptr);}}while(0)
#else
#   define NEW_AO new(__FILE__, __LINE__, __FUNCTION__)
#   define DELETE_AO delete
// for primitive types, types not inherited from AllocatedObject
#   define NEW_PT(T, A) new (::CasaEngine::AllocatorConfig<A>::Allocator::allocateBytes(sizeof(T), __FILE__, __LINE__, __FUNCTION__)) T
#   define NEW_ARRAY_PT(T, count, A) ::CasaEngine::constructN(static_cast<T*>(::CasaEngine::AllocatorConfig<A>::Allocator::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__)), count)
#   define DELETE_PT(ptr, T, A) do{if(ptr){(ptr)->~T(); ::CasaEngine::AllocatorConfig<A>::Allocator::deallocateBytes((void*)ptr);}}while(0)
#   define DELETE_ARRAY_PT(ptr, T, count, A) do{if(ptr){for (size_t b = count; b-- > 0;){ (ptr)[b].~T();} ::CasaEngine::AllocatorConfig<A>::Allocator::deallocateBytes((void*)ptr);}}while(0)
#endif

#ifndef CA_CUSTOM_ALLOCATORS_INCLUDE
#   define CA_CUSTOM_ALLOCATORS_INCLUDE "Memory/MemoryDebugAllocator.h"
//#   define CA_CUSTOM_ALLOCATORS_INCLUDE "Memory/MemoryStdAllocator.h"
#endif

// all the wrappers have been declared, now we include the chosen memory allocator file
#include CA_CUSTOM_ALLOCATORS_INCLUDE

#else

// dummy macros
#define NEW_AO new
#define DELETE_AO delete
// for primitive types, types not inherited from AllocatedObject
#define NEW_PT(T, Allocator) new T
#define NEW_ARRAY_PT(T, count, Allocator) new T[count]
#define DELETE_PT(ptr, T, Allocator) delete ptr
#define DELETE_ARRAY_PT(ptr, T, count, Allocator) delete [] ptr

#endif

#include "MemoryAllocatedObject.h"
#include "MemorySTLWrapper.h"

#endif
