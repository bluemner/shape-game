#include "../includes/client.hpp"

namespace betacore
{
Client::Client(
		MODE mode,
		int port,
		std::string url,
		std::function<void(SHAPE &S, MODE &M)> &update) : _mode(mode),
																											_port(port),
																											_url(url),
																											_update(update)
{
	
	lookup["TRIANGLE"] = "APPLE";
	lookup["CIRCLE"] = "ORANGE";
	lookup["SQUARE"] = "BANANA";
	lookup["PENTAGON"] = "PINEAPPLE";

	lookup["APPLE"] = "TRIANGLE";
	lookup["ORANGE"] = "CIRCLE";
	lookup["BANANA"] = "SQUARE";
	lookup["PINEAPPLE"] = "PENTAGON";
	this->start();
}
Client::~Client(){
	this->_running= false;
	this->_online=false;
}
void Client::start()
{
	std::cout
			<< "Start"
			<< "\nConnecting to: " << _url << ":" << _port
			<< std::endl;
	//Create a socket point
	this->_client_socket = socket(AF_INET, SOCK_STREAM, 0);
	_server = gethostbyname(_url.c_str());
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

	bcopy(
			(char *)_server->h_addr,
			(char *)&_server_address.sin_addr.s_addr,
			_server->h_length);
	_server_address.sin_port = htons(_port);

	// Now connect to the server
	if (connect(
					_client_socket,
					(struct sockaddr *)&_server_address,
					sizeof(_server_address)) < 0)
	{
		std::cout << "ERROR connecting" << std::endl;
		return;
	}
	this->_online = true;
	this->_running = true;
	std::thread listen_thread([this] { this->listener(); });
	listen_thread.detach();

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

std::vector<std::string> Client::explode(std::string &message){
	std::stringstream stream(message);
	std::string tmp;
	std::vector<std::string> words;
	while (std::getline(stream, tmp, ':'))
		words.push_back(tmp);
	return words;
}

SHAPE Client::parse(const std::string &message)
{
	SHAPE result = decode(message);
	if (result != UNKOWN)
		return result;
	if (_mode == EVE)
		return UNKOWN;
	return decode(crypt(message));
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

	// std::string output = std::string(message);

	// for (int i = 0; i < message.size(); i++)
	// 	output.at(i) = message[i] ^ key;
	std::cout << "Crypt::" << message << " : " << lookup[message] << std::endl;
	return lookup[message];
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

	std::string message = "SHAPE:";
	message += encrypt ? crypt(encode(shape)) : encode(shape);
	message += ":";
	message += Parser::mode(this->_mode);
	std::cout << "Sending Message: " << message << "\n"
						<< std::endl;
	char buffer[BUFFER_LENGTH];
	bzero(buffer, BUFFER_LENGTH);
	strcpy(buffer, message.c_str());
	buffer[BUFFER_LENGTH - 1] = '\0';
	int x = write(this->_client_socket, buffer, strlen(buffer));
	if (x < 0)
	{
		std::cout << "Failed send to server" << std::endl;
	}
}

void Client::listener()
{
	std::cout << "listener" << std::endl;
	char buffer[BUFFER_LENGTH];
	while (_online)
	{

		// Now read server response

		bzero(buffer, BUFFER_LENGTH);
		std::cout << "Wating For message" << std::endl;
		if (read(_client_socket, buffer, BUFFER_LENGTH - 1) < 0)
		{
			std::cout << "ERROR reading from socket" << std::endl;
		}

		std::string message(buffer);
		std::cout << "Got Message: " << message << std::endl;
		auto parts = explode(message);
		if(parts.size() < 3)
			return;
		SHAPE shape = parse(parts.at(1));
		MODE mode = Parser::mode(parts.at(2));
		_update(shape,mode);
	}
}
} // namespace betacore