cmake_minimum_required(VERSION 3.15)
project(d003_package_easy_glpk)

set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(/usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)
LINK_LIBRARIES(-lglpk)

add_executable(d003_package_easy_glpk src/main.cpp src/c10_easy_glpk_ilp.h src/c10_easy_glpk_ilp.cpp src/b99_test.h src/b99_test.cpp src/c20_fs_ff_solver.cpp src/c20_fs_ff_solver.h)



