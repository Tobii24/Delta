#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "./token.h"

enum NodeType
{
    NT_Statements,

    // Literals
    NT_Integer,
    NT_Float,
    NT_String,
    NT_Char,
    NT_Bool,
    NT_Array,
    NT_Binary,
    NT_Dictionary,
    NT_Identifier,

    NT_SpecialKeyword,

    NT_PointerValue,
    NT_PointerAddress,
    NT_PointerType,
    NT_PointerObject,

    // Operations
    NT_BinaryOperation,
    NT_UnaryOperation,
    NT_BitwiseOperation,

    NT_VariableDefine,
    NT_VariableAssign,
    NT_VariableAccess,

    NT_Comparison,

    NT_Instruction,

    NT_Cast,

    NT_ArraySet,
    NT_ArrayGet,
    NT_ArrayDel,

    NT_Input,
    NT_Output,

    NT_OpenFile,
    NT_ReadFile,
    NT_WriteFile,
    NT_ReadBinaryFile,
    NT_WriteBinaryFile,
    NT_CloseFile,

    NT_ReferenceDefine,
    NT_ReferenceAccess
};

class Node
{
public:
    Node(NodeType type);
    ~Node();

    NodeType getType();

    void setValue(std::string key, void *value);
    void *getValue(std::string key);

    void addChild(Node child);

    std::string typeAsString() const;

    void print();

    bool operator==(const Node &other) const
    {
        return (type == other.type && values == other.values && children == other.children);
    }

private:
    NodeType type;
    std::map<std::string, void *> values;
    std::vector<Node> children;

    void pretty_node(Node *root, std::string indent, bool isLast) const;
};
