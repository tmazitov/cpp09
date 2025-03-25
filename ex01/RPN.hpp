#ifndef RPN_H
#define RPN_H

#include <stack>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <utility>

class RPN {
	private:
		std::stack<double> _digitKeys;

	public:
		RPN();
		~RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		
		typedef double (RPN::*Operation)(double, double);
		static const std::pair<char, Operation> operations[4];

		void calculateByString(std::string originStr);
		double plus(double x, double y);
		double minus(double x, double y);
		double multiply(double x, double y);
		double divide(double x, double y);
		double makeOperation(char operation, double x, double y);
		bool isArithmeticOperator(char ch);
		int stoi(std::string);

	class ErrInvalidKey : public std::exception {
        public:
            virtual const char * what() const throw();
    };

	class ErrInvalidInputString : public std::exception {
		public:
			std::string reason;
			ErrInvalidInputString(std::string reason);
			~ErrInvalidInputString() throw();
			virtual const char * what() const throw();
			std::string generateMessage() const;
	};

	class ErrStoiConvert : public std::exception {
		public:
			std::string errorValue;
			ErrStoiConvert(std::string value);
			~ErrStoiConvert() throw();
			virtual const char * what() const throw();
			std::string generateMessage(std::string value) const;
	};
};

#endif // !RPN_H