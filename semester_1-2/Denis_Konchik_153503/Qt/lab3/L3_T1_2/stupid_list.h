#ifndef STUPID_LIST_H
#define STUPID_LIST_H
#include <QDebug>
#include <iostream>
#define compare_function bool (*compare)(const T& left, const T& right)

namespace stupid_list {

    template<class T>
    struct Node {
        T data;
        int next;
        int prev;
    };

    template<class T>
    class iterator;

    template<class T>
    class list {
    public:
        int head;
        int tail;
        int count;
        int arr_size;

        Node<T>* array;

        // Класс сортировки
        class SortList
        {
        private:
            friend list<T>;

            static bool less(const T& left, const T& right) {
                return left < right;
            }

            static void swap(T& left, T& right) {
                T temp = left;
                left = right;
                right = temp;
            }

            static void qsort(Node<T>* array, int left, int right, compare_function) {

                int l = left;
                int r = right;
                T mid = array[(l + r) / 2].data;

                while (l <= r) {
                    while (compare(array[l].data, mid))
                        l++;

                    while (compare(mid, array[r].data))
                        r--;

                    if (l <= r) {
                        swap(array[l].data, array[r].data);
                        l++; r--;
                    }
                }

                if (left < r)
                    qsort(array, left, r, compare);

                if (l < right)
                    qsort(array, l, right, compare);

            }
        };



    public:

        // Стандартный конструктор
        list() {
            array = nullptr;
            arr_size = 0;
            count = 0;
            head = -1;
            tail = -1;
        }

        // Конструктор копии
        list(const list<T>& other) {

            count = other.count;
            arr_size = other.arr_size;
            head = other.head;
            tail = other.tail;

            array = (Node<T>*)malloc(arr_size * sizeof(Node<T>));

            for (int i = 0; i < arr_size; i++)
                array[i] = other.array[i];
        }

        // Деструктор
        ~list() {
            clear();
        }

        // Количество элементов
        int size() {
            return count;
        }

        // Удалить все элеметы
        void clear() {
            head = -1;
            tail = -1;
            count = 0;
            free(array);
            array = nullptr;
            arr_size = 0;
            return;
        }

        // Пустой ли список
        bool empty() {
            return count == 0;
        }

        // Переворачивание списка
        void reverse() {

            int index = head;
            list<T>* reversed = new list<T>;
            while (index != -1) {
                reversed->push_front(array[index].data);
                index = array[index].next;
            }

            clear();
            *this = *reversed;
        }

        // Удаление элемента
        void erase(int pos) {

            if (pos > count - 1 || pos < 0)
                throw std::out_of_range("Index was out of range");

            if (pos == 0) {
                pop_front();
                return;
            }
            else if (pos == count - 1) {
                pop_back();
                return;
            }

            int del = head;
            for (int i = 0; i < pos; i++)
                del = array[del].next;

            int prev_del = array[del].prev;
            int next_del = array[del].next;

            array[prev_del].next = next_del;
            array[next_del].prev = prev_del;

            count--;
        }

        // Вставка элемента
        void insert(int pos, T data) {

            if (pos > count || pos < 0)
                throw std::out_of_range("Index was out of range");

            if (pos == count) {
                push_back(data);
                return;
            }
            else if (pos == 0) {
                push_front(data);
                return;
            }

            array = (Node<T>*)realloc(array, ++arr_size * sizeof(Node<T>));

            int ins = head;
            for (int i = 0; i < pos; i++)
                ins = array[ins].next;

            int prev_ins = array[ins].prev;

            array[prev_ins].next = arr_size - 1;
            array[ins].prev = arr_size - 1;

            array[arr_size - 1].data = data;
            array[arr_size - 1].prev = prev_ins;
            array[arr_size - 1].next = ins;

            count++;
        }

        // Добавить элемент в конец
        void push_back(T data) {

            array = (Node<T>*)realloc(array, ++arr_size * sizeof(Node<T>));
            array[arr_size - 1].data = data;
            array[arr_size - 1].next = -1;

            if (tail != -1) {
                array[tail].next = arr_size - 1;
                array[arr_size - 1].prev = tail;
                tail = arr_size - 1;
            }
            else {
                tail = 0;
                array[tail].next = -1;
                array[tail].prev = -1;
                head = 0;
                array[head].prev = -1;
                array[head].next = -1;
            }

            count++;

        }

