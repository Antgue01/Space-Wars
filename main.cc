#include <iostream>
#include "SpaceWars.h"
int main(int argc, char **argv)
{

	try
	{

		if (argc == 4)
		{
			//si se recibe como parámetro 1 se creará una instancia que hará de cliente y si se recibe un 0 se creará una instancia que hará de servidor
			bool isClient = std::atoi(argv[3]) == 1;
			SpaceWars s(argv[1], argv[2], isClient);
			s.start();
		}
		else
		{
			std::cout << "Usage: main <host> <port> <isClient> (1 is client or 0 is server)\n";
		}
	}
	catch (std::string &e)
	{ 		cout << e << endl;
	}
	catch (const std::exception &e)
	{ 		cout << e.what();
	}
	catch (...)
	{
		cerr << "Caught and exception of unknown type ..";
	}

	return 0;
}