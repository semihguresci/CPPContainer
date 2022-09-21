#include "mArray.h"
#include <string>
#include <vector>

namespace Movesemantics {


    Array<std::string> buildStringArray(const size_t size)
    {
        Array<std::string> result{ size };
        for (size_t i{}; i < size; ++i)
            result[i] = "You should learn from your competitor, but never copy. Copy and you die.";
        return result;
    }

    void Run()
    {
        std::vector<Array<std::string>> v;

        v.push_back(buildStringArray(1'000));

        std::cout << std::endl;

        v.push_back(buildStringArray(2'000));
    }
}