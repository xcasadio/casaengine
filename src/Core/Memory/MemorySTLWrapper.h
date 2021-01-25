#ifndef _CASAENGINEMemorySTLWrapper_h_
#define _CASAENGINEMemorySTLWrapper_h_

#ifndef _CASAENGINEMemoryAllocation_h_
#   error Dont include this directly! Include MemoryAllocation.h instead.
#endif

namespace CasaEngine
{
#ifdef CA_CUSTOM_ALLOCATORS

	template<typename T>
	struct STLAllocatorWrapperBase
	{
		typedef T value_type;
	};
	// getting rid of const trick taken from Ogre :-)
	template<typename T>
	struct STLAllocatorWrapperBase<const T>
	{
		typedef T value_type;
	};

	template <typename T, typename Allocator>
	class STLAllocatorWrapper : public STLAllocatorWrapperBase<T>
	{
	public:
		typedef STLAllocatorWrapperBase<T> Base;
		typedef typename Base::value_type value_type;

		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;

		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

		template<typename U>
		struct rebind
		{
			typedef STLAllocatorWrapper<U, Allocator> other;
		};

		inline explicit STLAllocatorWrapper()
		{}

		inline STLAllocatorWrapper(const STLAllocatorWrapper&)
		{}

		template <typename U, typename P>
		inline STLAllocatorWrapper(const STLAllocatorWrapper<U, P>&)
		{}

		inline pointer address(reference x) const
		{
			return &x;
		}

		inline const_pointer address(const_reference x) const
		{
			return &x;
		}

		inline size_type max_size() const throw()
		{
			return Allocator::getMaxAllocationSize();
		}

		inline pointer allocate(size_type count, typename std::allocator<void>::const_pointer ptr = 0)
		{
			(void)ptr;
			return static_cast<pointer>(Allocator::allocateBytes(count * sizeof(T)));
		}

		inline void deallocate(pointer ptr, size_type /*size*/)
		{
			Allocator::deallocateBytes(ptr);
		}

		inline void construct(pointer p, const T& val)
		{
			new(static_cast<void*>(p)) T(val);
		}

		inline void destroy(pointer p)
		{
			p->~T();
		}
	};

	template<typename T, typename T2, typename P>
	inline bool operator==(const STLAllocatorWrapper<T, P>&, const STLAllocatorWrapper<T2, P>&)
	{
		// same allocator, return true
		return true;
	}

	template<typename T, typename P, typename OtherAllocator>
	inline bool operator==(const STLAllocatorWrapper<T, P>&, const OtherAllocator&)
	{
		// if the template abose doesn't get matched, return false (allocators differ)
		return false;
	}

	template<typename T, typename T2, typename P>
	inline bool operator!=(const STLAllocatorWrapper<T, P>&, const STLAllocatorWrapper<T2, P>&)
	{
		// same allocator, return false (they are not different)
		return false;
	}

	template<typename T, typename P, typename OtherAllocator>
	inline bool operator!=(const STLAllocatorWrapper<T, P>&, const OtherAllocator&)
	{
		// the above didn't get matched, that means the allocators differ...
		return true;
	}

	// STL allocator helper macros
#define CA_VECTOR_ALLOC(T) , ::CasaEngine::STLAllocatorWrapper<T, ::CasaEngine::AllocatorConfig< ::CasaEngine::STLAllocator >::Allocator>
#define CA_SET_ALLOC(T) , ::CasaEngine::STLAllocatorWrapper<T, ::CasaEngine::AllocatorConfig< ::CasaEngine::STLAllocator >::Allocator>
#define CA_MAP_ALLOC(K, V) , ::CasaEngine::STLAllocatorWrapper<std::pair<K, V>, ::CasaEngine::AllocatorConfig< ::CasaEngine::STLAllocator >::Allocator>
#define CA_MULTIMAP_ALLOC(K, V) , ::CasaEngine::STLAllocatorWrapper<std::pair<K, V>, ::CasaEngine::AllocatorConfig< ::CasaEngine::STLAllocator >::Allocator>

#else

	// STL allocator helper macros
#define CA_VECTOR_ALLOC(T)
#define CA_SET_ALLOC(T)
#define CA_MAP_ALLOC(K, V)
#define CA_MULTIMAP_ALLOC(K, V)

#endif
}

#endif	// end of guard _CASAENGINEMemorySTLWrapper_h_
