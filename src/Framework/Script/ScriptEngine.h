#ifndef SCRIPTENGINE_H_
#define SCRIPTENGINE_H_

#include "CA_Export.h"
#include "IScriptObject.h"
#include "IScriptObjectFactory.h"
#include <map>

#include "Entities\BaseEntity.h"

//struct lua_State;

namespace CasaEngine
{
	class CA_EXPORT ScriptEngine
	{
	public:
		ScriptEngine();
		~ScriptEngine();

		void Initialize();
		void Release();

		void RegisterFactory(IScriptObjectFactory *pFactory_);
		void UnRegisterFactory(IScriptObjectFactory *pFactory_);

		IScriptObject *CreateScriptObjectFromClassID(ScriptObjectClassID id_, BaseEntity *pEntity_);

	private:
		typedef std::map<ScriptObjectFactoryID, IScriptObjectFactory *> FactoryMap;
		FactoryMap m_Factories;


#ifdef USE_LUA_SCRIPT
		void executeFromBuffer(const char *str_, size_t length_);

		/** Init the error handler function.  Return the lua stack index that
		 *  should be passed to lua_pcall.  NB: This should be called prior to
		 *  pushing any function parameters onto the lua stack.
		 */
		int initErrorHandlerFunc();
		/** Init the error handler function.  Return the lua stack index that
		 *  should be passed to lua_pcall.  NB: This should be called prior to
		 *  pushing any function parameters onto the lua stack.
		 */
		int initErrorHandlerFunc(const std::string func_name);
		/** Init the error handler function.  Return the lua stack index that
		 *  should be passed to lua_pcall.  NB: This should be called prior to
		 *  pushing any function parameters onto the lua stack.
		 */
		int initErrorHandlerFunc(int func);

		/** do any needed cleanup after having called initErrorHandlerFunc and
		 * (possible) executed a script.
		 *
		 * NB: This probably does less than you think ;)
		 */
		void cleanupErrorHandlerFunc();

		//! release any reference we might have made to an error handling function.
		void unrefErrorFunc();
		void SetField( void* pData_, const char *fieldName_ );

	private:
		//! The lua_State that this script module uses.
		lua_State *m_pLuaState;

		//! Default error handler function to pass to lua_pcall.
		std::string m_ErrFuncName;

		//! Default registry index of the function to pass to lua_pcall.
		int m_ErrFuncIndex;

		/** Error handler function that is currently in use (as setup via a call
			to initErrorHandlerFunc)
		*/
		std::string m_ActiveErrFuncName;

		/** Registry index of the function that is currently in use (as setup via a
			call to initErrorHandlerFunc)
		*/
		int m_ActiveErrFuncIndex;

#endif
	};
}

#endif
