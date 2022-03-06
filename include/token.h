#ifndef TOKEN_H

#define TOKEN_H

#include <iostream>
#include <map>
#include <string>

enum TokenType : unsigned int
{
    // Literals
    TT_INT = 1,
    TT_FLOAT,
    TT_STRING,
    TT_CHAR,
    TT_BOOL,

    // Misc
    TT_IDENTIFIER,
    TT_KEYWORD,
    TT_OPERATOR,
    TT_EOF
};

enum OperatorType : unsigned int
{
    // Operators
    OP_PLUS = 1,
    OP_MINUS,
    OP_TIMES,
    OP_DIVIDE,
    OP_MODULO,
    OP_EXPONENT,

    OP_ASSIGN,
    OP_ARROW,

    OP_LEFT_PARENTHESIS,
    OP_RIGHT_PARENTHESIS,
    OP_LEFT_BRACE,
    OP_RIGHT_BRACE,
    OP_LEFT_BRACKET,
    OP_RIGHT_BRACKET,

    // Comparison
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_LTE,
    OP_GT,
    OP_GTE,

    OP_AND,
    OP_OR,
    OP_NOT
};

enum KeywordType : unsigned int
{
    // Operators
    K_XOR = 1,
    K_BAND,
    K_BOR,
    K_LSHIFT,
    K_RSHIFT,
    K_BNOT,

    // Instructions
    K_ADD,
    K_SUB,
    K_MUL,
    K_DIV,
    K_MOD,
    K_POW,

    K_TBOOL,
    K_TNOT,

    K_SET,
    K_GET,
    K_DEL,

    // Variable
    K_MUTABLE,
    K_FIXED,

    // Special Keywords
    K_TODEF,
    K_UNDEF,
    K_NULL,
    K_RTERR,
    K_INDEX,
    K_KEY,
    K_VALUE,

    // Input & Output
    K_IN,
    K_OUT,

    // File Manipulation
    K_OPENF,
    K_READF,
    K_WRITEF,
    K_READBF,
    K_WRITEBF,
    K_CLOSEF,
};

class Token
{
public:
    Token(TokenType type, int data, int line, int column, const void *value = nullptr, std::string repr = "");
    ~Token();

    TokenType getType() const;

    int getData() const;
    int getLine() const;
    int getColumn() const;

    const void *getValue() const;

    std::string getRepr() const;

    std::string asString() const;

private:
    TokenType type;

    int data;
    int line;
    int column;

    const void *value;

    std::string repr;

    std::string typeAsString() const;
    std::string dataAsString() const;
};

#endif // TOKEN_H