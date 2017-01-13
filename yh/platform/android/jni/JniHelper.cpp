#include "JniHelper.h"
#include <android/log.h>
#include <string.h>
#include <pthread.h>

#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static pthread_key_t g_key;

jclass _getClassID(JNIEnv* env,const char *className) {

    if (NULL == className) {
        return NULL;
    }

    if(env==NULL)
        return NULL;

	jclass _clazz = NULL;

	if (yh::JniHelper::classloader) {
		jstring _jstrClassName = env->NewStringUTF(className);

		_clazz = (jclass)env->CallObjectMethod(yh::JniHelper::classloader,
			yh::JniHelper::loadclassMethod_methodID,
			_jstrClassName);
		env->DeleteLocalRef(_jstrClassName);
	}

    if (NULL == _clazz) {
        _clazz = env->FindClass(className);
        if (!_clazz)
        {
            LOGE("Classloader failed to find class of %s", className);
            env->ExceptionClear();
        }       
    } 
        
    return _clazz;
}


void _detachCurrentThread(void* a) {
    yh::JniHelper::getJavaVM()->DetachCurrentThread();
}

NS_YH_BEGIN

    JavaVM* JniHelper::_psJavaVM = NULL;
    jmethodID JniHelper::loadclassMethod_methodID = NULL;
    jobject JniHelper::classloader = NULL;

    JavaVM* JniHelper::getJavaVM() {
        pthread_t thisthread = pthread_self();
        LOGD("JniHelper::getJavaVM(), pthread_self() = %ld", thisthread);
        return _psJavaVM;
    }

    void JniHelper::setJavaVM(JavaVM *javaVM) {
        pthread_t thisthread = pthread_self();
        LOGD("JniHelper::setJavaVM(%p), pthread_self() = %ld", javaVM, thisthread);
        _psJavaVM = javaVM;

        pthread_key_create(&g_key, _detachCurrentThread);
    }

    JNIEnv* JniHelper::cacheEnv(JavaVM* jvm) {
        JNIEnv* _env = NULL;
        // get jni environment
        jint ret = jvm->GetEnv((void**)&_env, JNI_VERSION_1_4);
        
        switch (ret) {
        case JNI_OK :
            // Success!
            pthread_setspecific(g_key, _env);
            return _env;
                
        case JNI_EDETACHED :
            // Thread not attached
            if (jvm->AttachCurrentThread(&_env, NULL) < 0)
                {
                    LOGE("Failed to get the environment using AttachCurrentThread()");

                    return NULL;
                } else {
                // Success : Attached and obtained JNIEnv!
                pthread_setspecific(g_key, _env);
                return _env;
            }
                
        case JNI_EVERSION :
            // Cannot recover from this error
            LOGE("JNI interface version 1.4 not supported");
        default :
            LOGE("Failed to get the environment using GetEnv()");
            return NULL;
        }
    }

    JNIEnv* JniHelper::getEnv() {
        JNIEnv *_env = (JNIEnv *)pthread_getspecific(g_key);
        if (_env == NULL)
            _env = JniHelper::cacheEnv(_psJavaVM);
        return _env;
    }

    
	bool JniHelper::setClassLoaderFrom(JNIEnv* env,jobject activityinstance) {
		JniMethodInfo _getclassloaderMethod;
		if (!JniHelper::getMethodInfo_DefaultClassLoader(_getclassloaderMethod,
			"android/content/Context",
			"getClassLoader",
			"()Ljava/lang/ClassLoader;")) {
			return false;
		}

		JniMethodInfo _m;
		if (!JniHelper::getMethodInfo_DefaultClassLoader(_m,
			"java/lang/ClassLoader",
			"loadClass",
			"(Ljava/lang/String;)Ljava/lang/Class;")) {
			return false;
		}

		jobject _c =env->CallObjectMethod(activityinstance,
			_getclassloaderMethod.methodID);

		if (NULL == _c) {
			return false;
		}
		
		JniHelper::classloader = env->NewGlobalRef(_c);
		JniHelper::loadclassMethod_methodID = _m.methodID;
		env->DeleteLocalRef(_c);
		return true;
	}

    bool JniHelper::setClassLoaderFrom(jobject activityinstance) {
		return setClassLoaderFrom(JniHelper::getEnv(), activityinstance);
    }

    bool JniHelper::getStaticMethodInfo(JNIEnv *env,JniMethodInfo &methodinfo,
                                        const char *className, 
                                        const char *methodName,
                                        const char *paramCode) {
        if ((NULL == className) ||
            (NULL == methodName) ||
            (NULL == paramCode)) {
            return false;
        }

        if (!env) {
            LOGE("Failed to get JNIEnv");
            return false;
        }
            
        jclass classID = _getClassID(env,className);
        if (! classID) {
            LOGE("Failed to find class %s", className);
            env->ExceptionClear();
            return false;
        }

        jmethodID methodID = env->GetStaticMethodID(classID, methodName, paramCode);
        if (! methodID) {
            LOGE("Failed to find static method id of %s", methodName);
            env->DeleteLocalRef(classID);
            env->ExceptionClear();
            return false;
        }
            
        methodinfo.classID = classID;
        methodinfo.env = env;
        methodinfo.methodID = methodID;
        return true;
    }

	bool JniHelper::getStaticMethodInfo(JniMethodInfo &methodinfo,
		const char *className,
		const char *methodName,
		const char *paramCode) 
	{
		if ((NULL == className) ||
			(NULL == methodName) ||
			(NULL == paramCode)) {
			return false;
		}
		else
		{
			return getStaticMethodInfo(getEnv(), methodinfo, className, methodName, paramCode);
		}
	}

    bool JniHelper::getMethodInfo_DefaultClassLoader(JNIEnv *env ,JniMethodInfo &methodinfo,
                                                     const char *className,
                                                     const char *methodName,
                                                     const char *paramCode) {
        if ((NULL == className) ||
            (NULL == methodName) ||
            (NULL == paramCode)) {
            return false;
        }

        if (!env) {
            return false;
        }

        jclass classID = env->FindClass(className);
        if (! classID) {
            LOGE("Failed to find class %s", className);
            env->ExceptionClear();
            return false;
        }

        jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
        if (! methodID) {
            LOGE("Failed to find method id of %s", methodName);
            env->DeleteLocalRef(classID);
            env->ExceptionClear();
            return false;
        }

        methodinfo.classID = classID;
        methodinfo.env = env;
        methodinfo.methodID = methodID;

        return true;
    }

	bool JniHelper::getMethodInfo_DefaultClassLoader(JniMethodInfo &methodinfo,
		const char *className,
		const char *methodName,
		const char *paramCode) {
		if ((NULL == className) ||
			(NULL == methodName) ||
			(NULL == paramCode)) {
			return false;
		}
		else
		{
			return getMethodInfo_DefaultClassLoader(getEnv(), methodinfo, className, methodName, paramCode);
		}
	}

    bool JniHelper::getMethodInfo(JNIEnv *env ,JniMethodInfo &methodinfo,
                                  const char *className,
                                  const char *methodName,
                                  const char *paramCode) {
        if ((NULL == className) ||
            (NULL == methodName) ||
            (NULL == paramCode)) {
            return false;
        }

        if (!env) {
            return false;
        }

        jclass classID = _getClassID(env,className);
        if (! classID) {
            LOGE("Failed to find class %s", className);
            env->ExceptionClear();
            return false;
        }

        jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
        if (! methodID) {
            LOGE("Failed to find method id of %s", methodName);
            env->DeleteLocalRef(classID);
            env->ExceptionClear();
            return false;
        }

        methodinfo.classID = classID;
        methodinfo.env = env;
        methodinfo.methodID = methodID;

        return true;
    }

	bool JniHelper::getMethodInfo(JniMethodInfo &methodinfo,
		const char *className,
		const char *methodName,
		const char *paramCode) {
		if ((NULL == className) ||
			(NULL == methodName) ||
			(NULL == paramCode)) {
			return false;
		}
		else
		{
			return getMethodInfo(getEnv(), methodinfo, className, methodName, paramCode);
		}
	}

	std::string JniHelper::jstring2string(JNIEnv *env,jstring jstr) {
		if (jstr == NULL) {
			return "";
		}

		if (!env) {
			return "";
		}

		const char* chars = env->GetStringUTFChars(jstr, NULL);
		std::string strValue(chars);
		env->ReleaseStringUTFChars(jstr, chars);
		return strValue;
	}

    std::string JniHelper::jstring2string(jstring jstr) {
        if (jstr == NULL) {
            return "";
        }
        
        JNIEnv *env = JniHelper::getEnv();
        if (!env) {
            return "";
        }

        const char* chars = env->GetStringUTFChars(jstr, NULL);
        std::string strValue(chars);
        env->ReleaseStringUTFChars(jstr, chars);
        return strValue;
    }

NS_YH_END
