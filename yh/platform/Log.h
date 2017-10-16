#ifndef YH_PLATFORM_LOG_H_
#define YH_PLATFORM_LOG_H_

#include "../NSMacros.h"

NS_YH_BEGIN

static const int kMaxLogLen = 16*1024;

void log(const char * pszFormat, ...);

#define __YHLOGWITHFUNCTION(s, ...) \
    yh::log("%s : " s ,__FUNCTION__,  ##__VA_ARGS__)

#define YH_LOG_LEVEL_DEBUG 4
#define YH_LOG_LEVEL_INFO 3
#define YH_LOG_LEVEL_WARN 2
#define YH_LOG_LEVEL_ERROR 1
#define YH_LOG_LEVEL_NONE 0

#if !defined(YH_LOG_LEVEL) || YH_LOG_LEVEL == YH_LOG_LEVEL_NONE
#define YHDEBUG(...)       do {} while (0)
#define YHINFO(...)   do {} while (0)
#define YHWARN(...)   do {} while (0)
#define YHERROR(...)  do {} while (0)

#elif YH_LOG_LEVEL == YH_LOG_LEVEL_ERROR
#define YHDEBUG(...)   do {} while (0)
#define YHINFO(...) do {} while (0)
#define YHWARN(...)  do {} while (0)
#define YHERROR(...) __YHLOGWITHFUNCTION(__VA_ARGS__)

#elif YH_LOG_LEVEL == YH_LOG_LEVEL_WARN
#define YHDEBUG(...)   do {} while (0)
#define YHINFO(...)  do {} while (0)
#define YHWARN(format,...) yh::log(format, ##__VA_ARGS__)
#define YHERROR(format,...)  __YHLOGWITHFUNCTION(format,##__VA_ARGS__)

#elif YH_LOG_LEVEL == YH_LOG_LEVEL_INFO
#define YHDEBUG(...)   do {} while (0)
#define YHINFO(format, ...)  yh::log(format, ##__VA_ARGS__)
#define YHWARN(format,...) yh::log(format, ##__VA_ARGS__)
#define YHERROR(format,...)  __YHLOGWITHFUNCTION(format,##__VA_ARGS__)

#elif YH_LOG_LEVEL > YH_LOG_LEVEL_INFO
#define YHDEBUG(format, ...)      yh::log(format, ##__VA_ARGS__)
#define YHINFO(format,...)   yh::log(format, ##__VA_ARGS__)
#define YHWARN(format,...) yh::log(format, ##__VA_ARGS__)
#define YHERROR(format,...)  __YHLOGWITHFUNCTION(format,##__VA_ARGS__)
#endif // yh log

//define func ptf
typedef void(*ScriptDeubgFuncPtr)(const char *);

void SetScriptDeubgFuncPtr(ScriptDeubgFuncPtr fp);

NS_YH_END

#endif // YH_PLATFORM_LOG_H_
