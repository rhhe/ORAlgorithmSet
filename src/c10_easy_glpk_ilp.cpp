//
// Created by Ron on 2019/10/7.
//

#include <utility>
#include <vector>
#include "c10_easy_glpk_ilp.h"
#include <string>
#include "../src_utils/ExceptionUtils.h"

using namespace std;

void EasyGlpkILP::SetOptimization(const std::vector<std::pair<int, double>> &factors,
                                  const string &opt) {
    try {
        m_opt.m_glp_opt = m_optimizationTypeMapper.at(opt);
    }
    catch (...) {
        throw ExceptionUtils("Error: EasyGlpkILP::SetOptimization(): bad inputs");
    }
    m_opt.m_factors = factors;
}

void EasyGlpkILP::AddRow(const std::vector<std::pair<int, double>> &row,
                         const string &comparison, double b1, double b2) {
    m_rows.emplace_back();
    auto &unit = m_rows.back();
    try {
        unit.m_glp_comparison = m_comparisonTypeMapper.at(comparison);
    }
    catch (...) {
        throw ExceptionUtils("Error: EasyGlpkILP::AddRow(): bad inputs");
    }
    unit.m_index = int(m_rows.size());
    unit.m_factors = row;
    unit.m_b1 = b1;
    unit.m_b2 = b2;
}

bool EasyGlpkILP::CheckInput() {
    m_n_row = int(m_rows.size());
    m_n_col = 0;

    for (const auto &glpk_row : m_rows) {
        for (std::pair<int, double> index_value : glpk_row.m_factors) {
            if (index_value.first <= 0) {
                throw ExceptionUtils("Error: EasyGlpkILP::CheckInput() glpk_row: index_value.first <= 0;");
            }
            if (index_value.first > m_n_col)
                m_n_col = index_value.first;
        }
    }
    for (std::pair<int, double> index_value : m_opt.m_factors) {
        if (index_value.first <= 0) {
            throw ExceptionUtils("Error: EasyGlpkILP::CheckInput() m_optimization: index_value.first <= 0;");
        }
        if (index_value.first > m_n_col)
            m_n_col = index_value.first;
    }
    return true;
}

void EasyGlpkILP::Solve() {
//     check inputs
    if (!CheckInput())
        return;

//     initialize
    glp_prob *lp;
    lp = glp_create_prob();
    glp_set_obj_dir(lp, m_opt.m_glp_opt);

//     auxiliary_variables_rows
    glp_add_rows(lp, m_n_row);
    char row_name[m_NAME_SIZE];
    for (const auto &row : m_rows) {
        sprintf(row_name, "r%d", row.m_index);
        glp_set_row_name(lp, row.m_index, row_name);
        glp_set_row_bnds(lp, row.m_index, row.m_glp_comparison, row.m_b1, row.m_b2);
    }

//     variables_columns
    glp_add_cols(lp, m_n_col);
    char col_name[m_NAME_SIZE];
    for (int i_col = 0, col_index; i_col < m_n_col; ++i_col) {
        col_index = i_col + 1;
        sprintf(col_name, "c%d", col_index);
        glp_set_col_name(lp, col_index, col_name);
        glp_set_col_bnds(lp, col_index, GLP_LO, 0.0, 0.0);
    }

//     to optimize
    for (auto index_value : m_opt.m_factors) {
        glp_set_obj_coef(lp, index_value.first, index_value.second);
    }

//     constrant_matrix
    std::vector<int> ia(1, 0);
    std::vector<int> ja(1, 0);
    std::vector<double> ar(1, 0.);
    for (const auto &row : m_rows) {
        for (const auto &index_value : row.m_factors) {
            ia.push_back(row.m_index);
            ja.push_back(index_value.first);
            ar.push_back(index_value.second);
        }
    }
    try {
        glp_load_matrix(lp, int(ia.size()) - 1, ia.data(), ja.data(), ar.data());
    } catch (...) {}

//    set_variables_to_integer
    for (int index_col = 1; index_col <= m_n_col; ++index_col) {
        glp_set_col_kind(lp, index_col, GLP_IV);
    }

//    calculate:
    glp_simplex(lp, nullptr);
    glp_intopt(lp, nullptr);

//    output
    m_z_final = glp_mip_obj_val(lp);
    m_col_res.resize(m_n_col + 1, -1);
    for (int index = 1; index <= m_n_col; ++index) {
        m_col_res.at(index) = glp_mip_col_val(lp, index);
    }

//    cleanup:
    glp_delete_prob(lp);
}

double EasyGlpkILP::GetFinalZ() const {
    return m_z_final;
}

const vector<int> &EasyGlpkILP::GetResults() const {
    return m_col_res;
}

