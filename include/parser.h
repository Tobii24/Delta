#pragma once

#include <iostream>
#include <vector>

#include "./token.h"
#include "./node.h"
#include "./error.h"

typedef std::vector<std::vector<unsigned int>> Matrix;

class Parser
{
public:
    Parser(std::string filename, std::vector<Token> tokens);
    ~Parser();

    Node parse();

    Node statements();
    Node body();
    Node binaryOperation(Node (*func)(), Matrix ops);

    Node externalStatement();
    Node innerStatement();
    Node comparisonStatement();
    Node arithmeticStatement();
    Node term();
    Node factor();
    Node atom();
    Node primary();

    void log(ErrorType type, std::string msg);

    void addStatement(Node statement);

private:
    std::string filename;
    std::vector<Token> tokens;
    std::vector<Error> logs;

    Node syntaxTree = Node(NT_Statements);

    int current = 0;

    void advance();

    Token peek() const;
    Token peekNext() const;
    Token peekPrevious() const;

    bool lookfor(unsigned int type, unsigned int data, Matrix matrix) const;
};