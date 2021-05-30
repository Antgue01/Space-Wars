#include <iostream>
#include "SpaceWars.h"
#include "SDLGame.h"
int main()
{  
    try {
    	SpaceWars s;
		s.start();
		//SDLGame::instance()->closeSDL();
	} catch (std::string &e) { // catch errors thrown as strings
		cerr << e << endl;
	} catch (const std::exception &e) { // catch other exceptions
		cerr << e.what();
	} catch (...) {
		cerr << "Caught and exception of unknown type ..";
	}
    

    return 0;
}