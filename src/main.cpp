// General Includes
#include <iostream>
#include <string>
#include <chrono>

// Local Includes
#include "../include/token.h"
#include "../include/util.h"
#include "../include/lexer.h"
#include "../include/node.h"
#include "../include/parser.h"

int main(int argc, char *argv[])
{
    // Time Start
    auto start = std::chrono::high_resolution_clock::now();

    // Filter amount of args
    if (argc < 3)
    {
        std::cout << "Too few arguments!" << std::endl;
        return EXIT_FAILURE;
    }

    // Flags
    bool lexerDebug = false;
    bool parserDebug = false;
    bool compilerDebug = false;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            // Lexer Debug
            if (strcmp(argv[i], "-dl") == 0)
            {
                lexerDebug = true;
            }
            // Parser Debug
            else if (strcmp(argv[i], "-dp") == 0)
            {
                parserDebug = true;
            }
            // Compiler Debug
            else if (strcmp(argv[i], "-dc") == 0)
            {
                compilerDebug = true;
            }
            // Unknown Flag
            else
            {
                std::cout << "Unknown flag '" << argv[i] << "'" << std::endl;
                return EXIT_FAILURE;
            }
            argv[i] = argv[argc - 1];
        }
    }

    // Get some probable arguments
    std::string cmd = argv[1];
    char *filepath = argv[2];

    // Check for command
    if (cmd == "compile")
    {
        bool errored = false;

        // Get file content as string
        std::string source = util::readFile(filepath);

        // Get filename
        std::string filename = util::getFilename(filepath);

        // Check if it's empty
        if (source.empty())
        {
            std::cout << "File '" << filename << "' is empty!" << std::endl;
            return EXIT_FAILURE;
        }

        // Start compiling
        std::cout << "Compiling '" << filename << "'..." << std::endl;

        // Create lexer and get tokens
        Lexer lexer(std::string(filename), source);
        auto tokens = lexer.lex();

        // Error Check
        errored = lexer.chlogs();

        if (errored)
        {
            util::colorPrint("\nCompilation failed!\n\n", util::FAILURE);
            return EXIT_FAILURE;
        }

        // Print tokens
        if (lexerDebug)
        {
            std::cout << "\nTOKENS:" << std::endl;
            for (Token token : tokens)
                util::printToken(token);
        }

        // Create parser and get AST
        Parser parser(filename, tokens);

        Node ast = parser.parse();

        // Error Check
        errored = parser.chlogs();

        if (errored)
        {
            util::colorPrint("\nCompilation failed!\n\n", util::FAILURE);
            return EXIT_FAILURE;
        }

        // Print AST
        if (parserDebug)
            ast.print();

        // Success
        util::colorPrint("\nCompilation successful!\n\n", util::SUCCESS);
    }
    else if (cmd == "metf")
    {
        std::cout << "Not Implemented!" << std::endl;
    }
    else if (cmd == "help")
    {
        std::cout << "Usage: " << argv[0] << " <command> <file>"
                  << "\n";
        std::cout << "Commands:"
                  << "\n";
        std::cout << "\tcompile <file>\tCompiles to bytecode"
                  << "\n";
        std::cout << "\tmetf <file>\tMetaphrase compilation"
                  << "\n";
        std::cout << "\thelp\t\tShows this help" << std::endl;
    }
    else
    {
        std::cout << "Unknown command '" << cmd << "'!" << std::endl;
        return EXIT_FAILURE;
    }

    // Time End
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Log time
    std::cout << "Tempo: " << (double long)duration.count() / 1000000 << "s" << std::endl;

    // Successful Execution
    return EXIT_SUCCESS;
}