#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <ctime>
#include <sys/time.h>
#include <iomanip>

class PmergeMe
{
    private:

    public:
        static std::vector<int> prepareVector(int ac, char **av);
        static std::list<int> prepareList(int ac, char **av);

        static int stoi(std::string line);

        static void sortVector(std::vector<int> &vector);
        static void sortList(std::list<int> &list);
        static int getListValue(std::list<int> &list, int index);
        
        static void printVector(std::vector<int> &vector);


    class ErrStoiConvert : public std::exception {
        public:
            std::string errorValue;
            ErrStoiConvert(std::string value);
            ~ErrStoiConvert() throw();
            virtual const char * what() const throw();
            std::string generateMessage(std::string value) const;
    };    
};


#endif // !PMERGEME_HPP