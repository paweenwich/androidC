LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libarmhlpx86
LOCAL_SRC_FILES := armhlp.cpp ../util/util.cpp
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)
