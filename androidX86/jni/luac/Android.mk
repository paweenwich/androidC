LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE 	:= liblualib
LOCAL_SRC_FILES := lapi.c lauxlib.c lbaselib.c lbitlib.c lcode.c lcorolib.c lctype.c ldblib.c ldebug.c \
	    ldo.c ldump.c lfunc.c lgc.c linit.c liolib.c lmathlib.c lmem.c loadlib.c lobject.c lopcodes.c\
	    loslib.c lparser.c lstate.c lstring.c lstrlib.c ltable.c ltablib.c ltm.c lundump.c\
	    lvm.c lzio.c llex.c 

#LOCAL_CFLAGS +=  -std=c++11

include $(BUILD_STATIC_LIBRARY)    # <-- Use this to build an executable.

include $(CLEAR_VARS)

LOCAL_MODULE := luac
LOCAL_SRC_FILES := luac.c
#LOCAL_CPPFLAGS := -std=c++11         # whatever g++ flags you like
LOCAL_STATIC_LIBRARIES := liblualib
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog   # whatever ld flags you like
LOCAL_CFLAGS += -Wno-write-strings -Wformat -save-temps -g# -O0

include $(BUILD_EXECUTABLE)    # <-- Use this to build an executable.

include $(CLEAR_VARS)

LOCAL_MODULE := lua
LOCAL_SRC_FILES := lua.c
#LOCAL_CPPFLAGS := -std=c++11         # whatever g++ flags you like
LOCAL_STATIC_LIBRARIES := liblualib
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog   # whatever ld flags you like
LOCAL_CFLAGS += -Wno-write-strings -Wformat -save-temps -g# -O0

include $(BUILD_EXECUTABLE)    # <-- Use this to build an executable.