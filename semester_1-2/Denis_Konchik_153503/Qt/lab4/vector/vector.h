#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#define v_it vector<T>::iterator
#define v_cnst_it vector<T>::const_iterator

namespace my_vector {


    template<class T>
    class vector {
    private:
        T* arr_;
        size_t size_;
        size_t capacity_;

        void AddMemory();

    public:

        class iterator
        {
        private:
            T* ptr_;
            friend vector<T>;
        public:

            // CONSTRUCTORS
            iterator();
            iterator(T* ptr);
            iterator(const vector<T>::iterator& other);

            // OPERATORS
            iterator& operator++();
            iterator& operator--();
            iterator& operator+(int n);
            iterator& operator-(int n);
            T& operator*() const;
            iterator& operator=(const vector<T>::iterator& other);
            bool operator==(const vector<T>::iterator& other) const;
            bool operator!=(const vector<T>::iterator& other) const;
        };

        iterator begin();
        iterator end();



        class const_iterator
        {
        private:
            T* ptr_;
            friend vector<T>;
        public:

            // CONSTRUCTORS
            const_iterator();
            const_iterator(T* ptr);
            const_iterator(const vector<T>::const_iterator& other);
            const_iterator(const vector<T>::iterator& other);

            // OPERATORS
            const_iterator& operator++();
            const_iterator& operator--();
            const_iterator& operator+(int n);
            const_iterator& operator-(int n);
            T operator*() const;
            const_iterator& operator=(const const_iterator& other);
            const_iterator& operator=(const iterator& other);
            bool operator==(const const_iterator& other) const;
            bool operator!=(const const_iterator& other) const;
        };

        const_iterator cbegin() const;
        const_iterator begin() const;
        const_iterator cend() const;
        const_iterator end() const;




        /*
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
        */




        // CONSTRUCTORS
        vector();
        vector(size_t size);
        vector(size_t size, T c);
        vector(const std::initializer_list<T>& list);
        vector(const vector<T>& other);
        vector(vector<T>&& other);

        /*
        // Конструктор для QVector
        vector(const QVector<T>& other) {
            for (auto item : other)
                push_back(item.c_str());
        }
        */

        // DESTRUCTOR
        ~vector();

        // OPERATORS
        vector& operator=(const vector<T>& other);
        vector& operator=(vector<T>&& other);
        vector& operator=(const std::initializer_list<T>& list);
        T operator[](const size_t& index) const;
        T& operator[](const size_t& index);

        // METHODS
        bool empty() const;
        size_t size() const;
        size_t capacity() const;
        size_t max_size() const;
        void push_back(const T& value);
        void pop_back();
        T at(size_t index) const;
        T& at(size_t index);
        T& front() const;
        T& back() const;
        void clear();
        T* data() const;
        void reserve(size_t new_cap);
        void resize(size_t new_size);
        void resize(size_t new_size, const T& value);
        void swap(vector<T>& other);
        void assign(size_t new_size, const T& value);
        void assign(const std::initializer_list<T>& list);
        vector<T>::iterator insert(vector<T>::const_iterator it, const size_t count, const T& value);
        vector<T>::iterator insert(vector<T>::const_iterator it, const std::initializer_list<T>& list);
        vector<T>::iterator insert(vector<T>::const_iterator it, const T& value);
        vector<T>::iterator erase(vector<T>::const_iterator it);
        vector<T>::iterator erase(vector<T>::const_iterator it1, vector<T>::const_iterator it2);

        template<class... Args>
        vector<T>::iterator emplace(vector<T>::const_iterator it, Args&&... args);
        template<class... Args>
        vector<T>::iterator emplace_back(Args&&... args);

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


    template<class T>
    void vector<T>::AddMemory() {
        capacity_ *= 2;
        T* del = arr_;

        arr_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++)
            arr_[i] = del[i];

        delete[] del;
    }






    template<class T>
    v_it::iterator()
        : ptr_(nullptr) {
    }

    template<class T>
    v_it::iterator(T* ptr) : ptr_(ptr) { }

    template<class T>
    v_it::iterator(const v_it& other) : ptr_(other.ptr_) { }

    template<class T>
    typename v_it& v_it::operator++() {
        if (!ptr_)
            throw(std::exception());

        ++ptr_;
        return *this;
    }

    template<class T>
    typename v_it& v_it::operator--() {
        if (!ptr_)
            throw(std::exception());

        --ptr_;
        return *this;
    }

    template<class T>
    typename v_it& v_it::operator+(int n) {
        if (!ptr_)
            throw(std::exception());

        ptr_ += n;
        return *this;
    }

