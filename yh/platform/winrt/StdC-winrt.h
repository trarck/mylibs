#ifndef YH_PLATFORM_STDC_WINRT_H_
#define YH_PLATFORM_STDC_WINRT_H_

#include "../CCPlatformConfig.h"
#if YH_TARGET_PLATFORM == YH_PLATFORM_WINRT


#include "../CCPlatformMacros.h"
#include <float.h>
#include <BaseTsd.h>

#ifndef __SSIZE_T
#define __SSIZE_T
typedef SSIZE_T ssize_t;
#endif // __SSIZE_T

// for math.h on win32 platform

#if !defined(_USE_MATH_DEFINES)
    #define _USE_MATH_DEFINES       // make M_PI can be use
#endif

#if !defined(isnan)
    #define isnan   _isnan
#endif

#if _MSC_VER < 1900
#ifndef snprintf
#define snprintf _snprintf
#endif
#endif

#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef M_PI
  #define M_PI      3.14159265358
#endif
#ifndef M_PI_2
  #define M_PI_2    1.57079632679
#endif


// for MIN MAX and sys/time.h on win32 platform
#ifndef NOMINMAX
  #define NOMINMAX
#endif

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#include <stdint.h>

#ifdef WINRT_NO_WINSOCK
#undef timeval
struct timeval
{
	long tv_sec;		// seconds
	long tv_usec;    // microSeconds
}; 
#else
// Structure timeval has define in winsock.h, include windows.h for it.
#define _WINSOCKAPI_
#include <WinSock2.h>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#endif
#endif

struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};

int YH_DLL gettimeofday(struct timeval *, struct timezone *);

#endif // YH_TARGET_PLATFORM == YH_PLATFORM_WINRT

#endif  // YH_PLATFORM_STDC_WINRT_H_

