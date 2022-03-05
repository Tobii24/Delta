#ifndef UTIL_H

#define UTIL_H

#include <iostream>
#include "./token.h"

namespace util
{
    void printToken(Token *token);
    char *readFile(char *filename);
}

#endif // UTIL_H