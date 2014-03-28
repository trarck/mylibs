#ifndef YH_PLATFORM_YHSTDC_H_
#define YH_PLATFORM_YHSTDC_H_

#include "PlatformConfig.h"

//stdc 
#if YH_TARGET_PLATFORM == YH_PLATFORM_WIN32

    #include "win32/YHStdC.h"

#else //stdc other platforms

    #include <float.h>
    #include <math.h>
    #include <string.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <sys/time.h>
    #include <stdint.h>

    #ifndef MIN
    #define MIN(x,y) (((x) > (y)) ? (y) : (x))
    #endif  // MIN

    #ifndef MAX
    #define MAX(x,y) (((x) < (y)) ? (y) : (x))
    #endif  // MAX

#endif //stdc


#endif  // YH_PLATFORM_YHSTDC_H_

