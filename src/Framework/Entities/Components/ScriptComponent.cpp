#include "Base.h"
#include "ScriptComponent.h"
#include "Log/LogVerbose.h"
#include "Log/LogManager.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"

namespace CasaEngine
{
	ScriptComponent::ScriptComponent(BaseEntity* entity) :
		Component(entity, SCRIPT)
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
		if (m_pScriptObject != nullptr)
		{
			m_pScriptObject->OnInitialize();
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

	CasaEngine::IScriptObject* ScriptComponent::GetScriptObject()
	{
		return m_pScriptObject;
	}

}
