#include "../include/lexer.h"

// Constructor & Destructor
Lexer::Lexer(std::string filename, std::string source)
{
    this->filename = filename;
    this->source = source;

    this->buffi = 0;
    this->index = 0;
    this->column = 1;
    this->line = 1;
}

Lexer::~Lexer() {}

// Public Methods
Token *Lexer::getToken(std::string buffer, int ln, int col) const
{
    Token *token = nullptr;

#pragma region Keywords
    // Operators
    if (buffer == "xor")
        token = new Token(TT_KEYWORD, K_XOR, ln, col);
    else if (buffer == "band")
        token = new Token(TT_KEYWORD, K_BAND, ln, col);
    else if (buffer == "bor")
        token = new Token(TT_KEYWORD, K_BOR, ln, col);
    else if (buffer == "lshift")
        token = new Token(TT_KEYWORD, K_LSHIFT, ln, col);
    else if (buffer == "rshift")
        token = new Token(TT_KEYWORD, K_RSHIFT, ln, col);
    else if (buffer == "bnot")
        token = new Token(TT_KEYWORD, K_BNOT, ln, col);

    // Instructions
    else if (buffer == "add")
        token = new Token(TT_KEYWORD, K_ADD, ln, col);
    else if (buffer == "sub")
        token = new Token(TT_KEYWORD, K_SUB, ln, col);
    else if (buffer == "mul")
        token = new Token(TT_KEYWORD, K_MUL, ln, col);
    else if (buffer == "div")
        token = new Token(TT_KEYWORD, K_DIV, ln, col);
    else if (buffer == "mod")
        token = new Token(TT_KEYWORD, K_MOD, ln, col);
    else if (buffer == "pow")
        token = new Token(TT_KEYWORD, K_POW, ln, col);

    else if (buffer == "tbool")
        token = new Token(TT_KEYWORD, K_TBOOL, ln, col);
    else if (buffer == "tnot")
        return token;

    else if (buffer == "set")
        token = new Token(TT_KEYWORD, K_SET, ln, col);
    else if (buffer == "get")
        token = new Token(TT_KEYWORD, K_GET, ln, col);
    else if (buffer == "del")
        token = new Token(TT_KEYWORD, K_DEL, ln, col);

    // Variable
    else if (buffer == "mutable")
        token = new Token(TT_KEYWORD, K_MUTABLE, ln, col);
    else if (buffer == "fixed")
        token = new Token(TT_KEYWORD, K_FIXED, ln, col);

    // Special Keywords
    else if (buffer == "todef")
        token = new Token(TT_KEYWORD, K_TODEF, ln, col);
    else if (buffer == "undef")
        token = new Token(TT_KEYWORD, K_UNDEF, ln, col);
    else if (buffer == "null")
        token = new Token(TT_KEYWORD, K_NULL, ln, col);
    else if (buffer == "rterr")
        token = new Token(TT_KEYWORD, K_RTERR, ln, col);
    else if (buffer == "index")
        token = new Token(TT_KEYWORD, K_INDEX, ln, col);
    else if (buffer == "key")
        token = new Token(TT_KEYWORD, K_KEY, ln, col);
    else if (buffer == "value")
        token = new Token(TT_KEYWORD, K_VALUE, ln, col);

    // Input & Output
    else if (buffer == "in")
        token = new Token(TT_KEYWORD, K_IN, ln, col);
    else if (buffer == "out")
        token = new Token(TT_KEYWORD, K_OUT, ln, col);

    // File Manipulation
    else if (buffer == "openf")
        token = new Token(TT_KEYWORD, K_OPENF, ln, col);
    else if (buffer == "readf")
        token = new Token(TT_KEYWORD, K_READF, ln, col);
    else if (buffer == "writef")
        token = new Token(TT_KEYWORD, K_WRITEF, ln, col);
    else if (buffer == "readbf")
        token = new Token(TT_KEYWORD, K_READBF, ln, col);
    else if (buffer == "writebf")
        token = new Token(TT_KEYWORD, K_WRITEBF, ln, col);
    else if (buffer == "closef")
        token = new Token(TT_KEYWORD, K_CLOSEF, ln, col);
#pragma endregion

#pragma region Operators
    else if (buffer == "=")
        token = new Token(TT_OPERATOR, OP_ASSIGN, ln, col);
    else if (buffer == "(")
        token = new Token(TT_OPERATOR, OP_LEFT_PARENTHESIS, ln, col);
    else if (buffer == ")")
        token = new Token(TT_OPERATOR, OP_RIGHT_PARENTHESIS, ln, col);
    else if (buffer == "[")
        token = new Token(TT_OPERATOR, OP_LEFT_BRACKET, ln, col);
    else if (buffer == "]")
        token = new Token(TT_OPERATOR, OP_RIGHT_BRACKET, ln, col);
    else if (buffer == "{")
        token = new Token(TT_OPERATOR, OP_LEFT_BRACE, ln, col);
    else if (buffer == "}")
        token = new Token(TT_OPERATOR, OP_RIGHT_BRACE, ln, col);
    else if (buffer == "->")
        token = new Token(TT_OPERATOR, OP_ARROW, ln, col);
    else if (buffer == "==")
        token = new Token(TT_OPERATOR, OP_EQ, ln, col);
    else if (buffer == "!=")
        token = new Token(TT_OPERATOR, OP_NEQ, ln, col);
    else if (buffer == "<")
        token = new Token(TT_OPERATOR, OP_LT, ln, col);
    else if (buffer == ">")
        token = new Token(TT_OPERATOR, OP_GT, ln, col);
    else if (buffer == "<=")
        token = new Token(TT_OPERATOR, OP_LTE, ln, col);
    else if (buffer == ">=")
        token = new Token(TT_OPERATOR, OP_GTE, ln, col);
    else if (buffer == "&&")
        token = new Token(TT_OPERATOR, OP_AND, ln, col);
    else if (buffer == "||")
        token = new Token(TT_OPERATOR, OP_OR, ln, col);
    else if (buffer == "!")
        token = new Token(TT_OPERATOR, OP_NOT, ln, col);
#pragma endregion

#pragma region Literals
    // Bool
    else if (buffer == "true")
        token = new Token(TT_BOOL, 0, ln, col, new bool(true), "true");
    else if (buffer == "false")
        token = new Token(TT_BOOL, 0, ln, col, new bool(false), "false");
    // Identifier
    else if (std::regex_match(buffer, std::regex("[_|A-Z|a-z]+[_|A-Z|a-z|0-9]+")))
    {
        std::string *str = new std::string(buffer);
        token = new Token(TT_IDENTIFIER, 0, ln, col, str, buffer.c_str());
    }
    // Integer
    else if (std::regex_match(buffer, std::regex("[0-9]+")))
    {
        int *num = new int(std::stoi(buffer));

        token = new Token(TT_INT, 0, ln, col, num, buffer.c_str());
    }
    // Float
    else if (std::regex_match(buffer, std::regex("[0-9]+([.][0-9]*)?|[.][0-9]+")))
    {
        if (buffer[0] == '.')
            buffer = "0" + buffer;
        float *num = new float(std::stof(buffer));

        token = new Token(TT_FLOAT, 0, ln, col, num, buffer.c_str());
    }
    // String
    else if (std::regex_match(buffer, std::regex("\"[^\"]*\"")))
    {
        std::string *str = new std::string(buffer);
        str->erase(str->begin());
        str->erase(str->end() - 1);

        token = new Token(TT_STRING, 0, ln, col, str, buffer.c_str());
    }
    // Char
    else if (std::regex_match(buffer, std::regex("\'[^\']*\'")))
    {
        std::string *str = new std::string(buffer);
        str->erase(str->begin());
        str->erase(str->end() - 1);

        token = new Token(TT_CHAR, 0, ln, col, str, buffer.c_str());
    }

#pragma endregion

    return token;
}

