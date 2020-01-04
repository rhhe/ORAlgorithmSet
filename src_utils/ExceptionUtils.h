//
// Created by Ron on 2020/1/4.
//
#ifndef D003_PACKAGE_EASY_GLPK_EXCEPTIONUTILS_H
#define D003_PACKAGE_EASY_GLPK_EXCEPTIONUTILS_H

#include <exception>
#include <string>

class ExceptionUtils : public std::exception {
public:
    ExceptionUtils() = default;
    ExceptionUtils(const std::string & errors);
    ~ExceptionUtils() override = default;
    std::string m_error = "Error: General error;";
    void setError(const std::string & errors);
    virtual const char *what();
    static ExceptionUtils m_public;
    ExceptionUtils & Err(const std::string & errors);
};


#endif //D003_PACKAGE_EASY_GLPK_EXCEPTIONUTILS_H
