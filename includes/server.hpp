#ifndef __BETACORE_SERVER_HPP__
#define __BETACORE_SERVER_HPP__
#include <vector>
#include <algorithm>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>

#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <thread>
#include <utility>
#include <functional>
#include "common.hpp"

namespace betacore
{


class Server
{
private:
  fd_set rset;
	bool online = false;
	bool server_running= false;
	int port;
	int server_socket;
	std::vector<int> clients;
	struct sockaddr_in server_address;
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