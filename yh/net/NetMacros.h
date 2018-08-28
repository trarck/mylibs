#ifndef YH_NET_NETMACROS_H_
#define YH_NET_NETMACROS_H_

#ifdef __cplusplus

#define NS_YH_NET_BEGIN                     namespace yh { namespace net {
#define NS_YH_NET_END                       }}
#define USING_NS_YH_NET                     using namespace yh::net

#define NS_YH_NET_TCP_BEGIN                     namespace yh { namespace net {namespace tcp {
#define NS_YH_NET_TCP_END                       }}}
#define USING_NS_YH_NET_TCP                     using namespace yh::net::tcp

#define NS_YH_NET_UDP_BEGIN                     namespace yh { namespace net {namespace udp {
#define NS_YH_NET_UDP_END                       }}}
#define USING_NS_YH_NET_UDP                     using namespace yh::net::udp

#else

#define NS_YH_IO_BEGIN
#define NS_YH_IO_END
#define USING_NS_YH_IO

#define NS_YH_NET_TCP_BEGIN
#define NS_YH_NET_TCP_END
#define USING_NS_YH_NET_TCP

#define NS_YH_NET_UDP_BEGIN
#define NS_YH_NET_UDP_END
#define USING_NS_YH_NET_UDP
#endif

#endif //YH_NET_NETMACROS_H_