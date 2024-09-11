#ifndef BST_H
#define BST_H

#include <functional>
#include <iostream>
#include <format>
#include <compare>
#include <queue>

class BST {
public:
    class Node {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);

        int value;
        Node* left;
        Node* right;
    };

    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

private:
    Node* root;
};

using Node = BST::Node;

std::ostream& operator << (std::ostream& os, const Node& node);

bool operator < (int lhs, const Node& rhs);
bool operator > (int lhs, const Node& rhs);
bool operator == (int lhs, const Node& rhs);
bool operator >= (int lhs, const Node& rhs);
bool operator <= (int lhs, const Node& rhs);

bool operator < (const Node& lhs, int rhs);
bool operator > (const Node& lhs, int rhs);
bool operator == (const Node& lhs, int rhs);
bool operator >= (const Node& lhs, int rhs);
bool operator <= (const Node& lhs, int rhs);

#endif //BST_H
