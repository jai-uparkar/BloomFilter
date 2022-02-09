#include "HashTable3.h"
#include <iostream>
#include <string>
using namespace std;


HashTable::HashTable(int q){
    this->size = q;
    htable = new Node* [size];
    for (int i = 0; i < size; i++){
      htable[i] = 0;
    }
}
 
HashTable::~HashTable(){
  for (int i = 0; i < size; i++){
    Node* entry = htable[i];
    // deleting each node in the bucket
    while(entry != NULL){
       Node* prev = entry;
       entry = entry->next;
       delete prev;
    }
  }
  delete[] htable; // deleting the table
}
 
void HashTable::insertItem(string key)
{
  unsigned int i = hashFunction(key);
  Node *newNode = new Node(key);

  // insert at head
  if (htable[i] == NULL){
    htable[i] = newNode;
  }
  else{
    Node *next = htable[i]->next;
    htable[i]->next = newNode;
    newNode->next = next;
  }
  
}
 
void HashTable::deleteItem(string key)
{
  unsigned int i = hashFunction(key);
  Node *front = htable[i];
  Node *end = NULL;

  while (front != NULL && front->data != key){
    end = front;
    front = front->next;
  }

  if (front == NULL){
    cout << "List is empty." << endl;
  }

  else {
    if (end == NULL){
      htable[i] = front->next;
    }
    else{
      end->next = front->next;
    }
    delete front;
  }
}

bool HashTable::findItem(string key){
  unsigned int i = hashFunction(key);
  Node *front = htable[i];
  while (front != NULL){
    if(front->data == key){
      return true;
    }
    front = front->next; // go to next node
  }
  return false;
}
 
// function to display hash table
void HashTable::displayHash() {
  for (int i = 0; i < size; i++) {
    cout << i << ": "; // bucket i
    Node *front = htable[i]; // head of list
    while(front != NULL){ // keep going till you reach end of the list
      cout << front->data << " ";
      front = front->next;
    }
    cout << endl;  
  }
  cout << endl;
}

unsigned int HashTable::hashFunction(std::string element){
  // same hash function as in the bloom filter
    unsigned int num = 5381; // start out with large prime number
    for (int i = 0; i < (int) element.length(); i++){
        // bitwise shift operator is faster than multiplying by 33
        num = ((num<<5) + num) + element[i]; 
    }
    return num%size;
}
 