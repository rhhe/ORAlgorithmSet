//
// Created by Ron on 2019/12/1.
//

#ifndef D003_PACKAGE_EASY_GLPK_C20_FS_FF_SOLVER_H
#define D003_PACKAGE_EASY_GLPK_C20_FS_FF_SOLVER_H

#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

class c20_fs_ff_solver {
public:
    vector<unsigned int> m_fs_old_s_index;
    vector<vector<double>> m_fs_score;
    vector<vector<double>> m_ff_score;
    vector<unsigned int> m_solution;
    unsigned int n_f_changed_max;

    bool solve();

    c20_fs_ff_solver();

    virtual ~c20_fs_ff_solver() = default;

private:
    bool check_data();
    unsigned int get_n_f()const ;
    unsigned int get_n_s()const ;
    vector<pair<unsigned int, unsigned int>> m_useful_fs_pair;
};


#endif //D003_PACKAGE_EASY_GLPK_C20_FS_FF_SOLVER_H