std::vector<Token> Lexer::lex()
{
    while (true)
    {
        buff = "";

        int col = column;

        // Loop until we find some delimiter
        while (source[index] != ' ' && source[index] != '\n' && source[index] != '\0' && source[index] != '\t')
            buff += source[index++];

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

        // Single-Line comment
        if (buff.rfind("//", 0) == 0)
        {
            while (source[index] != '\n' && source[index] != '\0')
                index++;

            if (source[index] == '\n')
            {
                line++;
                column = 1;
            }

            continue;
        }

        // Multi-Line comment
        if (buff.rfind("/*", 0) == 0)
        {
            int startline = line;
            int startcol = column;
            while (true)
            {
                if (source[index] == '\0')
                {
                    std::cout << "Unterminated multi-line comment" << std::endl;
                    std::cout << "Line: " << startline << ", Column: " << column << '\n'
                              << std::endl;
                    exit(EXIT_FAILURE);
                }

                if (source[index] == '\n')
                {
                    line++;
                    column = 1;
                }

                if (source[index] == '*' && source[index + 1] == '/')
                {
                    index += 2;
                    break;
                }

                index++;
            }

            continue;
        }

        // Try to convert to a token
        Token *tok = getToken(buff, line, col);

        if (tok != nullptr)
        {
            tokens.push_back(*tok);
            delete tok;
        }
        else
        {
            std::cout << "\nUnknown token: '" << buff << "'\n";
            std::cout << "Line: " << line << ", Column: " << col << '\n'
                      << std::endl;
            exit(EXIT_FAILURE);
        }

        // New line
        if (source[index] == '\n')
        {
            line++;
            column = 1;
        }

        // End of file
        else if (source[index] == '\0')
        {
            tokens.push_back(Token(TT_EOF, 0, line, col));
            break;
        }

        buffi = 0;
        index++;
        column++;
    }

    return this->tokens;
}