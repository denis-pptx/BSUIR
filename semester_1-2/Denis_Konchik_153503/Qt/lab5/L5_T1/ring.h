#ifndef RING_H
#define RING_H

#include <iostream>
#include "unique_ptr.h"
using namespace p;

template<class T>
class ring
{
private:

    struct Node {
        Node* next = nullptr;
        Node* prev = nullptr;
        T data;
    };

    Node* current = nullptr;
    size_t size_ = 0;

public:
    ring() {};

    ~ring() {

        clear();

    }

    void clear() {


        for (size_t i = 0; i < size_; i++) {
            current = current->next;
            delete current->prev;
        }
        current = nullptr;
        size_ = 0;
    }

    // Вставить после текущего
    void push_next(T data) {

        size_++;

        Node* new_node = new Node;
        new_node->data = data;

        if (!current) {
            current = new_node;
            current->next = current;
            current->prev = current;
            return;
        }

        new_node->next = current->next;
        new_node->prev = current;
        current->next->prev = new_node;
        current->next = new_node;
    }

    // Вставить перед текущим
    void push_prev(T data) {

        size_++;

        Node* new_node = new Node;
        new_node->data = data;

        if (!current) {
            current = new_node;
            current->next = current;
            current->prev = current;
            return;
        }

        new_node->next = current;
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;
    }

    // Удалить текущий (смещение по часовой)
    void pop() {

        if (!current)
            return;

        Node* del = current;

        if (current->next == current) {
            current = nullptr;
        } else {

            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->next;
        }

        delete del;

        size_--;
    }

    // Просмотреть текущий
    T& curr() {
        if (current)
            return current->data;
        else
            throw std::exception();
    }

    // По часовой
    void go_next() {

        if (current)
            current = current->next;
    }

    // Против часовой
    void go_prev() {

        if (current)
            current = current->prev;
    }


    size_t size() {
        return size_;
    }

    bool empty() {
        return !current;
    }


};

#endif // RING_H
