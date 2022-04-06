#ifndef _CASAENGINESlotFunctorBase_h_
#define _CASAENGINESlotFunctorBase_h_

#include "CA_Export.h"


namespace CasaEngine
{
	// forward refs
	class EventArgs;

	/*!
	\brief
		Defines abstract interface which will be used when constructing various
		functor objects that bind slots to signals (or in CEGUI terms, handlers to
		events).
	*/
	class CA_EXPORT SlotFunctorBase 
	{
	public:
		virtual ~SlotFunctorBase() = default;;
		virtual bool operator()(const EventArgs& args) = 0;
	};
}

#endif
