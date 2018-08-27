LOCAL_PATH := $(call my-dir)
	
include $(CLEAR_VARS)

LOCAL_MODULE 	:= upgrade
LOCAL_SRC_FILES := upgrade.cpp \
		../util/util.cpp ../util/logger.cpp ../util/payload.cpp ../util/Mutex.cpp \
		../util/PtraceUtil.cpp ../util/ProcessScanner.cpp
LOCAL_CFLAGS +=  -Ijni/luac -std=c++11 -Wno-write-strings  #-save-temps
LOCAL_STATIC_LIBRARIES := lua-prebuilt tolua-prebuilt
LOCAL_LDLIBS    := -llog

include $(BUILD_EXECUTABLE)    # <-- Use this to build an executable.
