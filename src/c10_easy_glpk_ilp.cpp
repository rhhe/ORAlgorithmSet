//
// Created by Ron on 2019/10/7.
//

#include <vector>
#include <cstdlib>
#include <iostream>
#include "c10_easy_glpk_ilp.h"

void EasyGlpkILP::SetOptimization(std::vector<std::pair<int, double>> factors,
                                  GlpkOptimizationType opt_type) {
    m_optimization.m_optimization_type = opt_type;
    m_optimization.m_factor = std::move(factors);
}

void EasyGlpkILP::AddRow(std::vector<std::pair<int, double>> row,
                         GlpkComparisonType comparison_type, double b1, double b2) {
    m_rows.emplace_back();
    m_rows.back().m_i = int(m_rows.size() - 1);
    m_rows.back().m_index = int(m_rows.size());
    m_rows.back().m_row = std::move(row);
    m_rows.back().m_comparison_type = comparison_type;
    m_rows.back().m_b1 = b1;
    m_rows.back().m_b2 = b2;
}

bool EasyGlpkILP::CheckInput() {
    m_n_row = int(m_rows.size());
    m_n_col = 0;
    for (const GlpkILPRow &glpk_row : m_rows) {
        for (std::pair<int, double> index_value : glpk_row.m_row) {
            if (index_value.first <= 0)
                return false;
            if (index_value.first > m_n_col)
                m_n_col = index_value.first;
        }
    }
    for (std::pair<int, double> index_value : m_optimization.m_factor) {
        if (index_value.first <= 0)
            return false;
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
    glp_set_obj_dir(lp, m_optimization.m_optimization_type);

//     auxiliary_variables_rows
    glp_add_rows(lp, m_n_row);
    char row_name[m_NAME_SIZE];
    for (const auto &row : m_rows) {
        sprintf(row_name, "r%d", row.m_index);
        glp_set_row_name(lp, row.m_index, row_name);
        glp_set_row_bnds(lp, row.m_index, row.m_comparison_type, row.m_b1, row.m_b2);
    }

//     variables_columns
    glp_add_cols(lp, m_n_col);
    char col_name[m_NAME_SIZE];
    for (int i_col = 0, col_index; i_col < m_n_col; ++i_col) {
        col_index = i_col + 1;
        sprintf(col_name, "c%d", col_index);
        glp_set_col_name(lp, col_index, col_name);
        glp_set_col_bnds(lp, col_index, GLPK_COMPARISON_LOWER_BOUNDARY, 0.0, 0.0);
    }

//     to optimize
    for (auto index_value : m_optimization.m_factor) {
        glp_set_obj_coef(lp, index_value.first, index_value.second);
    }

//     constrant_matrix
    std::vector<int> ia(1, 0);
    std::vector<int> ja(1, 0);
    std::vector<double> ar(1, 0.);
    for (const auto &row : m_rows) {
        for (const auto &index_value : row.m_row) {
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

int EasyGlpkILP::GetResults(int index) const {
    int res = -1;
    try {
        res = m_col_res.at(index);
    }
    catch (...) {
        res = -1;
    }
    return res;
}

EasyGlpkILP::EasyGlpkILP() {
    m_n_row = 0;
    m_n_col = 0;
    m_rows.clear();
    m_z_final = -9999;
    m_col_res.clear();
}

double EasyGlpkILP::GetFinalZ() const {
    return m_z_final;
}


