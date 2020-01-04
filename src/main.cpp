#include <iostream>
#include <exception>
#include <iostream>
#include "b99_test.h"
#include "../src_utils/ExceptionUtils.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    try{
        test_c10_easy_glpk();
    }
    catch(ExceptionUtils e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
