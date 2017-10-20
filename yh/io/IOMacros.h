#ifndef YH_IO_BINARYMACROS_H_
#define YH_IO_BINARYMACROS_H_

#ifdef __cplusplus

#define NS_YH_IO_BEGIN                     namespace yh { namespace io {
#define NS_YH_IO_END                       }}
#define USING_NS_YH_IO                     using namespace yh::io

#else

#define NS_YH_IO_BEGIN                     
#define NS_YH_IO_END                       
#define USING_NS_YH_IO

#endif

#define YH_IO_BYTE_SIZE 1
#define YH_IO_SHORT_SIZE 2
#define YH_IO_INT_SIZE 4
#define YH_IO_LONG_SIZE 8

#endif //YH_IO_BINARYMACROS_H_