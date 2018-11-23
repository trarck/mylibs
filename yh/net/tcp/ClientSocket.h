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

	int _connectV4();
	int _connectV6();

protected:
	socket_t _fd;
	std::string _remoteIP;
	int _remotePort;
	bool _isIpV6;

};

#endif // YH_NET_TCP_CLIENTSOCKET_H_

