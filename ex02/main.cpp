#include "PmergeMe.hpp"

int main(int ac, char **av) {

    if (ac == 1) {
        return 0;
    }

    PmergeMe merger;

    std::vector<int> vector;
    std::list<int> list;
    try
    {
        vector = merger.prepareVector(ac, av);
        list = merger.prepareList(ac, av);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    clock_t startVector, endVector;
    clock_t startList, endList;
    
    std::cout << "Before : ";
    merger.printVector(vector);

    startVector = clock();  
    merger.sortVector(vector);
    endVector = clock();  
    
    startList = clock();
    merger.sortList(list);
    endList = clock();
    
    
    std::cout << "After : ";
    merger.printVector(vector);
    
    std::cout << std::fixed << std::setprecision(6);  
    std::cout << "Vector time for " 
            << vector.size() <<  " elements : " 
            << double(endVector - startVector) / CLOCKS_PER_SEC << std::endl;
    std::cout << "List time for "
            << vector.size() << " elements : " 
            << double(endList - startList) / CLOCKS_PER_SEC << std::endl;
    
    return 0;
}