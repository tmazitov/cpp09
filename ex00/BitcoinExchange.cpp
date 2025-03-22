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
	std::vector<int> dateVector;
	std::string dateString;
	double rate;

	while (std::getline(database, line)) {
		std::istringstream iss(line);

		if (!(std::getline(iss, dateString, ',') && (iss >> rate))) {
			throw BitcoinExchange::ErrInvalidDataFormat(line);
		} 
		dateVector = parseDate(dateString);
		_exchangeRates[dateVector] = rate;
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
	dateVector.push_back(date.tm_mday);
	dateVector.push_back(date.tm_mon + 1);
	dateVector.push_back(date.tm_year + 1900);

	return dateVector;
}

bool BitcoinExchange::dateIsValid(int day, int month, int year) 
{
	std::vector<int> initDate;
	initDate.push_back(day);
	initDate.push_back(month);
	initDate.push_back(year);

	std::vector<int> updatedDate = dateToVector(day, month, year);

    return initDate == updatedDate;
}

std::vector<int> BitcoinExchange::parseDate(std::string dateString)
{
	std::istringstream issDate(dateString);

	std::string yearString, 
				dayString, 
				monthString;

	std::getline(issDate, yearString, '-');
	std::getline(issDate, monthString, '-');
	std::getline(issDate, dayString, '-');	

	if (yearString.empty() || monthString.empty() || dayString.empty()) {
		throw BitcoinExchange::ErrInvalidDataFormat(dateString);
	}
	
	// if (!dateIsValid(day, month, year)) {
	// 	throw BitcoinExchange::ErrInvalidDataFormat(line);
	// }
		
	std::vector<int> dateVector = dateToVector(
		stoi(dayString), 
		stoi(monthString), 
		stoi(yearString));

	// std::cout << dateVector[0] << "." << dateVector[1] << "." << dateVector[2] << std::endl;

	return dateVector;
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
	std::vector<int> dateVector;
	double amount;
	while (std::getline(inputFile, line)) {
		std::istringstream iss(line);
		try
		{	
			if (!(std::getline(iss, dateString, '|') && (iss >> amount))) {
				throw BitcoinExchange::ErrInvalidInputFile();
			} 
			dateVector = parseDate(dateString);
			std::cout << dateVector[0] << "." << dateVector[1] << "." << dateVector[2] << std::endl;
		}
		catch(const BitcoinExchange::ErrInvalidInputFile& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}