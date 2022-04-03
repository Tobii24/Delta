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
            this->log(ET_ERROR, "Expected ';'", peek()->getLine(), peek()->getColumn());
            break;
        }
    }

    // Return
    return syntaxTree;
}

Node *Parser::externalStatement()
{
    auto current_tok = peek();

    // Variable Definition
    if (current_tok->getType() == TT_KEYWORD && current_tok->getData() == K_FIXED || current_tok->getData() == K_MUTABLE)
    {
        bool isFixed = false;
        bool isTodef = false;
        void *val = nullptr;

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

                // Todef
                if (peek()->getType() == TT_KEYWORD && peek()->getData() == K_TODEF)
                {
                    isTodef = true;
                    advance();
                }
                else
                {
                    auto expr = comparisonExpr();

                    if (expr == nullptr)
                        return nullptr;

                    val = expr;
                }

                auto node = new Node(NT_VariableDefine);
                node->setValue("id", id);
                node->setValue("isFixed", &isFixed);
                node->setValue("isTodef", &isTodef);
                node->setValue("value", val);

                return node;
            }
            else
            {
                this->log(ET_ERROR, "Expected '->'", peek()->getLine(), peek()->getColumn());
                return nullptr;
            }
        }
        else
        {
            this->log(ET_ERROR, "Expected identifier", peek()->getLine(), peek()->getColumn());
            return nullptr;
        }
    }

    // Error
    else
    {
        this->log(ET_ERROR, "Expected <type-def>, <variable-def> or <reference-def>", peek()->getLine(), peek()->getColumn());
        return nullptr;
    }
}

Node *Parser::innerStatement() { return nullptr; }

Node *Parser::comparisonExpr() { return nullptr; }

Node *Parser::arithmeticExpr() { return nullptr; }

Node *Parser::term() { return nullptr; }

Node *Parser::factor() { return nullptr; }

Node *Parser::atom() { return nullptr; }

Node *Parser::primary() { return nullptr; }

Node *Parser::binaryOperation(Node *(*func)(), Matrix ops)
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
        node->setValue("left", &left);
        node->setValue("op", &op);
        node->setValue("right", &right);
    }

    return node;
}

#pragma endregion

// Logs
void Parser::log(ErrorType type, std::string msg, int ln, int col)
{
    logs.push_back(Error(type, msg, ln, col));
}

void Parser::chlogs() const
{
    bool hasErrors = false;

    for (Error log : logs)
    {
        if (log.type == ET_ERROR)
            hasErrors = true;

        log._throw();
    }

    if (hasErrors)
        util::colorPrint("\nCompilation failed!\n\n", util::FAILURE);
    else
        util::colorPrint("\nCompilation successful!\n\n", util::SUCCESS);

    exit(hasErrors ? 1 : 0);
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