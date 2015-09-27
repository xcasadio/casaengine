#ifndef SCRIPTOBJECTFACTORY_H_
#define SCRIPTOBJECTFACTORY_H_

#include "Script\IScriptObjectFactory.h"
#include "Script\IScriptObject.h"
#include "Entities\BaseEntity.h"
#include "Export.h"
#include "CompilationMacro.h"

//#define AUTO_REGISTER_FACTORY()

using namespace CasaEngine;

/**
 * 
 */
class GAMEPLAYDLL_EXPORT ScriptObjectFactory : public IScriptObjectFactory
{
public:
	ScriptObjectFactory();
	~ScriptObjectFactory();

	IScriptObject *CreateObject(ScriptObjectClassID id_, BaseEntity *pEntity_) OVERRIDE;

};

#endif // SCRIPTOBJECTFACTORY_H_