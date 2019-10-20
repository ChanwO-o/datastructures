// AVLSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"



template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;

    // std::string toString();

    unsigned int height();


private:

    struct Node
    {
        T key;
        Node* left = nullptr;
        Node* right = nullptr;

        Node() {}
        Node(T ky, Node* l = nullptr, Node* r = nullptr) : key{ky}, left{l}, right{r} {}
    };

    int used;
    Node* root;

    void destroyTree(Node* node);

    bool checkContains(const Node* current, const T& element) const;

    void copyTree(Node*& rootTo, Node* rootFrom);

    void placeNode(Node*& n, const T& element);

    int getHeight(Node* node);

    void insert(const T& element, Node*& node);

    void llRotation(Node*& node);

    void rrRotation(Node*& node);

    void lrRotation(Node*& node);

    void rlRotation(Node*& node);
};


template <typename T>
AVLSet<T>::AVLSet()
{
    used = 0;
    root = nullptr;
}


template <typename T>
AVLSet<T>::~AVLSet()
{
    // std::cout << "DELETING bst\n";
    destroyTree(root);
    // std::cout << "DELETED bst\n";
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
    used = s.used;
    copyTree(root, s.root);
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
{
    Node* oldTree;
    copyTree(oldTree, s.root);
    destroyTree(root);
    root = oldTree;
    return *this;
}


template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
    if (contains(element))
        return;
    // placeNode(root, element);
    insert(element, root);
    used++;
}


template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
    return checkContains(root, element);
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return used;
}

template <typename T>
unsigned int AVLSet<T>::height()
{
    return getHeight(root);
}


template <typename T>
void AVLSet<T>::destroyTree(Node* node)
{
    if (node == nullptr)
        return;
    destroyTree(node -> left);
    destroyTree(node -> right);
    if (node != nullptr)
        delete node;
}


template <typename T>
bool AVLSet<T>::checkContains(const Node* current, const T& element) const
{
    if (current == nullptr)
        return false;
    if (current -> key == element)
        return true;
    return checkContains(current -> left, element) or checkContains(current -> right, element);
}


template <typename T>
void AVLSet<T>::copyTree(Node*& rootTo, Node* rootFrom)
{
    if (rootFrom == nullptr)
        return;
    rootTo = new Node(rootFrom -> key);
    copyTree(rootTo -> left, rootFrom -> left);
    copyTree(rootTo -> right, rootFrom -> right);
}


template <typename T>
void AVLSet<T>::placeNode(Node*& n, const T& element)
{
    if (n == nullptr)
        n = new Node(element);
    else if (element < n -> key)
        placeNode(n -> left, element);
    else
        placeNode(n -> right, element);
}


template <typename T>
int AVLSet<T>::getHeight(Node* node)
{
    if (node == nullptr)
        return 0;

    int leftHeight = 1 + getHeight(node -> left);
    int rightHeight = 1 + getHeight(node -> right);
    if (leftHeight > rightHeight)
        return leftHeight;
    else
        return rightHeight;
}


template <typename T>
void AVLSet<T>::insert(const T& element, Node*& node)
{
    if (node == nullptr) {
        node = new Node(element);
        return;
    }

    if (element < node -> key) {
        insert(element, node -> left);

        int heightDifference = getHeight(node -> left) - getHeight(node -> right);
        // std::cout << "Height diff is " << heightDifference << "\n";

        if (heightDifference >= 2) {
            if (element < node -> left -> key)
                llRotation(node);
            else
                lrRotation(node);
        }
    }

    else if (node -> key < element) {
        insert(element, node -> right);

        int heightDifference = getHeight(node->right) - getHeight(node->left);
        if (heightDifference >= 2) {
            if (node -> right -> key < element)
                rrRotation(node);
            else
                rlRotation(node);
        }
    }
}

///////////////////////////////
///////// ROTATIONS ///////////
///////////////////////////////


template <typename T>
void AVLSet<T>::llRotation(Node*& node)
{
    Node* temp = node -> left;
    node -> left = temp -> right;
    temp -> right = node;
    node = temp;
}


template <typename T>
void AVLSet<T>::rrRotation(Node*& node)
{
    Node* temp = node -> right;
    node -> right = temp -> left;
    temp -> left = node;
    node = temp;
}


template <typename T>
void AVLSet<T>::lrRotation(Node*& node)
{
    rrRotation(node -> left);
    llRotation(node);

    // llRotation(node -> right);
    // rrRotation(node);
}


template <typename T>
void AVLSet<T>::rlRotation(Node*& node)
{
    llRotation(node -> right);
    rrRotation(node);

    // rrRotation(node -> left);
    // llRotation(node);
}


#endif // AVLSET_HPP

