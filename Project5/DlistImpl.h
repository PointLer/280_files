#ifndef DLISTIMPL_H
#define DLISTIMPL_H

#include <iostream>
#include "Dlist.h"
using namespace std;

template <class T>
bool Dlist<T>::isEmpty() const{
    return (!first && !last);
}

template <class T>
void Dlist<T>::insertFront(T *op){
    node *new_node = new node;
    new_node->op = op;
    if(isEmpty()){
        new_node->prev = nullptr;
        new_node->next = nullptr;
        first = new_node;
        last = new_node;
    }
    else{
        new_node->prev = nullptr;
        new_node->next = first;
        first->prev = new_node;
        first = new_node;
    }
}

template <class T>
void Dlist<T>::insertBack(T *op){
    node *new_node = new node;
    new_node->op = op;
    if(isEmpty()){
        new_node->prev = nullptr;
        new_node->next = nullptr;
        first = new_node;
        last = new_node;
    }
    else{
        new_node->prev = last;
        new_node->next = nullptr;
        last->next = new_node;
        last = new_node;
    }
}

template <class T>
T* Dlist<T>::removeFront()
{
    if (isEmpty()){
        EmptyList err;
        throw err;
    }
    node *victim = first;
    T* val = victim->op;
    if(first == last){
        first = nullptr;
        last = nullptr;
    }
    else{
        first = first->next;
        first->prev = nullptr;//
    }
    delete victim;
    return val;
}

template <class T>
T* Dlist<T>::removeBack()
{
    if (isEmpty()){
        EmptyList err;
        throw err;
    }
    node *victim = last;
    T* val = victim->op;
    if(first == last){
        first = nullptr;
        last = nullptr;
    }
    else{
        last = last->prev;
        last->next = nullptr;
    }
    delete victim;
    return val;
}

template <class T>
void Dlist<T>::removeAll(){
    while(!isEmpty()){
        T* to_remove = removeBack();
        delete to_remove;
    }
}

template <class T>
void Dlist<T>::copyAll(const Dlist<T> &l){
    removeAll();
    if(l.isEmpty()) return;
    node *temp = l.first;
    while(temp){
        T *new_op = new T(*temp->op);
        insertBack(new_op);
        temp = temp->next;
    }
}

template <class T>
Dlist<T>::Dlist():first(nullptr), last(nullptr){}

template <class T>
Dlist<T>::Dlist(const Dlist<T> &l):first(nullptr), last(nullptr){
    copyAll(l);
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist<T> &l){
    if(this != &l){
        copyAll(l);
    }
    return *this;
}

template <class T>
Dlist<T>::~Dlist(){
    removeAll();
}

#endif //DLISTIMPL_H