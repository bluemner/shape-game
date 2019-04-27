#include "../includes/client.hpp"

namespace betacore
{
Client::Client(MODE mode, int port, std::string address, std::function<void(SHAPE &S)> &update) : _mode(mode),
																																																		 _port(port),
																																																		 _address(address),
																																																		 _update(update)
{
	this->start();
}
void Client::start()
{
	std::cout
			<< "Start"
			<< "\nConnecting to: " << _address << ":" <<_port
			<< std::endl;
	//Create a socket point
	_client_socket = socket(AF_INET, SOCK_STREAM, 0);
	_server =	gethostbyname(_address.c_str());
	if (_client_socket < 0)
	{
		std::cout << "ERROR opening socket" << std::endl;
		return;
	}
	std::cout
			<< "Socket Open"
			<< std::endl;
	bzero((char *)&_server_address, sizeof(_server_address));
	_server_address.sin_family = AF_INET;
	std::cout
			<< "AF_INT SET"
			<< std::endl;
	bcopy((char *)_server->h_addr, (char *)&_server_address.sin_addr.s_addr, _server->h_length);
	_server_address.sin_port = htons(_port);
	
	// Now connect to the server
	if (connect(_client_socket, (struct sockaddr *)&_server_address, sizeof(_server_address)) < 0)
	{
		std::cout << "ERROR connecting" << std::endl;
		return;
	}
	std::cout
			<< "Client Connected"
			<< std::endl;
}
void Client::stop()
{
	std::cout
			<< "Stop"
			<< std::endl;
}

void Client::kill()
{
	std::cout
			<< "Kill"
			<< std::endl;
	this->_online = false;
}
bool Client::running()
{
	return this->_running;
}

SHAPE Client::parse(const std::string &message)
{
	std::stringstream stream(message);
	std::string tmp;
	std::vector<std::string> words;
	while (std::getline(stream, tmp, ':'))
		words.push_back(tmp);

	if (words.size() < 2)
		return NONE;
	tmp = words.at(1);
	SHAPE result = decode(tmp);
	if (result != UNKOWN)
		return result;
	if (_mode == EVE)
		return UNKOWN;
	return decode(crypt(tmp));
}
SHAPE Client::decode(const std::string &shape)
{

	if (shape == "TRIANGLE")
		return TRIANGLE;
	if (shape == "CIRCLE")
		return CIRCLE;
	if (shape == "SQUARE")
		return SQUARE;
	if (shape == "PENTAGON")
		return PENTAGON;
	return UNKOWN;
}
std::string Client::crypt(const std::string &message)
{

	std::string output = message;
	for (int i = 0; i < message.size(); i++)
		output[i] = message[i] ^ key;
	return output;
}
std::string Client::encode(const SHAPE &shape)
{
	std::string message;
	switch (shape)
	{
	case TRIANGLE:
		message = "TRIANGLE";
		break;
	case CIRCLE:
		message = "CIRCLE";
		break;
	case SQUARE:
		message = "SQUARE";
		break;
	case PENTAGON:
		message = "PENTAGON";
		break;
	default:
		message = "UNKOWN";
		break;
	}
	return message;
}
void Client::send(bool encrypt, SHAPE shape)
{

	std::string message = "SHAPE:" + encrypt ? crypt(encode(shape)) : encode(shape) + ":END";
	std::cout << "Sending Message: " << message << std::endl;
	char buffer[BUFFER_SIZE];
	bzero(buffer, BUFFER_SIZE);
	strcpy(buffer, message.c_str());
	if (write(_client_socket, buffer, strlen(buffer) < 0))
	{
		std::cout << "Failed send to server" << std::endl;
	}
}

void Client::listener()
{
	while (_online)
	{
		// Now read server response
		char buffer[BUFFER_SIZE];
		bzero(buffer, BUFFER_SIZE);

		if (read(_client_socket, buffer, BUFFER_SIZE-1) < 0)
		{
			std::cout << "ERROR reading from socket" << std::endl;
		}
		std::string message(buffer);
		SHAPE shape = parse(buffer);
		_update(shape);
	}
}
} // namespace betacore