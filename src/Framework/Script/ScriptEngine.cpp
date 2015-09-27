
#include "Base.h"
#include "ScriptEngine.h"
#include "Log/LogVerbose.h"
#include "Log/LogManager.h"

#ifdef USE_LUA_SCRIPT
// include Lua libs and tolua++
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "tolua++.h"

// prototype for bindings initialisation function
int tolua_CasaEngine_open(lua_State* tolua_S);

#endif // USE_LUA_SCRIPT

namespace CasaEngine
{
	SINGLETON_IMPL(ScriptEngine)

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


#ifdef USE_LUA_SCRIPT

ScriptEngine::ScriptEngine()
{
	m_pLuaState = nullptr;
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
	m_pLuaState = luaL_newstate(); //lua_open();

	if (nullptr == m_pLuaState) 
	{
		CA_ERROR("Error Initializing lua\n");
		return;
	}

	luaL_openlibs(m_pLuaState); // initialize all lua standard library functions
	tolua_open(m_pLuaState); // initialize tolua

	static const luaL_Reg lualibs[] = {
		{"", luaopen_base},
		{LUA_LOADLIBNAME, luaopen_package},
		{LUA_TABLIBNAME, luaopen_table},
		{LUA_IOLIBNAME, luaopen_io},
		{LUA_OSLIBNAME, luaopen_os},
		{LUA_STRLIBNAME, luaopen_string},
		{LUA_MATHLIBNAME, luaopen_math},
#if defined(DEBUG) || defined (_DEBUG)
		{LUA_DBLIBNAME, luaopen_debug},
#endif
		{0, 0}
	};

	const luaL_Reg *lib = lualibs;
	for (; lib->func; lib++)
	{
		lua_pushcfunction(m_pLuaState, lib->func);
		lua_pushstring(m_pLuaState, lib->name);
		lua_call(m_pLuaState, 1, 0);
	}

	tolua_CasaEngine_open(m_pLuaState);


	//register all class and functions
	//tolua_Player_open(m_pLuaState);   // make Player class accessible from LUA

	CA_TRACE("Script Engine initialized : %s\n", LUA_RELEASE);
}

/**
 *
 */
void ScriptEngine::Release()
{
	if (m_pLuaState != nullptr)
	{
		lua_close(m_pLuaState);
		m_pLuaState = nullptr;
	}
}

void ScriptEngine::executeFromBuffer(const char *str_, size_t length_)
{
	int top = lua_gettop(m_pLuaState);
	int err_idx = 0; //initErrorHandlerFunc();

	// load code into lua and call it
	int error = luaL_loadbuffer(m_pLuaState, str_, length_, str_) ||
		lua_pcall(m_pLuaState, 0, 0, err_idx); //

	// handle errors
	if (error)
	{
		const char *pErrMsg = lua_tostring(m_pLuaState, -1);
		lua_settop(m_pLuaState, top);
		CA_ERROR("Unable to execute Lua script string: '%s' error is %s\n", str_, pErrMsg);
	}

	lua_settop(m_pLuaState, top);
}

/**
 * 
 */
int ScriptEngine::initErrorHandlerFunc()
{
	m_ActiveErrFuncName = m_ErrFuncName;

	// should we create a registry reference for named function
	if ((m_ErrFuncIndex == LUA_NOREF) && !m_ErrFuncName.empty())
	{
		int top = lua_gettop(m_pLuaState);

		//LuaFunctor::pushNamedFunction(m_pLuaState, m_ErrFuncName);
		// reference function
		m_ErrFuncIndex = luaL_ref(m_pLuaState, LUA_REGISTRYINDEX);

		lua_settop(m_pLuaState, top);
	}

	// init handler via function index in registry
	return initErrorHandlerFunc(m_ErrFuncIndex);
}

//----------------------------------------------------------------------------//
int ScriptEngine::initErrorHandlerFunc(const std::string func_name)
{
	m_ActiveErrFuncName = func_name;

	// string has some text in it?
	if (!func_name.empty())
	{
		//LuaFunctor::pushNamedFunction(m_pLuaState, func_name);
		return lua_gettop(m_pLuaState);
	}

	// use no error handler function.
	return 0;
}

//----------------------------------------------------------------------------//
int ScriptEngine::initErrorHandlerFunc(int func)
{
	m_ActiveErrFuncIndex = func;

	// check if we have a valid registry index for the error handler function
	if (func != LUA_NOREF)
	{
		lua_rawgeti(m_pLuaState, LUA_REGISTRYINDEX, func);
		return lua_gettop(m_pLuaState);
	}

	// use no error handler function.
	return 0;
}

/**
 * 
 */
void ScriptEngine::cleanupErrorHandlerFunc()
{
	m_ActiveErrFuncIndex = LUA_NOREF;
	m_ActiveErrFuncName.clear();
}

/**
 * 
 */
void ScriptEngine::unrefErrorFunc()
{
	if ((m_ErrFuncIndex != LUA_NOREF) && !m_ErrFuncName.empty())
	{
		luaL_unref(m_pLuaState, LUA_REGISTRYINDEX, m_ErrFuncIndex);
		m_ErrFuncIndex = LUA_NOREF;
	}
}

void ScriptEngine::SetField( void *pData_, const char *fieldName_ )
{
	//lua_pushnumber(m_pLuaState, 256);
	lua_pushlightuserdata(m_pLuaState, pData_);
	lua_setfield(m_pLuaState, -1, fieldName_);
}

#endif // USE_LUA_SCRIPT

} // namespace CasaEngine
