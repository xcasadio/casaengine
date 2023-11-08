#pragma once

namespace CasaEngine
{
	/*!
	\brief
		Simple, generic, reference counted pointer class.  This is primarily here
		for use by the Events system to track when to delete slot bindings.

	\note
		Only safe to use with AllocatedObject<T> derived classes!
	*/
	template<typename T>
	class RefCounted
	{
	public:
		/*!
		\brief
			Default constructor.
		*/
		RefCounted() :
			d_object(nullptr),
			d_count(nullptr)
		{
		}

		/*!
		\brief
			Contruct a RefCounted object that wraps the pointer \a ob.
		*/
		RefCounted(T* ob) :
			d_object(ob),
			// use system heap for this! no CEGUI_NEW_PT!
			d_count(ob != nullptr ? new unsigned int(1) : nullptr)
		{
		}

		/*!
		\brief
			Copy constructor
		*/
		RefCounted(const RefCounted<T>& other) :
			d_object(other.d_object),
			d_count(other.d_count)
		{
			if (d_count)
			{
				addRef();
			}
		}

		/*!
		\brief
			Destructor.  Only deletes the associated object if no further references
			exist.
		*/
		~RefCounted()
		{
			if (d_object)
			{
				release();
			}
		}

		/*!
		\brief
			Assignment operator.  Previously held object gets its reference count
			reduced, and is deleted if no further references exist.  The newly
			assigned object, taken from \a other, gets its count increased.
		*/
		RefCounted<T>& operator=(const RefCounted<T>& other)
		{
			if (*this != other)
			{
				if (d_object)
				{
					release();
				}

				d_object = other.d_object;
				d_count = d_object ? other.d_count : nullptr;

				if (d_count)
				{
					addRef();
				}
			}

			return *this;
		}

		/*!
		\brief
			Return whether the two RefCounted ptrs are equal
			(point to the same object)
		*/
		bool operator==(const RefCounted<T>& other) const
		{
			return d_object == other.d_object;
		}

		/*!
		\brief
			Return whether the two RefCounted ptrs are not equal
			(point to different objects)
		*/
		bool operator!=(const RefCounted<T>& other) const
		{
			return d_object != other.d_object;
		}

		/*!
		\brief
			Return the object referred to by the wrapped pointer.
			(beware of null pointers when using this!)
		*/
		const T& operator*() const
		{
			return *d_object;
		}

		T& operator*()
		{
			return *d_object;
		}

		/*!
		\brief
			Return the wrapped pointer.
		*/
		const T* operator->() const
		{
			return d_object;
		}

		T* operator->()
		{
			return d_object;
		}

		/*!
		\brief
			Return whether the wrapped pointer is valid.  i.e. that it is not null.
		*/
		bool isValid() const
		{
			return d_object != nullptr;
		}

	private:
		/*!
		\brief
			Increases the reference count for the wrapped object.
		*/
		void addRef() const
		{
			++* d_count;
		}

		/*!
		\brief
			Decreases the reference count for the wrapped object, and if the count
			has reached zero, the object and the shared counter are deleted.
		*/
		void release()
		{
			if (!-- * d_count)
			{
				// use CEGUI allocators for the object
				delete d_object;

				// use system heap for this! no CEGUI_DELETE_PT!
				delete d_count;
				d_object = 0;
				d_count = nullptr;
			}
		}

		T* d_object;            //! pointer to the object.
		unsigned int* d_count;  //! pointer to the shared counter object.
	};
}