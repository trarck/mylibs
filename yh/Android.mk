LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := yh_static

LOCAL_MODULE_FILENAME := libyh

ifeq ($(USE_ARM_MODE),1)
LOCAL_ARM_MODE := arm
endif

LOCAL_SRC_FILES := \
	base/Ref.cpp \
    base/RefCount.cpp \
    base/RefPtr.cpp \
    io/Buffer.cpp \
    io/IeeeHalfPrecision.cpp \
    io/InputStream.cpp \
    io/OutputStream.cpp \
    jsoncpp/json_reader.cpp \
    jsoncpp/json_value.cpp \
    jsoncpp/json_writer.cpp \
    platform/Log.cpp \
    plist/Plist.cpp \
    pugixml/pugixml.cpp \
    plist/Plist.cpp \
    string/YHString.cpp \
    collections/ObjectValue.cpp \
    securesqlite3/sqlite3secure.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_EXPORT_LDLIBS := -llog \
                       -landroid

LOCAL_CFLAGS := -Wno-psabi
LOCAL_CFLAGS +=  -fexceptions
LOCAL_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat

LOCAL_EXPORT_CFLAGS := -Wno-psabi
LOCAL_EXPORT_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat


include $(BUILD_STATIC_LIBRARY)
