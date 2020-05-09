#include "CA_Assert.h"
#include "IGameDataFactory.h"
#include "GameDataFactory.h"
#include "Game/Game.h"
#include "Log\LogManager.h"


namespace CasaEngine
{
GameDataFactoryID IGameDataFactory::GetID() const { return m_ID; }
IGameDataFactory::IGameDataFactory(GameDataFactoryID id_) { m_ID = id_; }

AutoRegisterGameDataFactory::AutoRegisterGameDataFactory(
		IGameDataFactory *pObject_, const char *factoryName_, 
		const char *filename, int line)
{
	CA_TRACE("register GameData factory '%s' (%d) (%d:%s)\n", factoryName_, pObject_->GetID(), line, filename);
	Game::Instance().GetGameDataFactory().RegisterFactory(pObject_);
}

}