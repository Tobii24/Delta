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

void Node::addChild(Node *child)
{
    this->children.push_back(*child);
    delete child;
}

std::string Node::typeAsString() const
{
    static std::map<NodeType, std::string> strings;
    if (strings.size() == 0)
    {
#define INSERT_ELEMENT(p, nm) strings[p] = nm
        INSERT_ELEMENT(NT_Statements, "Statements");

        // Literals
        INSERT_ELEMENT(NT_Integer, "Integer");
        INSERT_ELEMENT(NT_Float, "Float");
        INSERT_ELEMENT(NT_String, "String");
        INSERT_ELEMENT(NT_Char, "Char");
        INSERT_ELEMENT(NT_Bool, "Bool");
        INSERT_ELEMENT(NT_Array, "Array");
        INSERT_ELEMENT(NT_Binary, "Binary");
        INSERT_ELEMENT(NT_Dictionary, "Dictionary");

        INSERT_ELEMENT(NT_SpecialKeyword, "SpecialKeyword");

        INSERT_ELEMENT(NT_PointerValue, "PointerValue");
        INSERT_ELEMENT(NT_PointerAddress, "PointerAddress");
        INSERT_ELEMENT(NT_PointerType, "PointerType");
        INSERT_ELEMENT(NT_PointerObject, "PointerObject");

        // Operations
        INSERT_ELEMENT(NT_BinaryOperation, "BinaryOperation");
        INSERT_ELEMENT(NT_UnaryOperation, "UnaryOperation");
        INSERT_ELEMENT(NT_BitwiseOperation, "BitwiseOperation");

        INSERT_ELEMENT(NT_VariableDefine, "VariableDefine");
        INSERT_ELEMENT(NT_VariableAssign, "VariableAssign");
        INSERT_ELEMENT(NT_VariableAccess, "VariableAccess");

        INSERT_ELEMENT(NT_Comparison, "Comparison");

        INSERT_ELEMENT(NT_Instruction, "Instruction");

        INSERT_ELEMENT(NT_Cast, "Cast");

        INSERT_ELEMENT(NT_ArraySet, "ArraySet");
        INSERT_ELEMENT(NT_ArrayGet, "ArrayGet");
        INSERT_ELEMENT(NT_ArrayDel, "ArrayDel");

        INSERT_ELEMENT(NT_Input, "Input");
        INSERT_ELEMENT(NT_Output, "Output");

        INSERT_ELEMENT(NT_OpenFile, "OpenFile");
        INSERT_ELEMENT(NT_ReadFile, "ReadFile");
        INSERT_ELEMENT(NT_WriteFile, "WriteFile");
        INSERT_ELEMENT(NT_ReadBinaryFile, "ReadBinaryFile");
        INSERT_ELEMENT(NT_WriteBinaryFile, "WriteBinaryFile");
        INSERT_ELEMENT(NT_CloseFile, "CloseFile");

        INSERT_ELEMENT(NT_ReferenceDefine, "ReferenceDefine");
        INSERT_ELEMENT(NT_ReferenceAccess, "ReferenceAccess");
#undef INSERT_ELEMENT
    }

    return strings[this->type];
}

void Node::print()
{
    std::cout << "\nAST:\n";
    pretty_node(this, "", false);
    std::cout << std::endl;
}

void Node::pretty_node(Node *root, std::string indent, bool isLast) const
{
    auto marker = isLast ? "L--" : "|--";

    std::cout << indent;
    std::cout << marker;

    std::string newindent = indent + (isLast ? "   " : "|  ");

    // Type
    std::cout << root->typeAsString();

    // Values
    if (root->values.size() > 0)
    {
        std::cout << " (";

        switch (root->type)
        {
        // Literals
        case NT_Integer:
            std::cout << *(util::ull *)root->getValue("value");
            break;
        case NT_Float:
            std::cout << *(util::ld *)root->getValue("value");
            break;
        case NT_String:
            std::cout << *(std::string *)root->getValue("value");
            break;
        case NT_Char:
            std::cout << *(char *)root->getValue("value");
            break;
        case NT_Bool:
            std::cout << *(bool *)root->getValue("value");
            break;

        // Variable
        case NT_VariableAccess:
            std::cout << *(std::string *)root->getValue("id");
            break;

        // Binary Operation
        case NT_BinaryOperation:
            std::cout << ((Token *)root->getValue("op"))->getRepr();
            break;

        // Variables
        case NT_VariableDefine:
            std::cout << "id: '" << ((Token *)root->getValue("id"))->getRepr()
                      << "', "
                      << "fixed: " << *(bool *)root->getValue("isFixed")
                      << ", "
                      << "todef: " << *(bool *)root->getValue("isTodef");
            break;
        }

        std::cout << ")";
    }

    std::cout << "\n";

    /* C# Adapted
    var children = new List<ISyntax>();
    foreach (var c in nod.Children())
        children.Add(c);

    if (children.Count < 1) return;

    var lastChild = children[^1];

    foreach (var child in nod.Children())
        _PrettyPrint(child, indent, child == lastChild);
    */

    if (root->children.size() < 1)
        return;

    Node lastChild = root->children[root->children.size() - 1];

    for (Node child : root->children)
        child.pretty_node(&child, newindent, child == lastChild);
}