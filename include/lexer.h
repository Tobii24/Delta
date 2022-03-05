#ifndef LEXER_H

#define LEXER_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "./token.h"

class Lexer
{
public:
    Lexer(std::string filename, std::string source);
    ~Lexer();
    Token **lex();

private:
    std::string filename;
    std::string source;

    std::string buff;
    int buffi;
    int index;
    int line;
    int column;

    Token **tokens;
};

#endif // LEXER_H