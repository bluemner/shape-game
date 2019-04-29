#ifndef __BETACORE_SERVER_HPP__
#define __BETACORE_SERVER_HPP__
#include <vector>
#include <algorithm>
#include <iostream>

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <thread>
#include <utility>
#include <functional>
#include "common.hpp"

// LINUX SYSTEM CALLS :)
#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <unistd.h>


namespace betacore
{

class Server
{
private:
	fd_set rset;
	bool online = false;
	bool server_running = false;
	int port;
	int server_socket;
	std::vector<int> clients;
	struct sockaddr_in server_address;

	/* 
	 *	Starts the server
	 */
	void start();

	/*
	 * Shutdown Routine 
	 */
	void shutdown();

	/*
	 * Listen for connection and spawn a new thread
	 */
	void listener();

	/*
	 * Read the socket, is blocking, but will block its own thread
	 */
	void read_socket(int client);

	/*
	 * This will forward to all connected clients except the client fd given
	 */
	void forward_message(int client, char buffer[BUFFER_LENGTH]);

public:
	/* 
	 * Create a server on port
   */
	Server(int port);
	/* 
	 * Turn it off
	 */
	void off();

	/*
	 * Return true if the server is running
	 */
	bool running();
};
} // namespace betacore

#endif