#include "IScriptObject.h"
#include "CA_Assert.h"

namespace CasaEngine
{
	IScriptObject::IScriptObject(BaseEntity* pEntity_)
	{
		CA_ASSERT(pEntity_ != nullptr, "IScriptObject::IScriptObject()");
		m_pEntity = pEntity_;
	}
	
	BaseEntity* IScriptObject::GetEntity() const
	{
		return m_pEntity;
	}
}
