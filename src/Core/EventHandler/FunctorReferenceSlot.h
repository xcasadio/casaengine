/************************************************************************
	filename:   CEGUIFunctorReferenceSlot.h
	created:    Tue Feb 28 2006
	author:     Paul D Turner <paul@cegui.org.uk>
*************************************************************************/
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

#endif  // end of guard _CASAENGINEFunctorReferenceSlot_h_
