#include "Base.h"
#include <cstdlib>
#include "DynamicModule.h"
#include "Exceptions.h"

#if defined(__WIN32__) || defined(_WIN32)
#   if defined(_MSC_VER)
#       pragma warning(disable : 4552)  // warning: operator has no effect; expected operator with side-effect
#   endif
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#   define DYNLIB_LOAD( a ) LoadLibrary( (a).c_str() )
#   define DYNLIB_GETSYM( a, b ) GetProcAddress( a, (b).c_str() )
#   define DYNLIB_UNLOAD( a ) !FreeLibrary( a )
typedef HMODULE DYNLIB_HANDLE;
#endif

#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__HAIKU__) || defined(__CYGWIN__)
#   include "dlfcn.h"
#   define DYNLIB_LOAD( a ) dlopen( (a).c_str(), RTLD_LAZY )
#   define DYNLIB_GETSYM( a, b ) dlsym( a, (b).c_str() )
#   define DYNLIB_UNLOAD( a ) dlclose( a )
typedef void* DYNLIB_HANDLE;
#endif

// setup default-default path
#ifndef CA_MODULE_DIR
#define CA_MODULE_DIR "./bin/"
#endif

namespace CasaEngine
{
	struct DynamicModule::Impl
	{
		Impl(const std::string& name) :
			d_moduleName(name),
			d_handle(0)
		{}

		~Impl()
		{
			DYNLIB_UNLOAD(d_handle);
		}

		std::string d_moduleName;
		DYNLIB_HANDLE d_handle;
	};

	static const char MODULE_DIR_VAR_NAME[] = "CA_MODULE_DIR";

#if defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN__)
	static const std::string LibraryExtension(".dll");
#elif defined(__APPLE__)
	static const std::string LibraryExtension(".dylib");
#else
	static const std::string LibraryExtension(".so");
#endif
	
	// return whether module name has it's extension in place
	static bool hasDynamicLibraryExtension(const std::string& name)
	{
		const size_t ext_len = LibraryExtension.length();

		if (name.length() < ext_len)
			return false;

		return name.compare(name.length() - ext_len, ext_len, LibraryExtension) == 0;
	}

	static void appendDynamicLibraryExtension(std::string& name)
	{
		name.append(LibraryExtension);
	}

	static void addLibraryNameSuffixes(std::string& name)
	{
#ifdef CA_HAS_BUILD_SUFFIX
		name += CA_BUILD_SUFFIX;
#endif

		appendDynamicLibraryExtension(name);
	}

	static std::string getModuleDirEnvVar()
	{
		if (const char* envModuleDir = getenv(MODULE_DIR_VAR_NAME))
			return std::string(envModuleDir);

		return std::string();
	}
	
	// Returns a std::string containing the last failure message from the platform's
	// dynamic loading system.
	static std::string getFailureString()
	{
		std::string retMsg;
#if defined(__linux__) || defined (__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__HAIKU__) || defined(__CYGWIN__)
		retMsg = dlerror();
#elif defined(__WIN32__) || defined(_WIN32)
		LPVOID msgBuffer;

		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			0,
			GetLastError(),
			MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
			reinterpret_cast<LPTSTR>(&msgBuffer),
			0,
			0))
		{
			retMsg = static_cast<LPTSTR>(msgBuffer);
			LocalFree(msgBuffer);
		}
		else
		{
			retMsg = "Unknown Error";
		}
#else
		retMsg = "Unknown Error";
#endif
		return retMsg;
	}

	static DYNLIB_HANDLE DynLibLoad(const std::string& name)
	{
		DYNLIB_HANDLE handle = 0;

		// prefer whatever location is set in CEGUI_MODULE_DIR environment var
		const std::string envModuleDir(getModuleDirEnvVar());

		if (!envModuleDir.empty())
			handle = DYNLIB_LOAD(envModuleDir + '/' + name);

		if (!handle)
#ifdef __APPLE__
			// on apple, look in the app bundle frameworks directory
			handle = DYNLIB_LOAD("@executable_path/../Frameworks/" + name);

		if (!handle)
#endif
			// try loading without any explicit location (i.e. use OS search path)
			handle = DYNLIB_LOAD(name);

		// finally, try using the compiled-in module directory
		if (!handle)
			handle = DYNLIB_LOAD(CA_MODULE_DIR + name);

		return handle;
	}
	
	DynamicModule::DynamicModule(const std::string& name) :
		d_pimpl(new Impl(name))
	{
		if (name.empty())
			return;

		if (!hasDynamicLibraryExtension(d_pimpl->d_moduleName))
			addLibraryNameSuffixes(d_pimpl->d_moduleName);

		d_pimpl->d_handle = DynLibLoad(d_pimpl->d_moduleName);

#if defined(__linux__) || defined(__APPLE__) || defined(__MINGW32__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__HAIKU__)
		// see if adding a leading 'lib' helps us to open the library
		if (!d_pimpl->d_handle && d_pimpl->d_moduleName.compare(0, 3, "lib") != 0)
		{
			d_pimpl->d_moduleName.insert(0, "lib");
			d_pimpl->d_handle = DynLibLoad(d_pimpl->d_moduleName);
		}
#endif

#if defined(__CYGWIN__)
		// see if adding a leading 'cyg' helps us to open the library
		if (!d_pimpl->d_handle && d_pimpl->d_moduleName.compare(0, 3, "cyg") != 0)
		{
			d_pimpl->d_moduleName.insert(0, "cyg");
			d_pimpl->d_handle = DynLibLoad(d_pimpl->d_moduleName);
		}
#endif

		// check for library load failure
		if (!d_pimpl->d_handle)
			throw CException("Failed to load module '" +
				d_pimpl->d_moduleName + "': " + getFailureString());
	}
	
	DynamicModule::~DynamicModule()
	{
		delete d_pimpl;
	}
	
	const std::string& DynamicModule::getModuleName() const
	{
		return d_pimpl->d_moduleName;
	}
	
	void* DynamicModule::getSymbolAddress(const std::string& symbol) const
	{
		return static_cast<void*>(DYNLIB_GETSYM(d_pimpl->d_handle, symbol));
	}
}