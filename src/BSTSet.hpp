// BSTSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include <sstream>
#include "Set.hpp"



template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;

    std::string toString();

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

    std::string stringTree(Node* node, std::string s);

};


template <typename T>
BSTSet<T>::BSTSet()
{
    used = 0;
    root = nullptr;
}


template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
{
    used = s.used;
    copyTree(root, s.root);
}


template <typename T>
BSTSet<T>::~BSTSet()
{
    // std::cout << "DELETING bst\n";
    destroyTree(root);
    // std::cout << "DELETED bst\n";
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
    Node* oldTree;
    copyTree(oldTree, s.root);
    destroyTree(root);
    root = oldTree;
    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element)
{
    if (contains(element))
        return;
    placeNode(root, element);
    used++;
}


template <typename T>
bool BSTSet<T>::contains(const T& element) const
{
    return checkContains(root, element);
}


template <typename T>
unsigned int BSTSet<T>::size() const
{
    return used;
}

template <typename T>
void BSTSet<T>::destroyTree(Node* node)
{
    // std::cout << " destroying tree\n";
    if (node == nullptr) {
        // std::cout << " .. is null ptr (end)\n";
        return;
    }
    // std::cout << " has key " << node -> key << "\n";
    // std::cout << " destroying left\n";
    destroyTree(node -> left);
    // std::cout << " destroying right\n";
    destroyTree(node -> right);
    // std::cout << " left right destroyed\n";
    if (node != nullptr) {
        // std::cout << " deleting node\n";
        delete node;
        // std::cout << " deleted node\n";
    }
    // std::cout<<"all destroyed\n";
}


template <typename T>
bool BSTSet<T>::checkContains(const Node* current, const T& element) const
{
    if (current == nullptr)
        return false;
    if (current -> key == element)
        return true;
    return checkContains(current -> left, element) or checkContains(current -> right, element);
}


template <typename T>
void BSTSet<T>::copyTree(Node*& rootTo, Node* rootFrom)
{
    // std::cout << " copying tree\n";
    if (rootFrom == nullptr) {
        // std::cout << " .. origin is null ptr (end)\n";
        return;
    }
    // std::cout << "copying node with " << rootFrom -> key << "\n";
    rootTo = new Node(rootFrom -> key);
    // std::cout << "node copied with " << rootFrom -> key << "\n";

    // std::cout << "copying left tree of " << rootTo -> key << "\n";
    copyTree(rootTo -> left, rootFrom -> left);
    // std::cout << "copying right tree of " << rootTo -> key << "\n";
    copyTree(rootTo -> right, rootFrom -> right);
    // std::cout << "copied both trees of " << rootTo -> key << "\n";
}


template <typename T>
void BSTSet<T>::placeNode(Node*& n, const T& element)
{
    if (n == nullptr) {
        // std::cout << "inserting new node " << element << "\n";
        n = new Node(element);
    }
    else if (element < n -> key) {
        // std::cout << "shifting left\n";
        placeNode(n -> left, element);
    }
    else {
        // std::cout << "shifting right\n";
        placeNode(n -> right, element);
    }
}


template <typename T>
std::string BSTSet<T>::stringTree(Node* node, std::string s)
{
    if (node == nullptr) {
        s += "[] ";
        return s;
    }
    std::string childs = "";
    s += stringTree(node -> left, childs);
    s += "["; s += std::to_string(node -> key); s += "] ";
    s += stringTree(node -> right, childs);
    return s;
}


template <typename T>
std::string BSTSet<T>::toString()
{
    std::string s;
    return stringTree(root, s);
}

#endif // BSTSET_HPP