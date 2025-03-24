#include "RPN.hpp"

RPN::RPN() : _operationKeys() {}

RPN::~RPN() {}

RPN::RPN(const RPN& other){(void)other;}

RPN& RPN::operator=(const RPN& other){(void)other;return *this;}

bool RPN::isArithmeticOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

void RPN::loadByString(std::string inputStr)
{
	std::string temp;

	if (inputStr.empty()) {
		throw RPN::ErrInvalidKey();
	}

	std::string::iterator begin = inputStr.begin();
	std::string::iterator end = inputStr.end();
	std::string::iterator it;
	bool keyIsFaced = false;
	int digitsAmount = 0;
	int operationsAmount = 0;
	char key;

	for (it = begin; it != end; it++)
	{
		if ( *it == ' ')
		{
			keyIsFaced = false;
			continue;
		}
		key = *it;
		if (keyIsFaced || !(std::isdigit(key) || isArithmeticOperator(key))) {
			throw RPN::ErrInvalidKey();
		}

		if (std::isdigit(key)) {
			if (digitsAmount == 2) {
				throw RPN::ErrInvalidKey();
			}
			digitsAmount++;
		}

		if (isArithmeticOperator(key)) {
			if ((digitsAmount == 2 && operationsAmount == 0)
			 ||	(digitsAmount == 1 && operationsAmount > 0)) {
				digitsAmount = 0;
			} else {
				throw RPN::ErrInvalidKey();
			}	
			operationsAmount++;
		}
		
		std::cout << key << std::endl;
		_operationKeys.push(key);
		keyIsFaced = true;
	}

	std::cout << "last key " << key << std::endl;
}


const char * RPN::ErrInvalidKey::what() const throw()
{
	return "RPN ErrInvalidKey error : calculation key is invalid. You must to use digits and basic arithmetical operators only.";
}


