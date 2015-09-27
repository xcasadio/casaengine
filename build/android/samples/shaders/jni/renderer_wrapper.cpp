//#include "game.h"
//#include "macros.h"

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <android/log.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>

//#include "renderer_wrapper.h"
#include "SampleCubeAndroid.h"
#include "IO/IOManager.h"
#include "Log/LogManager.h"
#include "Log/LoggerAndroid.h"
#include "Log/LogVerbose.h"
#include "Window/Event.h"

#define LOG_TAG "ShaderSample"

#define LOG_D(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOG_F(...) __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__)
//#define LOG_F(fn_name) __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "JNI Called : " fn_name )

#ifdef __cplusplus
extern "C" {
#endif

SampleCubeAndroid game;

/**
 *
 */
JNIEXPORT void JNICALL Java_com_casaproduction_casaengine_RendererWrapper_initAssetManager(JNIEnv * env, jclass jclazz, 
	jobject java_asset_manager)
{
	//UNUSED(jclazz);

	AAssetManager *asset_manager = AAssetManager_fromJava(env, java_asset_manager);
	IOManager::SetAssetManager(asset_manager);
}

/**
 *
 */
JNIEXPORT void JNICALL
Java_com_casaproduction_casaengine_RendererWrapper_onSurfaceCreated(JNIEnv * env, jclass cls)
{
	//UNUSED(env);
	//UNUSED(cls);
	// 
	Logging.AddLogger(NEW_AO CasaEngine::LoggerAndroid());
}

/**
 *
 */
JNIEXPORT void JNICALL 
Java_com_casaproduction_casaengine_RendererWrapper_onSurfaceChanged(JNIEnv * env, jclass cls, 
	jint width, jint height) {
	//UNUSED(env);
	//UNUSED(cls);
	// 
	try
	{
		game.Run(width, height, 32);
	}
	catch (const std::exception& ex)
	{
		Logging.Log(CasaEngine::Fatal, ex.what());
	}
	catch (...)
	{
		Logging.Log(CasaEngine::Fatal, "generic exception");
	}
}

/**
 *
 */
JNIEXPORT void JNICALL 
Java_com_casaproduction_casaengine_RendererWrapper_onDrawFrame(JNIEnv* env, jclass cls)
{
	//UNUSED(env);
	//UNUSED(cls);

	game.MainLoop();
}

//TODO: exit ? game.EndRun();

////////////////////////////////////////////////////////////

/**
 *
 */
JNIEXPORT void JNICALL 
Java_com_casaproduction_casaengine_RendererWrapper_onTouchPress(JNIEnv* env, jclass cls, 
	int index, jfloat normalized_x, jfloat normalized_y)
{
	//UNUSED(env);
	//UNUSED(cls);
	
	//Logging.Log(CasaEngine::Trace, "JNI Called onTouchPress");
	CasaEngine::SystemEvent event;
	event.Type = CasaEngine::SystemEvent::TouchDown;
	event.Touch.index = index;
	event.Touch.X = normalized_x;
	event.Touch.Y = normalized_y;
	game.GetWindow()->GetInput()->OnEvent(event);
}

/**
 *
 */
JNIEXPORT void JNICALL 
Java_com_casaproduction_casaengine_RendererWrapper_onTouchRelease(JNIEnv* env, jclass cls, 
	int index, jfloat normalized_x, jfloat normalized_y)
{
	//UNUSED(env);
	//UNUSED(cls);
	//Logging.Log(CasaEngine::Trace, "JNI Called onTouchRelease");
	CasaEngine::SystemEvent event;
	event.Type = CasaEngine::SystemEvent::TouchUp;
	event.Touch.index = index;
	event.Touch.X = normalized_x;
	event.Touch.Y = normalized_y;
	game.GetWindow()->GetInput()->OnEvent(event);
}

/**
 *
 */
JNIEXPORT void JNICALL 
Java_com_casaproduction_casaengine_RendererWrapper_onTouchDrag(JNIEnv* env, jclass cls, 
	int index, jfloat normalized_x, jfloat normalized_y)
{
	//UNUSED(env);
	//UNUSED(cls);
	//Logging.Log(CasaEngine::Trace, "JNI Called onTouchDrag");
	CasaEngine::SystemEvent event;
	event.Type = CasaEngine::SystemEvent::TouchMove;
	event.Touch.index = index;
	event.Touch.X = normalized_x;
	event.Touch.Y = normalized_y;
	game.GetWindow()->GetInput()->OnEvent(event);
}

#ifdef __cplusplus
}
#endif
