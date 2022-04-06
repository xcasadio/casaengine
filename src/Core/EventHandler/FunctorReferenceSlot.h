#ifndef _CASAENGINEFunctorReferenceSlot_h_
#define _CASAENGINEFunctorReferenceSlot_h_

#include "SlotFunctorBase.h"

namespace CasaEngine
{
	/*!
	\brief
		Slot template class that creates a functor that calls back via a functor
		object reference.
	*/
	template<typename T>
	class FunctorReferenceSlot : public SlotFunctorBase
	{
	public:
		FunctorReferenceSlot(T& functor) :
			d_functor(functor)
		{}

		bool operator()(const EventArgs& args) override
		{
			return d_functor(args);
		}

	private:
		T& d_functor;
	};
}

#endif
