package com.casaproduction.casaengine;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.Toast;
import android.util.Log;

public class MainActivity extends Activity {
	private GLSurfaceView glSurfaceView;
	private boolean rendererSet;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
		ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();

		//getExternalStorageDirectory()
		
		final boolean supportsEs2 = 
			configurationInfo.reqGlEsVersion >= 0x20000 || isProbablyEmulator();

		if (supportsEs2) {
			glSurfaceView = new GLSurfaceView(this);
			
			if (isProbablyEmulator()) {
				// Avoids crashes on startup with some emulator images.
				glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
			}
			
			Log.d("ShaderSample", "GLES 2 OK");
			//android.os.Debug.waitForDebugger();

			final RendererWrapper rendererWrapper = new RendererWrapper(this);
			glSurfaceView.setEGLContextClientVersion(2);
			glSurfaceView.setRenderer(rendererWrapper);
			rendererSet = true;
			setContentView(glSurfaceView);
			
			glSurfaceView.setOnTouchListener(new OnTouchListener() {
	            @Override
	            public boolean onTouch(View v, MotionEvent event) {
	                if (event != null) {           
	                    // Convert touch coordinates into normalized device
	                    // coordinates, keeping in mind that Android's Y
	                    // coordinates are inverted.
	                    final float normalizedX = event.getX(); //(event.getX() / (float) v.getWidth()) * 2 - 1;
	                    final float normalizedY = -event.getY(); //-((event.getY() / (float) v.getHeight()) * 2 - 1);
	                    final int index = event.getActionIndex();
	                    
	        			Log.d("ShaderSample", "Touch event " + actionToString(event.getAction()));
	                    
	                    if (event.getAction() == MotionEvent.ACTION_DOWN) {
	                        glSurfaceView.queueEvent(new Runnable() {
	                            @Override
	                            public void run() {
	                            	rendererWrapper.handleTouchPress(
	                            			index, normalizedX, normalizedY);
	                            }
	                        });
	                    } else if (event.getAction() == MotionEvent.ACTION_UP) {
	                        glSurfaceView.queueEvent(new Runnable() {
	                            @Override
	                            public void run() {
	                            	rendererWrapper.handleTouchRelease(
	                            			index, normalizedX, normalizedY);
	                            }
	                        });
	                    } else if (event.getAction() == MotionEvent.ACTION_MOVE) {
	                        glSurfaceView.queueEvent(new Runnable() {
	                            @Override
	                            public void run() {
	                            	rendererWrapper.handleTouchDrag(
	                            			index, normalizedX, normalizedY);
	                            }
	                        });
	                    }                    

	                    return true;                    
	                } else {
	                    return false;
	                }
	            }
	        });
		} else {
			// Should never be seen in production, since the manifest filters
			// unsupported devices.
			Toast.makeText(this, "This device does not support OpenGL ES 2.0.",
					Toast.LENGTH_LONG).show();
			return;
		}
	}

	protected String actionToString(int action) {
	    switch (action) {
	        case MotionEvent.ACTION_DOWN:
	            return "ACTION_DOWN";
	        case MotionEvent.ACTION_UP:
	            return "ACTION_UP";
	        case MotionEvent.ACTION_CANCEL:
	            return "ACTION_CANCEL";
	        case MotionEvent.ACTION_OUTSIDE:
	            return "ACTION_OUTSIDE";
	        case MotionEvent.ACTION_MOVE:
	            return "ACTION_MOVE";
/*	        case MotionEvent.ACTION_HOVER_MOVE:
	            return "ACTION_HOVER_MOVE";
	        case MotionEvent.ACTION_SCROLL:
	            return "ACTION_SCROLL";
	        case MotionEvent.ACTION_HOVER_ENTER:
	            return "ACTION_HOVER_ENTER";
	        case MotionEvent.ACTION_HOVER_EXIT:
	            return "ACTION_HOVER_EXIT";*/
	    }
	    int index = (action & MotionEvent.ACTION_POINTER_INDEX_MASK) >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
	    switch (action & MotionEvent.ACTION_MASK) {
	        case MotionEvent.ACTION_POINTER_DOWN:
	            return "ACTION_POINTER_DOWN(" + index + ")";
	        case MotionEvent.ACTION_POINTER_UP:
	            return "ACTION_POINTER_UP(" + index + ")";
	        default:
	            return Integer.toString(action);
	    }
	}

	private boolean isProbablyEmulator() {
		return true; //Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1
				/*&& (Build.FINGERPRINT.startsWith("generic")
						|| Build.FINGERPRINT.startsWith("unknown")
						|| Build.MODEL.contains("google_sdk")
						|| Build.MODEL.contains("Emulator")
						|| Build.MODEL.contains("Android SDK built for x86"));*/
	}

	@Override
	protected void onPause() {
		super.onPause();

		if (rendererSet) {
			glSurfaceView.onPause();
		}
	}

	@Override
	protected void onResume() {
		super.onResume();

		if (rendererSet) {
			glSurfaceView.onResume();
		}
	}
}