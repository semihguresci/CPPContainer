#include <iostream>
#include <functional>
#include <cmath>
#include "Optimum.h"
#include "Finder.h"
#include <RandomInRange.h>
namespace FuctionPointerLamda{
    bool less(int x, int y) { return x < y; }

    void Run()
    {
        std::vector<double> numbers{ 91, 18, 92, 22, 13, 43 };

        int number_to_search_for{ RandomInRange::getRandomNum<int,0,100>()};
        
        Finder finder;
        finder.setNumberToSearchFor(number_to_search_for);
        std::cout << "The number nearest to " << finder.getNumberToSearchFor() << " is "
            << *finder.findNearest(numbers) << std::endl;

        int a{ 18 }, b{ 8 };
        std::cout << std::boolalpha; 

        std::function<bool(int, int)> compare;

        compare = less;              
        std::cout << a << " < " << b << ": " << compare(a, b) << std::endl;

        compare = std::greater<>{};  
        std::cout << a << " > " << b << ": " << compare(a, b) << std::endl;

        int n{ 10 };                 
        compare = [n](int x, int y) { return std::abs(x - n) < std::abs(y - n); };
        std::cout << a << " nearer to " << n << " than " << b << ": " << compare(a, b);

        std::function<void(const int&)> empty;
        if (empty)             
        {
            std::cout << "Calling a default-constructed std::function<>?" << std::endl;
            empty(a);
        }
    }
}