/************************************************************************
	filename:   CEGUIEvent.cpp
	created:    Tue Feb 28 2006
	author:     Paul D Turner <paul@cegui.org.uk>
*************************************************************************/
#include "Event.h"
#include "EventArgs.h"

#include <algorithm>

namespace CasaEngine
{
	/*!
	\brief
		Implementation helper functor which is used to locate a BoundSlot in the
		multimap collection of BoundSlots.
	*/
	class SubComp
	{
	public:
		SubComp(const BoundSlot& s) :
			d_s(s)
		{}

		bool operator()(std::pair<Event::Group, Event::Connection> e) const
		{
			return *e.second == d_s;
		}

	private:
		void operator=(const SubComp&) const {}
		const BoundSlot& d_s;
	};

	//----------------------------------------------------------------------------//
	Event::Event(const std::string& name) :
		d_name(name)
	{
	}

	//----------------------------------------------------------------------------//
	Event::~Event()
	{
		auto iter(d_slots.begin());
		const SlotContainer::const_iterator end_iter(d_slots.end());

		for (; iter != end_iter; ++iter)
		{
			iter->second->d_event = 0;
			iter->second->d_subscriber->cleanup();
		}

		d_slots.clear();
	}

	//----------------------------------------------------------------------------//
	Event::Connection Event::subscribe(const Subscriber& slot)
	{
		return subscribe(static_cast<Group>(-1), slot);
	}

	//----------------------------------------------------------------------------//
	Event::Connection Event::subscribe(Group group,
		const Subscriber& slot)
	{
		Connection c(new BoundSlot(group, slot, *this));
		d_slots.insert(std::pair<Group, Connection>(group, c));
		return c;
	}

	//----------------------------------------------------------------------------//
	void Event::operator()(EventArgs& args)
	{
		auto iter(d_slots.begin());
		const SlotContainer::const_iterator end_iter(d_slots.end());

		// execute all subscribers, updating the 'handled' state as we go
		for (; iter != end_iter; ++iter)
			if ((*iter->second->d_subscriber)(args))
				++args.handled;
	}

	//----------------------------------------------------------------------------//
	void Event::unsubscribe(const BoundSlot& slot)
	{
		// try to find the slot in our collection
		auto curr =
			std::find_if(d_slots.begin(),
				d_slots.end(),
				SubComp(slot));

		// erase our reference to the slot, if we had one.
		if (curr != d_slots.end())
			d_slots.erase(curr);
	}
}