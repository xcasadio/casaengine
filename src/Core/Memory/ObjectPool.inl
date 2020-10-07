
#include "Memory/MemoryAllocation.h"

/**
 * 
 */
template <class T>
std::vector<T* >& ObjectPool<T>::get_list()
{
	static std::vector<T* > m_free;
	return m_free;
}

/**
 *
 */
template <class T >
inline void *ObjectPool<T>::operator new( size_t /*stAllocateBlock*/)
{
	#ifdef ___USE_MT___
	EnterCriticalSection(get_cs());
	#endif

	if (T::get_list().size() <= 0)
	{
		T::addElement();
	}

	T* p = T::get_list().back();
	T::get_list().pop_back();

	#ifdef ___USE_MT___
	LeaveCriticalSection(get_cs());
	#endif

	return p;
}	

/**
 *
 */
template <class T >
inline void ObjectPool<T>::operator delete( void *p )
{
	#ifdef ___USE_MT___
	EnterCriticalSection(get_cs());
	#endif

	T::get_list().push_back(static_cast<T*>(p));

	#ifdef ___USE_MT___
	LeaveCriticalSection(get_cs());
	#endif
}


/**
	*
	*/
template <class T >
ObjectPool<T>::ObjectPool() {}
	
/**
	*
	*/
template <class T >
ObjectPool<T>::~ObjectPool() {}
	
/**
	*
	*/
#ifdef ___USE_MT___
inline ObjectPool<T>::CRITICAL_SECTION* get_cs()
{
	static CRITICAL_SECTION __m_cs;
	return &__m_cs;
}
#endif
	
/**
	*
	*/
template <class T >
void ObjectPool<T>::__op_initialize()
{
	#ifdef ___USE_MT___
	InitializeCriticalSection(get_cs());
	#endif
	addElement();
}
	
/**
	*
	*/
template <class T >
void ObjectPool<T>::__op_finalize()
{
	#ifdef ___USE_MT___
	DeleteCriticalSection(get_cs());
	#endif
	destroy();
}

/**
	*
	*/
template <typename T >
void ObjectPool<T>::capacity(size_t capacity_)
{
	size_t nbElement = T::get_list().size();

	if (capacity_ < nbElement)
	{
		//destroy 
		typename std::vector<T* >::iterator first = T::get_list().begin() + capacity_;
		typename std::vector<T* >::iterator last = T::get_list().end();
		while (first != last)
		{
			T* p = *first; ++first;
			::delete p;
		}
		T::get_list().erase(T::get_list().begin() + capacity_, T::get_list().end());
	}
	else if (capacity_ > nbElement)
	{
		for (size_t i = 0; i < capacity_ - nbElement; ++i)
		{
			T::addElement();
		}
	}
}

	

/**
	*
	*/
template <typename T >
void ObjectPool<T>::destroy()
{
	typename std::vector<T* >::iterator first = T::get_list().begin();
	typename std::vector<T* >::iterator last = T::get_list().end();
	while (first != last)
	{
		T* p = *first; ++first;
		::delete p;
	}
	T::get_list().erase(T::get_list().begin(), T::get_list().end());
}

/**
 *
 */
template <class T >
void ObjectPool<T>::addElement()
{
	for (int i = 0; i < 1; ++i)
	{
		//T* p = (T*) CasaEngine::CMemoryManager::Instance().Allocate(sizeof(T), __FILE__, __LINE__, false);
		T* p = ::new T;
		T::get_list().push_back(p);
	}
}
