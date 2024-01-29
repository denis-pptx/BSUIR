#ifndef HASH_H
#define HASH_H

#include "stack.h"
#include <cmath>

class HashTable {
protected:
    stack<int>* arr_;
    int arr_size_;
    int size_;

    const double V = 0.618033;

    int getHash(int key) {
        //return abs(value % arr_size_);

        double temp = key * V;
        temp = fabs(temp - (int)temp);
        return (int)(arr_size_ * temp);
    }

public:
    HashTable(int arr_size) {
        arr_size_ = arr_size;
        arr_ = new stack<int>[arr_size_];
        size_ = 0;
    }

    ~HashTable() {
        clear();
        delete[] arr_;
    }

    void clear() {
        for (int i = 0; i < arr_size_; i++)
            arr_[i].clear();

        size_ = 0;
    }

    void push(int key) {

        int hash = getHash(key);

        stack<int> tmp = arr_[hash];

        while (!tmp.empty() && tmp.top() != key)
            tmp.pop();

        if (tmp.empty()) {
            arr_[hash].push(key);
            ++size_;
        }


    }

    void pop(int key) {
        int hash = getHash(key);

        if (arr_[hash].empty())
            return;

        stack<int> tmp;

        while (!arr_[hash].empty() && arr_[hash].top() != key) {
            tmp.push(arr_[hash].top());
            arr_[hash].pop();
        }

        if (!arr_[hash].empty()) {
            arr_[hash].pop();
            --size_;
        }

        while (!tmp.empty()) {
            arr_[hash].push(tmp.top());
            tmp.pop();
        }
    }

    bool contains(int key) {
        int hash = getHash(key);

        stack<int> tmp = arr_[hash];

        while (!tmp.empty() && tmp.top() != key)
            tmp.pop();

        if (tmp.empty())
            return false;
        else
            return true;
    }


};

class HashTableMod : public HashTable {
public:
    stack<int>* get_arr() {
        return arr_;
    }

    int get_size() {
        return size_;
    }

    int get_arr_size() {
        return arr_size_;
    }

    int get_max() {

        int max = INT_MIN;

        for (int i = 0; i < arr_size_; i++) {
            stack<int> tmp = arr_[i];

            while (!tmp.empty()) {
                max = tmp.top() > max ? tmp.top() : max;
                tmp.pop();
            }
        }

        return max;
    }

    HashTableMod(int size) : HashTable(size) {

    }
};

#endif // HASH_H
