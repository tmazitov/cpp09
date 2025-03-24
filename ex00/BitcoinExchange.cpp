#include "BitcoinExchange.hpp"

/*
* ORTHODOX section
*/

BitcoinExchange::BitcoinExchange() : _exchangeRates()
{
	loadExchangeRates();
}

BitcoinExchange::~BitcoinExchange() 
{
}


BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	(void)other; // Mark the parameter as unused
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other) {
		this->loadExchangeRates();
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


const char * BitcoinExchange::ErrInvalidInputFile::what() const throw()
{
	return "BitcoinExchange ErrInvalidInputFile error : invalid format of input file.";
}
BitcoinExchange::ErrInvalidDateFormat::ErrInvalidDateFormat(std::string errorValue): errorValue(errorValue){}
BitcoinExchange::ErrInvalidDateFormat::~ErrInvalidDateFormat() throw() {}
std::string BitcoinExchange::ErrInvalidDateFormat::generateMessage() const
{
	return "BitcoinExchange ErrInvalidDateFormat error : record date bad input => '" + errorValue + "'.";
}
const char * BitcoinExchange::ErrInvalidDateFormat::what() const throw()
{
	static std::string message = generateMessage();
	return message.c_str();
}

const char * BitcoinExchange::ErrNegativeInputAmount::what() const throw()
{
	return "BitcoinExchange ErrNegativeInputAmount error : record amount is not a positive number.";
}
const char * BitcoinExchange::ErrInputAmountTooLarge::what() const throw()
{
	return "BitcoinExchange ErrInputAmountTooLarge error : record amount is too large a number.";
}


/**
 * PARSING section
 */

void BitcoinExchange::loadExchangeRates()
{
	std::string line;
	std::ifstream database("data.csv");
	if (!database.good()) {
		throw BitcoinExchange::ErrNoDatabase();
	}

	// Check database header
	std::getline(database, line);
	if (line != "date,exchange_rate") {
		throw BitcoinExchange::ErrInvalidDatabase();
	}

	// Parsing data from database
	std::string dateString;
	double rate;

	while (std::getline(database, line)) {
		std::istringstream iss(line);

		if (!(std::getline(iss, dateString, ',') && (iss >> rate))) {
			throw BitcoinExchange::ErrInvalidDataFormat(line);
		} 
		dateString = parseDate(dateString);
		_exchangeRates[dateString] = rate;
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

std::vector<int> BitcoinExchange::dateToVector(int day, int month, int year)
{
	std::tm date = {};
    date.tm_mday = day;
    date.tm_mon = month - 1; // month from 0
    date.tm_year = year - 1900; // year from 1900

	// If tm values is invalid it will shift a date
    std::mktime(&date);

	std::vector<int> dateVector;
	dateVector.push_back(date.tm_year + 1900);
	dateVector.push_back(date.tm_mon + 1);
	dateVector.push_back(date.tm_mday);

	return dateVector;
}

std::string BitcoinExchange::intToString(int num) 
{
    std::stringstream ss;
    ss << num;  
    return ss.str(); 
}

std::string BitcoinExchange::vectorToString(std::vector<int> dateVector)
{
	std::string result = "";

	result += intToString(dateVector[0]) + "-";
	result += dateVector[1] <= 9 ? "0" : "";
	result += intToString(dateVector[1]) + "-";
	result += dateVector[2] <= 9 ? "0" : "";
	result += intToString(dateVector[2]);
	
	return result;
}

bool BitcoinExchange::dateIsValid(int day, int month, int year) 
{
	std::vector<int> initDate;
	initDate.push_back(year);
	initDate.push_back(month);
	initDate.push_back(day);

	std::vector<int> updatedDate = dateToVector(day, month, year);

	// std::cout << "old" << initDate[0] << "." << initDate[1] << "." << initDate[2] << std::endl;
	// std::cout << "new" << updatedDate[0] << "." << updatedDate[1] << "." << updatedDate[2] << std::endl;

    return initDate == updatedDate;
}

std::string BitcoinExchange::parseDate(std::string dateString, bool withValidation)
{
	std::istringstream issDate(dateString);

	std::string yearString, 
				dayString, 
				monthString;

	std::getline(issDate, yearString, '-');
	std::getline(issDate, monthString, '-');
	std::getline(issDate, dayString, '-');	

	if (yearString.empty() || monthString.empty() || dayString.empty()) {
		throw BitcoinExchange::ErrInvalidDateFormat(dateString);
	}
	
	int year = stoi(yearString),
		month = stoi(monthString),
		day = stoi(dayString);

	if (withValidation && !dateIsValid(day, month, year)) {
		throw BitcoinExchange::ErrInvalidDateFormat(dateString);
	}
		
	std::vector<int> dateVector = dateToVector(day, month, year); 

	

	return vectorToString(dateVector);
}

void BitcoinExchange::doFileRequest(std::string filePath)
{

	if (filePath.empty()) {
		throw BitcoinExchange::ErrInvalidFilepath();
	}

	std::ifstream inputFile(filePath.c_str());
	if (!inputFile.good()) {
		throw BitcoinExchange::ErrInvalidFilepath();
	}
	std::string line;
	std::getline(inputFile, line);
	std::cout << line << std::endl; 
	if (line != "date | value") {
		throw BitcoinExchange::ErrInvalidInputFile();
	}


	std::string dateString;
	double amount;
	while (std::getline(inputFile, line)) {
		std::istringstream iss(line);
		// std::cout << "line '" << line << "'" << std::endl;
		try
		{	
			if (!std::getline(iss, dateString, '|')) {
				throw BitcoinExchange::ErrInvalidDateFormat(dateString);
			} 
			dateString = parseDate(dateString, true);
			if (!(iss >> amount)) {
				throw BitcoinExchange::ErrInvalidDataFormat(line);
			}
			if (amount < 0) {
				throw BitcoinExchange::ErrNegativeInputAmount();
			}
			if (amount > 1000) {
				throw BitcoinExchange::ErrInputAmountTooLarge();
			}
			std::cout << dateString << " => " << amount << std::endl;

		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}