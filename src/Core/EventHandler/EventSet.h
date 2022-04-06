#ifndef _CASAENGINEEventSet_h_
#define _CASAENGINEEventSet_h_

#include <string>
#include "Event.h"
#include "IteratorBase.h"
#include <map>

#if defined (_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable : 4251)
#endif

namespace CasaEngine
{
	/*!
	\brief
		Class that collects together a set of Event objects.

		The EventSet is a means for code to attach a handler function to some
		named event, and later, for that event to be fired and the subscribed
		handler(s) called.
		\par
		As of 0.5, the EventSet no longer needs to be filled with available events.
		Events are now added to the set as they are first used; that is, the first
		time a handler is subscribed to an event for a given EventSet, an Event
		object is created and added to the EventSet.
		\par
		Instead of throwing an exception when firing an event that does not actually
		exist in the set, we now do nothing (if the Event does not exist, then it
		has no handlers subscribed, and therefore doing nothing is the correct
		course action).
	*/
	class CA_EXPORT EventSet
	{
	public:
		/*!
		\brief
			Constructor for EventSet objects
		*/
		EventSet();

		/*!
		\brief
			Destructor for EventSet objects
		*/
		virtual ~EventSet();

		/*!
		\brief
			Creates a new Event object with the given name and adds it to the
			EventSet.

		\param name
			std::string object containing the name to give the new Event.  The name must
			be unique for the EventSet.

		\exception AlreadyExistsException
			Thrown if an Event already exists named \a name.
		*/
		void addEvent(const std::string& name);

		/*!
		\brief
			Adds the given Event object to the EventSet.  Ownership of the object
			passes to EventSet and it will be deleted when it is removed from the
			EventSet - whether explicitly via removeEvent or when the EventSet
			is destroyed.

		\param event
			Reference to an Event or Event based object that is to be added to the
			EventSaet

		\exception AlreadyExistsException
			Thrown if the EventSet already contains an Event with the same name
			as \a event.  Note that \a event will be destroyed under this scenario.
		*/
		void addEvent(Event& event);

		/*!
		\brief
			Removes the Event with the given name.  All connections to the event
			are disconnected, and the underlying Event object is destroyed.

		\param name
			std::string object containing the name of the Event to remove.  If no such
			Event exists, nothing happens.
		*/
		void removeEvent(const std::string& name);

		/*!
		\brief
			Removes the given event from the EventSet.  All connections to the event
			are disconnected, and the event object is destroyed.

		\param event
			Reference to the Event or Event based object to be removed from the
			EventSet.
		*/
		void removeEvent(Event& event);

		/*!
		\brief
			Remove all Event objects from the EventSet.  Add connections will be
			disconnected, and all Event objects destroyed.
		*/
		void removeAllEvents(void);

		/*!
		\brief
			Checks to see if an Event with the given name is present in this
			EventSet.

		\return
			- true if an Event named \a name is defined for this EventSet.
			- false if no Event named \a name is defined for this EventSet.
		*/
		bool isEventPresent(const std::string& name);

		/*!
		\brief
			Subscribes a handler to the named Event.  If the named Event is not yet
			present in the EventSet, it is created and added.

		\param name
			std::string object containing the name of the Event to subscribe to.

		\param subscriber
			Function or object that is to be subscribed to the Event.

		\return
			Connection object that can be used to check the status of the Event
			connection and to disconnect (unsubscribe) from the Event.
		*/
		virtual Event::Connection subscribeEvent(const std::string& name,
			Event::Subscriber subscriber);

		/*!
		\brief
			Subscribes a handler to the specified group of the named Event.  If the
			named Event is not yet present in the EventSet, it is created and added.

		\param name
			std::string object containing the name of the Event to subscribe to.

		\param group
			Group which is to be subscribed to.  Subscription groups are called in
			ascending order.

		\param subscriber
			Function or object that is to be subscribed to the Event.

		\return
			Connection object that can be used to check the status of the Event
			connection and to disconnect (unsubscribe) from the Event.
		*/
		virtual Event::Connection subscribeEvent(const std::string& name,
			Event::Group group,
			Event::Subscriber subscriber);

		/*!
		\copydoc EventSet::subscribeEvent

		\internal This is there just to make the syntax a tad easier
		*/
		template<typename Arg1, typename Arg2>
		Event::Connection subscribeEvent(const std::string& name, Arg1 arg1, Arg2 arg2)
		{
			return subscribeEvent(name, Event::Subscriber(arg1, arg2));
		}

