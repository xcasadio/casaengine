
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

#ifdef USE_LUA_SCRIPT
	m_pFileName = nullptr;
#endif // USE_LUA_SCRIPT
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

/**
 * 
 */
ScriptObjectClassID ScriptComponent::GetObjectClassID() const
{
	return m_ClassID;
}

void ScriptComponent::SetObjectClassID(ScriptObjectClassID val)
{
	m_ClassID = val;
}


#ifdef USE_LUA_SCRIPT

void ScriptComponent::SetScriptFile(const char *pFileName_)
{
	m_pFileName = pFileName_;
}


void ScriptComponent::SetScriptFromBuffer(const char *pBuffer_, size_t length_)
{
	//set variable in lua
	/*lua_pushnumber(l, i);
	lua_setglobal(l, "foo");

	lua_getglobal(l, "test_f");
	if (lua_pcall(l, 0, 0, 0) != 0)
	{
		printf( "%s", lua_tostring(l, -1));
	}*/

	// make my_function() available to Lua programs
	//Game::Instance()->GetScriptEngine()->executeFromBuffer(pBuffer_, length_);
	

	//lua_register(L, "my_function", my_function);
	/*int s = luaL_loadfile(L, file);

	if ( s==0 ) {
		// execute Lua program
		s = lua_pcall(L, 0, LUA_MULTRET, 0);
	}

	//report_errors(L, s);
	if ( s!=0 ) {
		std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1); // remove error message
	}*/

}

const char *ScriptComponent::GetScriptFile() const
{
	return m_pFileName;
}

void ScriptComponent::Initialize()
{
	if (m_pFileName != nullptr)
	{
		IFile *pFile = MediaManager::Instance().FindMedia(m_pFileName, false);
		SetScriptFromBuffer(pFile->GetBuffer(), pFile->GetBufferLength());
		DELETE_AO pFile;

		//TODO crash
		//Game::Instance()->GetScriptEngine()->SetField(GetEntity(), "entity");

		//call function OnScriptInitialize()
		//Game::Instance()->GetScriptEngine()->CallFunction("OnScriptInitialize");
	}
}

#endif // USE_LUA_SCRIPT


} // namespace CasaEngine
