#include "SubscriberSlot.h"

namespace CasaEngine
{
	SubscriberSlot::SubscriberSlot(FreeFunctionSlot::SlotFunction* func) :
		d_functor_impl(NEW_AO FreeFunctionSlot(func))
	{
	}

	SubscriberSlot::SubscriberSlot() :
		d_functor_impl(0)
	{
	}

	SubscriberSlot::~SubscriberSlot() = default;

	void SubscriberSlot::cleanup()
	{
		DELETE_AO d_functor_impl;
		d_functor_impl = 0;
	}
}