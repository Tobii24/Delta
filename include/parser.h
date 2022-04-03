#pragma once

#include <iostream>
#include <vector>

#include "./token.h"
#include "./node.h"
#include "./error.h"
#include "./util.h"

typedef std::vector<std::vector<unsigned int>> Matrix;

class Parser
{
public:
    Parser(std::string filename, std::vector<Token> tokens);
    ~Parser();

    Node parse();

    void chlogs() const;

private:
    std::string filename;
    std::vector<Token> tokens;
    std::vector<Error> logs;

    Node syntaxTree = Node(NT_Statements);

    int current = 0;

    Node statements();
    Node body();
    Node *binaryOperation(Node *(*func)(), Matrix ops);

    Node *externalStatement();
    Node *innerStatement();
    Node *comparisonExpr();
    Node *arithmeticExpr();
    Node *term();
    Node *factor();
    Node *atom();
    Node *primary();

    void log(ErrorType type, std::string msg, int ln, int col);

    inline void addStatement(Node statement)
    {
        syntaxTree.addChild(statement);
    }

    inline void advance() noexcept
    {
        current++;
    }

    inline Token *peek()
    {
        if (current >= tokens.size())
            return nullptr;

        return &tokens[current];
    };

    Token *peekNext();
    Token *peekPrevious();

    bool lookfor(unsigned int type, unsigned int data, Matrix matrix) const;
};