#ifndef LUA_REQUIRED_H_
#define LUA_REQUIRED_H_

#include <fstream>

#include "SFML\Window\Mouse.hpp"
#include "SFML\Window\Keyboard.hpp"

#include "IO/IFile.h"
#include "IO/File.h"
#include "IO/IOManager.h"
#include "Log/LogManager.h"
#include "Maths/Vector2.h"
#include "Maths/Vector3.h"
#include "Maths/Vector4.h"
#include "Maths/Matrix3.h"
#include "Maths/Matrix4.h"
#include "Maths/Plane.h"
#include "Maths/Quaternion.h"
#include "Maths/Random.h"
#include "Maths/Rectangle.h"
//#include "Maths/Shape/Box.h"

#include "EventHandler/IteratorBase.h"
#include "EventHandler/EventArgs.h"
#include "EventHandler/Event.h"
#include "EventHandler/EventSet.h"
#include "EventHandler/GlobalEventSet.h"

#include "Memory/MemoryAllocation.h"

#define __operator_increment    operator++
#define __operator_decrement    operator--
#define __operator_dereference  operator*


#if defined(_MSC_VER) && !defined(snprintf)
#   define snprintf _snprintf
#endif

// map the utf8string funcs to c-string funcs
// #define tolua_pushutf8string(x,y) tolua_pushstring(x,y)
// #define tolua_isutf8string tolua_isstring
// #define tolua_isutf8stringarray tolua_isstringarray
// #define tolua_pushfieldutf8string(L,lo,idx,s) tolua_pushfieldstring(L, lo, idx, s)
// #define tolua_toutf8string tolua_tostring
// #define tolua_tofieldutf8string tolua_tofieldstring

// typedef std::string string;
// //typedef unsigned char* utf8string;
// typedef char* utf8string;

#ifdef Mtolua_new
#define Mtolua_new(EXP) NEW_AO EXP
#endif

#ifdef Mtolua_delete
#define Mtolua_delete(EXP) DELETE_AO EXP
#endif

namespace CasaEngine
{
	/*************************************************************************
    Helper class to enable us to represent an Event::Connection object
    (which is actually a RefCounted<BoundSlot> object)
	*************************************************************************/
	class EventConnection
	{
		RefCounted<BoundSlot> d_slot;

	public:
		EventConnection(RefCounted<BoundSlot> slot);
		bool connected() const;
		void disconnect();
	};

}

// the binding file generates alot of
// warning C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
#if defined(_MSC_VER)
#   pragma warning(disable : 4800)
#endif

#endif // LUA_REQUIRED_H_