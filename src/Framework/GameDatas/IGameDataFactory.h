#ifndef IGAMEDATAFACTORY_H_
#define IGAMEDATAFACTORY_H_

#include "CA_Export.h"

#include "Memory\MemoryAllocation.h"


namespace CasaEngine
{
	typedef unsigned int GameDataFactoryID;

	/**
	 *
	 */
	class CA_EXPORT IGameDataFactory :
		public AllocatedObject<IGameDataFactory>
	{
	public:
		virtual ~IGameDataFactory() {}

		GameDataFactoryID GetID() const;

	protected:
		IGameDataFactory(GameDataFactoryID id_);

	private:
		GameDataFactoryID m_ID;
		//std::string m_Name;
	};

	/**
	 *
	 */
	class CA_EXPORT AutoRegisterGameDataFactory
	{
	public:
		AutoRegisterGameDataFactory(IGameDataFactory* pObject_, const char* factoryName_,
			const char* filename, int line);
	};

#define GAMEDATA_REGISTER(FactoryName) \
	FactoryName auto_gamedata_instance_##FactoryName; \
	AutoRegisterGameDataFactory autoreg_gamedata_##FactoryName(&auto_gamedata_instance_##FactoryName, #FactoryName, __FILE__, __LINE__ );

}

#endif // IGAMEDATAFACTORY_H_