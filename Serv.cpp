#include "Serv.hpp"

Serv::Serv( void )
{
	this->_socket = -1;
}

Serv::Serv( int port )
{
	this->_socket = -1;
	this->_port = port;
}

Serv::Serv( const Serv& serv)
{
	this->_addr = serv._addr;
	this->_port = serv._port;
	this->_socket = serv._socket;
}

Serv::~Serv( void ) {}

int Serv::connectServer(void)
{
	int reuse_addr = 1;
	int ret;

	this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socket < 0)
		return print_error("socket() error", -1);

	ret = setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr));
	if (ret < 0)
		return print_error("setsockopt() error", -2);

	this->initServer();
	ret = bind(this->_socket, (struct sockaddr *)&this->_addr, sizeof(this->_addr));
	if (ret < 0)
	{
		close(this->_socket);
		return print_error("bind() error", -4);
	}

	ret = listen(this->_socket, SOMAXCONN);
	if (ret < 0)
	{
		close(this->_socket);
		return print_error("listen() error", -5);
	}		
	return 0;
}

void Serv::initServer( void )
{
	memset(&this->_addr, 0, sizeof(this->_addr));
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	this->_addr.sin_port = htons(this->_port);
}

int Serv::getSocket( void ) { return this->_socket; }

void Serv::closeSock( void )
{
	if (this->_socket > 0)
		close(this->_socket);
	this->_socket = -1;
}

struct sockaddr_in & Serv::getAddress( void ) { return this->_addr; }