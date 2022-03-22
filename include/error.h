#pragma once

#include <iostream>
#include <string.h>

struct Error
{
public:
    void _throw() const;

    Error(const std::string title, const std::string msg);

private:
    std::string title;
    std::string msg;
};
