#include "../include/token.h"

Token::Token(TokenType type, int data, int line, int column_s, int column_e, const void *value, std::string repr)
{
    this->type = type;
    this->data = data;
    this->line = line;
    this->column_start = column_s;
    this->column_end = column_e;
    this->value = value;
    this->repr = repr;
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

int Token::getColumnStart() const
{
    return this->column_start;
}

int Token::getColumnEnd() const
{
    return this->column_end;
}

const void *Token::getValue() const
{
    return this->value;
}

std::string Token::getRepr() const
{
    return this->repr;
}

std::string Token::typeAsString() const
{
    static std::map<TokenType, std::string> strings;
    if (strings.size() == 0)
    {
#define INSERT_ELEMENT(p, nm) strings[p] = nm
        INSERT_ELEMENT(TT_INT, "INT");
        INSERT_ELEMENT(TT_FLOAT, "FLOAT");
        INSERT_ELEMENT(TT_STRING, "STRING");
        INSERT_ELEMENT(TT_CHAR, "CHAR");
        INSERT_ELEMENT(TT_BOOL, "BOOL");
        INSERT_ELEMENT(TT_IDENTIFIER, "IDENTIFIER");
        INSERT_ELEMENT(TT_KEYWORD, "KEYWORD");
        INSERT_ELEMENT(TT_OPERATOR, "OPERATOR");
        INSERT_ELEMENT(TT_SEMICOLON, "SEMICOLON");
        INSERT_ELEMENT(TT_EOF, "EOF");
#undef INSERT_ELEMENT
    }

    return strings[this->type];
}

std::string Token::dataAsString() const
{
    static std::map<KeywordType, std::string> keyword_s;
    if (keyword_s.size() == 0)
    {
#define INSERT_ELEMENT(p) keyword_s[p] = #p
        // Operators
        INSERT_ELEMENT(K_XOR);
        INSERT_ELEMENT(K_BAND);
        INSERT_ELEMENT(K_BOR);
        INSERT_ELEMENT(K_LSHIFT);
        INSERT_ELEMENT(K_RSHIFT);
        INSERT_ELEMENT(K_BNOT);

        // Instructions
        INSERT_ELEMENT(K_ADD);
        INSERT_ELEMENT(K_SUB);
        INSERT_ELEMENT(K_MUL);
        INSERT_ELEMENT(K_DIV);
        INSERT_ELEMENT(K_MOD);
        INSERT_ELEMENT(K_POW);

        INSERT_ELEMENT(K_TBOOL);
        INSERT_ELEMENT(K_TNOT);

        INSERT_ELEMENT(K_SET);
        INSERT_ELEMENT(K_GET);
        INSERT_ELEMENT(K_DEL);

        // Variable
        INSERT_ELEMENT(K_MUTABLE);
        INSERT_ELEMENT(K_FIXED);

        // Special Keywords
        INSERT_ELEMENT(K_TODEF);
        INSERT_ELEMENT(K_UNDEF);
        INSERT_ELEMENT(K_NULL);
        INSERT_ELEMENT(K_RTERR);
        INSERT_ELEMENT(K_VOID);

        INSERT_ELEMENT(K_TYPE);

        INSERT_ELEMENT(K_BREAK);
        INSERT_ELEMENT(K_CONTINUE);
        INSERT_ELEMENT(K_RETURN);

        INSERT_ELEMENT(K_RTV);

        // Reference Special
        INSERT_ELEMENT(K_REF);

        INSERT_ELEMENT(K_WHILE);
        INSERT_ELEMENT(K_DO);
        INSERT_ELEMENT(K_FOR);
        INSERT_ELEMENT(K_ITERATE);

        INSERT_ELEMENT(K_IF);
        INSERT_ELEMENT(K_ELSEIF);
        INSERT_ELEMENT(K_ELSE);

        INSERT_ELEMENT(K_CALL);

        // Input & Output
        INSERT_ELEMENT(K_IN);
        INSERT_ELEMENT(K_OUT);

        // File Manipulation
        INSERT_ELEMENT(K_OPENF);
        INSERT_ELEMENT(K_READF);
        INSERT_ELEMENT(K_WRITEF);
        INSERT_ELEMENT(K_READBF);
        INSERT_ELEMENT(K_WRITEBF);
        INSERT_ELEMENT(K_CLOSEF);

#undef INSERT_ELEMENT
    }

    static std::map<OperatorType, std::string> operator_s;
    if (operator_s.size() == 0)
    {
#define INSERT_ELEMENT(p) operator_s[p] = #p
        // Operators
        INSERT_ELEMENT(OP_PLUS);
        INSERT_ELEMENT(OP_MINUS);
        INSERT_ELEMENT(OP_TIMES);
        INSERT_ELEMENT(OP_DIVIDE);
        INSERT_ELEMENT(OP_MODULO);
        INSERT_ELEMENT(OP_EXPONENT);

        INSERT_ELEMENT(OP_ASSIGN);
        INSERT_ELEMENT(OP_ARROW);

        INSERT_ELEMENT(OP_LEFT_BRACE);
        INSERT_ELEMENT(OP_RIGHT_BRACE);
        INSERT_ELEMENT(OP_LEFT_BRACKET);
        INSERT_ELEMENT(OP_RIGHT_BRACKET);

        // Comparison
        INSERT_ELEMENT(OP_EQ);
        INSERT_ELEMENT(OP_NEQ);
        INSERT_ELEMENT(OP_LT);
        INSERT_ELEMENT(OP_LTE);
        INSERT_ELEMENT(OP_GT);
        INSERT_ELEMENT(OP_GTE);

        INSERT_ELEMENT(OP_AND);
        INSERT_ELEMENT(OP_OR);
        INSERT_ELEMENT(OP_NOT);
#undef INSERT_ELEMENT
    }

    if (this->type == TT_KEYWORD)
        return keyword_s[(KeywordType)this->data];
    else if (this->type == TT_OPERATOR)
        return operator_s[(OperatorType)this->data];

    return "";
}

std::string Token::asString() const
{
    auto builder = "Token[" + this->typeAsString();

    if (data > 0)
        builder += ": " + this->dataAsString();

    builder += "]";

    if (value != nullptr)
        builder += " => '" + this->getRepr() + "'";

    return builder;
}