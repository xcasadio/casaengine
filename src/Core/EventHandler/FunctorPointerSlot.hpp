#pragma once

#include  "SlotFunctorBase.hpp"

namespace CasaEngine
{
	/*!
	\brief
		Slot template class that creates a functor that calls back via a functor
		object pointer.
	*/
	template<typename T>
	class FunctorPointerSlot : public SlotFunctorBase
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
