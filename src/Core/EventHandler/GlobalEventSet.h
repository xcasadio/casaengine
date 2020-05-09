/***********************************************************************
	filename: 	CEGUIGlobalEventSet.h
	created:	16/1/2005
	author:		Paul D Turner
*************************************************************************/
#ifndef _CASAENGINEGlobalEventSet_h_
#define _CASAENGINEGlobalEventSet_h_

#include "EventSet.h"

#include "CA_Export.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#endif


namespace CasaEngine
{
/*!
\brief
    The GlobalEventSet singleton allows you to subscribe to an event for all
    instances of a class.  The GlobalEventSet effectively supports "late binding"
    to events; which means you can subscribe to some event that does not actually
    exist (yet).
*/
class CA_EXPORT GlobalEventSet :
    public EventSet
{
public :
	static GlobalEventSet* Instance();
	static void Destroy();

	~GlobalEventSet();
	GlobalEventSet(const GlobalEventSet& rsh) = delete;
	GlobalEventSet& operator=(const GlobalEventSet& rsh) = delete;

	/*!
	\brief
		Fires the named event passing the given EventArgs object.

	\param name
		std::string object holding the name of the Event that is to be fired (triggered)

	\param args
		The EventArgs (or derived) object that is to be bassed to each subscriber of the Event.  Once all subscribers
		have been called the 'handled' field of the event is updated appropriately.
		
	\param eventNamespace
		std::string object describing the namespace prefix to use when firing the global event.

	\return
		Nothing.
	*/
	void	fireEvent(const std::string& name, EventArgs& args, const std::string& eventNamespace = "") override;

private:
	GlobalEventSet();

	static GlobalEventSet* s_pInstance;
};

}


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	// end of guard _CASAENGINEGlobalEventSet_h_
