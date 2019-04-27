#ifndef __BETACORE_CLIENT_HPP__
#define __BETACORE_CLIENT_HPP__
#include <string>
#include <iostream>
#include <functional>
#include <sstream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include "common.hpp"

namespace betacore{	


class Client{
	private: 
		bool _online = false;
		bool _running= false;
		char key = 'Z';
		int _port;
		std::string _address;
		MODE _mode;
		int _client_socket;
	 std::function<void(SHAPE &S)> _update;
   struct sockaddr_in _server_address;
   struct hostent * _server;
	

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
		Client(MODE mode, int port, std::string address, std::function<void(SHAPE &S)> &update);
		void kill();
		bool running();
		void send(bool encrypt, SHAPE shape);

		
};
}
#endif