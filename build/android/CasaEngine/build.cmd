if "%COMPUTERNAME%"=="DK272433" (goto :path1) else (goto :path2)

:path1
set JAVA_HOME=C:\Program Files\Java\jdk1.8.0
set ANDROID_DIR=C:\dev\test\Android
goto :pathcommon

:path2
set JAVA_HOME=C:\Program Files\Java\jdk1.7.0_71
set ANDROID_DIR=C:\NVPACK

:pathcommon
set ANDROID_SDK=%ANDROID_DIR%\android-sdk-windows
set NDK_ROOT=%ANDROID_DIR%\android-ndk-r10d

call "%NDK_ROOT%\ndk-build.cmd" -j NDK_DEBUG=1
rem V=1 clean NDK_DEBUG=1