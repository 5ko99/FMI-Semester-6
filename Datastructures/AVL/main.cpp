#include <iostream>
#include<cmath>

struct Node {
    int val;
    Node *left;
    Node *right;
    int height;

    explicit Node(int val = 0, Node *left = nullptr, Node *right = nullptr, int height = 0) :
            val(val), left(left), right(right), height(height) {}

    Node(const Node &node) = delete;

    Node &operator=(const Node &node) = delete;
};

void preOrderPrint(const Node *root) {
    if (root != nullptr) {
        std::cout << root->val << ' ';
        preOrderPrint(root->left);
        preOrderPrint(root->right);
    }
}

void inOrderPrint(const Node *root) {
    if(root!= nullptr) {
        inOrderPrint(root->left);
        std::cout<<root->val<<' ';
        inOrderPrint(root->right);
    }
}

void postOrderPrint(const Node* root) {
  if(root!= nullptr) {
        inOrderPrint(root->left);
        inOrderPrint(root->right);
        std::cout<<root->val<<' ';
    }
}

int height(const Node *node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

Node *newNode(int val) {
    Node *node = new Node;
    node->val = val;
    node->left = node->right = nullptr;
    node->height = 1;
    return node;
}

inline int getBalance(const Node *node) {
    return height(node->left) - height(node->right);
}

inline void updateHeightByOne(Node *x) {
    x->height = std::max(height(x->left), height(x->right)) + 1;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *t2 = y->left;

    y->left = x;
    x->right = t2;

    updateHeightByOne(x);
    updateHeightByOne(y);
    return y;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *t2 = x->right;

    x->right = y;
    y->left = t2;

    updateHeightByOne(x);
    updateHeightByOne(y);

    return x;
}

Node *insert(Node *node, int val) {
    if (node == nullptr)
        return newNode(val);
    if (val > node->val)
        node->right = insert(node->right, val);
    else if (val < node->val)
        node->left = insert(node->left, val);
    else
        return node;

    updateHeightByOne(node);
    int balance = getBalance(node);

    //Left left case
    if (balance > 1 && val < node->left->val)
        return rightRotate(node);
    // right right case
    if (balance < -1 && val > node->right->val)
        return leftRotate(node);
    //left right case
    if (balance > 1 && val > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    //right left case
    if (balance < -1 && val < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

bool binarySearch(const Node* root, const int& elem) {
    if(root == nullptr)
        return false;
    if(root->val == elem)
        return true;
    if(elem > root->val)
        return binarySearch(root->right,elem);
    else
        return binarySearch(root->left,elem);
}

int main() {
    Node *root = nullptr;

    /* Constructing tree given in
    the above figure */
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    root = insert(root,5);
    root = insert(root,100);
    root = insert(root, -3);
    root = insert(root,331);
    root = insert(root,101);

    /* The constructed AVL Tree would be
             30
            / \
            20 40
            / \ \
           10 25 50
    */
    preOrderPrint(root);
    std::cout<<"\n";
    inOrderPrint(root);
    std::cout<<"\n";
    const int c = 101;
    std::cout<<"Number "<<c<<" is in AVL Tree: "<<(binarySearch(root,101) ? "True\n" : "False\n");
    delete root;
    return 0;
}
