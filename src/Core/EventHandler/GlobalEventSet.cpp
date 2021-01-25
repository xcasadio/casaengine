/***********************************************************************
	filename: 	CEGUIGlobalEventSet.cpp
	created:	16/1/2005
	author:		Paul D Turner
*************************************************************************/
#include "GlobalEventSet.h"
#include <string>
#include "Log\LogManager.h"

// Start of CEGUI namespace section
namespace CasaEngine
{
	GlobalEventSet* GlobalEventSet::s_pInstance(nullptr);

	GlobalEventSet* GlobalEventSet::Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = NEW_AO GlobalEventSet();
		}

		return s_pInstance;
	}

	void GlobalEventSet::Destroy()
	{
		DELETE_AO s_pInstance;
	}

	/*************************************************************************
		GlobalEventSet constructor.
	*************************************************************************/
	GlobalEventSet::GlobalEventSet()
	{
		CA_TRACE("GlobalEventSet singleton created. (%p)\n", static_cast<void*>(this));
	}

	/*************************************************************************
		GlobalEventSet destructor.
	*************************************************************************/
	GlobalEventSet::~GlobalEventSet()
	{
		CA_TRACE("GlobalEventSet singleton destroyed. (%p)\n", static_cast<void*>(this));
	}

	/*************************************************************************
		Overridden fireEvent which always succeeds.
	*************************************************************************/
	void GlobalEventSet::fireEvent(const std::string& name, EventArgs& args, const std::string& eventNamespace)
	{
		// here we are very explicit about how we construct the event std::string.
		// Doing it 'longhand' like this saves significant time when compared
		// to the obvious - and previous - implementation:
		//     fireEvent_impl(eventNamespace + "/" + name, args);
		std::string evt_name;
		if (eventNamespace.empty() == false) // TODO : need to always specify eventNamespace ?
		{
			evt_name.reserve(eventNamespace.length() + name.length() + 1);
			evt_name.append(eventNamespace);
			evt_name.append(1, '/');
		}

		evt_name.append(name);
		fireEvent_impl(evt_name, args);
	}
} // End of  CEGUI namespace section