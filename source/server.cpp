#include "../includes/server.hpp"


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
	signal(SIGPIPE,SIG_IGN);
	std::thread listen_thread([this] { this->listener(); } );
	listen_thread.detach();
}
void Server::listener()
{
	std::cout << "Listener "<< online << std::endl;
	struct sockaddr_in client_address;
	listen(this->server_socket, 10);
	while (online) {
	
		socklen_t client_socket_length = sizeof(client_address);
		int client_number =
			accept(server_socket, (struct sockaddr *)&client_address, &client_socket_length);
		this->clients.push_back(client_number);
		std::cout << "New Conenction"<< std::endl;
		if (client_number < 0)
		{
			std::cout << "ERROR on accept"<< std::endl;
			continue;
		}
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
	char buffer[1024];
	while (online &&
			std::find(clients.begin(), clients.end(), client) != clients.end())
	{	
		
	
		bzero(buffer, 1024);
	
		n = read(client, buffer, 1024-1);

		if (n < 0)
		{
			std::cout << "ERROR reading from socket"<< std::endl;
			break;
		}


		printf("Here is the message: %s\n", buffer);
		n = write(client, "I got your mesage\n", 18);

		if (n < 0)
		{
			std::cout << "ERROR Writing socket"<< std::endl;
			break;
		}
	}
	clients.erase(
		std::remove(clients.begin(), clients.end(), client), clients.end());
	close(client);
}
void Server::shutdown()
{
	std::cout << "Server is shuting down"<< std::endl;

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