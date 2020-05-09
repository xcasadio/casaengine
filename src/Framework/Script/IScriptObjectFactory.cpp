#include "CA_Assert.h"
#include "IScriptObjectFactory.h"
#include "ScriptEngine.h"
#include "Game/Game.h"


namespace CasaEngine
{
ScriptObjectFactoryID IScriptObjectFactory::GetID() const { return m_ID; }
IScriptObjectFactory::IScriptObjectFactory(ScriptObjectFactoryID id_) { m_ID = id_; }

AutoRegisterScriptObjectFactory::AutoRegisterScriptObjectFactory(
		IScriptObjectFactory *pObject_, const char *factoryName_, 
		const char *filename, int line)
{
	CA_TRACE("register script factory '%s' (%d) (%d:%s)\n", factoryName_, pObject_->GetID(), line, filename);
	Game::Instance().GetScriptEngine().RegisterFactory(pObject_);
}

}
