#include "Base.h"
#include "ScriptEngine.h"
#include "Log/LogVerbose.h"
#include "Log/LogManager.h"

namespace CasaEngine
{
	ScriptEngine::ScriptEngine()
	{
		
	}

	ScriptEngine::~ScriptEngine()
	{
		Release();
	}

	/**
	 *
	 */
	void ScriptEngine::Initialize()
	{
		
	}

	/**
	 *
	 */
	void ScriptEngine::Release()
	{
		
	}

	/**
	 * 
	 */
	void ScriptEngine::RegisterFactory(IScriptObjectFactory *pFactory_)
	{
		//assert not already exist

		m_Factories[pFactory_->GetID()] = pFactory_;
	}

	/**
	 * 
	 */
	void ScriptEngine::UnRegisterFactory(IScriptObjectFactory *pFactory_)
	{
		m_Factories.erase(pFactory_->GetID());
		DELETE_AO pFactory_;
	}

	/**
	 * 
	 */
	IScriptObject *ScriptEngine::CreateScriptObjectFromClassID(ScriptObjectClassID id_, BaseEntity *pEntity_)
	{
		IScriptObject *pObj = nullptr;

		for (FactoryMap::iterator it = m_Factories.begin();
			it != m_Factories.end();
			it++)
		{
			pObj = (*it).second->CreateObject(id_, pEntity_);

			if (pObj != nullptr)
			{
				break;
			}
		}

		return pObj;
	}

}
