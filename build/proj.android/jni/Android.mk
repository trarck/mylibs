LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := mylibs_android

LOCAL_MODULE_FILENAME := libmylibs_android

LOCAL_SRC_FILES := main.cpp 

LOCAL_C_INCLUDES :=  $(LOCAL_PATH)/../../../yh

LOCAL_STATIC_LIBRARIES := yh_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)