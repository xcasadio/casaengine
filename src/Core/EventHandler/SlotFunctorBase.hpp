#pragma once

#include "CA_Export.hpp"


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
