#ifndef YH_PLATFORM_WIN32_YHSTDC_H_
#define YH_PLATFORM_WIN32_YHSTDC_H_

#include "../PlatformConfig.h"
#include "../../NSMacros.h"

#include <float.h>

#ifdef __MINGW32__
	#include <string.h>
#endif

// for math.h on win32 platform
#ifndef __MINGW32__

#if !defined(_USE_MATH_DEFINES)
    #define _USE_MATH_DEFINES       // make M_PI can be use
#endif

#if !defined(isnan)
    #define isnan   _isnan
#endif

#ifndef snprintf
#define snprintf _snprintf
#endif

#endif // __MINGW32__

#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// for MIN MAX and sys/time.h on win32 platform
#ifndef __MINGW32__

#define MIN     min
#define MAX     max

#else // __MINGW32__

#include <sys/time.h>

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#endif // __MINGW32__


#if _MSC_VER >= 1600 || defined(__MINGW32__)
    #include <stdint.h>
#else
    #include "./stdint.h"
#endif

#define _WINSOCKAPI_
// Structure timeval has define in winsock.h, include windows.h for it.
#include <Windows.h>

#ifndef __MINGW32__

#include <WinSock2.h>

NS_YH_BEGIN

struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};

int gettimeofday(struct timeval *, struct timezone *);

NS_YH_END

#else

#include <winsock.h>

#endif // __MINGW32__

#endif  // YH_PLATFORM_WIN32_YHSTDC_H_

