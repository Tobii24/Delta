#include "../include/token.h"

Token::Token(TokenType type, int data, int line, int column, const void *value)
{
    this->type = type;
    this->data = data;
    this->line = line;
    this->column = column;
    this->value = value;
}

Token::~Token() {}

TokenType Token::getType() const
{
    return this->type;
}

int Token::getData() const
{
    return this->data;
}

int Token::getLine() const
{
    return this->line;
}

int Token::getColumn() const
{
    return this->column;
}

const void *Token::getValue() const
{
    return this->value;
}
