
#ifndef DX9MACRO_H_
#define DX9MACRO_H_

#include "SystemPlatform.h"

#include <winnt.h>
#include <winerror.h>
#include "dxerr.h"
#include "Graphics\Renderer\Renderer.h"
#include "CompilationConfig.h"


namespace CasaEngine
{

#ifdef CA_TRACE_API_3D

/**
 * 
 */
inline void DXTraceAPIFunc(const char* pFunc_, const std::string& File, unsigned int Line)
{
	CA_TRACE("\t%s : %s (%d)\n",
		pFunc_,
		File.substr(File.find_last_of("\\/") + 1).c_str(), 
		Line);
}

#if 1
#	define DXTraceAPI(func, file, line) DXTraceAPIFunc(func, file, line)
#else
#	define DXTraceAPI(func, file, line) CA_NOOP()
#endif

#define DXCheck(Func) (DXTraceAPI(#Func, __FILE__, __LINE__), DXOnError(#Func, (HRESULT)(Func), __FILE__, __LINE__))
#define DXTraceError(hr) DXTRACE_ERR(nullptr, hr)

////////////////////////////////////////////////////////////
/// Check DirectX error
////////////////////////////////////////////////////////////
inline HRESULT DXOnError(const char* pFunc_, HRESULT hr, const std::string& file_, DWORD Line)
{
	if (FAILED(hr))
	{
		//return DXTrace(file_.c_str(), Line, hr, nullptr, false);
		CA_ERROR("An internal DirectX call failed %s => %s (%d) : %s\n",
			pFunc_, 
			file_.substr(file_.find_last_of("\\/") + 1).c_str(), 
			Line, 
			DXGetErrorDescription(hr));
	}

	return hr;
}

#else

#define DXCheck(Func) (Func)

#endif // #if CA_TRACE_API_3D

} // namespace CasaEngine

#endif // DX9MACRO_H_
