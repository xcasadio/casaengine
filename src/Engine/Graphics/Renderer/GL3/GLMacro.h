
#ifndef GLMACRO_H_
#define GLMACRO_H_

#include "SystemPlatform.h"

#if CA_PLATFORM_ANDROID

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else

#include <GL/glew.h>
#include <gl/gl.h>
#include "Extensions/glext.h"

#endif // #if CA_PLATFORM_ANDROID

#include <string>
#include <ostream>

#include "Log\LogManager.h"
#include "Log\Logger.h"
#include "Macro.h"
#include "CompilationConfig.h"

namespace CasaEngine
{

#ifdef CA_TRACE_API_3D

/**
 * 
 */
inline void GLTraceAPIFunc(const char* pFunc_, const std::string& File, unsigned int Line)
{
	CA_TRACE("\t%s : %s (%d)\n",
		pFunc_,
		File.substr(File.find_last_of("\\/") + 1).c_str(), 
		Line);
}

#if 0
#	define GLTraceAPI(func, file, line) GLTraceAPIFunc(func, file, line)
#else
#	define GLTraceAPI(func, file, line) CA_NOOP()
#endif


/**
 * Macro that checks OpenGL state. If an error is present, it log it.
 * 
 * You cannot check for OpenGL errors between glBegin()/glEnd()-pairs, if you do,
 * you get an GL_INVALID_OPERATION error.
 */
#define GLCheck(Func) GLTraceAPI(#Func, __FILE__, __LINE__); (Func); GLCheckError(#Func, __FILE__, __LINE__)

	/**
	 * Internally used : used by the macro GLCheck
	 * Check the last OpenGL error and log it. 
	 */
	inline void GLCheckError(const char* pFunc_, const std::string& File, unsigned int Line)
	{
		GLenum errorCode = glGetError();

		while (errorCode != GL_NO_ERROR)
		{
			std::string strEnum = "unknown error";
			std::string strDesc = "no description";
			std::string strHint = "none";

			switch (errorCode)
			{
			case GL_INVALID_ENUM :
				strEnum = "GL_INVALID_ENUM";
				strDesc  = "an unacceptable value has been specified for an enumerated argument";
				strHint = "You probably tried to pass an enum value that is not specified as allowed for that command.";
				break;

			case GL_INVALID_VALUE :
				strEnum = "GL_INVALID_VALUE";
				strDesc  = "a numeric argument is out of range";					
				strHint = "E.g. this error is generated when you pass a negative value to a command that takes a sizei as parameter.";
				break;

			case GL_INVALID_OPERATION :
				strEnum = "GL_INVALID_OPERATION";
				strDesc  = "the specified operation is not allowed in the current state";
				strHint = "Some commands are not allowed between glBegin()/glEnd() pairs.";
				break;

			//No more used : fixed pipeline function
			/*
			case GL_STACK_OVERFLOW :
				strEnum = "GL_STACK_OVERFLOW";
				strDesc  = "this command would cause a stack overflow";
				strHint = "Calling glPushMatrix()/glPushAttrib()/glPushClientAttrib() to a full matrix causes this error.";
				break;

			case GL_STACK_UNDERFLOW :
				strEnum = "GL_STACK_UNDERFLOW";
				strDesc  = "this command would cause a stack underflow";
				strHint = "Calling glPopMatrix()/glPopAttrib()/glPopClientAttrib() to an empty matrix causes this error.";
				break;
			*/

			case GL_OUT_OF_MEMORY :
				strEnum = "GL_OUT_OF_MEMORY";
				strDesc  = "there is not enough memory left to execute the command";
				strHint = "If memory is exhausted as a side-effect of the execution of a command, this error may be generated. I.e., it is not definite whether or not the command was ignored or not.";
				break;

#if CA_PLATFORM_DESKTOP

			case GL_INVALID_FRAMEBUFFER_OPERATION_EXT :
				strEnum = "GL_INVALID_FRAMEBUFFER_OPERATION_EXT";
				strDesc  = "the object bound to FRAMEBUFFER_BINDING_EXT is not \"framebuffer complete\"";					
				break;

			case GL_TABLE_TOO_LARGE:
				strEnum = "GL_TABLE_TOO_LARGE";
				strDesc = "The specified table is too large. Offending command ignored.";
				break;

#endif // #if CA_PLATFORM_DESKTOP
			}

			CA_ERROR("An internal OpenGL call failed %s => %s (%d) : %s, %s (%s)\n",
				pFunc_, File.substr(File.find_last_of("\\/") + 1).c_str(), Line, strEnum.c_str(), strDesc.c_str(), strHint.c_str());

			errorCode = glGetError();
		} // end while
	}

#else

#define GLCheck(Func) (Func)

#endif // #if CA_TRACE_API_3D
	
} // namespace CasaEngine

#endif // GLMACRO_H_
