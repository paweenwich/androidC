ARCH := armeabi
	
LOCAL_PATH := $(call my-dir)
	
include $(CLEAR_VARS)
LOCAL_MODULE := lua-prebuilt
LOCAL_SRC_FILES := ../luac/liblua.a
include $(PREBUILT_STATIC_LIBRARY)	

include $(CLEAR_VARS)
LOCAL_MODULE := tolua-prebuilt
LOCAL_SRC_FILES := ../luac/libtolua.a
include $(PREBUILT_STATIC_LIBRARY)	

 

include $(CLEAR_VARS)
#LIB_PATH := $(LOCAL_PATH)
LOCAL_MODULE    := libloader
LOCAL_SRC_FILES := lua_server.cpp MonoEval.cpp MonoHooker.cpp Server.cpp loader.cpp \
	../util/logger.cpp ../util/payload.cpp ../util/Mutex.cpp \
	../luac/luascript.cpp 
LOCAL_STATIC_LIBRARIES := lua-prebuilt tolua-prebuilt
LOCAL_CFLAGS +=  -Ijni/luac -std=c++11 -Wno-write-strings  -fexceptions -fpermissive 
#LOCAL_LDLIBS += -L$(LIB_PATH)

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
#LIB_PATH := $(LOCAL_PATH)
LOCAL_MODULE    := testloader
LOCAL_SRC_FILES := lua_server.cpp MonoEval.cpp MonoHooker.cpp Server.cpp loader.cpp \
	../util/logger.cpp ../util/payload.cpp ../util/Mutex.cpp \
	../luac/luascript.cpp 
LOCAL_STATIC_LIBRARIES := lua-prebuilt tolua-prebuilt
LOCAL_CFLAGS +=  -Ijni/luac -std=c++11 -Wno-write-strings  -fexceptions -fpermissive 
#LOCAL_LDLIBS += -L$(LIB_PATH)

include $(BUILD_EXECUTABLE)