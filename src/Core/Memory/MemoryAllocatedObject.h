#ifndef CASAENGINE_MEMORY_ALLOCATED_OBJECT_H
#define CASAENGINE_MEMORY_ALLOCATED_OBJECT_H

#ifndef CASAENGINE_MEMORY_ALLOCATED_OBJECT_H
#   error Do not include this directly! Include MemoryAllocation.h instead.
#endif

namespace CasaEngine
{
#ifdef CA_CUSTOM_ALLOCATORS

	/*!
	\brief
		Defines a 'allocated object' class

		This is used to allocate CASAENGINE classes via custom allocators. It's
		basically a wrapper that calls given Allocator when new/delete is called.
		This is managed via overloading of new and delete operators.
	*/
	template <typename Class>
	class AllocatedObject
	{
	public:
		typedef typename AllocatorConfig<Class>::Allocator Allocator;

		explicit AllocatedObject() = default;
		virtual ~AllocatedObject() = default;

#ifndef CA_CUSTOM_ALLOCATORS_DEBUG
		inline void* operator new(size_t size)
		{
			return Allocator::allocateBytes(size);
		}
#else
		void* operator new(size_t size, const char* file, int line, const char* func)
		{
			return Allocator::allocateBytes(size, file, line, func);
		}
#endif

		void operator delete(void* ptr)
		{
			Allocator::deallocateBytes(ptr);
		}

#ifndef CA_CUSTOM_ALLOCATORS_DEBUG
		inline void* operator new[](size_t size)
		{
			return Allocator::allocateBytes(size);
		}
#else
		void* operator new[](size_t size, const char* file, int line, const char* func)
		{
			return Allocator::allocateBytes(size, file, line, func);
		}
#endif

		void operator delete[](void* ptr)
		{
			Allocator::deallocateBytes(ptr);
		}

			// todo: does debug variant even make sense with placement new?
		void* operator new(size_t size, void* ptr)
		{
			(void)size;
			return ptr;
		}

		void operator delete(void* ptr, void*)
		{
			Allocator::deallocateBytes(ptr);
		}
	};

#else

	// allocated object is just a stub template class if custom memory allocators aren't used
	template<typename Allocator>
	class AllocatedObject
	{
	public:
		explicit AllocatedObject() = default;
	};

#endif
}

#endif
