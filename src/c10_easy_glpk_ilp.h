//
// Created by Ron on 2019/10/7.
//

#ifndef D003_PACKAGE_EASY_GLPK_C10_EASY_GLPK_ILP_H
#define D003_PACKAGE_EASY_GLPK_C10_EASY_GLPK_ILP_H

#include <glpk.h>
#include <cstdlib>
#include <vector>
#include <map>
#include <cfloat>
#include <map>
#include <cstdlib>
#include <iostream>

using namespace std;

class EasyGlpkILP {
public:
    EasyGlpkILP() = default;

    virtual ~EasyGlpkILP() = default;


    void SetOptimization(const vector<pair<int, double>> &factors, const string &opt);

    void AddRow(const vector<pair<int, double>> &a, const string &comparison, double b1, double b2);

    void Solve();

    const vector<int> &GetResults() const;

    double GetFinalZ() const;

protected:
    const map<string, int> m_optimizationTypeMapper = {
            {"min", GLP_MIN},
            {"max", GLP_MAX}
    };

    const map<string, int> m_comparisonTypeMapper = {
            {"",   GLP_FR},
            {">=", GLP_LO},
            {"<=", GLP_UP},
            {"[]", GLP_DB},
            {"==", GLP_FX}
    };

    bool CheckInput();

    int m_n_col = 0;
    int m_n_row = 0;

    // c_factors, optimization
    class Optimization
    {
    public:
        Optimization() = default;
        ~Optimization() = default;
        vector<pair<int, double>> m_factors;
        int m_glp_opt = -1;
    };
    class Row
    {
    public:
        Row() = default;
        ~Row() = default;
        int m_index = -1;
        vector<pair<int, double>> m_factors;
        int m_glp_comparison = -1;
        double m_b1 = 0.0;
        double m_b2 = 0.0;
    };
    Optimization m_opt;
    vector<Row> m_rows;
    // results
    vector<int> m_col_res = vector<int>(0);

    // final value
    double m_z_final = 0.;
protected: // consts
    static const int m_NAME_SIZE = 100;

};

#endif //D003_PACKAGE_EASY_GLPK_C10_EASY_GLPK_ILP_H
