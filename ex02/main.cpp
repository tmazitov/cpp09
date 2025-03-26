#include "PmergeMe.hpp"

int main(int ac, char **av) {

    if (ac == 1) {
        return 0;
    }

    std::vector<int> vector;
    std::list<int> list;
    try
    {
        vector = PmergeMe::prepareVector(ac, av);
        list = PmergeMe::prepareList(ac, av);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    std::cout << "Before : ";
    PmergeMe::printVector(vector);

    PmergeMe::sortVector(vector);
    PmergeMe::sortList(list);

    std::cout << "After : ";
    PmergeMe::printVector(vector);


    // std::cout << "Vector sort time : " << vectorTime << std::endl;
    // std::cout << "List sort time : " << listTime << std::endl;
    
    return 0;
}