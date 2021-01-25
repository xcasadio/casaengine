/***********************************************************************
	filename:   CEGUIEventSet.cpp
	created:    21/2/2004
	author:     Paul D Turner

	purpose:    Implements the EventSet class
*************************************************************************/
#include "EventSet.h"
//#include "Exceptions.h"
#include "GlobalEventSet.h"
#include "Exceptions.h"
#include <sstream>
#include <fstream>
//#include "ScriptModule.h"
//#include "System.h"

// Start of CEGUI namespace section
namespace CasaEngine
{
	//----------------------------------------------------------------------------//
	EventSet::EventSet() :
		d_muted(false)
	{
	}

	//----------------------------------------------------------------------------//
	EventSet::~EventSet()
	{
		removeAllEvents();
	}

	//----------------------------------------------------------------------------//
	void EventSet::addEvent(const std::string& name)
	{
		addEvent(*new Event(name));
	}

	//----------------------------------------------------------------------------//
	void EventSet::addEvent(Event& event)
	{
		const std::string name(event.getName());

		if (isEventPresent(name))
		{
			delete& event;

			std::ostringstream oss;
			oss << "An event named " << name << " already exists in the EventSet.";
			throw CException(oss.str());
		}

		d_events.insert(std::make_pair(name, &event));
	}

	//----------------------------------------------------------------------------//
	void EventSet::removeEvent(const std::string& name)
	{
		EventMap::iterator pos = d_events.find(name);

		if (pos != d_events.end())
		{
			delete pos->second;
			d_events.erase(pos);
		}
	}

	//----------------------------------------------------------------------------//
	void EventSet::removeEvent(Event& event)
	{
		removeEvent(event.getName());
	}

	//----------------------------------------------------------------------------//
	void EventSet::removeAllEvents(void)
	{
		EventMap::const_iterator pos = d_events.begin();
		EventMap::const_iterator end = d_events.end();

		for (; pos != end; ++pos)
			delete pos->second;

		d_events.clear();
	}

	//----------------------------------------------------------------------------//
	bool EventSet::isEventPresent(const std::string& name)
	{
		return d_events.find(name) != d_events.end();
	}
	//
	// //----------------------------------------------------------------------------//
	// Event::Connection EventSet::subscribeScriptedEvent(const std::string& name,
	//                                                    const std::string& subscriber_name)
	// {
	//     return getScriptModule()->subscribeEvent(this, name, subscriber_name);
	// }
	//
	// //----------------------------------------------------------------------------//
	// Event::Connection EventSet::subscribeScriptedEvent(const std::string& name,
	//                                                    Event::Group group,
	//                                                    const std::string& subscriber_name)
	// {
	//     return getScriptModule()->subscribeEvent(this, name, group, subscriber_name);
	// }
	//
	// //----------------------------------------------------------------------------//
	// ScriptModule* EventSet::getScriptModule() const
	// {
	//     ScriptModule* sm = System::getSingletonPtr()->getScriptingModule();
	//
	//     if (sm)
	//         return sm;
	//
	//     CEGUI_THROW(InvalidRequestException(
	//         "No scripting module is available."));
	// }

	//----------------------------------------------------------------------------//
	Event::Connection EventSet::subscribeEvent(const std::string& name,
		Event::Subscriber subscriber)
	{
		return getEventObject(name, true)->subscribe(subscriber);
	}

	//----------------------------------------------------------------------------//
	Event::Connection EventSet::subscribeEvent(const std::string& name,
		Event::Group group,
		Event::Subscriber subscriber)
	{
		return getEventObject(name, true)->subscribe(group, subscriber);
	}

	//----------------------------------------------------------------------------//
	void EventSet::fireEvent(const std::string& name,
		EventArgs& args,
		const std::string& eventNamespace)
	{
		if (GlobalEventSet* ges = GlobalEventSet::Instance())
			ges->fireEvent(name, args, eventNamespace);

		fireEvent_impl(name, args);
	}

	//----------------------------------------------------------------------------//
	bool EventSet::isMuted(void) const
	{
		return d_muted;
	}

	//----------------------------------------------------------------------------//
	void EventSet::setMutedState(bool setting)
	{
		d_muted = setting;
	}

	//----------------------------------------------------------------------------//
	Event* EventSet::getEventObject(const std::string& name, bool autoAdd)
	{
		EventMap::const_iterator pos = d_events.find(name);

		// if event did not exist, add it as needed and then find it.
		if (pos == d_events.end())
		{
			if (!autoAdd)
				return 0;

			addEvent(name);
			pos = d_events.find(name);
		}

		return pos->second;
	}

	//----------------------------------------------------------------------------//
	void EventSet::fireEvent_impl(const std::string& name, EventArgs& args)
	{
		Event* ev = getEventObject(name);

		if (ev != 0 && !d_muted)
			(*ev)(args);
	}

	//----------------------------------------------------------------------------//
	EventSet::EventIterator EventSet::getEventIterator(void) const
	{
		return EventIterator(d_events.begin(), d_events.end());
	}

	//----------------------------------------------------------------------------//
} // End of  CEGUI namespace section