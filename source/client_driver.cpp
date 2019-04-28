#include "client.hpp"
#include <iostream>

void test(betacore::SHAPE &s){
	std::cout << "It worked\n" << std::endl;
}
int main(int argc, char * argv[]){
	std::function<void(betacore::SHAPE &S)> fn= test;
	betacore::Client client(betacore::ALICE,4444, "localhost",fn);	
	client.send(false, betacore::TRIANGLE);
	client.send(true, betacore::TRIANGLE);
	//s.off();
	//while(client.running()){}
	std::string a;
	while(client.running()){
		std::cin >> a;
		client.send(false, betacore::TRIANGLE);
		if (a == "q") client.kill();
	}	

	return 0;
}	
