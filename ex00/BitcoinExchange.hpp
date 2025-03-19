#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>

class BitcoinExchange {
	private:
		std::string _filepath;
		std::ifstream _file;
	public:
		BitcoinExchange();
		BitcoinExchange(std::string filepath);
		~BitcoinExchange();
		// BitcoinExchange(const BitcoinExchange& other);
		// BitcoinExchange& operator=(const BitcoinExchange& other);


    class ErrInvalidFilepath : public std::exception {
        public:
            virtual const char * what() const throw();
    };
};

#endif