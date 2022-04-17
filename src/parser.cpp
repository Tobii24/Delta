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
    return this->statements();
}

Node Parser::statements()
{
    while (peek() != nullptr && peek()->getType() != TT_EOF)
    {
        Node *statement = this->externalStatement();

        if (statement != nullptr)
            addStatement(statement);
        else
            break;

        if (peek()->getType() == TT_SEMICOLON)
            this->advance();
        else
        {
            this->log(ET_ERROR, "Expected ';'", peekPrevious()->getLine(), peekPrevious()->getColumnEnd());
            break;
        }
    }

    // Return
    return syntaxTree;
}

Node *Parser::externalStatement()
{
    // Variable Definition
    if (matchToken(TT_KEYWORD, K_FIXED) || matchToken(TT_KEYWORD, K_MUTABLE))
    {
        bool isFixed = false;

        if (matchToken(TT_KEYWORD, K_FIXED))
            isFixed = true;

        advance();

        // Variable Name
        if (matchToken(TT_IDENTIFIER))
        {
            auto id = peek();
            advance();

            // Arrow '->'
            if (matchToken(TT_OPERATOR, OP_ARROW))
            {
                advance();

                auto node = new Node(NT_VariableDefine);

                // Todef
                if (matchToken(TT_KEYWORD, K_TODEF))
                {
                    int line_e = peek()->getLine();
                    int column_e = peek()->getColumnEnd();
                    advance();

                    node->setValue("id", id);
                    node->setValue("isFixed", new bool(isFixed));
                    node->setValue("isTodef", new bool(true));

                    node->setLineStart(id->getLine());
                    node->setLineEnd(line_e);

                    node->setColumnStart(id->getColumnStart());
                    node->setColumnEnd(column_e);

                    return node;
                }
                else
                {
                    Node *expr = comparisonExpr();

                    if (expr == nullptr)
                    {
                        this->log(ET_ERROR, "Expected expression", peek()->getLine(), peek()->getColumnStart());
                        return nullptr;
                    }

                    node->setValue("id", id);
                    node->setValue("isFixed", new bool(isFixed));
                    node->setValue("isTodef", new bool(false));

                    node->addChild(expr);

                    node->setLineStart(id->getLine());
                    node->setLineEnd(expr->getLineEnd());

                    node->setColumnStart(id->getColumnStart());
                    node->setColumnEnd(expr->getColumnEnd());

                    return node;
                }
            }
            else
            {
                this->log(ET_ERROR, "Expected '->'", peek()->getLine(), peek()->getColumnStart());
                return nullptr;
            }
        }
        else
        {
            this->log(ET_ERROR, "Expected identifier", peek()->getLine(), peek()->getColumnStart());
            return nullptr;
        }
    }

    // Error
    else
    {
        // this->log(ET_ERROR, "Expected <type-def>, <variable-def> or <reference-def>", peek()->getLine(), peek()->getColumnStart());
        return nullptr;
    }
}

Node *Parser::innerStatement() { return nullptr; }

Node *Parser::comparisonExpr()
{
    return binaryOperation([this]()
                           { return this->arithmeticExpr(); },
                           {{TT_OPERATOR, OP_EQ},
                            {TT_OPERATOR, OP_NEQ},
                            {TT_OPERATOR, OP_LT},
                            {TT_OPERATOR, OP_LTE},
                            {TT_OPERATOR, OP_GT},
                            {TT_OPERATOR, OP_GTE}});
}

Node *Parser::arithmeticExpr()
{
    return binaryOperation([this]()
                           { return this->term(); },
                           {{TT_OPERATOR, OP_PLUS},
                            {TT_OPERATOR, OP_MINUS}});
    ;
}

Node *Parser::term()
{
    return binaryOperation([this]()
                           { return this->atom(); },
                           {{TT_OPERATOR, OP_TIMES},
                            {TT_OPERATOR, OP_DIVIDE},
                            {TT_OPERATOR, OP_MODULO}});
}

Node *Parser::atom()
{
    return binaryOperation([this]()
                           { return this->primary(); },
                           {{TT_OPERATOR, OP_EXPONENT}});
}

Node *Parser::primary()
{
    // Int & Float
    if (matchToken(TT_INT) || matchToken(TT_FLOAT))
    {
        auto num = new Node(peek()->getType() == TT_INT ? NT_Integer : NT_Float);

        num->setValue("value", (void *)peek()->getValue());

        advance();

        return num;
    }

    // Identifier
    else if (matchToken(TT_IDENTIFIER))
    {
        auto id = new Node(NT_VariableAccess);

        id->setValue("id", (void *)peek()->getValue());

        advance();

        return id;
    }

    // Error
    else
    {
        std::cout << "Primary Error" << std::endl;

        this->log(ET_ERROR, "Expected literal not <" + peek()->typeAsString() + ">", peek()->getLine(), peek()->getColumnStart());
        return nullptr;
    }
}

Node *Parser::binaryOperation(std::function<Node *()> func, Matrix ops)
{
    Node *left = func();

    if (left == nullptr)
        return nullptr;

    Node *node = left;

    while (lookfor(peek()->getType(), peek()->getData(), ops))
    {
        auto op = peek();

        advance();

        auto right = func();

        if (right == nullptr)
            return nullptr;

        node = new Node(NT_BinaryOperation);
        node->addChild(left);
        node->setValue("op", op);
        node->addChild(right);

        node->setColumnStart(left->getColumnStart());
        node->setColumnEnd(right->getColumnEnd());

        node->setLineStart(left->getLineStart());
        node->setLineEnd(right->getLineEnd());
    }

    return node;
}

#pragma endregion

// Logs
void Parser::log(ErrorType type, std::string msg, int ln, int col_s)
{
    logs.push_back(Error(type, msg, ln, col_s));
}

bool Parser::chlogs() const
{
    bool hasErrors = false;

    for (Error log : logs)
    {
        if (log.type == ET_ERROR)
            hasErrors = true;

        log._throw();
    }

    return hasErrors;
}

// Utils
Token *Parser::peekNext()
{
    if (current + 1 >= tokens.size())
        return nullptr;

    return &tokens[current + 1];
}

Token *Parser::peekPrevious()
{
    if (current - 1 >= tokens.size() || current - 1 < 0)
        return nullptr;

    return &tokens[current - 1];
}

bool Parser::lookfor(unsigned int type, unsigned int data, Matrix matrix) const
{
    for (auto i = 0; i < matrix.size(); i++)
    {
        if (matrix[i].size() == 2)
        {
            if (matrix[i][0] == type && matrix[i][1] == data)
                return true;
        }
        else
        {
            if (matrix[i][0] == type)
                return true;
            else
                continue;
        }
    }

    return false;
}