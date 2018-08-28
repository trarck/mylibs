#ifndef YH_NET_NETSTD_H_
#define YH_NET_NETSTD_H_

#include "../platform/YHStdC.h"

#if defined(_WINDOWS)
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <MSWSock.h>
#pragma comment(lib, "ws2_32")

typedef SOCKET socket_t;
#else
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
typedef int socket_t;
#define INVALID_SOCKET			(-1)
#define SOCKET_ERROR            (-1)
#endif //defined(_WINDOWS)

#endif //YH_NET_NETSTD_H_