#ifndef ISCRIPTOBJECT_H_
#define ISCRIPTOBJECT_H_

#include "Log\LogManager.h"
#include "CA_Export.h"
#include "Memory\MemoryAllocation.h"
#include "Entities\BaseEntity.h"


namespace CasaEngine
{
	typedef unsigned int ScriptObjectClassID;
	typedef unsigned int ScriptObjectID;

/**
 * 
 */
class CA_EXPORT IScriptObject :
	public AllocatedObject<IScriptObject>
{
public:
	virtual ~IScriptObject() {}

	BaseEntity *GetEntity() const;

	virtual void OnInitialize() = 0;
	virtual void OnUpdate(const GameTime& gameTime_) = 0;
	virtual void OnDestroy() = 0;

protected:
	IScriptObject(BaseEntity *pEntity_);

private:
	BaseEntity *m_pEntity;
};

} // namespace CasaEngine

#endif // ISCRIPTOBJECT_H_