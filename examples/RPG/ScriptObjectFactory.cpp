
#include "Base.h"
#include "ScriptObjectFactory.h"
#include "ScriptPlayer.h"

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
	if (id_ == ScriptPlayer::ClassID)
	{
		return NEW_AO ScriptPlayer(pEntity_);
	}

	return nullptr;
}
