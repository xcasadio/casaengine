#ifndef GAMEDATAFACTORY_H_
#define GAMEDATAFACTORY_H_

#include "CA_Export.h"
#include <string>
#include "IGameData.h"

#include <vector>
#include "IGameDataFactory.h"
#include <map>

namespace CasaEngine
{
	class CA_EXPORT GameDataFactory
	{
	public:
		GameDataFactory();
		~GameDataFactory();

		//void Initialize();
		void Release();

		void RegisterFactory(IGameDataFactory* pFactory_);
		void UnRegisterFactory(IGameDataFactory* pFactory_);

		IGameData* CreateGameDataFromClassID(GameDataClassID id_);

		IGameData* LoadGameData(GameDataClassID id_, std::ifstream& is);
		IGameData* LoadGameData(GameDataClassID id_, const tinyxml2::XMLElement& xmlElt);

		void SaveGameData(IGameData* pData, std::ostream& os);
		void SaveGameData(IGameData* pData, tinyxml2::XMLElement& xmlElt);

		std::vector<std::string> GetAllGameDataName() const;

	private:
		typedef std::map<GameDataClassID, IGameDataFactory*> FactoryMap;
		FactoryMap m_Factories;
	};

}

#endif