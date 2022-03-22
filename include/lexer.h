#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <regex>
#include "./token.h"

class Lexer
{
public:
    Lexer(std::string filename, std::string source);
    ~Lexer();
    std::vector<Token> lex();

private:
    std::string filename;
    std::string source;

    std::string buff;
    int buffi;
    int index;
    int line;
    int column;

    std::vector<Token> tokens;

    Token *getToken(std::string buffer, int ln, int col) const;
};