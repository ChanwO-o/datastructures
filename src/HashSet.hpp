// HashSet.hpp

// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun

// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.

// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.

// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include <sstream>
#include <string>
#include "Set.hpp"



template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;

    bool needsRehashing();

    void destroyAll();

    std::string toString();


private:

    struct Node
    {
        T key;
        Node* next = nullptr;

        Node() {}
        Node(T ky, Node* nxt = nullptr) : key{ky}, next{nxt} {}
    };

    int capacity;
    int used;
    HashFunction hashFunction;
    Node* buckets;
    // Node** buckets = new Node*[30]


    void rehash();

    void copyLinkList(Node& copyTo, const Node& copyFrom);

    void deleteList(Node* startingNode);
};


template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
    capacity = DEFAULT_CAPACITY;
    used = 0;
    buckets = new Node[capacity];
}


template <typename T>
HashSet<T>::~HashSet()
{
    // std::cout << "DELETING hashset\n";
    destroyAll();
    // std::cout << "DELETed hashset\n";
}


template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{s.hashFunction}
{
    // std::cout << "copy const\n";
    capacity = s.capacity;
    buckets = new Node[capacity];
    for (int i = 0; i < capacity; ++i)
        copyLinkList(buckets[i], s.buckets[i]);
    used = s.used;
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    // std::cout << "assignment\n";
    if (this != &s)
    {
        hashFunction = s.hashFunction;
        destroyAll();
        capacity = s.capacity;
        buckets = new Node[capacity];
        for (int i = 0; i < capacity; ++i)
            copyLinkList(buckets[i], s.buckets[i]);
        used = s.used;
    }

    return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void HashSet<T>::add(const T& element)
{
    if (contains(element)) {
        // std::cout << "already contains\n";
        return;
    }
    if (needsRehashing()) {
        // std::cout << "extending array\n";
        rehash();
    }
    
    int index = hashFunction(element) % capacity;
    // std::cout << "hashed index is " << index << "\n";
    Node* temp = buckets[index].next;           
    Node* newNode = new Node(element, temp);
    buckets[index].next = newNode;
    ++used;
    // std::cout << "inserted " << element << " at index " << index << "\n";
    // std::cout << "new used & cap is " << used << " " << capacity << "\n";
}


template <typename T>
bool HashSet<T>::contains(const T& element) const
{
    int index = hashFunction(element) % capacity;
    Node* current = buckets[index].next;
    while (current != nullptr) {
        if (current -> key == element)
            return true;
        current = current -> next;
    }
    return false;
}


template <typename T>
unsigned int HashSet<T>::size() const
{
    return used;
}

template <typename T>
bool HashSet<T>::needsRehashing()
{
    double d = static_cast<double>(used) / capacity;
    // std::cout << "d is " << d << "\n";
    return (d) > 0.8;
}

template <typename T>
void HashSet<T>::rehash()
{
    int oldCap = capacity;
    capacity = 2 * capacity;
    Node* newBuckets = new Node[capacity];

    for (int i = 0; i < oldCap; ++i) {
        Node* toRehash = buckets[i].next;
        while (toRehash != nullptr) {
            // std::cout << "rehashing " << toRehash -> key << "\n";
            int newIndex = hashFunction(toRehash -> key) % capacity;
            // std::cout << "newIndex is " << newIndex << "\n";

            Node* temp = newBuckets[newIndex].next;
            Node* rehashed = new Node(toRehash -> key, temp);
            newBuckets[newIndex].next = rehashed;
            toRehash = toRehash -> next;
        }
    }

    for (int i = 0; i < oldCap; ++i)
        deleteList(buckets[i].next);
    delete[] buckets;
    buckets = newBuckets;
}

template <typename T>
void HashSet<T>::copyLinkList(Node& copyTo, const Node& copyFrom) // refers to the buckets (the array cells)
{
    Node* currentTo = copyTo.next;
    Node* currentFrom = copyFrom.next;

    while (currentFrom != nullptr) {
        currentTo -> key = currentFrom -> key;
        currentTo = currentTo -> next;
        currentFrom = currentFrom -> next;
    }
}

template<typename T>
void HashSet<T>::deleteList(Node* startingNode)
{
    while (startingNode != nullptr) {
        // std::cout << "deleting single node " << startingNode -> key << "\n";
        Node* toDelete = startingNode;
        startingNode = startingNode -> next;
        delete toDelete;
    }
}

template <typename T>
void HashSet<T>::destroyAll()
{
    for (int i = 0; i < capacity; ++i) {
        // std::cout << "deleting list at " << i << "\n";
        deleteList(buckets[i].next);
    }
    delete[] buckets;
    buckets = nullptr;
}

template <typename T>
std::string HashSet<T>::toString()
{
    std::string s;
    Node* current;

    for (int i = 0; i < capacity; ++i) {
        s += "[";
        current = buckets[i].next;
        while (current != nullptr) {
            // std::cout << "key is " << current -> key << "\n";

            std::stringstream stream;
            stream << current -> key << " ";
            s += stream.str();
            
            current = current -> next;
        }
        s += "] ";
    }
    return s;
}


#endif // HASHSET_HPP
