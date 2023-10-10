//
//  LinkedList.h
//  Linked_List
//
//  Copyright © Tali Moreshet. All rights reserved.
//
//  This is an implementation of an ordered Linked List class, which is made up of Nodes.
//  All classes are templated, such that their types may be provided at creation.
//  Nodes contain data (which doubles as key), and pointers to all directions.

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <cstdlib>
#include <time.h>

#define MMIN -2147483648
#define MMAX 2147483647

using namespace std;

template<class T>
class Node {
public:
    Node(const T& data);                            // constructor
    T data;                                         // node data, doubles as key
    Node<T> *next;                                  // node next pointer
    Node<T> *prev;                                  // node previous pointer
    Node<T> *up;                                    // node above pointer
    Node<T> *down;                                  // node below pointer
    void printData();                               // prints data value
    void print();                                   // prints entire node object content
};

template <class T>
class LinkedList {
public:
    LinkedList(T minVal, T maxVal);                 // constructor: accepts -infinity, +infinity values,
                                                    //  creates linked list with two corresponding nodes
    ~LinkedList();                                  // destructor
    Node<T>* search(Node<T>* location, T data);     // search for data starting at location, return node <= data
    Node<T>* insert(Node<T>* location, T data);     // insert node with data at new node to be placed directly 
                                                    //  after node with povided location, return new node
    void printData();                               // prints linked list data
    void print();                                   // prints linked list with all nodes pointers
    Node<T>* head;                                  // head of list
};

/********************** From here down is the content of the LinkedList.cpp file: ***********************/

/****** Implementation of Node ******/

// Constructor
template<class T>
Node<T>::Node(const T& data)
{
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
    this->up = nullptr;
    this->down = nullptr;
}

// Print node's data value
template <class T>
void Node<T>::printData()
{
    cout << data << " ";
}

// Print entire node object content (data value, object's address, and all pointers)
template <class T>
void Node<T>::print()
{
    cout << " * " << data << ": [addr: " << this << " next: " << this->next << " prev: " << this->prev << " up: " << this->up << " down: " << this->down << "]  ";
}


/****** Implementation of linked list ******/

/*** TO BE COMPLETED ***/
template <class T>
LinkedList<T>::LinkedList(T minVal, T maxVal){
    head = new Node<T>(minVal);

    head->next = new Node<T>(maxVal);
    head->next->prev = head;
}

template<class T>
LinkedList<T>::~LinkedList(){
    Node<T> *iter = head;
    Node<T> *next;
    while(iter != nullptr){
        next = iter->next;
        delete iter;
        iter = next;
    }

}

template<class T>
Node<T>* LinkedList<T>::search(Node<T> *location, T data){
    Node<T> *iter = location;
    while(iter != nullptr){
        if(iter->data == data || (iter->data < data && iter->next->data > data)){
            return iter;
        }
        iter = iter->next;
    }  
    return nullptr;
}

template<class T>
Node<T>* LinkedList<T>::insert(Node<T> *location, T data) {
    Node<T> *iter = new Node(data);
    iter->down = search(location, data);
    if(iter->down != nullptr){
    iter->next = iter->down->next;
    iter->next->prev = iter;
    iter->down->next = iter;
    iter->prev = iter->down;
    iter->down = nullptr;
    return iter;
    }else{
        delete iter;
        return nullptr;
    }
}

//only craete if search doesn't return nullptr
// template<class T>
// Node<T>* LinkedList<T>::insert(Node<T> *location, T data) {
//     Node<T> *iter = search(location, data);
//     if(iter == nullptr){
//         return nullptr;
//     }else {
//         Node<T> *addNode = new Node(data);
//         iter->next = addNode;
//         addNode->next = iter->next;
//         iter->next->prev = addNode;
//         addNode->prev = iter;
//         return addNode;
//     }
// }

template<class T>
void LinkedList<T>::printData(){
    Node<T> *iter = head;
    while(iter != nullptr){
        iter->printData();
        iter = iter->next;
    }
    cout<<endl;
}

template<class T>
void LinkedList<T>::print(){
    Node<T> *iter = head;
    while(iter->next != nullptr){
        iter->print();
        iter = iter->next;
    }
    cout<<endl;
}



#endif /* LinkedList_h */