    template<class T>
    typename v_it& v_it::operator-(int n) {
        if (!ptr_)
            throw(std::exception());

        ptr_ -= n;
        return *this;
    }

    template<class T>
    T& v_it::operator*() const {
        if (!ptr_)
            throw(std::exception());

        return *ptr_;
    }

    template<class T>
    typename v_it& v_it::operator=(const typename v_it& other) {
        ptr_ = other.ptr_;
        return *this;
    }

    template<class T>
    bool v_it::operator==(const v_it& other) const { return ptr_ == other.ptr_; }

    template<class T>
    bool v_it::operator!=(const v_it& other) const { return ptr_ != other.ptr_; }

    template<class T>
    typename v_it vector<T>::begin() {
        return iterator(arr_);
    }

    template<class T>
    typename v_it vector<T>::end() {
        return iterator(arr_ + size_);
    }




    template<class T>
    v_cnst_it::const_iterator() : ptr_(nullptr) { }

    template<class T>
    v_cnst_it::const_iterator(T* ptr) : ptr_(ptr) { }

    template<class T>
    v_cnst_it::const_iterator(const v_cnst_it& other) : ptr_(other.ptr_) { }

    template<class T>
    v_cnst_it::const_iterator(const v_it& other) : ptr_(other.ptr_) { }

    template<class T>
    typename v_cnst_it& v_cnst_it::operator++() {
        if (!ptr_)
            throw(std::exception());

        ++ptr_;
        return *this;
    }

    template<class T>
    typename v_cnst_it& v_cnst_it::operator--() {
        if (!ptr_)
            throw(std::exception());

        --ptr_;
        return *this;
    }

    template<class T>
    typename v_cnst_it& v_cnst_it::operator+(int n) {
        if (!ptr_)
            throw(std::exception());

        ptr_ += n;
        return *this;
    }

    template<class T>
    typename v_cnst_it& v_cnst_it::operator-(int n) {
        if (!ptr_)
            throw(std::exception());

        ptr_ -= n;
        return *this;
    }

    template<class T>
    T v_cnst_it::operator*() const {
        if (!ptr_)
            throw(std::exception());

        return *ptr_;
    }

    template<class T>
    typename v_cnst_it& v_cnst_it::operator=(const typename v_cnst_it& other) {
        ptr_ = other.ptr_;
        return *this;
    }

    template<class T>
    typename v_cnst_it& v_cnst_it::operator=(const v_it& other) {
        ptr_ = other.ptr_;
        return *this;
    }

    template<class T>
    bool v_cnst_it::operator==(const v_cnst_it& other) const { return ptr_ == other.ptr_; }

    template<class T>
    bool v_cnst_it::operator!=(const v_cnst_it& other) const { return ptr_ != other.ptr_; }

    template<class T>
    typename v_cnst_it vector<T>::cbegin() const {
        return const_iterator(arr_);
    }

    template<class T>
    typename v_cnst_it vector<T>::begin() const {
        return const_iterator(arr_);
    }

    template<class T>
    typename v_cnst_it vector<T>::cend() const {
        return const_iterator(arr_ + size_);
    }

    template<class T>
    typename v_cnst_it vector<T>::end() const {
        return const_iterator(arr_ + size_);
    }












    template<class T>
    vector<T>::vector() {
        arr_ = new T[1];
        capacity_ = 1;
        size_ = 0;
    }

    template<class T>
    vector<T>::vector(size_t size) {
        arr_ = new T[size];
        capacity_ = size;
        size_ = size;
    }

    template<class T>
    vector<T>::vector(size_t size, T c) {
        arr_ = new T[size];
        capacity_ = size;
        size_ = size;

        for (size_t i = 0; i < size_; i++)
            arr_[i] = c;
    }

    template<class T>
    vector<T>::vector(const std::initializer_list<T>& list) {
        size_ = list.size();
        capacity_ = size_;

        arr_ = new T[size_];

        int i = 0;
        for (const auto& element : list)
            arr_[i++] = element;
    }

    template<class T>
    vector<T>::vector(const vector<T>& other) :
        size_(other.size_), capacity_(other.capacity_) {

        if (this == &other)
            return;

        arr_ = new T[capacity_];

        for (size_t i = 0; i < size_; i++)
            arr_[i] = other.arr_[i];
    }

