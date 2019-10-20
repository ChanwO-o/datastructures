#include "HashMap.hpp"

using namespace std;

namespace
{
    unsigned int myHashFunction(const string& s) {
        return s.size();
    }
}

// no argument constructor
HashMap::HashMap()
    : hasher{myHashFunction}, nodes{new Node*[initialBucketCount]}, currentBucketSize{initialBucketCount} {
   nullFill(); 
}

// constructor with defined hash function
HashMap::HashMap(HashFunction definedHashFunction)
    : hasher{definedHashFunction}, nodes{new Node*[initialBucketCount]}, currentBucketSize{initialBucketCount} {
    nullFill();
}


// copy constructor
HashMap::HashMap(const HashMap& hm)
    : hasher{hm.hasher}, nodes{new Node*[hm.currentBucketSize]}, currentBucketSize{hm.currentBucketSize}
{
    nullFill();
    
    for (int i = 0; i < currentBucketSize; i++) {
        Node* copyingList = hm.nodes[i];

        if (copyingList != nullptr) 
        {
            nodes[i] = new Node {copyingList -> key, copyingList -> value, nullptr};
            Node* temp = nodes[i];
            copyingList = copyingList -> next;
            
            
            while (copyingList != nullptr) 
            {
                temp -> next = new Node {copyingList -> key, copyingList -> value, nullptr};
                temp = temp -> next;
                copyingList = copyingList -> next;
            }
        }
    }
}

// destructor
HashMap::~HashMap()
{
    for (int i = 0; i < currentBucketSize; i++)
    {
        deleteLinkList(nodes[i]);
    }
    delete[] nodes; 
}


void HashMap::deleteLinkList(Node* node)
{
    if (node == nullptr) {

    }
    else if (node -> next == nullptr) {
        delete node;
    }
    else {
        deleteLinkList(node -> next);
    }
}

// overriding assignment operator
HashMap& HashMap::operator= (const HashMap& hm) {
    
    if (this != &hm) 
    {

        for (int i = 0; i < currentBucketSize; i++) { deleteLinkList(nodes[i]); }
        
        hasher = hm.hasher;
        nodes = new Node* [hm.currentBucketSize];
        
        this -> nullFill();
    
        for (int i = 0; i < currentBucketSize; i++) {
            Node* copyingList = hm.nodes[i];

            if (copyingList != nullptr) {
                nodes[i] = new Node {copyingList -> key, copyingList -> value, nullptr};
                Node* temp = nodes[i];
                copyingList = copyingList -> next;

                while (copyingList != nullptr) {
                    temp -> next = new Node {copyingList -> key, copyingList -> value, nullptr};
                    temp = temp -> next;
                    copyingList = copyingList -> next;
                }
            }
        } 
        currentBucketSize = hm.currentBucketSize;
    }
    return *this;
}

void HashMap::add(const string& key, const string& value)
{
    if (!contains(key))
    {
        addWithoutRehash(key, value);

        if (loadFactor() > 0.8) {
            int newBucketSize = currentBucketSize * 2 + 1;

            Node** oldNodes = nodes;
            nodes = new Node*[newBucketSize];
            //currentBucketSize = newBucketSize;
            
            nullFill();
            
            // add old nodes back to new list
            for (int i = 0; i < currentBucketSize; i++) {
                Node* addBackToNew = oldNodes[i];
                
                while (addBackToNew != nullptr) {
                    addWithoutRehash(addBackToNew -> key, addBackToNew -> value);
                    addBackToNew = addBackToNew -> next;
                }
            }

            // delete old list and nodes
            for (int i = 0; i < currentBucketSize; i++) {
                deleteLinkList(oldNodes[i]);
            }
            delete[] oldNodes;

            // reset bucket size
            currentBucketSize = newBucketSize;
        }
    }
}

void HashMap::addWithoutRehash(const string& key, const string& value) {
    unsigned int index = getIndex(key);
    // 
    if (nodes[index] != nullptr) {
        Node* newNodeLocation = nodes[index];
        if (newNodeLocation -> next == nullptr)
            newNodeLocation -> next = new Node {key, value, nullptr};
        
        else {
            do { newNodeLocation = newNodeLocation -> next; }
            while (newNodeLocation -> next != nullptr);
            newNodeLocation -> next = new Node {key, value, nullptr};
        }
    }
    else
        nodes[index] = new Node {key, value, nullptr};
}

void HashMap::remove(const string& key)
{
    if (contains(key))
    {
        int index = getIndex(key);
//        Node* removeNode = getNode(key, index);
//        deleteLinkList(getNode(key, index));

        //set last node at index 's next to nullptr
        //Node* current = nodes[i];
        //while

        Node* previous = nodes[index];

        Node* check = previous -> next;

        if (key == previous -> key) {
            nodes[index] = check;
            delete previous; // delete
        }
        else {
            while (key != check -> key) {
                previous = check;
                check = previous -> next;
            }
            previous -> next = check -> next;
            delete check; // delete current
        }
    }
}

bool HashMap::contains(const string& key) const
{
    int index = getIndex(key);
    Node* current = nodes[index];
    while (current != nullptr) {
        if (current -> key == key) { return true; }
        current = current -> next;
    }
    return false;
}


string HashMap::value(const string& key) const
{   /*if (contains(key)) {
       int index = getIndx(key);
        Node* current = odes[index];
      if (current -> ke == key) { return current -> value; }
      
       do 
           current = current-> next;
        } wurrent -> ke =ky);
        return current -> value;
    }
    else { return ""; }*/
    
    if (contains(key)) {
        int index = getIndex(key);
        return getNode(key, index) -> value;
    }
    else { return ""; }

}

unsigned int HashMap::size() const
{
    unsigned int size = 0;
    for (int i = 0; i < currentBucketSize; i++) {
        if (nodes[i] == nullptr) { }
        else {
            size += listLength(nodes[i]);
        }
    }
    return size;
}

unsigned int HashMap::bucketCount() const
{
    unsigned int counter = 0;
    for (int i = 0; i < currentBucketSize; i++) {
        if (nodes[i] != nullptr) { counter++; }
    }
    return counter;
}

double HashMap::loadFactor() const
{
//    double castedTotalSize = (double)size();
//    return size() / currentBucketSize;

    return size() / static_cast<double>(currentBucketSize);
}

unsigned int HashMap::maxBucketSize() const
{
    unsigned int max = 0;
    for (int i = 0; i < currentBucketSize; i++) {
        if (max < listLength(nodes[i])) { max = listLength(nodes[i]); }
    }
    return max;
}

void HashMap::nullFill()
{
    for (int i = 0; i < currentBucketSize; i++)
    {
        // deleteLinkList(nodes[i]); // ???????? ans: no, delete is separate.
        nodes[i] = nullptr;
    }
}

int HashMap::modBySize(const int hashResult) const {
    return hashResult % currentBucketSize;
}

int HashMap::getIndex(const string& key) const {
    return modBySize(hasher(key));
}

// precondition: nodes must contain key
HashMap::Node* HashMap::getNode(const string& key, const int index) const {
    Node* current = nodes[index];
    if (current -> key == key) { return current; }
    do {
        current = current -> next;
         if (current -> key == key) { return current; }
    } while (current != nullptr);
}

int HashMap::listLength(const Node* root) const {
    int count = 0;
    if (root == nullptr) { return count; }
    else {
        count++;
        count += listLength(root -> next); // recursion one nodee by one
    }
    return count;
}
