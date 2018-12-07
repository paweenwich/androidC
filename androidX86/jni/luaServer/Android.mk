LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := luaserver
LOCAL_SRC_FILES := lua_server.cpp MonoHooker.cpp MonoEval.cpp
#	../util/util.cpp ../util/SimpleTCPServer.cpp \
#		../util/ProcessScanner.cpp
LOCAL_STATIC_LIBRARIES := util liblualib libtolua
#LOCAL_LDLIBS    := -llog
LOCAL_CFLAGS +=  -fpermissive -Ijni/tolua -std=c++11 -Wno-write-strings
include $(BUILD_STATIC_LIBRARY)
