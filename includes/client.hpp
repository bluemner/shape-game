#ifndef __BETACORE_CLIENT_HPP__
#define __BETACORE_CLIENT_HPP__
#include <string>
#include <iostream>
#include <functional>
#include <sstream>
#include <vector>
#include <thread>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include "common.hpp"

namespace betacore
{

class Client
{
private:
	bool _online = false;
	bool _running = false;
	char key = 'Z';
	int _port;
	std::string _url;
	MODE _mode;
	int _client_socket;
	std::function<void(SHAPE &S, MODE &M)> _update;
	struct sockaddr_in _server_address;
	struct hostent *_server;
	std::map<std::string, std::string> lookup;
	std::vector<std::string> explode(std::string &message);
	std::string encode(const SHAPE &shape);
	std::string crypt(const std::string &shape);

	std::string raw(const SHAPE &shape);
	SHAPE parse(const std::string &message);

	SHAPE decode(const std::string &message);
	/**
		 * Function for Thread for getting information from server
		 */
	void listener();
	/**
		 * Function for Thread for sending to server
		 */
	void sender();
	void start();
	void stop();

public:

	/*
	 * Create an instance of client
	 */
	Client(
		MODE mode,
	  int port, 
		std::string url, 
		std::function<void(SHAPE &S, MODE &M)> &update);
	~Client();

	/* 
	 * Kill the server
	 */
	void kill();
	/*
	 * Running
	 */
	bool running();

	/*
	 * Send the shape encrypted or raw
	 */
	void send(bool encrypt, SHAPE shape);
};
} // namespace betacore
#endif