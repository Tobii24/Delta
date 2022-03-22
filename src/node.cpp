#include "../include/node.h"

Node::Node(NodeType type)
{
    this->type = type;
}

Node::~Node() {}

NodeType Node::getType()
{
    return this->type;
}

void Node::setValue(std::string key, void *value)
{
    this->values[key] = value;
}

void *Node::getValue(std::string key)
{
    return this->values[key];
}

void Node::addChild(Node child)
{
    this->children.push_back(child);
}