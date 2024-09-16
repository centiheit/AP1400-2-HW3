// 二级指针：https://blog.csdn.net/majianfei1023/article/details/46629065

#include "bst.h"

BST::Node::Node(int value, Node* left, Node* right) : value{value}, left{left}, right{right} {}

BST::Node::Node() : value{0}, left{nullptr}, right{nullptr} {}

// 拷贝构造函数，对于类中含有指针的成员变量，需要自己实现拷贝构造函数，
// 因为默认的拷贝构造函数是浅拷贝，会导致两个对象的指针成员变量指向同一个内存地址
// 我们需要自己实现深拷贝，使两个对象的指针成员变量指向不同的地址，但指向的内容相同
// ***哎，可是看unit_test里的测试用例TEST2，似乎是需要使用浅拷贝***
BST::Node::Node(const Node& node) : value{node.value}, left{node.left}, right{node.right} {}
// BST::Node::Node(const Node& node) {
//     value = node.value;
//     if (node.left != nullptr) {
//         left = new Node(*node.left);
//     }
//     else {
//         left = nullptr;
//     }
//     if (node.right != nullptr) {
//         right = new Node(*node.right);
//     }
//     else {
//         right = nullptr;
//     }
// }

std::ostream& operator<<(std::ostream& lhs, const BST::Node& rhs) {
    lhs << "Node's address: " << &rhs << ", node's value: " << rhs.value << ", node's left child address: " << rhs.left << ", node's right child address: " << rhs.right << std::endl;
    return lhs;
}

bool operator>(const BST::Node& lhs, const int& rhs) {
    return lhs.value > rhs;
}

bool operator>=(const BST::Node& lhs, const int& rhs) {
    return lhs.value >= rhs;
}

bool operator<(const BST::Node& lhs, const int& rhs) {
    return lhs.value < rhs;
}

bool operator<=(const BST::Node& lhs, const int& rhs) {
    return lhs.value <= rhs;
}

bool operator==(const BST::Node& lhs, const int& rhs) {
    return lhs.value == rhs;
}

bool operator>(const int& rhs, const BST::Node& lhs) {
    return rhs > lhs.value;
}

bool operator>=(const int& rhs, const BST::Node& lhs) {
    return rhs >= lhs.value;
}

bool operator<(const int& rhs, const BST::Node& lhs) {
    return rhs < lhs.value;
}

bool operator<=(const int& rhs, const BST::Node& lhs) {
    return rhs <= lhs.value;
}

bool operator==(const int& rhs, const BST::Node& lhs) {
    return rhs == lhs.value;
}

BST::Node*& BST::get_root() {
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func) const {
    std::deque<Node*> queue;
    queue.push_back(root);
    while (!queue.empty()) {
        Node* current = queue.front();
        queue.pop_front();
        func(current);
        if (current->left != nullptr) {
            queue.push_back(current->left);
        }
        if (current->right != nullptr) {
            queue.push_back(current->right);
        }
    }
}

size_t BST::length() const {
    size_t count = 0;
    bfs([&count](Node*& node) { count++; });
    return count;
}

bool BST::add_node(int value) {
    // 如果树中已经有这个节点，返回false
    if (find_node(value) != nullptr) {
        return false;
    }
    // 如果树为空，创建一个新的节点作为根节点
    if (root == nullptr) {
        root = new Node(value, nullptr, nullptr);
        return true;
    }
    // 从根节点开始，找到新节点应该插入的位置
    Node* current{root};
    bool add_flag = false;
    while (!add_flag) {
        if (value < current->value) {
            if (current->left == nullptr) {
                current->left = new Node(value, nullptr, nullptr);
                add_flag = true;
                return true;
            }
            current = current->left;
        }
        else {
            if (current->right == nullptr) {
                current->right = new Node(value, nullptr, nullptr);
                add_flag = true;
                return true;
            }
            current = current->right;
        }
    }
    return false;
}

