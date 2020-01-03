//
// Created by Ron on 2019/10/7.
//

#include "b99_test.h"
#include "c10_easy_glpk_ilp.h"
#include <iostream>


void test_c10_easy_glpk() {
    EasyGlpkILP a;
    std::vector<std::pair<int, double>> array_c
            {
                    std::pair<int, double>(1, 10.0),
                    std::pair<int, double>(2, 6.0)
            };
    a.SetOptimization(array_c, GLPK_OPTIMIZATION_MAX);

    std::vector<std::pair<int, double>> rows_factor_tmp(0);
    rows_factor_tmp = std::vector<std::pair<int, double>>{
            std::pair<int, double>(1, 1.0),
            std::pair<int, double>(2, 1.0)
    };
    a.AddRow(rows_factor_tmp, GLPK_COMPARISON_UPPER_BOUNDARY, 0.0, 200.);

    rows_factor_tmp = std::vector<std::pair<int, double>>{
            std::pair<int, double>(1, 1.0),
            std::pair<int, double>(2, 2.0)
    };
    a.AddRow(rows_factor_tmp, GLPK_COMPARISON_LOWER_BOUNDARY, 10.0, 0.0);

    rows_factor_tmp = std::vector<std::pair<int, double>>{
            std::pair<int, double>(1, 3.0),
            std::pair<int, double>(2, 1.0)
    };
    a.AddRow(rows_factor_tmp, GLPK_COMPARISON_UPPER_BOUNDARY, 0.0, 275.5);

    a.Solve();
    for(int i = 1; i <= 2; ++ i)
    {
        std::cout << "x_" << i << " = " << a.GetResults(i) << std::endl;
    }
    std::cout << "z_final = " << a.GetFinalZ() << std::endl;

}

