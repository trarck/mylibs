#ifndef YH_IO_IEEEHALFPRECISION_H_
#define YH_IO_IEEEHALFPRECISION_H_

#include "../YHMacros.h"
#include "../platform/YHStdC.h"

NS_YH_BEGIN


int singles2halfp(void *target, void *source);
int doubles2halfp(void *target, void *source,int next);
int halfp2singles(void *target, void *source);
int halfp2doubles(void *target, void *source,int next);

//使用具体的类型
int singles2halfpTyped(uint16_t* target, uint32_t* source);
int doubles2halfpTyped(uint16_t *target, uint64_t *source);
int halfp2singlesTyped(uint32_t *target, uint16_t *source);
int halfp2doublesTyped(uint64_t *target, uint16_t *source);

NS_YH_END

#endif // YH_IO_IEEEHALFPRECISION_H_
