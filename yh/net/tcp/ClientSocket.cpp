#include "ClientSocket.h"
#include "yh/platform/Log.h"

ClientSocket::ClientSocket()
{
	
}

ClientSocket::~ClientSocket()
{

}

bool ClientSocket::init()
{
	return true;
}

bool ClientSocket::connect(const std::string& remoteIP, int remotePort)
{

	_remoteIP = remoteIP;
	_remotePort = remotePort;
	_isIpV6 = remoteIP.find(':') != std::string::npos;
	int ret = -1;
	if (_isIpV6) {
		ret=_connectV6();
	}
	else
	{
		ret=_connectV4();
	}

	if (ret != 0 && errno != EINPROGRESS)
	{
		YHERROR("TcpSocket::doConnect[this0x" << this << "] ::connect error. " << OSTREAM_GET_LASTERROR);
		::closesocket(_fd);
		_fd = Invalid_FD;
		return false;
	}
	
	return true;
}


int ClientSocket::_connectV4()
{
	_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (_fd == INVALID_SOCKET)
	{
		YHERROR("ClientSocket::connect create socket error");
		return false;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(_remoteIP.c_str());
	addr.sin_port = htons(_remotePort);
	return ::connect(_fd,(sockaddr *)&addr, sizeof(addr));
}

int ClientSocket::_connectV6()
{
	_fd = socket(AF_INET6, SOCK_STREAM, 0);

	if (_fd == INVALID_SOCKET)
	{
		YHERROR("ClientSocket::connect create socket error");
		return false;
	}

	sockaddr_in6 addr;
	addr.sin6_family = AF_INET;
	inet_pton(AF_INET6, _remoteIP.c_str(), &addr.sin6_addr);
	addr.sin6_port = htons(_remotePort);
	return ::connect(_fd, (sockaddr *)&addr, sizeof(addr));
}

bool ClientSocket::send(char* buf, unsigned int len)
{
	return true;
}

bool ClientSocket::recv(char* buf, unsigned int len) 
{
	return true;
}
