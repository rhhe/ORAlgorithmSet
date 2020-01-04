//
// Created by Ron on 2019/10/7.
//

#include "b99_test.h"
#include "c10_easy_glpk_ilp.h"
#include <iostream>


void test_c10_easy_glpk() {
    EasyGlpkILP a;
    a.SetOptimization({{1, 10.0}, {2, 6.0}}, "max");

    a.AddRow({{1, 1.0}, {2, 1.0}}, "<=", 0., 200.);

    a.AddRow({{1, 1.0}, {2, 2.0}}, ">=", 10.0, 0.0);

    a.AddRow({{1, 3.0}, {2, 1.0}}, "<=", 0.0, 275.5);

    a.Solve();
    for (int i = 1; i <= 2; ++i) {
        std::cout << "x_" << i << " = " << a.GetResults().at(i) << std::endl;
    }
    std::cout << "z_final = " << a.GetFinalZ() << std::endl;

}

