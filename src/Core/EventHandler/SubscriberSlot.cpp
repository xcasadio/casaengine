/************************************************************************
	filename:   CEGUISubscriberSlot.cpp
	created:    Tue Feb 28 2006
	author:     Paul D Turner <paul@cegui.org.uk>
*************************************************************************/

#include "SubscriberSlot.h"

// Start of CEGUI namespace section
namespace CasaEngine
{
	SubscriberSlot::SubscriberSlot(FreeFunctionSlot::SlotFunction* func) :
		d_functor_impl(new FreeFunctionSlot(func))
	{
	}

	SubscriberSlot::SubscriberSlot() :
		d_functor_impl(0)
	{
	}

	SubscriberSlot::~SubscriberSlot()
	{
	}

	void SubscriberSlot::cleanup()
	{
		delete d_functor_impl;
		d_functor_impl = 0;
	}
} // End of  CEGUI namespace section