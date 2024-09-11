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
        Node(Node& node);

        int value;
        Node* left;
        Node* right;
    };

    BST();
    BST(const BST& bst);
    BST(BST&& bst);
    BST(std::initializer_list<int> values);

    BST& operator = (const BST& bst);
    BST& operator = (BST&& bst);

    BST& operator ++ ();
    BST operator ++ (int);

    Node*& get_root();
    const Node* get_root() const;
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
std::ostream& operator << (std::ostream& os, BST& bst);

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

Node** find_successor(BST* bst, int value);

static void copy_BST(const Node* src, Node*& dest);

#endif //BST_H
