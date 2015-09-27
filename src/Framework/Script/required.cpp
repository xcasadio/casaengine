#include "required.h"

namespace CasaEngine
{

/************************************************************************
    EventConnection helper class implementation
*************************************************************************/
EventConnection::EventConnection(RefCounted<BoundSlot> slot) :
    d_slot(slot)
{}

//----------------------------------------------------------------------------//
bool EventConnection::connected() const
{
    return d_slot->connected();
}

//----------------------------------------------------------------------------//
void EventConnection::disconnect()
{
    d_slot->disconnect();
}

} // namespace CEGUI