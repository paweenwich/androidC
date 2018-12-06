LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE 	:= util
LOCAL_SRC_FILES := util.cpp logger.cpp SimpleTCPServer.cpp Mutex.cpp ProcessScanner.cpp PtraceUtil.cpp \
		payload.cpp
LOCAL_CFLAGS +=  -std=c++11

include $(BUILD_STATIC_LIBRARY)    # <-- Use this to build an executable.
