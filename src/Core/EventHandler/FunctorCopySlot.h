/************************************************************************
    filename:   CEGUIFunctorCopySlot.h
    created:    Tue Feb 28 2006
    author:     Paul D Turner <paul@cegui.org.uk>
*************************************************************************/
#ifndef _CASAENGINEFunctorCopySlot_h_
#define _CASAENGINEFunctorCopySlot_h_

#include "SlotFunctorBase.h"


namespace CasaEngine
{
/*!
\brief
    Slot template class that creates a functor that calls back via a copy of a
    functor object.
*/
template<typename T>
class FunctorCopySlot : public SlotFunctorBase
{
public:
    FunctorCopySlot(const T& functor) :
        d_functor(functor)
    {}

    virtual bool operator()(const EventArgs& args)
    {
        return d_functor(args);
    }

private:
    T d_functor;
};

}

#endif  // end of guard _CASAENGINEFunctorCopySlot_h_
