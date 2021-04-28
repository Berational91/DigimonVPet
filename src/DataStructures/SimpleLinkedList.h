#include <Arduino.h>

#ifndef SimpleLinkedList_h
#define SimpleLinkedList_h


template<typename T>

/**
 * Implementation of a simple single-linked list
 * 
 */
class SimpleLinkedList {

private:

    struct Node {
        T data;
        Node* next;
    };

    int8_t size;
    Node* first;
    Node* last;

public:
    void getSize();
    void addElement(T data);
    void removeFirst();
    T getLast();
    T getFirst();
    T get(int index);

    ~SimpleLinkedList();
    
};


#endif