#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional>
#include <deque>

class BST {
public:
    class Node;

    // 默认构造函数
    BST();
    // 拷贝构造函数
    BST(const BST& bst);
    // 移动构造函数
    BST(BST&& bst) noexcept;
    // 拷贝赋值运算符
    BST& operator=(const BST& bst);
    // 移动赋值运算符
    BST& operator=(BST&& bst) noexcept;
    // 初始化列表构造函数
    BST(std::initializer_list<int> list);

    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func) const;
    size_t length() const;
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

    // 析构函数
    ~BST();

private:
    Node* root;
};

class BST::Node {
public:
	Node(int value, Node* left, Node* right);
	Node();
	Node(const Node& node);

	int value;
	Node* left;
	Node* right;
};

std::ostream& operator<<(std::ostream& lhs, const BST::Node& rhs);
bool operator>(const BST::Node& lhs, const int& rhs);
bool operator>=(const BST::Node& lhs, const int& rhs);
bool operator<(const BST::Node& lhs, const int& rhs);
bool operator<=(const BST::Node& lhs, const int& rhs);
bool operator==(const BST::Node& lhs, const int& rhs);
bool operator>(const int& rhs, const BST::Node& lhs);
bool operator>=(const int& rhs, const BST::Node& lhs);
bool operator<(const int& rhs, const BST::Node& lhs);
bool operator<=(const int& rhs, const BST::Node& lhs);
bool operator==(const int& rhs, const BST::Node& lhs);

std::ostream& operator<<(std::ostream& lhs, const BST& rhs);
BST& operator++(BST &bst);
BST operator++(BST &bst, int);

void deepCopy(const BST::Node* src_node, BST::Node* copy_node);
void deleteTree(BST::Node* root);

#endif //BST_H