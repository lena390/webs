#include "Serv.hpp"

Serv::Serv( void )
{
	this->_port = 0;
}

Serv::Serv( int port )
{
	this->_port = port;
}

Serv::Serv( const Serv& serv )
{
	this->_addr = serv._addr;
	this->_port = serv._port;
	this->_request = serv._request;
}

Serv::~Serv( void )
{
	if (this->_request.empty())
		return ;
	for (std::map<int, std::string>::iterator it = this->_request.begin();
		it != this->_request.end(); it++)
		this->closeSock(it->first);
}

int Serv::connectServer(void)
{
	int reuse_addr = 1;
	int sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		return print_error("socket() error", -1);

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr)) < 0)
		return print_error("setsockopt() error", -2);

	this->initServer();
	if (bind(sock, (struct sockaddr *)&this->_addr, sizeof(this->_addr)) < 0)
	{
		close(sock);
		return print_error("bind() error", -4);
	}

	if (listen(sock, SOMAXCONN) < 0)
	{
		close(sock);
		return print_error("listen() error", -5);
	}
	return sock;
}

void Serv::initServer( void )
{
	memset(&this->_addr, 0, sizeof(this->_addr));
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	this->_addr.sin_port = htons(this->_port);
}

std::map<int, std::string> & Serv::getRequest ( void ) 
{
	return this->_request;
}

void Serv::closeSock( int sock )
{
	std::map<int, std::string>::iterator it = this->_request.find(sock);
	if (it == this->_request.end())
		return ;
	close(it->first);
	this->_request.erase(it);
}

struct sockaddr_in & Serv::getAddress( void ) { return this->_addr; }