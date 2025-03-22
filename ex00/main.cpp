#include "BitcoinExchange.hpp"

void validateArgs(int ac)
{
	if (ac != 2) 
	{
		throw std::invalid_argument("BitcoinExchange error : invalid amount of arguments");
	}
}

BitcoinExchange* setupBitcoinExchange()
{
	return (new BitcoinExchange());
}


int main(int ac, char** av)
{	
	BitcoinExchange* exchange;
	try
	{
		/* code */
		validateArgs(ac);
		exchange = setupBitcoinExchange();
		(void)av;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	try
	{
		exchange->doFileRequest(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	delete exchange;
	return 0;
}