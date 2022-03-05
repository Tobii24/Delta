#include "../include/util.h"

namespace util
{
    void printToken(Token *token)
    {
        if (token == nullptr)
            return;

        if (token->getData() < 0)
            std::cout << "Token[" << token->getType() << "]";
        else
            std::cout << "Token[" << token->getType() << ": " << token->getData() << "]";

        if (token->getValue() == nullptr)
            std::cout << "\n";
        else
            printf(" => %p\n", *(token->getValue()));
    }
}