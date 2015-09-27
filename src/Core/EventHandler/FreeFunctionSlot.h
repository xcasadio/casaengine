/************************************************************************
    filename:   CEGUIFreeFunctionSlot.h
    created:    Tue Feb 28 2006
    author:     Paul D Turner <paul@cegui.org.uk>
*************************************************************************/
#ifndef _CASAENGINEFreeFunctionSlot_h_
#define _CASAENGINEFreeFunctionSlot_h_

#include "SlotFunctorBase.h"
#include "CA_Export.h"


namespace CasaEngine
{
/*!
\brief
    Slot functor class that calls back via a free function pointer.
*/
class CA_EXPORT FreeFunctionSlot : public SlotFunctorBase
{
public:
    //! Slot function type.
    typedef bool (SlotFunction)(const EventArgs&);

    FreeFunctionSlot(SlotFunction* func) :
        d_function(func)
    {}

    virtual bool operator()(const EventArgs& args)
    {
        return d_function(args);
    }

private:
    SlotFunction* d_function;
};


}

#endif  // end of guard _CASAENGINEFreeFunctionSlot_h_
