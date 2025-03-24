#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <ctime>
#include <iterator>
#include <string>

class BitcoinExchange {
	private:
		std::map<long, double> _exchangeRates;
		long _latestDateTimestamp; 
		long _earliestDateTimestamp; 

		/*Parsing*/

		void loadExchangeRates();
		long parseDate(std::string dateString, bool withValidation = false);
		void parseAmount(double amount);

		
		/*Utils*/
		
		int stoi(std::string);
		bool dateIsValid(int day, int month, int year);
		long dateToTimestamp(int day, int month, int year);
		std::string dateToString(int day, int month, int year);

		std::string intToString(int num);
		double getRateByTimestamp(long dateTimestamp);

		
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
	class ErrInvalidDateFormat : public std::exception {
		public:
			std::string errorValue;
			ErrInvalidDateFormat(std::string errorValue);
			~ErrInvalidDateFormat() throw();
			virtual const char * what() const throw();
			std::string generateMessage() const;
	};
	class ErrNegativeInputAmount : public std::exception {
		public:
			virtual const char * what() const throw();
	};
	class ErrInputAmountTooLarge : public std::exception {
		public:
			virtual const char * what() const throw();
	};
};

#endif