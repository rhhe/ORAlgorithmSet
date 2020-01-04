//
// Created by Ron on 2020/1/4.
//

#include "ExceptionUtils.h"

const char *ExceptionUtils::what() {
    return m_error.c_str();
}

void ExceptionUtils::setError(const std::string & errors) {
    m_error = errors;
}
ExceptionUtils ExceptionUtils::m_public;
ExceptionUtils &ExceptionUtils::Err(const std::string &errors) {
    m_public.setError(errors);
    return m_public;
}

ExceptionUtils::ExceptionUtils(const std::string &errors) {
    setError(errors);
}
