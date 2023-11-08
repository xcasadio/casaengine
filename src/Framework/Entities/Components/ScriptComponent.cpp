#include  "Base.hpp"
#include  "ScriptComponent.hpp"
#include  "Log/LogVerbose.hpp"
#include  "Log/LogManager.hpp"
#include  "Entities/ComponentTypeEnum.hpp"
#include  "Game/Game.hpp"

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