// BST::Node** BST::find_node(int value) {
//     Node** p_current{&root};
//     Node* current = *p_current;
//     bool find_flag = false;
//     while (!find_flag) {
//         if (current == nullptr) {
//             return nullptr;
//         }
//         if (current->value == value) {
//             // 这里将p_current指向current，但current是局部变量，函数结束后会被销毁，所以这里返回的指针是无效的
//             p_current = &current;
//             return p_current;
//         }
//         if (current->value > value) {
//             current = current->left;
//         }
//         else {
//             current = current->right;
//         }
//     }
//     return nullptr;
// }
BST::Node** BST::find_node(int value) {
     Node** p_current{&root};
     bool find_flag = false;
     while (!find_flag) {
         if (*p_current == nullptr) {
             return nullptr;
         }
         if ((*p_current)->value == value) {
             return p_current;
         }
         if ((*p_current)->value > value) {
             p_current = &(*p_current)->left;
         }
         else {
             p_current = &(*p_current)->right;
         }
     }
     return nullptr;
 }

BST::Node** BST::find_parrent(int value) {
    Node** p_child = find_node(value);
    if (*p_child == nullptr) {
        return nullptr;
    }
    Node** p_current{&root};
    // Node* current = *p_current;
    bool find_flag = false;
    // 下面这段代码的问题在于每次更新时只更新了current的值，而没有更新p_current的值
    // while (!find_flag) {
    //     if (current == nullptr) {
    //         return nullptr;
    //     }
    //     if (current->left == child || current->right == child) {
    //         return p_current;
    //     }
    //     if (current->value > value) {
    //         current = current->left;
    //     }
    //     else {
    //         current = current->right;
    //     }
    // }
    // return nullptr;
    while (!find_flag) {
        if (*p_current == nullptr) {
            return nullptr;
        }
        if ((*p_current)->left == *p_child || (*p_current)->right == *p_child) {
            return p_current;
        }
        if ((*p_current)->value > value) {
            p_current = &(*p_current)->left;
        }
        else {
            p_current = &(*p_current)->right;
        }
    }
    return nullptr;
}

// 我查询了网上的定义，successor（后继节点）是指中序遍历中的下一个节点，即比当前节点大的最小节点
// 但unit_test里的测试用例似乎是要找到比当前节点小的最大节点，感觉其实应该叫做predecessor（前驱节点）
// 不过也没办法了，这里就找比当前节点值小的最大节点吧
// BST::Node** BST::find_successor(int value) {
//     Node** p_parent = find_node(value);
//     if (*p_parent == nullptr) {
//         return nullptr;
//     }
//     // 如果要删除的节点没有右子节点，返回nullptr
//     if ((*p_parent)->right == nullptr) {
//         return nullptr;
//     }
//     // 如果要删除的节点有右子节点，找到右子节点的最小节点
//     Node** p_current{&(*p_parent)->right};
//     bool find_flag = false;
//     while (!find_flag) {
//         if ((*p_current)->left == nullptr) {
//             return p_current;
//         }
//         p_current = &(*p_current)->left;
//     }
//     return nullptr;
// }
BST::Node** BST::find_successor(int value) {
    Node** p_parent = find_node(value);
    if (*p_parent == nullptr) {
        return nullptr;
    }
    // 如果要删除的节点没有左子节点，返回nullptr
    if ((*p_parent)->left == nullptr) {
        return nullptr;
    }
    // 如果要删除的节点有左子节点，找到左子节点的最大节点
    Node** p_current{&(*p_parent)->left};
    bool find_flag = false;
    while (!find_flag) {
        if ((*p_current)->right == nullptr) {
            return p_current;
        }
        p_current = &(*p_current)->right;
    }
    return nullptr;
}

