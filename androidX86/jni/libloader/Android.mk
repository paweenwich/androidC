LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libloader
LOCAL_SRC_FILES := loader.cpp BaseCommandService.cpp ../util/util.cpp ../util/SimpleTCPServer.cpp 
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)
