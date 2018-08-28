#ifndef YH_NET_TCP_CLIENTSOCKET_H_
#define YH_NET_TCP_CLIENTSOCKET_H_

#include "../NetStd.h"
#include "../NetMacros.h"

class ClientSocket
{
public:
	ClientSocket();

	virtual ~ClientSocket();

	bool init();

	bool connect(const std::string& remoteIP, int remotePort);

	bool send(char* buf, unsigned int len);

	bool recv(char* buf, unsigned int len);

protected:

	bool _connect4();
	bool _connect6();

protected:
	socket_t _fd;

};

#endif // YH_NET_TCP_CLIENTSOCKET_H_