    template<class T>
    vector<T>::vector(vector<T>&& other) :
        size_(other.size_), capacity_(other.capacity_) {

        if (this == &other)
            return;

        delete[] arr_;
        arr_ = other.arr_;

        other.arr_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    template<class T>
    vector<T>::~vector() {
        delete[] arr_;
    }

    template<class T>
    vector<T>& vector<T>::operator=(const vector<T>& other) {

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

    template<class T>
    vector<T>& vector<T>::operator=(vector<T>&& other) {

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

    template<class T>
    vector<T>& vector<T>::operator=(const std::initializer_list<T>& list) {
        clear();

        for (const auto& element : list)
            push_back(element);

        return *this;
    }

    template<class T>
    bool vector<T>::empty() const {
        return size_ == 0;
    }

    template<class T>
    size_t vector<T>::size() const {
        return size_;
    }

    template<class T>
    size_t vector<T>::capacity() const {
        return capacity_;
    }

    template<class T>
    size_t vector<T>::max_size() const {
        return SIZE_MAX / sizeof(T);
    }

    template<class T>
    void vector<T>::push_back(const T& value) {

        if (size_ >= capacity_)
            AddMemory();

        arr_[size_++] = value;
    }

    template<class T>
    void vector<T>::pop_back() {
        if (!size_)
            throw(std::out_of_range(""));

        --size_;
    }

    template<class T>
    T vector<T>::operator[](const size_t& index) const {
        return arr_[index];
    }

    template<class T>
    T& vector<T>::operator[](const size_t& index) {
        return arr_[index];
    }

    template<class T>
    T vector<T>::at(size_t index) const {
        if (!(index < size_) || index < 0)
            throw std::out_of_range("");

        return arr_[index];
    }

    template<class T>
    T& vector<T>::at(size_t index) {
        if (!(index < size_) || index < 0)
            throw std::out_of_range("");

        return arr_[index];
    }

    template<class T>
    T& vector<T>::front() const {
        return *arr_;
    }

    template<class T>
    T& vector<T>::back() const {
        return *(arr_ + size_ - 1);
    }

    template<class T>
    void vector<T>::clear() {
        delete[] arr_;
        arr_ = new T[capacity_];
        size_ = 0;
    }

    template<class T>
    T* vector<T>::data() const {
        return !size_ ? nullptr : arr_;
    }

    template<class T>
    void vector<T>::reserve(size_t new_cap) {
        if (new_cap > capacity_) {
            T* del = arr_;
            capacity_ = new_cap;
            arr_ = new T[capacity_];

            for (size_t i = 0; i < size_; i++)
                arr_[i] = del[i];

            delete[] del;
        }
    }

    template<class T>
    void vector<T>::resize(size_t new_size) {
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

    template<class T>
    void vector<T>::resize(size_t new_size, const T& value) {
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

    template<class T>
    void vector<T>::swap(vector<T>& other) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(arr_, other.arr_);
    }

    template<class T>
    void vector<T>::assign(size_t new_size, const T& value) {
        delete[] arr_;
        size_ = new_size;
        capacity_ = new_size;

        arr_ = new T[size_];
        for (int i = 0; i < size_; i++)
            arr_[i] = value;
    }

    template<class T>
    void vector<T>::assign(const std::initializer_list<T>& list) {
        size_ = list.size();
        capacity_ = size_;

        delete[] arr_;
        arr_ = new T[size_];

        int i = 0;
        for (const auto& element : list)
            arr_[i++] = element;
    }

    template<class T>
    typename v_it vector<T>::insert(v_cnst_it it, const size_t count, const T& value) {

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

    template<class T>
    typename v_it vector<T>::insert(v_cnst_it it, const std::initializer_list<T>& list) {

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

    template<class T>
    typename v_it vector<T>::insert(v_cnst_it it, const T& value) {

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

    template<class T>
    typename v_it vector<T>::erase(v_cnst_it it) {

        size_t pos = it.ptr_ - arr_;

        for (size_t i = pos; i < size_ - 1; i++)
            arr_[i] = arr_[i + 1];

        --size_;

        return iterator(arr_);
    }

    template<class T>
    typename v_it vector<T>::erase(v_cnst_it it1, v_cnst_it it2) {

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


    template<class T>
    template<class... Args>
    typename v_it vector<T>::emplace(typename v_cnst_it it, Args&&... args) {
        insert(it, T(args...));
        return iterator(arr_);
    }

    template<class T>
    template<class... Args>
    typename v_it vector<T>::emplace_back(Args&&... args) {
        //push_back(T(std::forward<Args>(args)...));
        push_back(T(args...));
        return iterator(arr_);
    }




}




#endif // VECTOR_H
