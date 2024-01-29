#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <QVector>

namespace my_vector {


    template<class T>
    class vector {
    private:
        T* arr_;
        size_t size_;
        size_t capacity_;

        // Увеличить вместимость x2
        void AddMemory() {
            capacity_ *= 2;
            T* del = arr_;

            arr_ = new T[capacity_];
            for (size_t i = 0; i < size_; i++)
                arr_[i] = del[i];

            delete[] del;
        }

    public:

        // Итератор
        class iterator
        {
        private:
            T* ptr_;
            friend vector<T>;
        public:

            iterator() : ptr_(nullptr) { }

            iterator(T* ptr) : ptr_(ptr) { }

            iterator(const vector<T>::iterator& other) : ptr_(other.ptr_) { }

            iterator& operator++() {
                if (!ptr_)
                    throw(std::exception());

                ++ptr_;
                return *this;
            }

            iterator& operator--() {
                if (!ptr_)
                    throw(std::exception());

                --ptr_;
                return *this;
            }

            iterator& operator+(int n) {
                if (!ptr_)
                    throw(std::exception());

                ptr_ += n;
                return *this;
            }

            iterator& operator-(int n) {
                if (!ptr_)
                    throw(std::exception());

                ptr_ -= n;
                return *this;
            }

            T& operator*() const {
                if (!ptr_)
                    throw(std::exception());

                return *ptr_;
            }

            iterator& operator=(const iterator& other) {
                ptr_ = other.ptr_;
                return *this;
            }

            bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }

            bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
        };

        // Итератор на начало
        iterator begin() {
            return iterator(arr_);
        }

        // Итератор на конец
        iterator end() {
            return iterator(arr_ + size_);
        }





        // Константный итератор
        class const_iterator
        {
        private:
            T* ptr_;
            friend vector<T>;
        public:

            const_iterator() : ptr_(nullptr) { }

            const_iterator(T* ptr) : ptr_(ptr) { }

            const_iterator(const vector<T>::const_iterator& other) : ptr_(other.ptr_) { }

            const_iterator(const vector<T>::iterator& other) : ptr_(other.ptr_) { }

            const_iterator& operator++() {
                if (!ptr_)
                    throw(std::exception());

                ++ptr_;
                return *this;
            }

            const_iterator& operator--() {
                if (!ptr_)
                    throw(std::exception());

                --ptr_;
                return *this;
            }

            const_iterator& operator+(int n) {
                if (!ptr_)
                    throw(std::exception());

                ptr_ += n;
                return *this;
            }

            const_iterator& operator-(int n) {
                if (!ptr_)
                    throw(std::exception());

                ptr_ -= n;
                return *this;
            }

            T operator*() const {
                if (!ptr_)
                    throw(std::exception());

                return *ptr_;
            }

            const_iterator& operator=(const const_iterator& other) {
                ptr_ = other.ptr_;
                return *this;
            }

            const_iterator& operator=(const iterator& other) {
                ptr_ = other.ptr_;
                return *this;
            }

            bool operator==(const const_iterator& other) const { return ptr_ == other.ptr_; }

            bool operator!=(const const_iterator& other) const { return ptr_ != other.ptr_; }
        };

        // Константный итератор на начало
        const_iterator cbegin() const {
            return const_iterator(arr_);
        }

        const_iterator begin() const {
            return const_iterator(arr_);
        }

        // Константный итератор на конец
        const_iterator cend() const {
            return const_iterator(arr_ + size_);
        }

        const_iterator end() const {
            return const_iterator(arr_ + size_);
        }





        // Реверсивный итератор
        class reverse_iterator
        {
        private:
            T* ptr_;
            friend vector<T>;
        public:

            reverse_iterator() : ptr_(nullptr) { }

            reverse_iterator(T* ptr) : ptr_(ptr) { }

            reverse_iterator(const vector<T>::reverse_iterator& other) : ptr_(other.ptr_) { }

            reverse_iterator& operator++() {
                if (!ptr_)
                    throw(std::exception());

                --ptr_;
                return *this;
            }

