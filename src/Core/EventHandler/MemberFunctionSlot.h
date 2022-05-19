#pragma once

#include "SlotFunctorBase.h"

namespace CasaEngine
{
	/*!
	\brief
		Slot template class that creates a functor that calls back via a class
		member function.
	*/
	template<typename T>
	class MemberFunctionSlot : public SlotFunctorBase
	{
	public:
		//! Member function slot type.
		typedef bool(T::* MemberFunctionType)(const EventArgs&);

		MemberFunctionSlot(MemberFunctionType func, T* obj) :
			d_function(func),
			d_object(obj)
		{}

		bool operator()(const EventArgs& args) override
		{
			return (d_object->*d_function)(args);
		}

	private:
		MemberFunctionType d_function;
		T* d_object;
	};
}
