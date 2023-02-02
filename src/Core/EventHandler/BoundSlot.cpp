#include "BoundSlot.h"
#include "Event.h"

namespace CasaEngine
{
	BoundSlot::BoundSlot(Group group, const SubscriberSlot& subscriber, Event& event) :
		d_group(group),
		d_subscriber(new SubscriberSlot(subscriber)),
		d_event(&event)
	{}

	BoundSlot::BoundSlot(const BoundSlot& other) = default;

	BoundSlot::~BoundSlot()
	{
		disconnect();
		delete d_subscriber;
	}

	BoundSlot& BoundSlot::operator=(const BoundSlot& other) = default;

	bool BoundSlot::operator==(const BoundSlot& other) const
	{
		return d_subscriber == other.d_subscriber;
	}

	bool BoundSlot::operator!=(const BoundSlot& other) const
	{
		return !(*this == other);
	}

	bool BoundSlot::connected() const
	{
		return d_subscriber != nullptr && d_subscriber->connected();
	}

	void BoundSlot::disconnect()
	{
		// cleanup the bound subscriber functor
		if (connected())
		{
			d_subscriber->cleanup();
		}

		// remove the owning Event's reference to us
		if (d_event)
		{
			// get the event to erase the subscriber functor.
			d_event->unsubscribe(*this);
			d_event = nullptr;
		}
	}
}