#include "RPN.hpp"

const std::pair<char, RPN::Operation> RPN::operations[4] = {
    std::make_pair('+', &RPN::plus),
    std::make_pair('-', &RPN::minus),
    std::make_pair('*', &RPN::multiply),
    std::make_pair('/', &RPN::divide)
};

RPN::RPN() :  _digitKeys(){

}

RPN::~RPN() {}

RPN::RPN(const RPN& other){(void)other;}

RPN& RPN::operator=(const RPN& other){(void)other;return *this;}

bool RPN::isArithmeticOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

double RPN::plus(double x, double y) { return x + y; }
double RPN::minus(double x, double y) { return x - y; }
double RPN::multiply(double x, double y) { return x * y; }
double RPN::divide(double x, double y) { return x / y; }

double RPN::makeOperation(char operation, double x, double y)
{
	const std::pair<char, RPN::Operation> operationFunc;
	int counter = 0;

	while (counter < 4) 
	{

		if (RPN::operations[counter].first == operation) {
			return (this->*(RPN::operations[counter].second))(x, y);
		}

		counter++;
	}
	throw RPN::ErrInvalidKey();
}

void RPN::calculateByString(std::string inputStr)
{
	std::string temp;

	if (inputStr.empty()) {
		return ;
	}

	std::string::iterator begin = inputStr.begin();
	std::string::iterator end = inputStr.end();
	std::string::iterator it;
	bool keyIsFaced = false;
	int operationsAmount = 0;
	double tempValue1;
	double tempValue2;
	int sign = 1;

	char key;

	for (it = begin; it != end; it++)
	{
		if ( *it == ' ')
		{
			keyIsFaced = false;
			continue;
		}
		if (*it == '-' && (it + 1) != end && std::isdigit(*(it + 1)))
		{
			sign = -1;
			continue;
		}
		key = *it;
		if (keyIsFaced || !(std::isdigit(key) || isArithmeticOperator(key))) {
			throw RPN::ErrInvalidKey();
		}


		/*
		If func faced a digit it will record it to the stack
		to use it when it face an operator*/
		if (std::isdigit(key)) {
			std::string keyString = "";
			keyString += key;
			if (sign == -1)
				keyString = "-" + keyString;
			_digitKeys.push(stoi(keyString));
			sign = 1;
		}

		/*
		If func faced an operator it will take 1 or 2 values from the stack
		to make arithmetic operation */ 
		if (isArithmeticOperator(key)) {
			if (_digitKeys.size() < 2) 
			{
				throw RPN::ErrInvalidInputString("before the first operation symbol should be at least 2 digits");
			}

			tempValue2 = _digitKeys.top();
			_digitKeys.pop();

			tempValue1 = _digitKeys.top();
			_digitKeys.pop();

			// std::cout << tempValue2 << " " << key << " " << tempValue1 << std::endl;


			_digitKeys.push(makeOperation(key, tempValue1, tempValue2));

			operationsAmount++;
		}
		
		
		keyIsFaced = true;
	}

	if (_digitKeys.size() != 1) 
	{
		throw RPN::ErrInvalidInputString("not enough arithmetic operators");
	}

	std::cout << _digitKeys.top() << std::endl;
}
int RPN::stoi(std::string line) 
{
	std::istringstream issLine(line);
	int num;
	char leftover;

	if (line.empty() || !(issLine >> num) || (issLine >> leftover)) {
		throw RPN::ErrStoiConvert(line);
	}
	return num;
}

const char * RPN::ErrInvalidKey::what() const throw()
{
	return "RPN ErrInvalidKey error : calculation key is invalid. You must to use digits and basic arithmetical operators only.";
}

RPN::ErrInvalidInputString::ErrInvalidInputString(std::string reason) : reason(reason) {}
RPN::ErrInvalidInputString::~ErrInvalidInputString() throw() {} 
std::string RPN::ErrInvalidInputString::generateMessage() const
{
	return "RPN ErrInvalidKey error : calculation string is invalid. Reason: " + reason + ".";
}

const char * RPN::ErrInvalidInputString::what() const throw()
{
	static std::string message = generateMessage();
	return message.c_str();
}


RPN::ErrStoiConvert::ErrStoiConvert(std::string errorValue): errorValue(errorValue){}
RPN::ErrStoiConvert::~ErrStoiConvert() throw() {}


std::string RPN::ErrStoiConvert::generateMessage(std::string value) const
{
	return "RPN ErrStoiConvert error : stoi unable to convert '" + value + "' to int.";
}

const char * RPN::ErrStoiConvert::what() const throw()
{
	static std::string message = generateMessage(errorValue);
	return message.c_str();
}