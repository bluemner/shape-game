#ifndef __BETACORE_SERVER_HPP__
#define __BETACORE_SERVER_HPP__
#include <vector>


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <utility>
#include <functional>
namespace betacore
{


class Server
{
private:
	bool online = false;
	bool server_running= false;
	int port;
	int server_socket;
	std::vector<int> clients;
	char buffer[1024];
	struct sockaddr_in server_address;
	std::vector<sockaddr_in> client_socket_collection;
	void start();
	void shutdown();
	void listener();
	void read_socket(int client);
public:
	Server(int port);
	void off();
	bool running();
};
} // namespace betacore

#endif