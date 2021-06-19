#include "Server.hpp"

Server::Server( void ) 
{
	this->_maxfd = -1;
}

Server::Server( std::vector<Serv> const & serv )
{
	this->_tmp = serv;
	this->_maxfd = -1;
	FD_ZERO(&this->_master);
	FD_ZERO(&this->_masterwrt);
}

Server::~Server( void ) 
{
	this->clearServer();
}

int Server::initServer( void )
{
	int	sock;

	for (std::vector<Serv>::iterator it = this->_tmp.begin(); it != this->_tmp.end(); it++)
	{
		sock = it->connectServer();
		if (sock > 0)
		{
			this->_server[sock] = *it;
			FD_SET(sock, &this->_master);
			if (this->_maxfd < sock)
				this->_maxfd = sock;
		}
		// Иначе закрываем все добавленные сокеты, очищаем списки и завершаем выполнение программы
	}
	return 0;
}

int Server::startServer( void )
{
	struct timeval	timeout;
	fd_set			read_set;
	fd_set			write_set;
	int				ret;
	
	while (1)
	{
		timeout.tv_sec = 30;
		timeout.tv_usec = 0;

		memcpy(&read_set, &this->_master, sizeof(this->_master));
		memcpy(&write_set, &this->_masterwrt, sizeof(this->_masterwrt));
		
		std::cout << "Waiting on select" << std::endl;  
		ret = select(this->_maxfd + 1, &read_set, &write_set, NULL, &timeout);
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
		
		for (size_t i = 0; i <= this->_maxfd; i++)
		{
			std::cout << "Try to accept()" << std::endl;
			if (FD_ISSET(i, &read_set))
			{
				std::map<int, Serv>::iterator it = this->_server.find(i);
				if (it != this->_server.end())
				{
					ret = it->second.acceptServer(i);
					if (ret > 0)
					{
						this->_client[ret] = &it->second;
						FD_SET(ret, &this->_master);
						if (ret > this->_maxfd)
							this->_maxfd = ret;
					}
				}
				else
				{
					std::map<int, Serv*>::iterator itc = this->_client.find(i);
					if (itc != this->_client.end())
					{
						ret = itc->second->recvServer(i);
						if (ret < 0)
						{

							FD_CLR(i, &this->_master);
							FD_CLR(i, &read_set);
							this->_client.erase(itc);
						}
						else
						{
							FD_SET(i, &this->_masterwrt);
							itc->second->init_request(i);
						}							
					}
				}
			}
		}

		for (size_t i = 0; i <= this->_maxfd; i++)
		{
			if (FD_ISSET(i, &write_set))
			{
				std::map<int, Serv*>::iterator it = this->_client.find(i);
				if (it != this->_client.end())
				{
					ret = it->second->sendServer(i);
					FD_CLR(i, &this->_master);
					FD_CLR(i, &this->_masterwrt);
					FD_CLR(i, &read_set);
					this->_client.erase(it);
				}
			}
		}
	}
	return 0;
}

void Server::clearServer(void)
{
	if (!this->_client.empty())
		for (std::map<int, Serv*>::iterator it = this->_client.begin(); it != this->_client.end(); it++)
			it->second->closeSock(it->first);
	if (!this->_server.empty())
		for (std::map<int, Serv>::iterator it = this->_server.begin(); it != this->_server.end(); it++)
			it->second.closeSock(it->first);
}