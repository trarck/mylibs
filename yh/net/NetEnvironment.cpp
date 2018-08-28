

#include "NetEnvironment.h"
#include "NetMacros.h"


NetEnvironment::NetEnvironment()
{
#if defined(_WINDOWS)
	WORD version = MAKEWORD(2, 2);
	WSADATA d;
	if (WSAStartup(version, &d) != 0)
	{
		assert(0);
	}
#endif //defined(_WINDOWS)
}

NetEnvironment::~NetEnvironment()
{
#if defined(_WINDOWS)
	WSACleanup();
#endif //defined(_WINDOWS)
}
