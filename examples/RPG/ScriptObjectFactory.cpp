
#include "Base.h"
#include "ScriptObjectFactory.h"


#include "Enemy.h"
#include "PlayerStates.h"
#include "ScriptCharacter.h"

using namespace CasaEngine;

SCRIPT_OBJECT_REGISTER(ScriptObjectFactory)

/**
 * 
 */
ScriptObjectFactory::ScriptObjectFactory() :
	IScriptObjectFactory(0x167D3D5E)
{

}

/**
 * 
 */
ScriptObjectFactory::~ScriptObjectFactory()
{
	
}

/**
 * 
 */
IScriptObject *ScriptObjectFactory::CreateObject(ScriptObjectClassID id_, BaseEntity *pEntity_)
{
	if (id_ == ScriptCharacter::ClassID)
	{
		return NEW_AO ScriptCharacter(pEntity_, new Enemy(pEntity_));
	}

	return nullptr;
}
