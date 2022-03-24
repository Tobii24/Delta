#include "../include/error.h"

Error::Error(ErrorType type, const std::string msg)
{
    this->type = type;

    if (type == ET_INFO)
    {
        this->title = "INFO";
        this->color = BLUE;
    }
    else if (type == ET_ERROR)
    {
        this->title = "ERROR";
        this->color = RED;
    }
    else if (type == ET_WARNING)
    {
        this->title = "WARNING";
        this->color = YELLOW;
    }

    this->msg = msg;
}

void Error::_throw() const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (type == ET_INFO)
    {
        SetConsoleTextAttribute(hConsole, 9);
    }
    else if (type == ET_ERROR)
    {
        SetConsoleTextAttribute(hConsole, 12);
    }
    else if (type == ET_WARNING)
    {
        SetConsoleTextAttribute(hConsole, 14);
    }

    std::cout << this->title << ": " << this->msg << std::endl;

    SetConsoleTextAttribute(hConsole, 7);
#else
    std::cout << this->color << this->title << ": " << this->msg << RESET << std::endl;
#endif
    exit(1);
}