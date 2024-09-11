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

bool BST::add_node(int value) {
    if (root == nullptr) {
        root = new Node{ value, nullptr, nullptr };
        return true;
    }

    auto fa = get_root(), p = get_root();
    bool flag = false;

    auto cmp = [value] (int lhs, Node *rhs) {
        if (rhs == nullptr || value == *rhs) {
            return 0;
        } else if (lhs < *rhs) {
            return -1;
        } else {
            return 1;
        }
    };

    while (cmp(value, p)) {
        if (cmp(value, p) < 0) 
            fa = p, p = p->left, flag = false;
        if (cmp(value, p) > 0) 
            fa = p, p = p->right, flag = true;
    }

    if (p == nullptr) 
        p = new Node{ value, nullptr, nullptr };
    else if (p->value == value)
        return false;


    if (flag)
        fa->right = p;
    else
        fa->left = p;


    return true;
}

