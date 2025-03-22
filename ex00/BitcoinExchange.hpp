#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <ctime>
#include <iterator>
#include <vector>

class BitcoinExchange {
	private:
		std::map<std::vector<int>, double> _exchangeRates;

		/*Parsing*/

		void loadExchangeRates();
		std::vector<int> parseDate(std::istringstream iss, std::string line);

		
		/*Utils*/
		
		int stoi(std::string);
		bool dateIsValid(int day, int month, int year);
		std::vector<int> dateToVector(int day, int month, int year);
		std::vector<int> parseDate(std::string dateString);
		
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);

		void doFileRequest(std::string filePath);
		

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

	class ErrInvalidInputFile : public std::exception {
		public:
			virtual const char * what() const throw();
	};
};

#endif