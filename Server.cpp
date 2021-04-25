#include "Server.hpp"
#include <sstream>

Server::Server( void ) { return ; }

Server::Server( Serv servers )
{
	this->_server = servers;
	this->_maxfd = -1;
}

Server::~Server( void ) { return ; }

int Server::initServer( void )
{
	int curfd;
	int ret;
  
	if (!(ret = this->_server.connectServer()))
	{
		FD_ZERO(&this->_masterwrt);
		FD_ZERO(&this->_master);
		curfd = this->_server.getSocket();
		FD_SET(curfd, &this->_master);
		if (this->_maxfd < curfd)
			this->_maxfd = curfd;
	}
	return ret;
}

int Server::startServer( void )
{
	struct timeval timeout;
	fd_set read_set;
	fd_set write_set;
	int ret;
	int ready;
	int newfd;
	bool fl = false;
	bool end_server = false;
	char buffer[65535];
	int n = 0;
	FD_ZERO(&write_set);
	while (1)
	{
		timeout.tv_sec = 30;
		timeout.tv_usec = 0;
		memcpy(&read_set, &this->_master, sizeof(this->_master));
		memcpy(&write_set, &this->_masterwrt, sizeof(this->_masterwrt));
		std::cout << "Waiting on select" << std::endl;  
		ret = select(this->_maxfd + 1, &read_set, &write_set, NULL, &timeout);
		std::cout << "Select return " << ret << std::endl;
		if (ret < 0)
		{
			print_error("Error server", -1); //Корректно обработать выход с сервера
			break ;
		} 
		if (ret == 0)
		{
			print_error("Select timeout", -1);
			break ;
		}
		
		for (int i = 0; i <= this->_maxfd; i++)
		{
			socklen_t sizeofaddr;
			std::cout << "Try to accept()" << std::endl;
			if (FD_ISSET(i, &read_set))
			{
				if (i == this->_server.getSocket())
				{
					newfd = accept(i, 0, 0);
					if (newfd == -1)
						std::cerr << "\033[31m" << "Error accept()" << "\033[0m" << std::endl;
					else
					{
						std::cout << "\033[32m" << "Accept complete()" << "\033[0m" << std::endl;
						fcntl(newfd, F_SETFL, O_NONBLOCK);
						FD_SET(newfd, &this->_master);
						if (newfd > this->_maxfd)
							this->_maxfd = newfd;
					}
				}
				else
				{
					ret = recv(i, buffer, sizeof(buffer) - 1, 0);
					if (ret <= 0)
					{
						if (ret < 0)
							std::cerr << "\033[31m" << "Error recv()" << "\033[0m" << std::endl;
						else if (ret == 0)
							std::cerr << "\033[31m" << "Socket close" << "\033[0m" << std::endl;
						close(i);
						FD_CLR(i, &this->_master);
					}
					else
					{
						std::cout << buffer << std::endl;
						FD_SET(i, &this->_masterwrt);
					}
				}
			}
		}
		for (int j = 0; j <= this->_maxfd; j++)
		{
			if (FD_ISSET(j, &write_set))
			{
				char buf[256];
				std::stringstream response; // сюда будет записываться ответ клиенту
    			std::stringstream response_body;
				response_body << "<title>Test C++ HTTP Server</title>\n"
            	<< "<h1>Test page</h1>\n"
            	<< "<p>This is body of the test page...</p>\n"
           		<< "<h2>Request headers</h2>\n"
           		<< "<pre>" << buf << "</pre>\n"
            	<< "<em><small>Test C++ Http Server</small></em>\n";
        		// Формируем весь ответ вместе с заголовками
        		response << "HTTP/1.1 200 OK\r\n"
            	<< "Version: HTTP/1.1\r\n"
            	<< "Content-Type: text/html; charset=utf-8\r\n"
            	<< "Content-Length: " << response_body.str().length()
            	<< "\r\n\r\n"
            	<< response_body.str();
				ret = send(j, response.str().c_str(), response.str().length(), 0);
				if (ret < 0)
					std::cerr << "\033[31m" << "Error send()" << "\033[0m" << std::endl;
				else
					std::cout << "\033[32m" << "send() complete" << "\033[0m" << std::endl;
				close(j);
				FD_CLR(j, &this->_masterwrt);
				FD_CLR(j, &this->_master);	
			}
		}
	}
	return 0;
}

void Server::clearServer(void)
{
	for (int i = 0; i <= this->_maxfd; ++i)
		if (FD_ISSET(i, &this->_master))
			close(i);
}