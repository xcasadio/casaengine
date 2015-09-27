#include "CA_Assert.h"
#include "GameDataFactory.h"


namespace CasaEngine
{
	SINGLETON_IMPL(GameDataFactory)

	/**
	 * 
	 */
	GameDataFactory::GameDataFactory()
	{

	}

	/**
	 * 
	 */
	GameDataFactory::~GameDataFactory()
	{

	}

	/**
	 * 
	 */
	void GameDataFactory::Release()
	{

	}

	/**
	 * 
	 */
	void GameDataFactory::RegisterFactory( IGameDataFactory *pFactory_ )
	{
		//assert not already exist

		m_Factories[pFactory_->GetID()] = pFactory_;
	}

	/**
	 * 
	 */
	void GameDataFactory::UnRegisterFactory(IGameDataFactory *pFactory_)
	{
		m_Factories.erase(pFactory_->GetID());
		DELETE_AO pFactory_;
	}

	/**
	 * 
	 */
	IGameData * GameDataFactory::CreateGameDataFromClassID(GameDataClassID id_)
	{
		IGameData *pRes = nullptr;


		return pRes;
	}

	/**
	 * 
	 */
	IGameData * GameDataFactory::LoadGameData( GameDataClassID id_, std::ifstream& is )
	{
		IGameData *pRes = nullptr;


		return pRes;
	}

	/**
	 * 
	 */
	IGameData * GameDataFactory::LoadGameData( GameDataClassID id_, const tinyxml2::XMLElement& xmlElt )
	{
		IGameData *pRes = nullptr;


		return pRes;
	}

	/**
	 * 
	 */
	void GameDataFactory::SaveGameData( IGameData *pData, std::ostream& os )
	{

	}

	/**
	 * 
	 */
	void GameDataFactory::SaveGameData( IGameData *pData, tinyxml2::XMLElement& xmlElt )
	{

	}

	/**
	 * 
	 */
	std::vector<std::string> GameDataFactory::GetAllGameDataName() const
	{
		std::vector<std::string> res;


		return res;
	}

} // namespace CasaEngine