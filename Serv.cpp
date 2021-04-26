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

/**********************************************************
 ************************GETTERS***************************
 *********************************************************/

std::map<int, std::string> & Serv::getRequest ( void ) 
{
	return this->_request;
}

struct sockaddr_in & Serv::getAddress( void )
{
	return this->_addr;
}

/**************************INIT****************************
 *************************CONNECT**************************
 **************************CLOSE***************************/
int Serv::connectServer(void)
{
	int	reuse_addr = 1;
	int	sock;

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

void Serv::closeSock( int sock )
{
	std::map<int, std::string>::iterator it = this->_request.find(sock);
	if (it == this->_request.end())
		return ;
	close(it->first);
	this->_request.erase(it);
}


/*************************ACCEPT***************************
 ************************RECIEVE***************************
 *************************SEND*****************************/
int Serv::acceptServer( int sock )
{
	int newfd = accept(sock, 0, 0);
	if (newfd < 0)
		std::cerr << RED << "Error accept()" << RESET << std::endl;
	else
	{
		std::cout << GREEN << "Accept complete()" << RESET << std::endl;
		fcntl(newfd, F_SETFL, O_NONBLOCK);
	}
	return newfd;
}

int Serv::recvServer( int sock )
{
	int ret;
	char buf[BUF_SIZE];

	ret = recv(sock, buf, BUF_SIZE - 1, 0);
	if (ret <= 0)
	{
		if (ret < 0)
			std::cerr << RED << "Error recv()" << RESET << std::endl;
		else
			std::cerr << RED << "Socket close" << RESET << std::endl;
		close(sock);
		return -1;
	}
	std::cout << buf << std::endl;
	this->_request[sock] = buf;
	return 0;
}

int Serv::sendServer( int sock )
{
	int ret;
	std::string buf = std::to_string(this->_port);
	std::stringstream response; // сюда будет записываться ответ клиенту
    std::stringstream response_body;
	response_body << "<title>Test C++ HTTP Server</title>\n" 
	<< "<h1>Test page</h1>\n" << "<p>This is body of the test page...</p>\n"
	<< "<h2>Request headers</h2>\n" << "<pre>" << "on port :" << buf << "</pre>\n" << "<em><small>Test C++ Http Server</small></em>\n";
    // Формируем весь ответ вместе с заголовками
    response << "HTTP/1.1 200 OK\r\n" << "Version: HTTP/1.1\r\n"
	<< "Content-Type: text/html; charset=utf-8\r\n" << "Content-Length: " << response_body.str().length()
	<< "\r\n\r\n" << response_body.str();
	ret = send(sock, response.str().c_str(), response.str().length(), 0);
	if (ret < 0)
		std::cerr << RED << "Error send()" << RESET << std::endl;
	else
		std::cout << GREEN << "send() complete" << RESET << std::endl;
	this->closeSock(sock);
	return ret;
}