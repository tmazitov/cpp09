#include "BitcoinExchange.hpp"

void validateArgs(int ac)
{
	if (ac != 2) 
	{
		throw std::invalid_argument("BitcoinExchange error : invalid amount of arguments");
	}
}

BitcoinExchange* setupBitcoinExchange(std::string filepath)
{
	return (new BitcoinExchange(filepath));
}


int main(int ac, char** av)
{	
	BitcoinExchange* exchange;
	try
	{
		/* code */
		validateArgs(ac);
		exchange = setupBitcoinExchange(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	
	(void)exchange;
}