#include "Base.h"
#include "ScriptComponent.h"
#include "Log/LogVerbose.h"
#include "Log/LogManager.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"

namespace CasaEngine
{
	ScriptComponent::ScriptComponent(BaseEntity* pEntity_) :
		Component(pEntity_, SCRIPT)
	{
		m_pScriptObject = nullptr;
	}

	ScriptComponent::~ScriptComponent()
	{
		if (m_pScriptObject != nullptr)
		{
			m_pScriptObject->OnDestroy();
			delete m_pScriptObject;
		}
	}

	void ScriptComponent::Initialize()
	{
		//m_pScriptObject = Game::Instance().GetScriptEngine().CreateScriptObjectFromClassID(m_ClassID, GetEntity());

		if (m_pScriptObject != nullptr)
		{
			m_pScriptObject->OnInitialize();
		}
		else
		{
			CA_ERROR("Error when create script object from the class id %d\n", m_ClassID);
		}
	}

	void ScriptComponent::Update(const GameTime& gameTime_)
	{
		if (m_pScriptObject != nullptr)
		{
			m_pScriptObject->OnUpdate(gameTime_);
		}
	}

	bool ScriptComponent::HandleMessage(const Telegram& msg)
	{
		if (m_pScriptObject != nullptr)
		{
			m_pScriptObject->HandleMessage(msg);
		}

		return Component::HandleMessage(msg);
	}

	void ScriptComponent::SetScriptObject(IScriptObject* pScriptObject)
	{
		m_pScriptObject = pScriptObject;
	}

}