            reverse_iterator& operator--() {
                if (!ptr_)
                    throw(std::exception());

                ++ptr_;
                return *this;
            }

            reverse_iterator& operator+(int n) {
                if (!ptr_)
                    throw(std::exception());

                ptr_ -= n;
                return *this;
            }

            reverse_iterator& operator-(int n) {
                if (!ptr_)
                    throw(std::exception());

                ptr_ += n;
                return *this;
            }

            T& operator*() const {
                if (!ptr_)
                    throw(std::exception());

                return *ptr_;
            }

            reverse_iterator& operator=(const iterator& other) {
                ptr_ = other.ptr_;
                return *this;
            }

            bool operator==(const reverse_iterator& other) const { return ptr_ == other.ptr_; }

            bool operator!=(const reverse_iterator& other) const { return ptr_ != other.ptr_; }
        };

        // Реверсиный итератор на начало
        reverse_iterator rbegin() {
            return reverse_iterator(arr_ + size_ - 1);
        }

        // Реверсивный тератор на конец
        reverse_iterator rend() {
            return reverse_iterator(arr_ - 1);
        }





        // Константный реверсивный итератор
        class const_reverse_iterator
        {
        private:
            T* ptr_;
            friend vector<T>;
        public:

            const_reverse_iterator() : ptr_(nullptr) { }

            const_reverse_iterator(T* ptr) : ptr_(ptr) { }

            const_reverse_iterator(const vector<T>::const_reverse_iterator& other) : ptr_(other.ptr_) { }

            const_reverse_iterator(const vector<T>::reverse_iterator& other) : ptr_(other.ptr_) { }

            const_reverse_iterator& operator++() {
                if (!ptr_)
                    throw(std::exception());

                --ptr_;
                return *this;
            }

            const_reverse_iterator& operator--() {
                if (!ptr_)
                    throw(std::exception());

                ++ptr_;
                return *this;
            }

            const_reverse_iterator& operator+(int n) {
                if (!ptr_)
                    throw(std::exception());

                ptr_ -= n;
                return *this;
            }

            const_reverse_iterator& operator-(int n) {
                if (!ptr_)
                    throw(std::exception());

                ptr_ += n;
                return *this;
            }

            T operator*() const {
                if (!ptr_)
                    throw(std::exception());

                return *ptr_;
            }

            const_reverse_iterator& operator=(const const_reverse_iterator& other) {
                ptr_ = other.ptr_;
                return *this;
            }

            const_reverse_iterator& operator=(const iterator& other) {
                ptr_ = other.ptr_;
                return *this;
            }

            bool operator==(const const_reverse_iterator& other) const { return ptr_ == other.ptr_; }

            bool operator!=(const const_reverse_iterator& other) const { return ptr_ != other.ptr_; }
        };

        // Константный реверсиный итератор на начало
        const_reverse_iterator сrbegin() const {
            return const_reverse_iterator(arr_ + size_ - 1);
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(arr_ + size_ - 1);
        }

        // Константный реверсивный тератор на конец
        const_reverse_iterator crend() const {
            return const_reverse_iterator(arr_ - 1);
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(arr_ - 1);
        }





        // Стандартный конструктор
        vector() {
            arr_ = new T[1];
            capacity_ = 1;
            size_ = 0;
        }

        // Конструктор с размером
        vector(size_t size) {
            arr_ = new T[size];
            capacity_ = size;
            size_ = size;
        }

        // Конструктор для { ... }
        vector(const std::initializer_list<T>& list) {
            size_ = list.size();
            capacity_ = size_;

            arr_ = new T[size_];

            int i = 0;
            for (const auto& element : list)
                arr_[i++] = element;
        }

        // Конструктор копии
        vector(const vector<T>& other) :
            size_(other.size_), capacity_(other.capacity_) {

            if (this == &other)
                return;

            arr_ = new T[capacity_];

            for (size_t i = 0; i < size_; i++)
                arr_[i] = other.arr_[i];
        }

