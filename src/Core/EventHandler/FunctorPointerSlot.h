#ifndef _CASAENGINEFunctorPointerSlot_h_
#define _CASAENGINEFunctorPointerSlot_h_

#include "SlotFunctorBase.h"
#include "Memory\MemoryAllocation.h"

namespace CasaEngine
{
	/*!
	\brief
		Slot template class that creates a functor that calls back via a functor
		object pointer.
	*/
	template<typename T>
	class FunctorPointerSlot : public SlotFunctorBase, public AllocatedObject<FunctorPointerSlot<T>>
	{
	public:
		FunctorPointerSlot(T* functor) :
			d_functor(functor)
		{}

		bool operator()(const EventArgs& args) override
		{
			return (*d_functor)(args);
		}

	private:
		T* d_functor;
	};
}

#endif
