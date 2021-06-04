#include <iostream>
#include "SpaceWars.h"
#include "SDLGame.h"

void Server(char* host, char* port)
{

}

void Client(char* host, char* port)
{

}

int main(int argc, char** argv)
{  
    try {

		if(argc==4)
		{
			bool isClient = argv[3]==0;
			SpaceWars s(argv[1],argv[2],isClient);
			s.start();
		}
		else
		{
			std::cout<<"Usage: ./main host port isClient(0 or 1)\n";
		}

	} catch (std::string &e) { // catch errors thrown as strings
		cerr << e << endl;
	} catch (const std::exception &e) { // catch other exceptions
		cerr << e.what();
	} catch (...) {
		cerr << "Caught and exception of unknown type ..";
	}
    

    return 0;
}