#include "../include/lexer.h"

// Constructor & Destructor
Lexer::Lexer(std::string filename, std::string source)
{
    this->filename = filename;
    this->source = source;

    this->column_s = 1;
    this->column_e = 1;
    this->line = 0;
}

Lexer::~Lexer() {}

// Private Methods
std::vector<std::string> Lexer::splitLines(const std::string &str) const
{
    std::vector<std::string> lines;

    std::stringstream ss(str);
    std::string line;

    while (std::getline(ss, line, '\n'))
        lines.push_back(line);

    return lines;
}

std::vector<std::string> Lexer::splitWords(const std::string &str) const
{
    std::vector<std::string> words;

    std::stringstream ss(str);
    std::string word;

    while (std::getline(ss, word, ' '))
    {
        words.push_back(word);
    }

    return words;
}

std::string Lexer::removeTabs(const std::string &str) const
{
    std::string result;

    for (char c : str)
    {
        if (c != '\t')
            result += c;
    }

    return result;
}

Token *Lexer::getToken(std::string buffer, int ln, int col_s, int col_e) const
{
    Token *token = nullptr;

#pragma region Keywords
    // Operators
    if (buffer == "xor")
        token = new Token(TT_KEYWORD, K_XOR, ln, col_s, col_e);
    else if (buffer == "band")
        token = new Token(TT_KEYWORD, K_BAND, ln, col_s, col_e);
    else if (buffer == "bor")
        token = new Token(TT_KEYWORD, K_BOR, ln, col_s, col_e);
    else if (buffer == "lshift")
        token = new Token(TT_KEYWORD, K_LSHIFT, ln, col_s, col_e);
    else if (buffer == "rshift")
        token = new Token(TT_KEYWORD, K_RSHIFT, ln, col_s, col_e);
    else if (buffer == "bnot")
        token = new Token(TT_KEYWORD, K_BNOT, ln, col_s, col_e);

    // Instructions
    else if (buffer == "add")
        token = new Token(TT_KEYWORD, K_ADD, ln, col_s, col_e);
    else if (buffer == "sub")
        token = new Token(TT_KEYWORD, K_SUB, ln, col_s, col_e);
    else if (buffer == "mul")
        token = new Token(TT_KEYWORD, K_MUL, ln, col_s, col_e);
    else if (buffer == "div")
        token = new Token(TT_KEYWORD, K_DIV, ln, col_s, col_e);
    else if (buffer == "mod")
        token = new Token(TT_KEYWORD, K_MOD, ln, col_s, col_e);
    else if (buffer == "pow")
        token = new Token(TT_KEYWORD, K_POW, ln, col_s, col_e);

    else if (buffer == "tbool")
        token = new Token(TT_KEYWORD, K_TBOOL, ln, col_s, col_e);
    else if (buffer == "tnot")
        return token;

    else if (buffer == "set")
        token = new Token(TT_KEYWORD, K_SET, ln, col_s, col_e);
    else if (buffer == "get")
        token = new Token(TT_KEYWORD, K_GET, ln, col_s, col_e);
    else if (buffer == "del")
        token = new Token(TT_KEYWORD, K_DEL, ln, col_s, col_e);

    // Variable
    else if (buffer == "mutable")
        token = new Token(TT_KEYWORD, K_MUTABLE, ln, col_s, col_e);
    else if (buffer == "fixed")
        token = new Token(TT_KEYWORD, K_FIXED, ln, col_s, col_e);

    // Special Keywords
    else if (buffer == "todef")
        token = new Token(TT_KEYWORD, K_TODEF, ln, col_s, col_e);
    else if (buffer == "undef")
        token = new Token(TT_KEYWORD, K_UNDEF, ln, col_s, col_e);
    else if (buffer == "null")
        token = new Token(TT_KEYWORD, K_NULL, ln, col_s, col_e);
    else if (buffer == "rterr")
        token = new Token(TT_KEYWORD, K_RTERR, ln, col_s, col_e);
    else if (buffer == "index")
        token = new Token(TT_KEYWORD, K_INDEX, ln, col_s, col_e);
    else if (buffer == "key")
        token = new Token(TT_KEYWORD, K_KEY, ln, col_s, col_e);
    else if (buffer == "value")
        token = new Token(TT_KEYWORD, K_VALUE, ln, col_s, col_e);

    // Input & Output
    else if (buffer == "in")
        token = new Token(TT_KEYWORD, K_IN, ln, col_s, col_e);
    else if (buffer == "out")
        token = new Token(TT_KEYWORD, K_OUT, ln, col_s, col_e);

    // File Manipulation
    else if (buffer == "openf")
        token = new Token(TT_KEYWORD, K_OPENF, ln, col_s, col_e);
    else if (buffer == "readf")
        token = new Token(TT_KEYWORD, K_READF, ln, col_s, col_e);
    else if (buffer == "writef")
        token = new Token(TT_KEYWORD, K_WRITEF, ln, col_s, col_e);
    else if (buffer == "readbf")
        token = new Token(TT_KEYWORD, K_READBF, ln, col_s, col_e);
    else if (buffer == "writebf")
        token = new Token(TT_KEYWORD, K_WRITEBF, ln, col_s, col_e);
    else if (buffer == "closef")
        token = new Token(TT_KEYWORD, K_CLOSEF, ln, col_s, col_e);
#pragma endregion

#pragma region Operators
    else if (buffer == "=")
        token = new Token(TT_OPERATOR, OP_ASSIGN, ln, col_s, col_e);
    else if (buffer == "(")
        token = new Token(TT_OPERATOR, OP_LEFT_PARENTHESIS, ln, col_s, col_e);
    else if (buffer == ")")
        token = new Token(TT_OPERATOR, OP_RIGHT_PARENTHESIS, ln, col_s, col_e);
    else if (buffer == "[")
        token = new Token(TT_OPERATOR, OP_LEFT_BRACKET, ln, col_s, col_e);
    else if (buffer == "]")
        token = new Token(TT_OPERATOR, OP_RIGHT_BRACKET, ln, col_s, col_e);
    else if (buffer == "{")
        token = new Token(TT_OPERATOR, OP_LEFT_BRACE, ln, col_s, col_e);
    else if (buffer == "}")
        token = new Token(TT_OPERATOR, OP_RIGHT_BRACE, ln, col_s, col_e);
    else if (buffer == "->")
        token = new Token(TT_OPERATOR, OP_ARROW, ln, col_s, col_e);
    else if (buffer == "==")
        token = new Token(TT_OPERATOR, OP_EQ, ln, col_s, col_e);
    else if (buffer == "!=")
        token = new Token(TT_OPERATOR, OP_NEQ, ln, col_s, col_e);
    else if (buffer == "<")
        token = new Token(TT_OPERATOR, OP_LT, ln, col_s, col_e);
    else if (buffer == ">")
        token = new Token(TT_OPERATOR, OP_GT, ln, col_s, col_e);
    else if (buffer == "<=")
        token = new Token(TT_OPERATOR, OP_LTE, ln, col_s, col_e);
    else if (buffer == ">=")
        token = new Token(TT_OPERATOR, OP_GTE, ln, col_s, col_e);
    else if (buffer == "&&")
        token = new Token(TT_OPERATOR, OP_AND, ln, col_s, col_e);
    else if (buffer == "||")
        token = new Token(TT_OPERATOR, OP_OR, ln, col_s, col_e);
    else if (buffer == "!")
        token = new Token(TT_OPERATOR, OP_NOT, ln, col_s, col_e);
#pragma endregion

#pragma region Literals
    // Bool
    else if (buffer == "true")
        token = new Token(TT_BOOL, 0, ln, col_s, col_e, new bool(true), "true");
    else if (buffer == "false")
        token = new Token(TT_BOOL, 0, ln, col_s, col_e, new bool(false), "false");
    // Identifier
    else if (std::regex_match(buffer, std::regex("[_|A-Z|a-z]+[_|A-Z|a-z|0-9]+")))
    {
        std::string *str = new std::string(buffer);
        token = new Token(TT_IDENTIFIER, 0, ln, col_s, col_e, str, buffer.c_str());
    }
    // Integer
    else if (std::regex_match(buffer, std::regex("[0-9]+")))
    {
        util::ull *num = new util::ull(std::stoull(buffer));

        token = new Token(TT_INT, 0, ln, col_s, col_e, num, std::to_string(*num).c_str());
    }
    // Float
    else if (std::regex_match(buffer, std::regex("[0-9]+([.][0-9]*)?|[.][0-9]+")))
    {
        if (buffer[0] == '.')
            buffer = "0" + buffer;
        util::ld *num = new util::ld(std::stold(buffer));

        token = new Token(TT_FLOAT, 0, ln, col_s, col_e, num, std::to_string(*num).c_str());
    }
    // String
    else if (std::regex_match(buffer, std::regex("\"[^\"]*\"")))
    {
        std::string *str = new std::string(buffer);
        str->erase(str->begin());
        str->erase(str->end() - 1);

        token = new Token(TT_STRING, 0, ln, col_s, col_e, str, buffer.c_str());
    }
    // Char
    else if (std::regex_match(buffer, std::regex("\'[^\']*\'")))
    {
        std::string *str = new std::string(buffer);
        str->erase(str->begin());
        str->erase(str->end() - 1);

        token = new Token(TT_CHAR, 0, ln, col_s, col_e, str, buffer.c_str());
    }

#pragma endregion

    return token;
}

