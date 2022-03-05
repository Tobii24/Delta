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
            printf(" => %p\n", token->getValue());
    }

    char *readFile(char *filename)
    {
        FILE *file = fopen(filename, "r");
        if (file == nullptr)
        {
            std::cout << "File not found!" << std::endl;
            return nullptr;
        }

        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);

        char *buffer = new char[size + 1];
        fread(buffer, 1, size, file);
        buffer[size] = '\0';

        fclose(file);

        return buffer;
    }
}