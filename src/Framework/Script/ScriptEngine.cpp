#include "Base.h"
#include "ScriptEngine.h"

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
		delete pFactory_;
	}

	/**
	 * 
	 */
	IScriptObject *ScriptEngine::CreateScriptObjectFromClassID(ScriptObjectClassID id_, BaseEntity *pEntity_)
	{
		IScriptObject *pObj = nullptr;

		for (auto factory : m_Factories)
		{
			pObj = factory.second->CreateObject(id_, pEntity_);

			if (pObj != nullptr)
			{
				break;
			}
		}

		return pObj;
	}

}
