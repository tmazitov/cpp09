#include "BitcoinExchange.hpp"

void validateArgs(int ac)
{
	if (ac != 2) 
	{
		std::cerr << "BitcoinExchange error : invalid amount of arguments" << std::endl;
		exit(1);
	}
}

BitcoinExchange* setupBitcoinExchange(std::string filepath)
{
	try
	{
		return (new BitcoinExchange(filepath));
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}


int main(int ac, char** av)
{	
	validateArgs(ac);
	BitcoinExchange* exchange = setupBitcoinExchange(av[1]);
	(void)exchange;
}