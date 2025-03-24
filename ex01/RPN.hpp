#ifndef RPN_H
#define RPN_H

#include <queue>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

class RPN {
	private:
		std::queue<char> _operationKeys;
		
		bool inputStrIsValid(std::string inputStr);
		bool isArithmeticOperator(char ch);

	public:
		RPN();
		~RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		
		void loadByString(std::string originStr);

	class ErrInvalidKey : public std::exception {
        public:
            virtual const char * what() const throw();
    };
};

#endif // !RPN_H