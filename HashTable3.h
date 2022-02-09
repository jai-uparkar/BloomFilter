// HashTable3.h
#ifndef HASHTABLE3_H
#define HASHTABLE3_H

#include <iostream>
#include <string>
using namespace std;

struct Node {
    string data; // string value
    Node* next; // pointer to next node
  
    // default constructor
    Node()
    {
        data = "";
        next = NULL;
    }
    
    Node(string data)
    {
        this->data = data;
        this->next = NULL;
    }
};
 
class HashTable
{
  private: 
    int size;    // size of table
    Node** htable; // double pointer to array

public:
    HashTable(){};  

    // Separate Chaining Hash Table
    // This will be used for your removed elements of the bloom filter.
    // q := the size of the hash table (prime number)
    HashTable(int);

    // destructor
    ~HashTable();

    // Insert a string into the hash table.
    void insertItem(std::string);
 
    // Return true if the element is in the hash table otherwise return false .
    bool findItem(std::string);
 
    // Delete an element from the hash table.
    void deleteItem(std::string);
 
    // hash function to map values to key
    unsigned int hashFunction(std::string);

    // print out the table
    void displayHash();
};
 
#endif