#pragma once

#include "SlotFunctorBase.h"
#include "CA_Export.h"

namespace CasaEngine
{
	/*!
	\brief
		Slot functor class that calls back via a free function pointer.
	*/
	class CA_EXPORT FreeFunctionSlot : public SlotFunctorBase
	{
	public:
		//! Slot function type.
		typedef bool (SlotFunction)(const EventArgs&);

		FreeFunctionSlot(SlotFunction* func) :
			d_function(func)
		{}

		bool operator()(const EventArgs& args) override
		{
			return d_function(args);
		}

	private:
		SlotFunction* d_function;
	};
}
