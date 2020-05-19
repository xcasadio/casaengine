#include "CA_Assert.h"
#include "GameDataFactory.h"


namespace CasaEngine
{
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
	void GameDataFactory::RegisterFactory(IGameDataFactory* pFactory_)
	{
		//assert not already exist

		m_Factories[pFactory_->GetID()] = pFactory_;
	}

	/**
	 *
	 */
	void GameDataFactory::UnRegisterFactory(IGameDataFactory* pFactory_)
	{
		m_Factories.erase(pFactory_->GetID());
		DELETE_AO pFactory_;
	}

	/**
	 *
	 */
	IGameData* GameDataFactory::CreateGameDataFromClassID(GameDataClassID id_)
	{
		IGameData* pRes = nullptr;


		return pRes;
	}

	/**
	 *
	 */
	IGameData* GameDataFactory::LoadGameData(GameDataClassID id_, const char* name)
	{
		IGameData* pRes = nullptr;


		return pRes;
	}

	/**
	 *
	 */
	void GameDataFactory::SaveGameData(IGameData* pData, const char* name)
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

}