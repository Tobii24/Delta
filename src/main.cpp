#include <iostream>
#include <string>

#include "../include/token.h"
#include "../include/util.h"
#include "../include/lexer.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Too few arguments!" << std::endl;
        return EXIT_FAILURE;
    }

    std::string cmd = argv[1];
    char *file = argv[2];

    if (cmd == "compile")
    {
        std::string source = util::readFile(file);

        if (source.empty())
        {
            std::cout << "Empty file!" << std::endl;
            return EXIT_FAILURE;
        }

        std::cout << "Compiling '" << file << "'..." << std::endl;

        Lexer lexer(std::string(file), source);
        Token **tokens = lexer.lex();
    }

    return EXIT_SUCCESS;
}