#pragma once

#include  "SlotFunctorBase.hpp"

namespace CasaEngine
{
	/*!
	\brief
		Slot template class that creates a functor that calls back via a copy of a
		functor object.
	*/
	template<typename T>
	class FunctorCopySlot : public SlotFunctorBase
	{
	public:
		FunctorCopySlot(const T& functor) :
			d_functor(functor)
		{}

		bool operator()(const EventArgs& args) override
		{
			return d_functor(args);
		}

	private:
		T d_functor;
	};
}
