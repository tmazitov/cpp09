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
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        std::vector<int> prepareVector(int ac, char **av);
        std::list<int> prepareList(int ac, char **av);

        int stoi(std::string line);

        void sortVector(std::vector<int> &vector);
        void sortList(std::list<int> &list);
        int getListValue(std::list<int> &list, int index);
        
        void printVector(std::vector<int> &vector);


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