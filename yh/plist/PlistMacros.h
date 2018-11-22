#ifndef YH_IO_PLISTMACROS_H_
#define YH_IO_PLISTMACROS_H_

#ifdef __cplusplus

#define NS_YH_PLIST_BEGIN                     namespace yh { namespace plist {
#define NS_YH_PLIST_END                       }}
#define USING_NS_YH_PLIST                     using namespace yh::plist

#else

#define NS_YH_PLIST_BEGIN                     
#define NS_YH_PLIST_END                       
#define USING_NS_YH_PLIST

#endif



#endif //YH_IO_PLISTMACROS_H_