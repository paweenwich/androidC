LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libloader
LOCAL_SRC_FILES := loader.cpp BaseCommandService.cpp \
#	../util/util.cpp ../util/SimpleTCPServer.cpp \
#		../util/ProcessScanner.cpp
LOCAL_STATIC_LIBRARIES := util luaserver liblualib libtolualib
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)
