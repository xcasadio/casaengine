
#include "Base.h"
#include "Log/LogManager.h"
#include "Component.h"
#include "BaseEntity.h"
#include "Macro.h"
#include "CA_Assert.h"
#include <iosfwd>

namespace CasaEngine
{
/**
 * 
 */
Component::Component(BaseEntity* pEntity_, int type)
{
	CA_ASSERT(pEntity_ != nullptr, 
		"Component::Component() : BaseEntity is nullptr");

	m_pEntity = pEntity_;
	m_Type = type;
}

/**
 * 
 */
Component::~Component()
{
	//Do nothing
}

/**
 * 
 */
BaseEntity* Component::GetEntity() 
{ 
	return m_pEntity; 
}

/**
 * 
 */
bool Component::HandleMessage(const Telegram& /*msg*/ )
{
	//Do nothing
	return false;
}

void Component::Draw() 
{ 
	//Do nothing
}

/**
 * 
 */
int Component::Type() const
{
	return m_Type;
}

/**
 * Editor
 */
void Component::ShowDebugWidget()
{
	// Do nothing
}

/**
 * 
 */
void Component::Read(const tinyxml2::XMLElement& xmlElt)
{
	CA_UNUSED_1(xmlElt)
}

/**
 * 
 */
void Component::Read(std::ifstream& is)
{
	//CA_UNUSED_1(is)
}

/**
 * 
 */
void Component::Write(tinyxml2::XMLElement& xmlElt)
{
	CA_UNUSED_1(xmlElt)
}

/**
 * 
 */
void Component::Write(std::ostream& os)
{
	CA_UNUSED_1(os)
}

}
