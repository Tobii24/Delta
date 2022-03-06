#include "../include/util.h"

namespace util
{
    void printToken(Token *token)
    {
        if (token == nullptr)
            return;

        std::cout << token->asString() << std::endl;
    }

    inline bool file_exists(const std::string &name)
    {
        std::ifstream f(name.c_str());
        return f.good();
    }

    std::string readFile(char *filename)
    {
        if (!file_exists(filename))
        {
            std::cout << "File '" << filename << "' not found\n";
            exit(EXIT_FAILURE);
        }

        std::ifstream ifs(filename);
        std::string content((std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()));

        return content;
    }
}