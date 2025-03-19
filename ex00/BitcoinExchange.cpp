#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _filepath(""), _file("") {}

BitcoinExchange::BitcoinExchange(std::string filepath) : _filepath(filepath), _file(filepath)
{
	if (!_file.good()) {
		throw BitcoinExchange::ErrInvalidFilepath();
	}
}

BitcoinExchange::~BitcoinExchange() {}

const char * BitcoinExchange::ErrInvalidFilepath::what() const throw()
{
	return "BitcoinExchange error : invalid filepath";
}