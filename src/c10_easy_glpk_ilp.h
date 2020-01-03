//
// Created by Ron on 2019/10/7.
//

#ifndef D003_PACKAGE_EASY_GLPK_C10_EASY_GLPK_ILP_H
#define D003_PACKAGE_EASY_GLPK_C10_EASY_GLPK_ILP_H

#include <glpk.h>
#include <cstdlib>
#include <vector>
#include <map>

/* kind of structural variable: */
typedef enum glpk_optimization_type
{
    GLPK_OPTIMIZATION_MIN = GLP_MIN,
    GLPK_OPTIMIZATION_MAX = GLP_MAX
} GlpkOptimizationType;

/* type of auxiliary/structural variable: */
typedef enum glpk_comparison_type
{
    GLPK_COMPARISON_FREE = GLP_FR,
    GLPK_COMPARISON_LOWER_BOUNDARY = GLP_LO,
    GLPK_COMPARISON_UPPER_BOUNDARY = GLP_UP,
    GLPK_COMPARISON_DOUBLE_BOUNDARY = GLP_DB,
    GLPK_COMPARISION_FIXED = GLP_FX
} GlpkComparisonType;

class GlpkILPRow
{
public:
    GlpkILPRow(): m_i(-1), m_index(-1) {};
    virtual ~GlpkILPRow() = default;;
    int m_i;
    int m_index;
    std::vector<std::pair<int, double>> m_row;
    GlpkComparisonType m_comparison_type;
    double m_b1{};
    double m_b2{};
};

class GlpkILPOptimization
{
public:
    std::vector<std::pair<int, double>> m_factor;
    GlpkOptimizationType m_optimization_type;
};

class EasyGlpkILP
{
public:
    EasyGlpkILP();
    virtual ~EasyGlpkILP() = default;;
    void SetOptimization(std::vector<std::pair<int, double>> factors,
            GlpkOptimizationType opt_type);
    void AddRow(std::vector<std::pair<int, double>> a,
            GlpkComparisonType comparison_type, double b1, double b2);
    void Solve();
    int GetResults(int index) const ;
    double GetFinalZ() const ;
private:
    bool CheckInput();
    int m_n_col;
    int m_n_row;
    GlpkILPOptimization m_optimization;
    std::vector<GlpkILPRow> m_rows;
    std::vector<int> m_col_res;
    double m_z_final;
private: // consts
    static const int m_NAME_SIZE = 100;
};

#endif //D003_PACKAGE_EASY_GLPK_C10_EASY_GLPK_ILP_H
