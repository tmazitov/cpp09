#include "BitcoinExchange.hpp"

/*
* ORTHODOX section
*/

BitcoinExchange::BitcoinExchange() : _filepath(""), _file(""), _exchangeRates()
{
	loadExchangeRates();
}

BitcoinExchange::BitcoinExchange(std::string filepath) : _filepath(filepath), _file(filepath.c_str()), _exchangeRates()
{
	if (!_file.good()) {
		throw BitcoinExchange::ErrInvalidFilepath();
	}
	loadExchangeRates();
}

BitcoinExchange::~BitcoinExchange() 
{
	if (_file.is_open()) {
		_file.close();
	}
}


BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _filepath(other._filepath), _file(other._filepath.c_str())
{
	if (!_file.good()) {
		throw BitcoinExchange::ErrInvalidFilepath();
	}
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other) {
		_filepath = other._filepath;
		_file.close();
		_file.open(_filepath.c_str());
		if (!_file.good()) {
			throw BitcoinExchange::ErrInvalidFilepath();
		}
	}
	return *this;
}

/**
 * ERRORS section
 */


const char * BitcoinExchange::ErrInvalidFilepath::what() const throw()
{
	return "BitcoinExchange ErrInvalidFilepath error : invalid filepath";
}

const char * BitcoinExchange::ErrNoDatabase::what() const throw()
{
	return "BitcoinExchange ErrNoDatabase error : database file 'data.csv' not found in the root folder";
}

const char * BitcoinExchange::ErrInvalidDatabase::what() const throw()
{
	return "BitcoinExchange ErrInvalidDatabase error : invalid format of database file.";
}

BitcoinExchange::ErrStoiConvert::ErrStoiConvert(std::string errorValue): errorValue(errorValue){}
BitcoinExchange::ErrStoiConvert::~ErrStoiConvert() throw() {}


std::string BitcoinExchange::ErrStoiConvert::generateMessage(std::string value) const
{
	return "BitcoinExchange ErrStoiConvert error : stoi unable to convert '" + value + "' to int.";
}

const char * BitcoinExchange::ErrStoiConvert::what() const throw()
{
	static std::string message = generateMessage(errorValue);
	return message.c_str();
}


BitcoinExchange::ErrInvalidDataFormat::ErrInvalidDataFormat(std::string errorValue): errorValue(errorValue){}
BitcoinExchange::ErrInvalidDataFormat::~ErrInvalidDataFormat() throw() {}


std::string BitcoinExchange::ErrInvalidDataFormat::generateMessage(std::string value) const
{
	return "BitcoinExchange ErrInvalidDataFormat error : data format of '" + value + "' record is invalid.";
}

const char * BitcoinExchange::ErrInvalidDataFormat::what() const throw()
{
	static std::string message = generateMessage(errorValue);
	return message.c_str();
}



/**
 * PARSING section
 */

void BitcoinExchange::loadExchangeRates()
{
	std::string line;
	std::ifstream database("data.csv");
	if (!_file.good()) {
		throw BitcoinExchange::ErrNoDatabase();
	}

	// Check database header
	std::getline(database, line);
	if (line != "date,exchange_rate") {
		throw BitcoinExchange::ErrInvalidDatabase();
	}

	// Parsing data from database
	while (std::getline(database, line)) {
		parseLine(line);
	}
}

int BitcoinExchange::stoi(std::string line) 
{
	std::istringstream issLine(line);
	int num;
	char leftover;

	if (!(issLine >> num) || (issLine >> leftover)) {
		throw BitcoinExchange::ErrStoiConvert(line);
	}
	return num;
}

bool BitcoinExchange::dateIsValid(int day, int month, int year) 
{
    std::tm timeinfo = {};
    timeinfo.tm_mday = day;
    timeinfo.tm_mon = month - 1; // month from 0
    timeinfo.tm_year = year - 1900; // year from 1900

	// If tm values is invalid it will shift a date
    std::mktime(&timeinfo);

    return timeinfo.tm_mday == day
		&& timeinfo.tm_mon == month - 1 
		&& timeinfo.tm_year == year - 1900;
}

void BitcoinExchange::parseLine(std::string line)
{
	std::istringstream iss(line);
	std::string date;
	double rate;

	// Split the line into date and rate
	if (!(std::getline(iss, date, ',') && iss >> rate)) {
		throw BitcoinExchange::ErrInvalidDatabase();
	} 

	std::istringstream issDate(date);

	std::string yearString, 
				dayString, 
				monthString;

	std::getline(issDate, yearString, '-');
	std::getline(issDate, monthString, '-');
	std::getline(issDate, dayString);	

	if (yearString.empty() || monthString.empty() || dayString.empty()) {
		throw BitcoinExchange::ErrInvalidDataFormat(line);
	}

	int month = stoi(monthString),
		year = stoi(yearString), 
		day = stoi(dayString);

	if (!dateIsValid(day, month, year)) {
		throw BitcoinExchange::ErrInvalidDataFormat(line);
	}
		
	std::cout << "Year: " << year << std::endl;
	std::cout << "Month: " << month << std::endl;
	std::cout << "Day: " << day << std::endl;	
}



