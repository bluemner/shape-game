#include "server.hpp"

int main(int argc, char * argv[]){
	betacore::Server s(4444);	
	//s.off();
	while(s.running()){}
	return 0;
}	
