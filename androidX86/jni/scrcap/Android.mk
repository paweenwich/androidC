LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := scrcapx86
LOCAL_SRC_FILES := main.cpp ../util/util.cpp ../util/PtraceUtil.cpp ../util/logger.cpp \
		    ../util/payload.cpp ../util/Mutex.cpp ../util/ProcessScanner.cpp
LOCAL_CPPFLAGS := -std=c++11         # whatever g++ flags you like
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog   # whatever ld flags you like
LOCAL_CFLAGS += -Wno-write-strings -Wformat -save-temps -g# -O0

include $(BUILD_EXECUTABLE)    # <-- Use this to build an executable.
