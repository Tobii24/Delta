#pragma once

#include <iostream>
#include <string.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#define RESET 7
#define RED 12
#define YELLOW 14
#define BLUE 9
#else
#define RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#endif

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

    ErrorType type;

    Error(enum ErrorType type, const std::string msg, const int line, const int column_start);

private:
    std::string title;
    std::string msg;
    int ln;
    int col_s;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    int color;
#else
    std::string color;
#endif
};
