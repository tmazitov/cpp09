#include "BitcoinExchange.hpp"

/*
* ORTHODOX section
*/

BitcoinExchange::BitcoinExchange() : _exchangeRates(), _latestDateTimestamp(0), _earliestDateTimestamp(0)
{
	_latestDateTimestamp = 0;
	_earliestDateTimestamp = 0;
	loadExchangeRates();
}

BitcoinExchange::~BitcoinExchange() 
{
}


BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	if (this != &other) {
		_latestDateTimestamp = 0;
		_earliestDateTimestamp = 0;
		this->loadExchangeRates();
	}
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other) {
		_latestDateTimestamp = 0;
		_earliestDateTimestamp = 0;
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
	long dateTimestamp;
	double rate;

	while (std::getline(database, line)) {
		std::istringstream iss(line);

		if (!(std::getline(iss, dateString, ',') && (iss >> rate))) {
			throw BitcoinExchange::ErrInvalidDataFormat(line);
		} 
		dateTimestamp = parseDate(dateString);

		if (_latestDateTimestamp == 0 || dateTimestamp > _latestDateTimestamp) {
			_latestDateTimestamp = dateTimestamp;
		}
		if (_earliestDateTimestamp == 0 || dateTimestamp < _earliestDateTimestamp) {
			_earliestDateTimestamp = dateTimestamp;
		}

		_exchangeRates[dateTimestamp] = rate;
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

long BitcoinExchange::dateToTimestamp(int day, int month, int year)
{
	std::tm date = {};
    date.tm_mday = day;
    date.tm_mon = month - 1; // month from 0
    date.tm_year = year - 1900; // year from 1900

	// If date values was invalid it will shift a date
	return std::mktime(&date);
}
bool BitcoinExchange::dateIsValid(int day, int month, int year)
{
	std::tm date = {};
    date.tm_mday = day;
    date.tm_mon = month - 1; // month from 0
    date.tm_year = year - 1900; // year from 1900

	// If date values was invalid it will shift a date
	std::mktime(&date);

	return date.tm_mday == day
		|| date.tm_year == year - 1900
		|| date.tm_mon == month - 1;
}

std::string BitcoinExchange::intToString(int num) 
{
    std::stringstream ss;
    ss << num;  
    return ss.str(); 
}

std::string BitcoinExchange::dateToString(int day, int month, int year)
{
	std::tm date = {};
    date.tm_mday = day;
    date.tm_mon = month - 1; // month from 0
    date.tm_year = year - 1900; // year from 1900

	// If date values was invalid it will shift a date
	std::mktime(&date);

	std::string result = "";

	result += intToString(date.tm_year) + "-";
	result += date.tm_mon <= 9 ? "0" : "";
	result += intToString(month) + "-";
	result += date.tm_mday <= 9 ? "0" : "";
	result += intToString(date.tm_mday);
	
	return result;
}

long BitcoinExchange::parseDate(std::string dateString, bool withValidation)
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
		
	return dateToTimestamp(day, month, year);
}

void BitcoinExchange::parseAmount(double amount)
{

	if (amount < 0) {
		throw BitcoinExchange::ErrNegativeInputAmount();
	}
	if (amount > 1000) {
		throw BitcoinExchange::ErrInputAmountTooLarge();
	}
}

double BitcoinExchange::getRateByTimestamp(long dateTimestamp)
{
	const int secondsPerDay = 86400;

	bool tooLate = dateTimestamp >= _latestDateTimestamp;
	bool tooEarly = dateTimestamp <= _earliestDateTimestamp;
	if (tooLate) 
	{
		return _exchangeRates[_latestDateTimestamp];
	} 
	else if (tooEarly) 
	{
		return _exchangeRates[_earliestDateTimestamp];
	}


	while(_exchangeRates.find(dateTimestamp) == _exchangeRates.end()) {
		dateTimestamp -= secondsPerDay;
	}

	return _exchangeRates[dateTimestamp];
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
	long dateTimestamp;
	double amount;
	double rate;

	while (std::getline(inputFile, line)) {
		std::istringstream iss(line);
		// std::cout << "line '" << line << "'" << std::endl;
		try
		{	
			if (!std::getline(iss, dateString, '|')) {
				throw BitcoinExchange::ErrInvalidDateFormat(dateString);
			} 
			dateTimestamp = parseDate(dateString, true);
			if (!(iss >> amount)) {
				throw BitcoinExchange::ErrInvalidDataFormat(line);
			}
			parseAmount(amount);
			rate = getRateByTimestamp(dateTimestamp);
			std::cout << dateString << " => " 
				<< amount << " = " 
				<< amount * rate << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}