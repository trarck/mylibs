#ifndef YH_PLATFORM_ANDROID_JNI_HELPER_H_
#define YH_PLATFORM_ANDROID_JNI_HELPER_H_

#include <jni.h>
#include <string>
#include "../../PlatformMacros.h"

NS_YH_BEGIN

class JniMethodInfo
{
public:
    JniMethodInfo():
        env(NULL),
        classID(NULL),
        methodID(NULL)
    {
        
    }

    ~JniMethodInfo()
    {
        if(classID!=NULL)
        {
            env->DeleteLocalRef(classID);
        }
    }

    JNIEnv *    env;
    jclass      classID;
    jmethodID   methodID;
};

class YH_DLL JniHelper
{
public:
    static void setJavaVM(JavaVM *javaVM);
    static JavaVM* getJavaVM();
    static JNIEnv* getEnv();

    static bool setClassLoaderFrom(JNIEnv* env, jobject activityInstance);
	static bool setClassLoaderFrom(jobject activityInstance);

	static bool getStaticMethodInfo(JNIEnv* env, JniMethodInfo &methodinfo,
		const char *className,
		const char *methodName,
		const char *paramCode);
	static bool getStaticMethodInfo(JniMethodInfo &methodinfo,
		const char *className,
		const char *methodName,
		const char *paramCode);

	static bool getMethodInfo(JNIEnv* env, JniMethodInfo &methodinfo,
		const char *className,
		const char *methodName,
		const char *paramCode);
	static bool getMethodInfo(JniMethodInfo &methodinfo,
		const char *className,
		const char *methodName,
		const char *paramCode);

	static std::string jstring2string(JNIEnv* env, jstring str);
	static std::string jstring2string(jstring str);

    static jmethodID loadclassMethod_methodID;
    static jobject classloader;

private:
    static JNIEnv* cacheEnv(JavaVM* jvm);

    static bool getMethodInfo_DefaultClassLoader(JniMethodInfo &methodinfo,
		const char *className,
		const char *methodName,
		const char *paramCode);
    static bool getMethodInfo_DefaultClassLoader(JniMethodInfo &methodinfo,
                                                 const char *className,
                                                 const char *methodName,
                                                 const char *paramCode);

    static JavaVM* _psJavaVM;
};

NS_YH_END

#endif // YH_PLATFORM_ANDROID_JNI_HELPER_H_
