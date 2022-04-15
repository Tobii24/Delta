#pragma once

#include <iostream>
#include <fstream>

#include "./token.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#define _RESET 7
#define _RED 12
#define _GREEN 2
#else
#define _RESET "\033[0m"
#define _RED "\033[31m"
#define _GREEN "\033[32m"
#endif
namespace util
{
    typedef unsigned long long ull;
    typedef long double ld;

    enum ReturnCode
    {
        SUCCESS,
        FAILURE
    };

    inline void printToken(const Token &token)
    {
        std::cout << token.asString() << std::endl;
    }

    inline bool file_exists(const std::string &name)
    {
        std::ifstream f(name.c_str());
        return f.good();
    }

    inline std::string readFile(const char *filename)
    {
        if (!file_exists(filename))
        {
            std::cout << "File '" << filename << "' not found\n";
            exit(EXIT_FAILURE);
        }

        std::ifstream ifs(filename);
        std::string content((std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()));

        return content;
    }

    inline std::string getFilename(const char *filename)
    {
        std::string file(filename);
        std::string::size_type pos = file.find_last_of("/\\");
        return file.substr(pos + 1);
    }

    inline void colorPrint(const std::string &message, const enum ReturnCode code)
    {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        if (code == SUCCESS)
            SetConsoleTextAttribute(hConsole, _GREEN);
        else
            SetConsoleTextAttribute(hConsole, _RED);

        std::cout << message;

        SetConsoleTextAttribute(hConsole, _RESET);
#else
        if (code == SUCCESS)
            std::cout << _GREEN << message << _RESET << std::endl;
        else
            std::cout << _RED << message << _RESET << std::endl;
#endif
    }
}