        // Конструктор для move
        vector(vector<T>&& other) :
            size_(other.size_), capacity_(other.capacity_) {

            if (this == &other)
                return;

            delete[] arr_;
            arr_ = other.arr_;

            other.arr_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

        // Конструктор для QVector
        vector(const QVector<T>& other) {
            for (auto item : other)
                push_back(item.c_str());
        }
        // Деструктор
        ~vector() {
            delete[] arr_;
        }

        // Копирующий оператор присваивания
        vector& operator=(const vector<T>& other) {

            if (this == &other)
                return *this;

            size_ = other.size_;
            capacity_ = other.capacity_;

            delete[] arr_;
            arr_ = new T[capacity_];

            for (size_t i = 0; i < size_; i++)
                arr_[i] = other.arr_[i];

            return *this;
        }

        // Оператор присваивания для move
        vector& operator=(vector<T>&& other) {

            if (this == &other)
                return *this;

            size_ = other.size_;
            capacity_ = other.capacity_;

            delete[] arr_;
            arr_ = other.arr_;

            other.arr_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;

            return *this;
        }

        // Оператор присваивания для { ... }
        vector& operator=(const std::initializer_list<T>& list) {
            clear();

            for (const auto& element : list)
                push_back(element);

            return *this;
        }

        // Пустой ли вектор
        bool empty() const {
            return size_ == 0;
        }

        // Размер вектора
        size_t size() const {
            return size_;
        }

        // Вместимость вектора
        size_t capacity() const {
            return capacity_;
        }

        // Максимальный размер вектора
        size_t max_size() const {
            return SIZE_MAX / sizeof(T);
        }

        // Добавить в конец
        void push_back(const T& value) {

            if (size_ >= capacity_)
                AddMemory();

            arr_[size_++] = value;
        }

        // Удалить с конца
        void pop_back() {
            if (!size_)
                throw(std::out_of_range(""));

            --size_;
        }

        // Оператор [] const
        T operator[](const size_t& index) const {
            return arr_[index];
        }

        // Оператор []
        T& operator[](const size_t& index) {
            return arr_[index];
        }

        // Доступ к элементу с проверкой границы const
        T at(size_t index) const {
            if (!(index < size_) || index < 0)
                throw std::out_of_range("");

            return arr_[index];
        }

        // Доступ к элементу с проверкой границы
        T& at(size_t index) {
            if (!(index < size_) || index < 0)
                throw std::out_of_range("");

            return arr_[index];
        }

        // Первый элемент
        T& front() const {
            return *arr_;
        }

        // Последний элемент
        T& back() const {
            return *(arr_ + size_ - 1);
        }

        // Очистить элементы вектора
        void clear() {
            delete[] arr_;
            arr_ = new T[capacity_];
            size_ = 0;
        }

        // Указатель на первый элемент
        T* data() const {
            return !size_ ? nullptr : arr_;
        }

        // Резервировать минимальную длину
        void reserve(size_t new_cap) {
            if (new_cap > capacity_) {
                T* del = arr_;
                capacity_ = new_cap;
                arr_ = new T[capacity_];

                for (size_t i = 0; i < size_; i++)
                    arr_[i] = del[i];

                delete[] del;
            }
        }

        // Изменить размер вектора
        void resize(size_t new_size) {
            if (new_size > size_) {
                T* del = arr_;
                arr_ = new T[new_size];

                for (size_t i = 0; i < size_; i++)
                    arr_[i] = del[i];

                size_ = new_size;
                delete[] del;
            }
            else {
                size_ = new_size;
            }
        }

        // Изменить размер вектора и заполнить
        void resize(size_t new_size, const T& value) {
            if (new_size > size_) {
                T* del = arr_;
                arr_ = new T[new_size];

                for (size_t i = 0; i < size_; i++)
                    arr_[i] = del[i];

                for (size_t i = size_; i < new_size; i++)
                    arr_[i] = value;

                size_ = new_size;
                delete[] del;
            }
            else {
                size_ = new_size;
            }
        }

        // Обменять вектора
        void swap(vector<T>& other) {
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
            std::swap(arr_, other.arr_);
        }

        // Удалить и заполнить вектор
        void assign(size_t new_size, const T& value) {
            delete[] arr_;
            size_ = new_size;
            capacity_ = new_size;

            arr_ = new T[size_];
            for (int i = 0; i < size_; i++)
                arr_[i] = value;
        }

        // Удалить и заполнить вектор для { ... }
        void assign(const std::initializer_list<T>& list) {
            size_ = list.size();
            capacity_ = size_;

            delete[] arr_;
            arr_ = new T[size_];

            int i = 0;
            for (const auto& element : list)
                arr_[i++] = element;
        }

        // Вставить n val'ов
        vector<T>::iterator insert(vector<T>::const_iterator it, const size_t count, const T& value) {

            T* del = arr_;
            arr_ = new T[size_ + count];

            size_t pos = it.ptr_ - del;
            for (size_t i = 0; i < pos; i++)
                arr_[i] = del[i];

            size_t new_pos = pos + count;
            for (size_t i = pos; i < new_pos; i++)
                arr_[i] = value;

            for (size_t i = new_pos; i < size_ + count; i++)
                arr_[i] = del[pos++];

            size_ = size_ + count;
            capacity_ = size_;

            delete[] del;

            return iterator(arr_);
        }

        // Вставить { ... }
        vector<T>::iterator insert(vector<T>::const_iterator it, const std::initializer_list<T>& list) {

            size_t count = list.size();
            T* del = arr_;
            arr_ = new T[size_ + count];

            size_t pos = it.ptr_ - del;
            for (size_t i = 0; i < pos; i++)
                arr_[i] = del[i];

            size_t new_pos = pos + count;
            size_t i = pos;
            for (const auto& element : list)
                arr_[i++] = element;

            for (size_t i = new_pos; i < size_ + count; i++)
                arr_[i] = del[pos++];

            size_ = size_ + count;
            capacity_ = size_;

            delete[] del;

            return iterator(arr_);
        }

        // Вставить величину
        vector<T>::iterator insert(vector<T>::const_iterator it, const T& value) {

            size_t old_size = size_;
            size_t pos = it.ptr_ - arr_;

            if (size_ >= capacity_)
                AddMemory();

            for (size_t i = old_size; i > pos; i--)
                arr_[i] = arr_[i - 1];

            arr_[pos] = value;
            ++size_;

            return iterator(arr_);
        }

        // Удалить элемент
        vector<T>::iterator erase(vector<T>::const_iterator it) {

            size_t pos = it.ptr_ - arr_;

            for (size_t i = pos; i < size_ - 1; i++)
                arr_[i] = arr_[i + 1];

            --size_;

            return iterator(arr_);
        }

        // Удалить элементы
        vector<T>::iterator erase(vector<T>::const_iterator it1, vector<T>::const_iterator it2) {

            size_t pos1 = it1.ptr_ - arr_;
            size_t pos2 = it2.ptr_ - arr_;
            size_t count = pos2 - pos1 + 1;

            for (size_t n = 0; n < count; n++) {
                for (size_t i = pos1; i < size_ - 1; i++)
                    arr_[i] = arr_[i + 1];
            }

            size_ -= count;

            return iterator(arr_);
        }

        // Создать на месте и вставить
        template<class... Args>
        vector<T>::iterator emplace(vector<T>::const_iterator it, Args&&... args) {
            insert(it, T(args...));
            return iterator(arr_);
        }

        // Создать на месте и вставить в конец
        template<class... Args>
        vector<T>::iterator emplace_back(Args&&... args) {
            //push_back(T(std::forward<Args>(args)...));
            push_back(T(args...));
            return iterator(arr_);
        }

        // Вывод вектора в поток
        template<class U>
        friend std::ostream& operator<<(const std::ostream& stream, const vector<T>& v);


    };

    // Вывод вектора в поток
    template<class T>
    std::ostream& operator<<(std::ostream& stream, const vector<T>& v) {

        size_t size = v.size();

        for (size_t i = 0; i < size; i++)
            stream << v[i] << " ";

        return stream;
    }

}
#endif
