#pragma once

#include <iostream>
#include <vector>

#include "./token.h"
#include "./node.h"

class Parser
{
public:
    Parser(std::string filename, std::vector<Token> tokens);
    ~Parser();

    void parse();
    void printTokens();
    void printNodes();

    void printError(std::string message);

    void printWarning(std::string message);

    void printInfo(std::string message);

    void printDebug(std::string message);

private:
    std::string filename;
    std::vector<Token> tokens;
    std::vector<Node> nodes;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    std::vector<std::string> infos;
    std::vector<std::string> debug;

    void parseTokens();
    void parseNodes();
};