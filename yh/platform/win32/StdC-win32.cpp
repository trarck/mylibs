#include "../PlatformConfig.h"
#if YH_TARGET_PLATFORM == YH_PLATFORM_WIN32
#include "../../NSMacros.h"
#include "../YHStdC.h"

#ifndef __MINGW32__

int getTimeofday(struct timeval * val, struct timezone * timezone)
{
	if (val)
	{
		LARGE_INTEGER liTime, liFreq;
		QueryPerformanceFrequency(&liFreq);
		QueryPerformanceCounter(&liTime);
		val->tv_sec = (long)(liTime.QuadPart / liFreq.QuadPart);
		val->tv_usec = (long)(liTime.QuadPart * 1000000.0 / liFreq.QuadPart - val->tv_sec * 1000000.0);
	}
	return 0;
}

NS_YH_BEGIN

NS_YH_END

#endif // __MINGW32__

#endif // YH_TARGET_PLATFORM == YH_PLATFORM_WIN32
