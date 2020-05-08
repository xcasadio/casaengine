#include "Base.h"
#include "ScriptComponent.h"
#include "Log/LogVerbose.h"
#include "Log/LogManager.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"
#include "IO/IOManager.h"


namespace CasaEngine
{

	/**
	 * 
	 */
ScriptComponent::ScriptComponent(BaseEntity* pEntity_) :
	Component(pEntity_, SCRIPT)
{
	m_pScriptObject = nullptr;
}

/**
 * 
 */
ScriptComponent::~ScriptComponent()
{
	if (m_pScriptObject != nullptr)
	{
		m_pScriptObject->OnDestroy();
		DELETE_AO m_pScriptObject;
	}
}

/**
 * 
 */
void ScriptComponent::Initialize()
{
	m_pScriptObject = ScriptEngine::Instance().CreateScriptObjectFromClassID(m_ClassID, GetEntity());
	
	if (m_pScriptObject != nullptr)
	{
		m_pScriptObject->OnInitialize();
	}
	else
	{
		CA_ERROR("Error when create script object from the class id %d\n", m_ClassID);
	}
}

/**
 * 
 */
void ScriptComponent::Update(const GameTime& gameTime_)
{
	if (m_pScriptObject != nullptr)
	{
		m_pScriptObject->OnUpdate(gameTime_);
	}
}

/**
 * 
 */
void ScriptComponent::Read( const tinyxml2::XMLElement& xmlElt )
{

}

/**
 * 
 */
void ScriptComponent::Read( std::ifstream& is )
{

}

/**
 * 
 */
void ScriptComponent::Write( tinyxml2::XMLElement& xmlElt )
{

}

/**
 * 
 */
void ScriptComponent::Write( std::ostream& os )
{

}

}
