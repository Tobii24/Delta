#include "../include/parser.h"

// Constructor & Destructor
Parser::Parser(std::string filename, std::vector<Token> tokens)
{
    this->filename = filename;
    this->tokens = tokens;
}

Parser::~Parser() {}

// Main
Node Parser::parse()
{
    // Define Variable
    if (peek().getData() == K_MUTABLE)
    {
        advance();

        if (peek().getData() == K_MUTABLE)
        {
        }
    }

    // Return
    return syntaxTree;
}

// Logs
void Parser::logError(ErrorType type, std::string msg)
{
    logs.push_back(Error(type, msg));
}

// Utils
void Parser::addStatement(Node statement)
{
    syntaxTree.addChild(statement);
}

void Parser::advance()
{
    current++;
}

Token Parser::peek() const
{
    return tokens[current];
}

Token Parser::peekNext() const
{
    return tokens[current + 1];
}

Token Parser::peekPrevious() const
{
    return tokens[current - 1];
}