bool BST::delete_node(int value) {
    Node** p_node = find_node(value);
    if (p_node == nullptr) {
        return false;
    }
    Node** p_parent = find_parrent(value);
    Node** p_successor = find_successor(value);
    // 如果要删除的节点有两个子节点，找到该节点的后继节点，将后继节点的值赋给要删除的节点
    if ((*p_node)->left != nullptr && (*p_node)->right != nullptr) {
        Node** p_successor_parent = find_parrent((*p_successor)->value);
        (*p_node)->value = (*p_successor)->value;
        // 这里也是遵循successor变为predecessor
        // 如果此时后继节点有左子节点，将后继节点的左子节点赋给后继节点，然后删除后继节点的左子节点
        if ((*p_successor)->left != nullptr) {
            (*p_successor)->value = (*p_successor)->left->value;
            delete (*p_successor)->left;
            (*p_successor)->left == nullptr;
            return true;
        }
        // 如果此时后继节点没有左子节点，先将其父节点的右子节点赋值为nullptr，然后删除后继节点
        delete *p_successor;
        (*p_successor_parent)->right = nullptr;
        return true;
    }
    // 如果要删除的节点只有一个子节点
    else if ((*p_node)->left != nullptr || (*p_node)->right != nullptr) {
        Node* child = ((*p_node)->left != nullptr) ? (*p_node)->left : (*p_node)->right;
        delete *p_node;
        if ((*p_parent)->left == *p_node) {
            (*p_parent)->left = child;
        }
        else {
            (*p_parent)->right = child;
        }
        return true;
    }
    // 如果要删除的节点没有子节点，将要删除的节点的父节点的左子节点置为nullptr，然后删除要删除的节点
    else {
        delete *p_node;
        if ((*p_parent)->left == *p_node) {
            (*p_parent)->left = nullptr;
        }
        else {
            (*p_parent)->right = nullptr;
        }
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& lhs, const BST& rhs) {
    lhs << std::string(50, '*') << std::endl;
    rhs.bfs([&lhs](BST::Node*& node) { lhs << node << "\t => value:" << node->value << "\t left:" << node->left << "\t right:" << node->right << std::endl; });
    lhs << "binary search tree size: " << rhs.length() << std::endl;
    lhs << std::string(50, '*') << std::endl;
    return lhs;
}

// 前置++运算符重载
BST& operator++(BST& bst) {
    bst.bfs([](BST::Node*& node) { ++node->value; });
    return bst;
}

// 后置++运算符重载
BST operator++(BST& bst, int) {
    BST copy{bst};
    ++bst;
    return copy;
}

BST::~BST() {
    // ***果然是这个几把析构函数有问题***
	//std::vector<Node*> nodes;
	//bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
	//for(auto& node: nodes)
	//	delete node;
    deleteTree(root);
}

// 默认构造函数，初始化根节点为空指针
BST::BST() : root{nullptr} {}

// 因为测试用例中要求node的拷贝构造函数是浅拷贝，所以只能单独设计一个深拷贝函数
void deepCopy(const BST::Node* src_node, BST::Node* copy_node) {
    if (src_node->left != nullptr) {
        copy_node->left = new BST::Node(src_node->left->value, nullptr, nullptr);
        deepCopy(src_node->left, copy_node->left);
    }
    if (src_node->right != nullptr) {
        copy_node->right = new BST::Node(src_node->right->value, nullptr, nullptr);
        deepCopy(src_node->right, copy_node->right);
    }
}

void deleteTree(BST::Node* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// 拷贝构造函数，深拷贝
BST::BST(const BST& bst) {
    if (bst.root != nullptr) {
        // 复制根节点创建新的内存副本，并将root指向新的根节点
        // 即现在有个新的内存空间存储了原树的所有节点
        root = new Node(*bst.root);
        deepCopy(bst.root, root);
    }
    else {
        root = nullptr;
    }
}

// 移动构造函数
// 使用时需要将传入的参数使用std::move转换为右值引用
BST::BST(BST&& bst) noexcept {
    root = bst.root;
    bst.root = nullptr;
}

// 拷贝赋值运算符，深拷贝
BST& BST::operator=(const BST& bst) {
    // 如果不是自我赋值，深拷贝
    if (this != &bst) {
        root = new Node(*bst.root);
        deepCopy(bst.root, root);
    }
    // 如果是自我赋值，直接返回
    return *this;
}

// 移动赋值运算符
BST& BST::operator=(BST&& bst) noexcept {
    // 如果不是自我赋值，删除原有的树，然后移动赋值
    if (this != &bst) {
        deleteTree(root);
        root = bst.root;
        bst.root = nullptr;
    }
    // 如果是自我赋值，直接返回
    return *this;
}

// 列表初始化构造函数
BST::BST(std::initializer_list<int> list) : root(nullptr) {
    for (auto value : list) {
        add_node(value);
    }
}

