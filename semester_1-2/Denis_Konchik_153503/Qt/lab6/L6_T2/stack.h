#ifndef STACK_H
#define STACK_H

#include <iostream>

template<class T>
class stack {
private:

    struct Node {
        T data;
        Node* prev;
    };

    Node* upper;
    int count;

public:
    stack() : upper(nullptr), count(0) { }
    ~stack() {
        while (upper)
            pop();
    }

    stack(const stack& other) {

        upper = nullptr;
        count = 0;

        Node* temp = other.upper;

        T* arr = new T[other.count];

        for (int i = 0; i < other.count; i++) {
            arr[i] = temp->data;
            temp = temp->prev;
        }

        for (int i = other.count - 1; i >= 0; i--)
            push(arr[i]);

        delete[] arr;
    }

    stack& operator=(const stack& other) {

        clear();

        Node* temp = other.upper;

        T* arr = new T[other.count];

        for (int i = 0; i < other.count; i++) {
            arr[i] = temp->data;
            temp = temp->prev;
        }

        for (int i = other.count - 1; i >= 0; i--)
            push(arr[i]);

        delete[] arr;

        return *this;
    }

    void clear() {
        while (upper)
            pop();
    }

    void push(T data) {
        Node* temp = new Node;
        temp->data = data;
        temp->prev = upper;
        upper = temp;

        ++count;
    }

    void pop() {
        if (upper == nullptr)
            throw(std::exception());

        if (count > 1) {
            Node* del = upper;
            upper = upper->prev;
            delete del;
        } else {
            delete upper;
            upper = nullptr;
        }

        --count;
    }

    T& top() {
        if (upper == nullptr)
            throw(std::exception());

        return upper->data;
    }

    bool empty() { return !count; }

    bool size() { return count; }
};


#endif
