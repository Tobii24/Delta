#include "../include/error.h"

Error::Error(enum ErrorType type, const std::string msg, const int line, const int column_start)
{
    this->type = type;
    this->ln = line;

    this->col_s = column_start;

    if (type == ET_INFO)
        this->color = BLUE;
    else if (type == ET_ERROR)
        this->color = RED;
    else if (type == ET_WARNING)
        this->color = YELLOW;

    if (type == ET_INFO)
        this->title = "Info";
    else if (type == ET_ERROR)
        this->title = "Error";
    else if (type == ET_WARNING)
        this->title = "Warning";

    this->msg = msg;
}

void Error::_throw() const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, this->color);

    std::cout << "\n["
              << this->title << "] " << this->msg << "\n"
              << "Line: " << this->ln << ", Column: " << this->col_s << std::endl;

    SetConsoleTextAttribute(hConsole, RESET);
#else
    std::cout << this->color << "\n["
              << this->title << "] " << this->msg << "\n"
              << "Line: " << this->ln << ", Column: " << this->col_s
              << RESET << std::endl;

#endif
}