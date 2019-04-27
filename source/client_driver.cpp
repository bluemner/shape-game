#include "client.hpp"
#include <iostream>

void test(betacore::SHAPE &s){
	std::cout << "It worked" << std::endl;
}
int main(int argc, char * argv[]){
	std::function<void(betacore::SHAPE &S)> fn= test;
	betacore::Client client(betacore::ALICE,4444, "localhost",fn);	
	client.send(false, betacore::TRIANGLE);
	client.send(true, betacore::TRIANGLE);
	//s.off();
	//while(client.running()){}
	return 0;
}	
