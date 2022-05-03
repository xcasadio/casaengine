#include "IScriptObject.h"
#include "CA_Assert.h"

namespace CasaEngine
{
	IScriptObject::IScriptObject(BaseEntity* entity_)
	{
		CA_ASSERT(entity_ != nullptr, "IScriptObject::IScriptObject()");
		_entity = entity_;
	}
	
	BaseEntity* IScriptObject::GetEntity() const
	{
		return _entity;
	}
}
