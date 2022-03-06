#ifndef UTIL_H

#define UTIL_H

#include <iostream>
#include <fstream>
#include "./token.h"

namespace util
{
    void printToken(Token *token);
    inline bool file_exists(const std::string &name);
    std::string readFile(char *filename);
}

#endif // UTIL_H