        // Добавить элемент в начало
        void push_front(T data) {

            array = (Node<T>*)realloc(array, ++arr_size * sizeof(Node<T>));
            array[arr_size - 1].data = data;

            if (head != -1) {
                array[arr_size - 1].prev = -1;
                array[arr_size - 1].next = head;
                array[head].prev = arr_size - 1;
                head = arr_size - 1;

            }
            else {
                tail = 0;
                array[tail].next = -1;
                array[tail].prev = -1;
                head = 0;
                array[head].prev = -1;
                array[head].next = -1;
            }

            count++;
        }

        // Удалить элемент с конца
        void pop_back() {
            if (count == 0)
                throw(std::exception());
            else if (count == 1) {
                head = -1;
                tail = -1;
                count = 0;
                free(array);
                array = nullptr;
                arr_size = 0;
                return;
            }

            int tail_prev = array[tail].prev;
            array[tail_prev].next = -1;
            tail = tail_prev;

            count--;
        }

        // Удалить элемент с начала
        void pop_front() {
            if (count == 0)
                throw(std::exception());
            else if (count == 1) {
                head = -1;
                tail = -1;
                count = 0;
                free(array);
                array = nullptr;
                arr_size = 0;
                return;
            }

            int head_next = array[head].next;
            array[head_next].prev = -1;
            head = head_next;

            count--;
        }

        // Получить конечный элемент
        T& back() {
            if (count == 0)
                throw(std::exception());

            return array[tail].data;
        }

        // Получить начальный элемент
        T& front() {
            if (count == 0)
                throw(std::exception());

            return array[head].data;
        }

        // Сортировка элементов
        void sort(compare_function = &SortList::less) {

            Node<T>* sorted = (Node<T>*)malloc(count * sizeof(Node<T>));

            int index = head;
            for (int i = 0; i < count; i++) {
                sorted[i] = array[index];
                index = array[index].next;
            }

            SortList::qsort(sorted, 0, count - 1, compare);

            for (int i = 0; i < count; i++) {
                sorted[i].prev = i - 1;
                sorted[i].next = i + 1;
            }
            sorted[count - 1].next = -1;

            free(array);
            head = 0;
            tail = count - 1;
            arr_size = count;
            array = sorted;

        }


        // Обмен списков
        void swap(list<T>& other) {

            std::swap(head, other.head);
            std::swap(tail, other.tail);
            std::swap(count, other.count);
            std::swap(arr_size, other.arr_size);
            std::swap(array, other.array);
        }

        // Вывод всех элеметнов
//        void print() {

//            int index = head;

//            std::cout << "\n";
//            while (index != -1) {
//                std::cout << array[index].data << " ";
//                index = array[index].next;
//            }
//        }

        // operator[]
        T& operator[](int pos) {

            if (pos > count - 1 || pos < 0)
                throw std::out_of_range("Index was out of range");

            int index = head;
            for (int i = 0; i < pos; i++)
                index = array[index].next;

            return array[index].data;
        }

        // operator=
        list<T>& operator=(const list<T>& other) {

            clear();

            count = other.count;
            arr_size = other.arr_size;
            head = other.head;
            tail = other.tail;

            array = (Node<T>*)malloc(arr_size * sizeof(Node<T>));

            for (int i = 0; i < arr_size; i++)
                array[i] = other.array[i];

            return *this;
        }


        // Класс итератор
        class iterator
        {
        private:
            int m_index;
            Node<T>* m_array;
        public:

            iterator() : m_index(-1) { }

            iterator(int index, Node<T>* array = nullptr) : m_index(index), m_array(array) { }

            iterator(const list<T>::iterator& other) : m_index(other.m_index), m_array(other.m_array) { }

            iterator& operator++() {
                if (m_index == -1)
                    throw(std::exception());

                m_index = m_array[m_index].next;
                return *this;
            }

            iterator& operator--() {
                if (m_index == -1)
                    throw(std::exception());

                m_index = m_array[m_index].prev;
                return *this;
            }

            T& operator*() {
                if (m_index == -1)
                    throw(std::exception());

                return m_array[m_index].data;
            }

            iterator& operator=(const iterator& other) {
                m_index = other.m_index;
                return *this;
            }

            iterator& operator=(T& data) {
                if (m_index == -1)
                    throw(std::exception());

                m_array[m_index].data = data;
                return *this;
            }

            //bool operator==(const iterator& other) { return m_index == other.m_index; }

            bool operator!=(int index) { return m_index != index; }
        };

        // Итератор на head
        iterator begin() {
            return { head, array };
        }

        // Итератор на tail
        iterator end() {
            return { tail, array };
        }
    };
}


#endif
