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

    // Get some probable arguments
    std::string cmd = argv[1];
    char *file = argv[2];

    // Check for command
    if (cmd == "compile")
    {
        // Get file content as string
        std::string source = util::readFile(file);

        // Get filename
        std::string filename = util::getFilename(file);

        // Check if it's empty
        if (source.empty())
        {
            std::cout << "File '" << file << "' is empty!" << std::endl;
            return EXIT_FAILURE;
        }

        // Start compiling
        std::cout << "Compiling '" << filename << "'..." << std::endl;

        // Create lexer and get tokens
        Lexer lexer(std::string(file), source);
        auto tokens = lexer.lex();

        // Print tokens
        // for (auto token : tokens)
        //     util::printToken(&token);

        // Create parser and get AST
        Parser parser(filename, tokens);

        Node ast = parser.parse();

        bool errored = parser.chlogs();

        if (errored)
        {
            util::colorPrint("\nCompilation failed!\n\n", util::FAILURE);
            return EXIT_FAILURE;
        }
        else
            util::colorPrint("\nCompilation successful!\n\n", util::SUCCESS);

        // Print AST
        ast.print();
    }
    else if (cmd == "metf")
    {
    }
    else if (cmd == "help")
    {
        std::cout << "Usage: " << argv[0] << " <command> <file>"
                  << "\n";
        std::cout << "Commands:"
                  << "\n";
        std::cout << "  compile <file>\tCompiles the file"
                  << "\n";
        std::cout << "  metf <file>\tMetaphrase compilation the file"
                  << "\n";
        std::cout << "  help\t\tShows this help" << std::endl;
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