void Lexer::addToken(Token *token)
{
    tokens.push_back(*token);
}

void Lexer::log(ErrorType type, std::string msg, int ln, int col_s)
{
    logs.push_back(Error(type, msg, ln, col_s));
}

bool Lexer::chlogs() const
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

// Public Methods
std::vector<Token> Lexer::lex()
{
    // Remove tabs from the source code
    std::string _source = this->removeTabs(this->source);

    auto lines = this->splitLines(_source);

    std::string _line;

    bool multiline_comment = false;
    bool comment = false;

    // Iterate Lines
    for (this->line; this->line < lines.size(); this->line++)
    {
        // Line string
        _line = lines[this->line];

        // Skip empty line
        if (_line.length() == 0)
            continue;

        // Update column
        this->column_s = 1;
        this->column_e = 1;

        // Get words
        auto words = this->splitWords(_line);

        // Iterate Words
        for (int index = 0; index < words.size(); index++)
        {
            if (comment)
                continue;

            // Consider spaces
            if (index != 0)
                this->column_e += 1;

            // Token string
            auto token = words[index];

            // Skip empty token
            if (token.length() == 0 || (int)token[0] == 0)
                continue;

            // Column Update
            this->column_s = this->column_e;
            this->column_e += token.length();

            // Comments
            if (token.rfind("//", 0) == 0)
            {
                comment = true;
                continue;
            }

            if (token.rfind("/*", 0) == 0)
            {
                multiline_comment = true;
                continue;
            }

            if (token.rfind("*/", 0) == 0)
            {
                multiline_comment = false;

                if (token.size() == 2)
                    continue;

                std::string n_buff = "";

                for (int i = 2; i < token.length(); i++)
                    n_buff += token[i];

                token = n_buff;
            }
            else if (multiline_comment)
                continue;

            // Semicolon
            bool hasSemicolon = false;

            if (token[token.length() - 1] == ';')
            {
                hasSemicolon = true;

                std::string n_buff = "";

                for (int i = 0; i < token.length() - 1; i++)
                    n_buff += token[i];

                token = n_buff;
            }

            // Try get token
            Token *tok = this->getToken(token, this->line + 1, this->column_s, hasSemicolon ? this->column_e - 1 : this->column_e);

            if (tok != nullptr)
            {
                addToken(tok);

                delete tok;

                if (hasSemicolon)
                    tokens.push_back(Token(TT_SEMICOLON, 0, line + 1, column_e - 1, column_e, nullptr, ";"));
            }
            else
            {
                log(ET_ERROR, "Unknown token: '" + token + "'", line + 1, column_e);
                break;
            }
        }

        comment = false;
    }

    if (multiline_comment)
        log(ET_ERROR, "Unterminated multiline comment", line + 1, column_e);

    return this->tokens;
}