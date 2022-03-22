#include "../include/error.h"

Error::Error(const std::string title, const std::string msg)
{
    this->title = title;
    this->msg = msg;
}

void Error::_throw() const
{
    std::cout << this->title << ": " << this->msg << std::endl;
    exit(1);
}