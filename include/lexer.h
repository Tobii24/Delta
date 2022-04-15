#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <regex>

#include "./token.h"
#include "./util.h"
#include "./error.h"

class Lexer
{
public:
    Lexer(std::string filename, std::string source);
    ~Lexer();

    std::vector<Token> lex();

    bool chlogs() const;

private:
    std::string filename;
    std::string source;

    int line;
    int column_s;
    int column_e;

    std::vector<Token> tokens;
    std::vector<Error> logs;

    std::string removeTabs(const std::string &str) const;

    std::vector<std::string>
    splitLines(const std::string &str) const;
    std::vector<std::string> splitWords(const std::string &str) const;

    Token *getToken(std::string buffer, int ln, int col_s, int col_e) const;
    void addToken(Token *token);
    void log(ErrorType type, std::string msg, int ln, int col_s);
};