#pragma once

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
    TT_SEMICOLON,
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
    K_VOID,

    K_TYPE,

    K_BREAK,
    K_CONTINUE,
    K_RETURN,

    K_RTV,

    // Reference Special
    K_REF,

    K_WHILE,
    K_DO,
    K_FOR,
    K_ITERATE,

    K_IF,
    K_ELSEIF,
    K_ELSE,

    K_CALL,

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
    Token(enum TokenType type, int data, int line, int column_s, int column_e, const void *value = nullptr, std::string repr = "");
    ~Token();

    enum TokenType getType() const;

    int getData() const;
    int getLine() const;
    int getColumnStart() const;
    int getColumnEnd() const;

    const void *getValue() const;

    std::string getRepr() const;

    std::string asString() const;

    std::string typeAsString() const;
    std::string dataAsString() const;

private:
    enum TokenType type;

    int data;
    int line;
    int column_start;
    int column_end;

    const void *value;

    std::string repr;
};