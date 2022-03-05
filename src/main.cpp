#include <iostream>
#include <string>

#include "../include/token.h"
#include "../include/util.h"
int main(int arc, char *argv[])
{
    int *v;
    v = new int;
    *v = 10;

    Token testToken(TT_INT, -1, 1, 1, v);

    util::printToken(&testToken);

    return 0;
}