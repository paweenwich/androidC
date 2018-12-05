LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE 	:= libtoluapplib
LOCAL_SRC_FILES := tolua_event.c tolua_is.c tolua_map.c tolua_push.c tolua_to.c

#LOCAL_CFLAGS +=  -std=c++11

include $(BUILD_STATIC_LIBRARY)    # <-- Use this to build an executable.

include $(CLEAR_VARS)

LOCAL_MODULE := toluapp
LOCAL_SRC_FILES := tolua.c toluabind.c
LOCAL_STATIC_LIBRARIES := liblualib libtoluapplib
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog   # whatever ld flags you like
LOCAL_CFLAGS += -Wno-write-strings -Wformat -save-temps -g# -O0

include $(BUILD_EXECUTABLE)    # <-- Use this to build an executable.

#include $(CLEAR_VARS)

#LOCAL_MODULE := lua
#LOCAL_SRC_FILES := lua.c
#LOCAL_STATIC_LIBRARIES := liblualib
#LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog   # whatever ld flags you like
#LOCAL_CFLAGS += -Wno-write-strings -Wformat -save-temps -g# -O0

#include $(BUILD_EXECUTABLE)    # <-- Use this to build an executable.