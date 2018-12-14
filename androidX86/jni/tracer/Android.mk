LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := tracerx86
LOCAL_SRC_FILES := tracer.cpp
LOCAL_STATIC_LIBRARIES := util luaserver liblualib libtolualib
LOCAL_CPPFLAGS := -std=c++11         # whatever g++ flags you like
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog   # whatever ld flags you like
LOCAL_CFLAGS += -I../tolua -Wno-write-strings -Wformat -save-temps -g -fexceptions# -O0

include $(BUILD_EXECUTABLE)    # <-- Use this to build an executable.

include $(CLEAR_VARS)

LOCAL_MODULE := elf
LOCAL_SRC_FILES := elf.cpp
LOCAL_STATIC_LIBRARIES := util
LOCAL_CPPFLAGS := -std=c++11         # whatever g++ flags you like
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog   # whatever ld flags you like
LOCAL_CFLAGS += -I../tolua -Wno-write-strings -Wformat -save-temps -g -fexceptions# -O0

include $(BUILD_EXECUTABLE)    # <-- Use this to build an executable.
