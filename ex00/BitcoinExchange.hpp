#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <ctime>

class BitcoinExchange {
	private:
		std::string _filepath;
		std::ifstream _file;
		std::map<std::string, double> _exchangeRates;

		/*Parsing*/

		void loadExchangeRates();
		void parseLine(std::string line);
		bool dateIsValid(int day, int month, int year);
		
		/*Utils*/
		
		int stoi(std::string);
		
	public:
		BitcoinExchange();
		BitcoinExchange(std::string filepath);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);



    class ErrInvalidFilepath : public std::exception {
        public:
            virtual const char * what() const throw();
    };

    class ErrNoDatabase : public std::exception {
        public:
            virtual const char * what() const throw();
    };

	class ErrInvalidDatabase : public std::exception {
		public:
			virtual const char * what() const throw();
	};

	class ErrStoiConvert : public std::exception {
		public:
			std::string errorValue;
			ErrStoiConvert(std::string value);
			~ErrStoiConvert() throw();
			virtual const char * what() const throw();
			std::string generateMessage(std::string value) const;
	};

	class ErrInvalidDataFormat : public std::exception {
		public:
			std::string errorValue;
			ErrInvalidDataFormat(std::string errorValue);
			~ErrInvalidDataFormat() throw();
			virtual const char * what() const throw();
			std::string generateMessage(std::string value) const;
	};
};

#endif