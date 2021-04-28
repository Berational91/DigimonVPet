#include "SimpleLinkedList.h"

template<typename T>
void SimpleLinkedList<T>::getSize() { return size; };

template<typename T>
void SimpleLinkedList<T>::addElement(T data){
    Node newNode = new Node();
    newNode.data = data;
    newNode.next = NULL;

    if(first == NULL){
        first = &newNode;
        last = &newNode;
        size++;
    }else{
        last->next = newNode;
        last = &newNode;
        size++;
    }
    
}

template<typename T>
void SimpleLinkedList<T>::removeFirst() {
    
    if(size > 1){
        Node* temp = first;
        first = first->next;
        delete temp;
        size--;
    }
    if(size==1){
        //if there is just one element then first is last,
        // so both must be null after deletion
        delete first;
        first = NULL;
        last = NULL;
        size--;
    }

 };


template<typename T>
T SimpleLinkedList<T>::getLast(){
    return last->data;
}

template<typename T>
T SimpleLinkedList<T>::getFirst(){
    return first->data;
}

template<typename T>
T SimpleLinkedList<T>::get(int index){

}



template<typename T>
SimpleLinkedList<T>::~SimpleLinkedList(){

}