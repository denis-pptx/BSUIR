#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>

template<class T>
class deque {
private:

    T** ptr;
    int arr_length = 10; // Длина одного массива
    int ptr_amount; // Число указателей T*
    int size_; // Элементов в очереди

    int k = 3; // Во сколько раз новый ptr_amount будет больше arr_amount

    int up_arr; // Индекс верхнего массива
    int begin_ = arr_length - 1; // Индекс свободного первого элемента

    int down_arr; // Индекс нижнего массива
    int end_ = 0; // Индекс свободного последнего элемента


    void increase_memory() {
        int arr_amount = down_arr - up_arr + 1;

        T** new_ptr = new T * [arr_amount * k];

        int new_up_arr = (arr_amount * k - (down_arr - up_arr)) / 2;
        int new_down_arr = new_up_arr + (down_arr - up_arr);

        for (int i = 0; i < arr_amount * k; i++) {
          //  new_ptr[i] = new T[arr_length];
            new_ptr[i] = nullptr;
        }

        for (int i = up_arr, j = new_up_arr; i <= down_arr; i++, j++)
            new_ptr[j] = ptr[i];

        delete ptr;

        ptr = new_ptr;
        ptr_amount = arr_amount * k;
        up_arr = new_up_arr;
        down_arr = new_down_arr;
    }

public:

    deque() {
        ptr_amount = 6;
        size_ = 0;

        ptr = new T * [ptr_amount];

        for (int i = 0; i < ptr_amount; i++) {
          //  ptr[i] = new T[arr_length];
            ptr[i] = nullptr;
        }

        up_arr = ptr_amount / 2;
        down_arr = up_arr + 1;

        ptr[up_arr] = new T[arr_length];
        ptr[down_arr] = new T[arr_length];
    }

    ~deque() {
        for (int i = 0; i < ptr_amount; i++)
            delete[] ptr[i];
        delete[] ptr;
    }

    void clear() {
        up_arr = ptr_amount / 2;
        down_arr = up_arr + 1;

        begin_ = arr_length - 1;
        end_ = 0;
        size_ = 0;
    }

    void push_back(T data) {

        if (end_ < arr_length) {
            ptr[down_arr][end_] = data;
            ++end_;
            ++size_;

        }
        else {



            if (down_arr == ptr_amount - 1)
                increase_memory();

            ++down_arr;
            if (!ptr[down_arr])
                ptr[down_arr] = new T[arr_length];

            ptr[down_arr][0] = data;
            end_ = 1;
            ++size_;

        }


    }

    void push_front(T data) {

        if (begin_ >= 0) {
            ptr[up_arr][begin_] = data;
            --begin_;
            ++size_;
        }
        else {

            if (up_arr == 0)
                increase_memory();

            --up_arr;
            if (!ptr[up_arr])
                ptr[up_arr] = new T[arr_length];

            ptr[up_arr][arr_length - 1] = data;
            begin_ = arr_length - 2;
            ++size_;
        }
    }

    void pop_back() {

        if (size_) {
            if (end_ == 0) {
                --down_arr;
                end_ = arr_length - 1;
            }
            else {
                --end_;
            }
            --size_;
        }
        else {
        //    throw(std::exception());
        }
    }

    void pop_front() {
        if (size_) {
            if (begin_ == arr_length - 1) {
                ++up_arr;
                begin_ = 0;
            }
            else {
                ++begin_;
            }
            --size_;
        }
        else {
        //    throw(std::exception());
        }
    }

    T& operator[](int i) {


        int index = begin_ + i + 1;
        int row = index / arr_length;
        int column = index - row * arr_length;

        return ptr[up_arr + row][column];
    }

    int size() {
        return size_;
    }

    T& back() {
        if (size_)
            return operator[](size_ - 1);
        else
            throw (std::exception());
    }

    T& front() {
        if (size_)
            return operator[](0);
        else
            throw (std::exception());
    }

    bool empty() {
        return !size_;
    }







    class iterator {
    private:
        T** ptr;
        int arr_length;

        int row;
        int column;

        int ptr_amount;

        iterator(T** ptr, int ptr_amount, int arr_length, int row, int column) {

            this->arr_length = arr_length;
            this->row = row;
            this->column = column;
            this->ptr_amount = ptr_amount;

            this->ptr = ptr;
            this->ptr = new T*[ptr_amount];
            for (int i = 0; i < ptr_amount; i++)
                this->ptr[i] = ptr[i];

        }

    public:

        iterator() {
            ptr = nullptr;
            arr_length = row = column = ptr_amount = 0;
        }

        iterator(const iterator& other) {

            arr_length = other.arr_length;
            row = other.row;
            column = other.column;
            ptr_amount = other.ptr_amount;

            this->ptr = new T** [ptr_amount];
            for (int i = 0; i < ptr_amount; i++)
                this->ptr[i] = other.ptr[i];
        }

        friend deque;

        ~iterator() {
            delete ptr;
        }

        T& operator*() {
            return ptr[row][column];
        }

        iterator& operator+(int n) {
            int index = column + n;
            int new_row = index / arr_length;
            int new_column = index - new_row * arr_length;

            row += new_row;
            column = new_column;

            return *this;
        }

        iterator& operator-(int n) {
            int index = column - n;
            int new_row = index / arr_length;



            int new_column = index - new_row * arr_length;
            if (new_column < 0) {
                new_row--;
                new_column = index - new_row * arr_length;
            }
            row += new_row;

            column = new_column;

            return *this;
        }

        iterator& operator++() {
            return operator+(1);
        }

        iterator& operator--() {
            return operator-(1);
        }

        iterator& operator=(const iterator& other) {

            arr_length = other.arr_length;
            row = other.row;
            column = other.column;
            ptr_amount = other.ptr_amount;

            T** new_ptr = new T * [ptr_amount];

            for (int i = 0; i < ptr_amount; i++)
                new_ptr[i] = other.ptr[i];

            T** del = ptr;

            ptr = new_ptr;

            delete del;

            return *this;
        }

        iterator& operator+=(int n) {
            *this = *this + n;
            return *this;
        }

        iterator& operator-=(int n) {
            *this = *this - n;
            return *this;
        }

        bool operator==(const iterator& other) {
            return &ptr[row][column] == &(other.ptr[other.row][other.column]);
        }

        bool operator!=(const iterator& other) {
            return !operator==(other);
        }
    };

    iterator begin() {
        int index = begin_ + 0 + 1;
        int row = index / arr_length;
        int column = index - row * arr_length;

        return iterator(ptr, ptr_amount, arr_length, up_arr + row, column);
    }

    iterator end() {
        int index = begin_ + size_ + 1;
        int row = index / arr_length;
        int column = index - row * arr_length;

        return iterator(ptr, ptr_amount, arr_length, up_arr + row, column);
    }



};

#endif // DEQUE_H
