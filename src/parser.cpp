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
            addStatement(*statement);
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
    std::cout << "externalStatement" << std::endl;

    auto current_tok = peek();

    // Variable Definition
    if (current_tok->getType() == TT_KEYWORD && current_tok->getData() == K_FIXED || current_tok->getData() == K_MUTABLE)
    {
        bool isFixed = false;

        if (peek()->getData() == K_FIXED)
            isFixed = true;

        advance();

        // Variable Name
        if (peek()->getType() == TT_IDENTIFIER)
        {
            auto id = peek();
            advance();

            // Arrow '->'
            if (peek()->getType() == TT_OPERATOR && peek()->getData() == OP_ARROW)
            {
                advance();

                auto node = new Node(NT_VariableDefine);

                // Todef
                if (peek()->getType() == TT_KEYWORD && peek()->getData() == K_TODEF)
                {
                    advance();

                    node->setValue("id", &id);
                    node->setValue("isFixed", &isFixed);
                    node->setValue("isTodef", new bool(true));

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

                    node->setValue("id", &id);
                    node->setValue("isFixed", &isFixed);
                    node->setValue("isTodef", new bool(true));

                    node->addChild(expr);

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
    std::cout << "comparison expr" << std::endl;

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
    std::cout << "arith expr" << std::endl;

    return binaryOperation([this]()
                           { return this->term(); },
                           {{TT_OPERATOR, OP_PLUS},
                            {TT_OPERATOR, OP_MINUS}});
    ;
}

Node *Parser::term()
{
    std::cout << "term" << std::endl;

    return binaryOperation([this]()
                           { return this->atom(); },
                           {{TT_OPERATOR, OP_TIMES},
                            {TT_OPERATOR, OP_DIVIDE},
                            {TT_OPERATOR, OP_MODULO}});
}

Node *Parser::atom()
{
    std::cout << "atom" << std::endl;

    return binaryOperation([this]()
                           { return this->primary(); },
                           {{TT_OPERATOR, OP_EXPONENT}});
}

Node *Parser::primary()
{
    std::cout << "primary" << std::endl;

    // Int & Float
    if (peek()->getType() == TT_INT || peek()->getType() == TT_FLOAT)
    {
        auto num = new Node(peek()->getType() == TT_INT ? NT_Integer : NT_Float);

        void *value = (void *)peek()->getValue();

        num->setValue("value", value);

        advance();

        return num;
    }

    // Error
    else
    {
        this->log(ET_ERROR, "Expected literal", peek()->getLine(), peek()->getColumnStart());
        return nullptr;
    }
}

Node *Parser::binaryOperation(std::function<Node *()> func, Matrix ops)
{
    std::cout << "binary operation" << std::endl;

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