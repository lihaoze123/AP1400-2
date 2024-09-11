#include "bst.h"

BST::BST() : root(nullptr) {}

BST::BST(std::initializer_list<int> values) : root(nullptr) {
    for (auto x : values)
        add_node(x);
}

// copy
static void copy_BST(const Node* src, Node*& dest) {
    if (src != nullptr) {
        dest = new Node{src->value, nullptr, nullptr};
        copy_BST(src->left, dest->left);
        copy_BST(src->right, dest->right);
    }
}

BST::BST(const BST& bst) {
    if (bst.get_root() != nullptr) 
        copy_BST(bst.get_root(), get_root());
}

BST& BST::operator = (const BST& bst) {
	auto bst2 = new BST(bst);
	this->~BST();
	root = bst2->root;
	return *this;
}

// move
BST::BST(BST&& bst) {
    root = bst.root;
    bst.root = nullptr;
}

BST& BST::operator = (BST&& bst) {
	if (this != &bst) {
		this->~BST();
		root = bst.root;
		bst.root = nullptr;
	}
	return *this;
}

BST& BST::operator ++ () {
    bfs([] (Node*& node) {
        ++node->value;
    });

    return *this;
}

BST BST::operator ++ (int) {
    auto tmp = *this;

    ++(*this);

    return tmp;
}

Node::Node() : value(0), left(nullptr), right(nullptr) {}
Node::Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
Node::Node(const Node& node) { *this = node; }
Node::Node(Node& node) { *this = std::move(node); }

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

const Node* BST::get_root() const {
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

void BST::bfs(std::function<void(Node*& node)> func) {
    auto root = get_root();

    std::queue<Node**> q;
    q.push(&root); 

    while (q.size()) { 
        auto t = q.front(); 
        q.pop(); 

        func(*t);

        if ((*t)->left != nullptr)
            q.push(&(*t)->left);
        if ((*t)->right != nullptr)
            q.push(&(*t)->right);
    }
}

size_t BST::length() {
    size_t res = 0;
    bfs([&res] (Node*& node) { ++ res; });

    return res;
}

std::ostream& operator << (std::ostream& os, BST& bst) {
    bst.bfs([&os] (Node*& node) { os << node->value << ' '; });

    return os;
}

Node** BST::find_node(int value) {
    auto fa = &get_root(), p = &get_root();
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

    while (cmp(value, *p)) {
        if (cmp(value, *p) < 0) 
            fa = p, p = &(*p)->left, flag = false;
        if (cmp(value, *p) > 0) 
            fa = p, p = &(*p)->right, flag = true;
    }

    if (*p == nullptr)
        return nullptr;
    if ((*p)->value == value)
        return p;

    return nullptr;
}

Node** BST::find_parrent(int value) {
    auto fa = &get_root(), p = &get_root();
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

    while (cmp(value, *p)) {
        if (cmp(value, *p) < 0) 
            fa = p, p = &(*p)->left, flag = false;
        if (cmp(value, *p) > 0) 
            fa = p, p = &(*p)->right, flag = true;
    }

    if (*p == nullptr)
        return nullptr;
    if ((*p)->value == value)
        return fa;

    return nullptr;
}

// dont know why, but this function is used to find predecessor
Node** BST::find_successor(int value) {
    auto p = &(*find_node(value))->left;

    if ((*p) == nullptr)
        return nullptr;

    while ((*p)->right != nullptr)
        p = &(*p)->right;

    return p;
}

// find real successor
Node** find_successor(BST* bst, int value) {
    auto p = &(*bst->find_node(value))->right;

    if ((*p) == nullptr)
        return nullptr;

    while ((*p)->left != nullptr)
        p = &(*p)->left;

    return p;
}

bool BST::delete_node(int value) {
    auto p = find_node(value);
    
    if (p == nullptr)
        return false;

    auto left = (*p)->left, right = (*p)->right;

    if (left == nullptr) {
        delete *p;
        *p = right;
    } else if (right == nullptr) {
        delete *p;
        *p = left;
    } else {
        auto succ = find_successor(value);
        (*p)->value = (*succ)->value;

        delete (*succ);
        *succ = nullptr;
    }

    return true;
}
