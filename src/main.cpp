#include <iostream>
#include <exception>
#include <stdexcept>
#include <exception>
#include "b99_test.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    try{
        test_c10_easy_glpk();
    }
    catch(const std::exception & err)
    {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}
