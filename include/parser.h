#pragma once

#include <iostream>
#include <vector>

#include "./token.h"
#include "./node.h"
#include "./error.h"

class Parser
{
public:
    Parser(std::string filename, std::vector<Token> tokens);
    ~Parser();

    Node parse();

    void logError(ErrorType type, std::string msg);

    void addStatement(Node statement);

    void advance();
    Token peek() const;
    Token peekNext() const;
    Token peekPrevious() const;

private:
    std::string filename;

    std::vector<Token> tokens;

    Node syntaxTree = Node(NT_Statements);

    std::vector<Error> logs;

    int current = 0;
};