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

}

bool ClientSocket::connect(const std::string& remoteIP, int remotePort)
{
	_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (_fd == INVALID_SOCKET) 
	{
		YHERROR("ClientSocket::connect create socket error");
		return false;
	}
}

bool ClientSocket::send(char* buf, unsigned int len)
{

}

bool ClientSocket::recv(char* buf, unsigned int len) 
{

}