#ifndef STACK_H
#define STACK_H

namespace my_stack {

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

            Node* del = upper;
            upper = upper->prev;
            delete del;

            --count;
        }

        T& top() {
            if (upper == nullptr)
                throw(std::exception());

            return upper->data;
        }

        bool empty() { return upper == nullptr; }

        bool size() { return count; }
    };

}
#endif
