#ifndef ISCRIPTOBJECTFACTORY_H_
#define ISCRIPTOBJECTFACTORY_H_

#include "CA_Export.h"
#include <string>
#include "IScriptObject.h"

#include "Memory\MemoryAllocation.h"


namespace CasaEngine
{
	typedef unsigned int ScriptObjectFactoryID;

/**
 * 
 */
class CA_EXPORT IScriptObjectFactory :
	public AllocatedObject<IScriptObjectFactory>
{
public:
	virtual ~IScriptObjectFactory() {}

	virtual IScriptObject *CreateObject(ScriptObjectClassID id_, BaseEntity *pEntity_) = 0;
	ScriptObjectFactoryID GetID() const;

protected:
	IScriptObjectFactory(ScriptObjectFactoryID id_);

private:
	ScriptObjectFactoryID m_ID;
	//std::string m_Name;
};


/**
 * 
 */
class CA_EXPORT AutoRegisterScriptObjectFactory
{
public:
	AutoRegisterScriptObjectFactory(IScriptObjectFactory *pObject_, const char *factoryName_, 
		const char *filename, int line);
};

#define SCRIPT_OBJECT_REGISTER(FactoryName)
/*#define SCRIPT_OBJECT_REGISTER(FactoryName) \
	FactoryName auto_gameplay_instance_##FactoryName; \
	AutoRegisterScriptObjectFactory autoreg_gameplay_##FactoryName(&auto_gameplay_instance_##FactoryName, #FactoryName, __FILE__, __LINE__ );
	*/
}

#endif // ISCRIPTOBJECTFACTORY_H_