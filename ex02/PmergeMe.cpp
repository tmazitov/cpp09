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
    std::vector<int> sorted;
    std::vector<int> pending;

    for (long unsigned int i = 0; i < vector.size(); i++)
    {
        if (i % 2 == 1)
        {
            sorted.push_back(std::max(vector[i], vector[i - 1]));
            pending.push_back(std::min(vector[i], vector[i - 1]));
        }
    }
    if (vector.size() % 2 == 1)
    {
        sorted.push_back(vector[vector.size() - 1]);
    }

    if (sorted.size() > 1)
    {
        sortVector(sorted);
    }

    for (long unsigned int i = 0; i < pending.size(); i++)
    {
        std::vector<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), pending[i]);
        sorted.insert(it, pending[i]);
    }

    vector = sorted;
}   

void PmergeMe::sortList(std::list<int> &list)
{
    std::list<int> sorted;
    std::list<int> pending;

    for (long unsigned int i = 0; i < list.size(); i++)
    {
        if (i % 2 == 1)
        {
            int a = getListValue(list, i);
            int b = getListValue(list, i - 1);
            sorted.push_back(std::max(a, b));
            pending.push_back(std::min(a, b));
        }
    }
    if (list.size() % 2 == 1)
    {
        sorted.push_back(getListValue(list, list.size() - 1));
    }

    if (sorted.size() > 1)
    {
        sortList(sorted);
    }

    for (long unsigned int i = 0; i < pending.size(); i++)
    {
        int a =  getListValue(list, i);;
        std::list<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), a);
        sorted.insert(it, a);
    }

    list = sorted;
}

int PmergeMe::getListValue(std::list<int> &list, int index)
{
    std::list<int>::iterator it = list.begin();
    std::advance(it, index); 
    return *it;
}

void PmergeMe::printVector(std::vector<int> &vector)
{
    for (long unsigned int i = 0; i < (unsigned long int)(std::min(int(vector.size()), 100)); i++)
    {
        std::cout << vector[i] << " ";
    }

    if (vector.size() > 100)
    {
        std::cout << "...";
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