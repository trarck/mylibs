#include "../Log.h"
#include "../YHStdC.h"
#include "../PlatformDefine.h"

NS_YH_BEGIN

#define MAX_LEN         kMaxLogLen + 1

void log(const char * pszFormat, ...)
{
    printf("yh: ");
    char szBuf[kMaxLogLen+1] = {0};
    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(szBuf, kMaxLogLen, pszFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
}

NS_YH_END
