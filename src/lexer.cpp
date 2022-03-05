#include "../include/lexer.h"

Lexer::Lexer(std::string filename, std::string source)
{
    this->filename = filename;
    this->source = source;

    this->buffi = 0;
    this->index = 0;
    this->column = 1;
    this->line = 1;

    this->tokens = new Token *[source.length()];
}

Lexer::~Lexer()
{
    delete[] this->tokens;
}

Token **Lexer::lex()
{
    while (1)
    {
        buff = "";

        // Loop until we find some delimiter
        while (source[index] != ' ' && source[index] != '\n' && source[index] != '\0' && source[index] != '\t')
        {
            buff += source[index++];
        }

        // Empty
        if ((int)buff[0] == 0)
        {
            buffi = 0;
            index++;
            column++;

            // New line
            if (source[index] == '\n')
            {
                line++;
                column = 1;
            }

            // End of file
            else if (source[index] == '\0')
            {
                break;
            }

            continue;
        }

        std::cout << "Found: '" << buff << "'" << std::endl;

        // New line
        if (source[index] == '\n')
        {
            line++;
            column = 1;
        }

        // End of file
        else if (source[index] == '\0')
        {
            break;
        }

        buffi = 0;
        index++;
        column++;
    }

    return this->tokens;
}