		/*!
		\copydoc EventSet::subscribeEvent

		\internal This is there just to make the syntax a tad easier
		*/
		template<typename Arg1, typename Arg2>
		Event::Connection subscribeEvent(const std::string& name, Event::Group group, Arg1 arg1, Arg2 arg2)
		{
			return subscribeEvent(name, group, Event::Subscriber(arg1, arg2));
		}

		/*!
		\brief
			Subscribes the named Event to a scripted funtion

		\param name
			std::string object containing the name of the Event to subscribe to.

		\param subscriber_name
			std::string object containing the name of the script funtion that is to be
			subscribed to the Event.

		\return
			Connection object that can be used to check the status of the Event
			connection and to disconnect (unsubscribe) from the Event.
		*/
		//     virtual Event::Connection subscribeScriptedEvent(const std::string& name,
		//                                                      const std::string& subscriber_name);

			/*!
			\brief
				Subscribes the specified group of the named Event to a scripted funtion.

			\param name
				std::string object containing the name of the Event to subscribe to.

			\param group
				Group which is to be subscribed to.  Subscription groups are called in
				ascending order.

			\param subscriber_name
				std::string object containing the name of the script funtion that is to be
				subscribed to the Event.

			\return
				Connection object that can be used to check the status of the Event
				connection and to disconnect (unsubscribe) from the Event.
			*/
			//     virtual Event::Connection subscribeScriptedEvent(const std::string& name,
			//                                                      Event::Group group,
			//                                                      const std::string& subscriber_name);

				/*!
				\brief
					Fires the named event passing the given EventArgs object.

				\param name
					std::string object holding the name of the Event that is to be fired
					(triggered)

				\param args
					The EventArgs (or derived) object that is to be bassed to each
					subscriber of the Event.  Once all subscribers
					have been called the 'handled' field of the event is updated
					appropriately.

				\param eventNamespace
					std::string object describing the global event namespace prefix for this
					event.
				*/
		virtual void fireEvent(const std::string& name, EventArgs& args,
			const std::string& eventNamespace = "");

		/*!
		\brief
			Return whether the EventSet is muted or not.

		\return
			- true if the EventSet is muted.  All requests to fire events will be
			  ignored.
			- false if the EventSet is not muted.  Requests to fire events are
			  processed as normal.
		*/
		bool isMuted(void) const;

		/*!
		\brief
			Set the mute state for this EventSet.

		\param setting
			- true if the EventSet is to be muted (no further event firing requests
			  will be honoured until EventSet is unmuted).
			- false if the EventSet is not to be muted and all events should fired
			  as requested.
		*/
		void    setMutedState(bool setting);

		/*!
		\brief
			Return a pointer to the Event object with the given name, optionally
			adding such an Event object to the EventSet if it does not already
			exist.

		\param name
			std::string object holding the name of the Event to return.

		\param autoAdd
			- true if an Event object named \a name should be added to the set
			  if such an Event does not currently exist.
			- false if no object should automatically be added to the set.  In this
			  case, if the Event does not already exist 0 will be returned.

		\return
			Pointer to the Event object in this EventSet with the specifed name.
			Or 0 if such an Event does not exist and \a autoAdd was false.
		*/
		Event* getEventObject(const std::string& name, bool autoAdd = false);

	protected:
		//! Implementation event firing member
		void fireEvent_impl(const std::string& name, EventArgs& args);
		//! Helper to return the script module pointer or throw.
	//    ScriptModule* getScriptModule() const;

		// Do not allow copying, assignment, or any other usage than simple creation.
		EventSet(EventSet&) {}
		EventSet& operator=(EventSet&)
		{
			return *this;
		}

		//     typedef std::map<std::string, Event*, std::stringFastLessCompare
		//         CEGUI_MAP_ALLOC(std::string, Event*)> EventMap;
		typedef std::map<std::string, Event*> EventMap;
		EventMap    d_events;

		bool    d_muted{};    //!< true if events for this EventSet have been muted.

	public:
		typedef ConstMapIterator<EventMap> EventIterator;

		/*!
		\brief
			Return a EventSet::EventIterator object to iterate over the events currently
			added to the EventSet.
		*/
		EventIterator getEventIterator(void) const;
	};
}

#if defined(_MSC_VER)
#   pragma warning(pop)
#endif

#endif
