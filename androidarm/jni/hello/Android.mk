LOCAL_PATH := $(call my-dir)
	
include $(CLEAR_VARS)

LOCAL_MODULE 	:= hello
LOCAL_SRC_FILES := lua_hello.cpp hello.cpp  \
		../util/util.cpp ../util/logger.cpp ../util/payload.cpp ../util/Mutex.cpp \
		../util/PtraceUtil.cpp ../util/ProcessScanner.cpp ../util/ProcessScannerCache.cpp \
		../luac/luascript.cpp 
LOCAL_CFLAGS +=  -Ijni/luac -std=c++11 -Wno-write-strings  #-save-temps
LOCAL_STATIC_LIBRARIES := lua-prebuilt tolua-prebuilt
LOCAL_LDLIBS    := -llog

include $(BUILD_EXECUTABLE)    # <-- Use this to build an executable.
