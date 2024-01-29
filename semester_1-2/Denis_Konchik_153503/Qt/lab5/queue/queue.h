#ifndef QUEUE_H
#define QUEUE_H
#include <QDebug>
#include <iostream>
#include "shared_ptr.h"
using namespace p;

template<class T>
class queue {
private:

    struct Node {
        shared_ptr<Node> prev;
        T data;
    };

    shared_ptr<Node> head;
    Node* tail;

    int size_;

public:

    queue() {
        head = nullptr;
        tail = nullptr;
        size_ = 0;
    }

    ~queue() {
        clear();
    }
    void push(T data) {

        shared_ptr<Node> new_node = make_shared(new Node);
        new_node->data = data;
        new_node->prev = nullptr;

        if (size_ == 0) {
            head = new_node;
            tail = new_node;
        }
        else {
            tail->prev = new_node;
            tail = new_node;
        }

        ++size_;
    }

    T& front() {

        if (!size_)
            throw(std::exception());
        else
            return head->data;
    }

    T& back() {
        if (!size_)
            throw(std::exception());
        else
            return tail->data;

    }

    void pop() {

        if (!size_)
            throw(std::exception());
        else {
            head = std::move(head->prev);
        }

        --size_;
    }

    bool empty() {
        return !size_;
    }

    void clear() {
        while(size_)
            pop();

    }

    int size() {
        return size_;
    }
};
#endif // QUEUE_H
