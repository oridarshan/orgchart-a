#include <string>

namespace ariel
{
    struct Node
    {
        std::string name;
        Node* father = NULL;
        Node* son = NULL;
        Node* brother = NULL;
    };
}