#include "../includes/server.hpp"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

namespace betacore
{
Server::Server(int port)
{
	this->port = port;
	std::cout << "And so it begins..." << std::endl;
	this->start();
}
void Server::start()
{
	this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->server_socket < 0)
	{
		std::cout << "ERROR on opening socket"<< std::endl;
		return;
	}
	std::cout << "Socket Connected"<< std::endl;

	bzero((char *)&server_address, sizeof(server_address));

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(this->port);

	if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
	{
		std::cout << "ERROR on binding "<< std::endl;

		return;
	}
	std::cout << "Bound"<< std::endl;
	online = true;
	server_running=true;
	std::cout << "Server is online"<< std::endl;
	std::thread listen_thread([this] { this->listener(); } );
	listen_thread.detach();
}
void Server::listener()
{
	std::cout << "Listener "<< online << std::endl;
	while (online) {
		struct sockaddr_in client_address;
		listen(this->server_socket, 5);
		socklen_t client_socket_length = sizeof(client_address);
		int client_number =
			accept(server_socket, (struct sockaddr *)&client_address, &client_socket_length);
		this->client_socket_collection.push_back(client_address);
		this->clients.push_back(client_number);
		std::cout << "New Conenction"<< std::endl;
		std::thread socket_thread([this,client_number]{this->read_socket(client_number);});
		socket_thread.detach();
	}
	this->shutdown();
}
void Server::read_socket(int client)
{
	std::cout 
		<< "Ready To Read "
		<< client 
		<< std::endl;
	int n;
	while (online)
	{
		if (client < 0)
		{
			std::cout << "ERROR on accept"<< std::endl;
		}
		bzero(buffer, 256);
		n = read(client, buffer, 1024);

		if (n < 0)
		{
			std::cout << "ERROR reading from socket"<< std::endl;
		}

		printf("Here is the message: %s\n", buffer);
		n = write(client, "I got your mesage\n", 18);

		if (n < 0)
		{
			std::cout << "ERROR Writing socket"<< std::endl;
		}
	}
}
void Server::shutdown()
{
	std::cout << "Server is shuting down"<< std::endl;

	for (auto socket : clients){
			std::cout 
				<< "Closing new socket :: " 
				<< socket
				<< std::endl;
		close(socket);
	}
	std::cout << "Closing server socket" << std::endl;
	close(this->server_socket);	
	server_running = false;
}
void Server::off(){
	this-> online = false;
}
bool Server::running(){
	return this->server_running;
}
} // namespace betacore