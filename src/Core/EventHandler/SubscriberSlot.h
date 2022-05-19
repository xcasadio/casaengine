#pragma once

#include "FreeFunctionSlot.h"
#include "FunctorCopySlot.h"
#include "FunctorReferenceSlot.h"
#include "FunctorPointerSlot.h"
#include "MemberFunctionSlot.h"
#include "FunctorReferenceBinder.h"
#include "CA_Export.h"

namespace CasaEngine
{
	/*!
	\brief
		SubscriberSlot class which is used when subscribing to events.

		For many uses, the construction of the SubscriberSlot may be implicit, so
		you do not have to specify Subscriber in your subscription calls. Notable
		exceptions are for subscribing member functions and references to functor
		objects.
	*/
	class CA_EXPORT SubscriberSlot
	{
	public:
		/*!
		\brief
			Default constructor.  Creates a SubscriberSlot with no bound slot.
		*/
		SubscriberSlot();

		/*!
		\brief
			Creates a SubscriberSlot that is bound to a free function.
		*/
		SubscriberSlot(FreeFunctionSlot::SlotFunction* func);

		/*!
		\brief
			Destructor.  Note this is non-virtual, which should be telling you not
			to sub-class!
		*/
		~SubscriberSlot();

		/*!
		\brief
			Invokes the slot functor that is bound to this Subscriber.  Returns
			whatever the slot returns, unless there is not slot bound when false is
			always returned.
		*/
		bool operator()(const EventArgs& args) const
		{
			return (*d_functor_impl)(args);
		}

		/*!
		\brief
			Returns whether the SubscriberSlot is internally connected (bound).
		*/
		bool connected() const
		{
			return d_functor_impl != 0;
		}

		/*!
		\brief
			Disconnects the slot internally and performs any required cleanup
			operations.
		*/
		void cleanup();

		// templatised constructors
		/*!
		\brief
			Creates a SubscriberSlot that is bound to a member function.
		*/
		template<typename T>
		SubscriberSlot(bool (T::* function)(const EventArgs&), T* obj) :
			d_functor_impl(new MemberFunctionSlot<T>(function, obj))
		{}

		/*!
		\brief
			Creates a SubscriberSlot that is bound to a functor object reference.
		*/
		template<typename T>
		SubscriberSlot(const FunctorReferenceBinder<T>& binder) :
			d_functor_impl(new FunctorReferenceSlot<T>(binder.d_functor))
		{}

		/*!
		\brief
			Creates a SubscriberSlot that is bound to a copy of a functor object.
		*/
		template<typename T>
		SubscriberSlot(const T& functor) :
			d_functor_impl(new FunctorCopySlot<T>(functor))
		{}

		/*!
		\brief
			Creates a SubscriberSlot that is bound to a functor pointer.
		*/
		template<typename T>
		SubscriberSlot(T* functor) :
			d_functor_impl(new FunctorPointerSlot<T>(functor))
		{}

	private:
		//! Points to the internal functor object to which we are bound
		SlotFunctorBase* d_functor_impl;
	};
}
