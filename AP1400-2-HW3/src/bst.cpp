#include "bst.h"

Node::Node() : value(0), left(nullptr), right(nullptr) {}
Node::Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
Node::Node(const Node& node) {
    *this = node;
}

std::ostream& operator << (std::ostream& os, const Node& node) {
    os << std::format("{{ value: {0} -> {{ left.value: {1}, right.value: {2} }} }}", node.value, node.left->value, node.right->value); 
    return os;
}

bool operator < (int lhs, const Node& rhs) {
    return lhs < rhs.value;
}

bool operator > (int lhs, const Node& rhs) {
    return lhs > rhs.value;
}

bool operator == (int lhs, const Node& rhs) {
    return !(lhs < rhs || lhs > rhs);
}

bool operator < (const Node& lhs, int rhs) {
    return rhs > lhs;
}

bool operator > (const Node& lhs, int rhs) {
    return rhs < lhs;
}

bool operator == (const Node& lhs, int rhs) {
    return rhs == lhs;
}

bool operator >= (int lhs, const Node& rhs) {
    return (lhs > rhs) || (lhs == rhs);
}

bool operator <= (int lhs, const Node& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator >= (const Node& lhs, int rhs) {
    return (lhs > rhs) || (lhs == rhs);
}

bool operator <= (const Node& lhs, int rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

Node*& BST::get_root() {
    return root;
}
