#ifndef _OBJECTPOOL_H_
#define _OBJECTPOOL_H_

#include <vector>

namespace CasaEngine
{
	/**
	 * Derived class must have a default constructor
	 */
	template <class T>
	class ObjectPool
	{
	public:

#ifdef ___USE_MT___
		inline static CRITICAL_SECTION* get_cs();
#endif

		static std::vector<T* >& get_list();

		static void __op_initialize();
		static void __op_finalize();

		inline void* operator new(size_t stAllocateBlock);
		inline void operator delete(void* p);

		static void capacity(size_t capacity_);
		static void destroy();

	protected:

		ObjectPool();
		~ObjectPool();

	private:

		static void addElement();
	};

#include "ObjectPool.inl"
}

#endif // _OBJECTPOOL_H_
