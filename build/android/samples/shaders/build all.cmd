@echo off

cls

cd ..\..
call "build CasaEngine.cmd"

cd samples\shaders

if "%COMPUTERNAME%"=="DK272433" (goto :path1) else (goto :path2)

:path1
set JAVA_HOME=C:\Program Files\Java\jdk1.8.0
set ANDROID_DIR=C:\dev\test\Android
goto :pathcommon

:path2
set JAVA_HOME=C:\Program Files\Java\jdk1.7.0_02
set ANDROID_DIR=H:\Developpement\Android

:pathcommon
set ANDROID_SDK=%ANDROID_DIR%\android-sdk
set NDK_ROOT=%ANDROID_DIR%\android-ndk-r9c

echo ======================================================
echo == Clean All
echo ======================================================
del /Q /S bin
del /Q /S gen
del /Q /S libs
del /Q /S obj

echo ======================================================
echo == Build JNI
echo ======================================================
call "%NDK_ROOT%\ndk-build.cmd" -j NDK_DEBUG=1

if %errorlevel% gtr 0 goto :JNIError
goto :buildJava

:JNIError
echo ******** BUILD JNI FAILED ********
goto :EOF

:buildJava
echo ======================================================
echo == Build Java
echo ======================================================
call "%ANDROID_SDK%\tools\android.bat" update project -p . -t android-14 --subprojects
call "%ANDROID_DIR%\apache-ant-1.9.0\bin\ant.bat" debug

if %errorlevel% gtr 0 goto :javaError
goto :install

:javaError
echo ******** BUILD JAVA FAILED ********
goto :EOF

:install
echo ======================================================
echo == Uninstall application
echo ======================================================
call "%ANDROID_SDK%\platform-tools\adb.exe" uninstall com.casaproduction.casaengine

echo ======================================================
echo == Install application
echo ======================================================
call "%ANDROID_SDK%\platform-tools\adb.exe" install -r bin/MainActivity-debug.apk

echo ======================================================
echo == Launch application
echo ======================================================
call "%ANDROID_SDK%\platform-tools\adb.exe" shell am start -n com.casaproduction.casaengine/com.casaproduction.casaengine.MainActivity

rem call "%ANDROID_DIR%\apache-ant-1.9.0\bin\ant.bat" release
rem call "%ANDROID_SDK%\platform-tools\adb.exe" install -r bin/MainActivity-release-unsigned.apk
