//
// Created by Ron on 2019/12/1.
//

#include <set>
#include "c20_fs_ff_solver.h"

bool c20_fs_ff_solver::solve() {
//    check inputs
    if (!check_data())
        return false;
//    initialize
    m_solution.clear();
    m_solution.resize(m_fs_score.size(), -1);
    unsigned int n_f = get_n_f();
    unsigned int n_s = get_n_s();
    if (n_f == 0 || n_s == 0)
        return true;
//    make x i_x-> (i_f, i_s)

    m_useful_fs_pair.clear();
    for (unsigned int i = 0; i < n_f; ++i) {
        for (unsigned int j = 0; j < n_s; ++j) {
            if(m_fs_score.at(i).at(j) < 0.0)
                continue;
            m_useful_fs_pair.emplace_back(i, j);
        }
    }

    return true;
}

bool c20_fs_ff_solver::check_data() {
    unsigned int n_f = m_fs_old_s_index.size();
    if (m_fs_score.size() != n_f) {
        return false;
    }
    if (m_ff_score.size() != n_f) {
        return false;
    }
    for (const auto &unit: m_ff_score) {
        if (unit.size() != n_f) {
            return false;
        }
    }
    set<unsigned int> s_lengths;
    for (const auto &unit: m_fs_score) {
        s_lengths.insert(unit.size());
    }
    return s_lengths.size() <= 1;
}

c20_fs_ff_solver::c20_fs_ff_solver() {
    m_fs_old_s_index.clear();
    m_fs_score.clear();
    m_ff_score.clear();
    m_solution.clear();
}

unsigned int c20_fs_ff_solver::get_n_f() const {
    return m_fs_score.size();
}

unsigned int c20_fs_ff_solver::get_n_s() const {
    if (m_fs_score.empty())
        return 0;
    return m_fs_score.front().size();
}
