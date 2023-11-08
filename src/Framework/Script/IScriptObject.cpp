#include  "IScriptObject.hpp"
#include  "CA_Assert.hpp"

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
