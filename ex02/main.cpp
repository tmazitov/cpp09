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
        return (1);
    }
    clock_t startVector, endVector;
    clock_t startList, endList;
    
    std::cout << "Before : ";
    PmergeMe::printVector(vector);

    startVector = clock();  
    PmergeMe::sortVector(vector);
    endVector = clock();  
    
    startList = clock();
    PmergeMe::sortList(list);
    endList = clock();
    
    
    std::cout << "After : ";
    PmergeMe::printVector(vector);
    
    std::cout << std::fixed << std::setprecision(6);  
    std::cout << "Vector time for " 
            << vector.size() <<  " elements : " 
            << double(endVector - startVector) / CLOCKS_PER_SEC << std::endl;
    std::cout << "List time for "
            << vector.size() << " elements : " 
            << double(endList - startList) / CLOCKS_PER_SEC << std::endl;
    
    return 0;
}