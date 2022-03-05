#ifndef TOKEN_H

#define TOKEN_H

enum TokenType : unsigned int
{
    // Literals
    TT_INT,
    TT_FLOAT,
    TT_STRING,
    TT_CHAR,
    TT_BOOL,
    TT_BINARY,
    TT_FILE,

    // Operators
    TT_PLUS,
    TT_MINUS,
    TT_TIMES,
    TT_DIVIDE,
    TT_MODULO,
    TT_EXPONENT,

    // Comparison
    TT_EQ,
    TT_NEQ,
    TT_LT,
    TT_LTE,
    TT_GT,
    TT_GTE,

    TT_AND,
    TT_OR,
    TT_NOT,

    // Misc
    TT_IDENTIFIER,
    TT_KEYWORD,
    TT_UNKOWN,
    TT_EOF
};

enum KeywordType : unsigned int
{
    // Operators
    TT_XOR,
    TT_BAND,
    TT_BOR,
    TT_LSHIFT,
    TT_RSHIFT,
    TT_BNOT,

    // Instructions
    TT_ADD,
    TT_SUB,
    TT_MUL,
    TT_DIV,
    TT_MOD,
    TT_POW,

    TT_TBOOL,
    TT_TNOT,

    TT_SET,
    TT_GET,
    TT_DEL,

    // Special Keywords
    TT_TODEF,
    TT_UNDEF,
    TT_NULL,
    TT_RTERR,
    TT_INDEX,
    TT_KEY,
    TT_VALUE,

    // Input & Output
    TT_IN,
    TT_OUT,

    // File Manipulation
    TT_OPENF,
    TT_READF,
    TT_WRITEF,
    TT_READBF,
    TT_WRITEBF
};

class Token
{
public:
    Token(TokenType type, int data, int line, int column, const void *value);
    ~Token();
    TokenType getType() const;
    int getData() const;
    int getLine() const;
    int getColumn() const;
    const void *getValue() const;

private:
    TokenType type;
    int data;
    int line;
    int column;
    const void *value;
};

#endif // TOKEN_H