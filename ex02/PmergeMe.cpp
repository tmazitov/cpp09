#include "PmergeMe.hpp"

int PmergeMe::stoi(std::string line) 
{
	std::istringstream issLine(line);
	int num;
	char leftover;

	if (!(issLine >> num) || (issLine >> leftover)) {
		throw PmergeMe::ErrStoiConvert(line);
	}
	return num;
}

std::vector<int> PmergeMe::prepareVector(int ac, char **av)
{
    std::vector<int> result;
    for (int i = 1; i < ac; i++)
    {
        result.push_back(PmergeMe::stoi(av[i]));
    }
    return result;
}

std::list<int> PmergeMe::prepareList(int ac, char **av)
{
    std::list<int> result;
    for (int i = 1; i < ac; i++)
    {
        result.push_back(PmergeMe::stoi(av[i]));
    }
    return result;
}


void PmergeMe::sortVector(std::vector<int> &vector)
{
    (void)vector;
}   

void PmergeMe::sortList(std::list<int> &list)
{
    (void)list;
}

void PmergeMe::printVector(std::vector<int> &vector)
{
    for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}


PmergeMe::ErrStoiConvert::ErrStoiConvert(std::string errorValue): errorValue(errorValue){}
PmergeMe::ErrStoiConvert::~ErrStoiConvert() throw() {}


std::string PmergeMe::ErrStoiConvert::generateMessage(std::string value) const
{
	return "PmergeMe ErrStoiConvert error : stoi unable to convert '" + value + "' to int.";
}

const char * PmergeMe::ErrStoiConvert::what() const throw()
{
	static std::string message = generateMessage(errorValue);
	return message.c_str();
}