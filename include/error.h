#pragma once

#include <iostream>
#include <string.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#endif

#define RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

enum ErrorType
{
    ET_INFO,
    ET_ERROR,
    ET_WARNING
};

struct Error
{
public:
    void _throw() const;

    Error(ErrorType type, const std::string msg);

private:
    ErrorType type;

    std::string title;
    std::string msg;
    std::string color;
};
