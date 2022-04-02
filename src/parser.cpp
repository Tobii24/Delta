#include "../include/parser.h"

// Constructor & Destructor
Parser::Parser(std::string filename, std::vector<Token> tokens)
{
    this->filename = filename;
    this->tokens = tokens;
}

Parser::~Parser() {}

#pragma region Main
Node Parser::parse()
{
    // Return
    return syntaxTree;
}

Node Parser::statements()
{
    // Return
    return syntaxTree;
}

Node Parser::binaryOperation(Node (*func)(), Matrix ops)
{
    Node left = func();
    Node node = left;

    while (lookfor(peek().getType(), peek().getData(), ops))
    {
        auto op = peek();
        advance();

        auto right = func();

        node = Node(NT_BinaryOperation);
        left.setValue("left", &left);
        left.setValue("op", &op);
        left.setValue("right", &right);
    }

    return node;
}

#pragma endregion

// Logs
void Parser::log(ErrorType type, std::string msg)
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

bool Parser::lookfor(unsigned int type, unsigned int data, Matrix matrix) const
{
    for (auto i = 0; i < matrix.size(); i++)
    {
        if (matrix[i][2] == NULL)
            if (matrix[i][1] == type)
                return true;
            else
                continue;

        if (matrix[i][1] == type && matrix[i][2] == data)
            return true;
    }

    return false;
}