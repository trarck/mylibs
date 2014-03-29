#include "../Log.h"
#include "../YHStdC.h"
#include "../PlatformDefine.h"
#include <android/log.h>

NS_YH_BEGIN

#define MAX_LEN         kMaxLogLen + 1

void log(const char * pszFormat, ...)
{
    char buf[MAX_LEN];

    va_list args;
    va_start(args, pszFormat);
    vsnprintf(buf, MAX_LEN, pszFormat, args);
    va_end(args);

    __android_log_print(ANDROID_LOG_DEBUG, "yh:", "%s", buf);
}

NS_YH_END
