#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << "RPN error : not enough arguments." << std::endl;
		return 1;
	}

	RPN instance;

	try
	{
		instance.loadByString(av[1]);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}