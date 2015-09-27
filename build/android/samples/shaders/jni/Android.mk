# Copyright (C) 2014 CasaEngine : sample shaders
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)

####################################################################
# CasaEngine.System
####################################################################
include $(CLEAR_VARS)

LOCAL_MODULE := casaenginesystem_shared
LOCAL_SRC_FILES := ../../../CasaEngineFramework/libs/$(TARGET_ARCH_ABI)/libcasaenginesystem.so

include $(PREBUILT_SHARED_LIBRARY)

####################################################################
# CasaEngine.Core
####################################################################
include $(CLEAR_VARS)

LOCAL_MODULE := casaenginecore_shared
LOCAL_SRC_FILES := ../../../CasaEngineFramework/libs/$(TARGET_ARCH_ABI)/libcasaenginecore.so

include $(PREBUILT_SHARED_LIBRARY)

####################################################################
# CasaEngine.Engine
####################################################################
include $(CLEAR_VARS)

LOCAL_MODULE := casaengineengine_shared
LOCAL_SRC_FILES := ../../../CasaEngineFramework/libs/$(TARGET_ARCH_ABI)/libcasaengineengine.so

include $(PREBUILT_SHARED_LIBRARY)

####################################################################
# CasaEngine.Framework
####################################################################
include $(CLEAR_VARS)

LOCAL_MODULE := casaengineframework_shared
LOCAL_SRC_FILES := ../../../CasaEngineFramework/libs/$(TARGET_ARCH_ABI)/libcasaengineframework.so

include $(PREBUILT_SHARED_LIBRARY)

####################################################################
# iconv
####################################################################
include $(CLEAR_VARS)

LOCAL_MODULE := iconv_shared
LOCAL_SRC_FILES := ../../../CasaEngineFramework/libs/$(TARGET_ARCH_ABI)/libiconv.so

include $(PREBUILT_SHARED_LIBRARY)

####################################################################
# shader sample
####################################################################
SAMPLE_ROOT_PATH := $(LOCAL_PATH)/../../../../../samples/android/cube
SAMPLE_RELATIVE_PATH := ../../../../../samples/android/cube
CASAENGINE_RELATIVE_PATH := $(LOCAL_PATH)/../../../../../src
EXTERNAL_PATH := $(LOCAL_PATH)/../../../../../external

include $(CLEAR_VARS)

LOCAL_MODULE := sampleshader
LOCAL_MODULE_FILENAME := libsampleshader

LOCAL_LDLIBS := -llog -lz -lm -ldl -lGLESv2 -lEGL -landroid

LOCAL_SHARED_LIBRARIES := \
	gnustl_shared \
	iconv_shared \
	casaenginesystem_shared \
	casaenginecore_shared \
	casaengineengine_shared \
	casaengineframework_shared

APP_OPTIM := debug
LOCAL_CFLAGS := -g -ggdb -O1 -DDEBUG -DANDROID_NDK -DANDROID

#LOCAL_CPPFLAGS := -std=c++0x
LOCAL_CPP_FEATURES := rtti exceptions

LOCAL_SRC_FILES := \
	$(SAMPLE_RELATIVE_PATH)/SampleCubeAndroid.cpp \
	renderer_wrapper.cpp

LOCAL_C_INCLUDES := $(SAMPLE_ROOT_PATH)/ \
	$(CASAENGINE_RELATIVE_PATH)/System/ \
	$(CASAENGINE_RELATIVE_PATH)/Core/ \
	$(CASAENGINE_RELATIVE_PATH)/Engine/ \
	$(CASAENGINE_RELATIVE_PATH)/Framework/ \
	$(EXTERNAL_PATH)/CEGUI \
	$(EXTERNAL_PATH)/bullet/include

include $(BUILD_SHARED_LIBRARY)
