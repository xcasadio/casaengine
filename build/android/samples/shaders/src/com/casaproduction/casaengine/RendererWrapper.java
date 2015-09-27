package com.casaproduction.casaengine;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView.Renderer;
import android.util.Log;

public class RendererWrapper implements Renderer {
	static 
	{
		Log.d("ShaderSample", "Load all native libs");
		System.loadLibrary("gnustl_shared");
		System.loadLibrary("iconv");
		System.loadLibrary("casaenginesystem");
		System.loadLibrary("casaenginecore");
		System.loadLibrary("casaengineengine");
		System.loadLibrary("casaengineframework");
		System.loadLibrary("sampleshader");
		Log.d("ShaderSample", "End loading all native libs");
	}
	
	private final Context context;
	
	public RendererWrapper(Context context) {
		this.context = context;
	}
	
	////////////////////////////////////////
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		try
		{
            onSurfaceCreated();
			initAssetManager(context.getAssets());
        }
		catch(UnsatisfiedLinkError e)
		{
			e.printStackTrace();
        }
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		try
		{
            onSurfaceChanged(width, height);
        }
		catch(UnsatisfiedLinkError e)
		{
			e.printStackTrace();
        }
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		try
		{
            onDrawFrame();
        }
		catch(UnsatisfiedLinkError e)
		{
			e.printStackTrace();
        }
	}
	
	public void handleTouchPress(int index, float normalizedX, float normalizedY) {
		try
		{
            onTouchPress(index, normalizedX, normalizedY);
        }
		catch(UnsatisfiedLinkError e)
		{
			e.printStackTrace();
        }
	}
	
	public void handleTouchRelease(int index, float normalizedX, float normalizedY) {
		try
		{
            onTouchRelease(index, normalizedX, normalizedY);
        }
		catch(UnsatisfiedLinkError e)
		{
			e.printStackTrace();
        }
	}

	public void handleTouchDrag(int index, float normalizedX, float normalizedY) {
		try
		{
            onTouchDrag(index, normalizedX, normalizedY);
        }
		catch(UnsatisfiedLinkError e)
		{
			e.printStackTrace();
        }
	}
	
	private native void initAssetManager(AssetManager assetManager);
	private native void onSurfaceCreated();
	private native void onSurfaceChanged(int width, int height);
	private native void onDrawFrame();
	private native void onTouchPress(int index, float normalized_x, float normalized_y);
	private native void onTouchRelease(int index, float normalized_x, float normalized_y);
	private native void onTouchDrag(int index, float normalized_x, float normalized_y);
}