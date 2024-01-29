#ifndef NODE_LIST_H
#define NODE_LIST_H

#include <iostream>
#define compare_function_node bool (*compare)(const T& left, const T& right)

namespace node_list {

    template<class T>
    struct Node
    {
        T data;
        Node<T>* next;
        Node<T>* prev;

        Node(T data_) : data(data_), next(nullptr), prev(nullptr) { }
        Node() : data(0), next(nullptr), prev(nullptr) { }
    };


    template<class T>
    class list
    {
    private:

        Node<T>* head;
        Node<T>* tail;
        int count;

        // Класс сортировки
        class SortList
        {
        public:

            static bool less(const T& left, const T& right) {
                return left < right;
            }

            static void swap(Node<T>* left, Node<T>* right) {
                T temp = left->data;
                left->data = right->data;
                right->data = temp;
            }

            static Node<T>* get_wall(Node<T>* left, Node<T>* right, compare_function_node)
            {
                Node<T>* current = left->prev;

                for (Node<T>* ptr = left; ptr != right; ptr = ptr->next) {
                    if (compare(ptr->data, right->data)) {
                        current = (!current ? left : current->next);
                        swap(ptr, current);
                    }
                }

                current = (!current ? left : current->next);

                swap(right, current);
                return current;
            }

            static void qsort(Node<T>* left, Node<T>* right, compare_function_node) {

                if (right != nullptr && left != right && left != right->next) {

                    Node<T>* wall = get_wall(left, right, compare);
                    qsort(left, wall->prev, compare);
                    qsort(wall->next, right, compare);
                }
            }

        };

    public:

        // Стандартный конструктор
        list() : head(nullptr), tail(nullptr), count(0) { }

        // Конструктор копии
        list(const list<T>& other)
            : head(nullptr), tail(nullptr), count(0) {

            Node<T>* temp = other.head;

            while (temp) {
                push_back(temp->data);
                temp = temp->next;
            }
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
            while (count)
                erase(0);
        }

        // Пустой ли список
        bool empty() {
            return count == 0;
        }

        // Переворачивание списка
        void reverse() {

            list<T>* reversed = new list<T>;
            Node<T>* temp = head;

            while (temp) {
                reversed->push_front(temp->data);
                temp = temp->next;
            }

            clear();
            *this = *reversed;
        }

        // Удаление элемента
        void erase(int pos) {

            if (pos > count - 1 || pos < 0)
                throw std::out_of_range("Index was out of range");

            Node<T>* del = head;

            for (int i = 0; i < pos; i++)
                del = del->next;

            Node<T>* prev_del = del->prev;
            Node<T>* next_del = del->next;

            if (prev_del != nullptr && count != 1)
                prev_del->next = next_del;

            if (next_del != nullptr && count != 1)
                next_del->prev = prev_del;


            if (pos == 0)
                head = next_del;

            if (pos == count - 1)
                tail = prev_del;

            delete del;

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

            Node<T>* ins = head;

            for (int i = 0; i < pos; i++)
                ins = ins->next;

            Node<T>* prev_ins = ins->prev;
            Node<T>* temp = new Node<T>(data);

            if (prev_ins != nullptr && count != 1)
                prev_ins->next = temp;

            temp->next = ins;
            temp->prev = prev_ins;
            ins->prev = temp;

            count++;
        }

        // Добавление элемента в конец
        void push_back(T data) {

            Node<T>* temp = new Node<T>(data);
            temp->next = nullptr;
            temp->prev = tail;

            if (tail != nullptr)
                tail->next = temp;

            if (head == nullptr)
                head = temp;

            tail = temp;

            count++;
        }

        // Добавление элемента в начало
        void push_front(T data) {

            Node<T>* temp = new Node<T>(data);
            temp->prev = nullptr;
            temp->next = head;

            if (head != nullptr)
                head->prev = temp;

            if (tail == nullptr)
                tail = temp;

            head = temp;

            count++;
        }

        // Удалить элемент с конца
        void pop_back() {
            if (count == 0)
                throw(std::exception());
            else if (count == 1) {
                head = nullptr;
                tail = nullptr;
                delete tail;
                count--;
                return;
            }

            Node<T>* del = tail;
            tail->prev->next = nullptr;

            delete tail;
            count--;
        }

        // Удалить элемент с начала
        void pop_front() {
            if (count)
                erase(0);
            else
                throw(std::exception());
        }

        // Получить конечный элемент
        T& back() {
            if (count == 0)
                throw(std::exception());

            return tail->data;
        }

        // Получить начальный элемент
        T& front() {
            if (count == 0)
                throw(std::exception());

            return head->data;
        }

        // Сортировка элементов
        void sort(compare_function_node = &SortList::less) {
            SortList::qsort(head, tail, compare);
        }

        // Обмен списков
        void swap(list<T>& other) {
            int temp_count = count;
            count = other.count;
            other.count = temp_count;

            Node<T>* temp = head;
            head = other.head;
            other.head = temp;

            temp = tail;
            tail = other.tail;
            other.tail = temp;
        }

        // Вывод всех элеметнов
        void print() {
            Node<T>* temp = head;
            //std::cout << "\n";
            while (temp) {
                //std::cout << temp->data << " ";
                temp = temp->next;
            }
        }

        // operator[]
        T& operator[](int pos) {

            if (pos > count - 1 || pos < 0)
                throw std::out_of_range("Index was out of range");

            Node<T>* temp = head;

            for (int i = 0; i < pos; i++)
                temp = temp->next;

            return temp->data;
        }

        // operator=
        list<T>& operator=(const list<T>& other) {

            clear();

            Node<T>* temp = other.head;

            while (temp) {
                push_back(temp->data);
                temp = temp->next;
            }

            return *this;
        }




        // Класс итератор
        class iterator
        {
        private:
            Node<T>* m_ptr;

        public:

            iterator() : m_ptr(nullptr) { }

            iterator(Node<T>* ptr) : m_ptr(ptr) { }

            iterator(const list<T>::iterator& other) : m_ptr(other.m_ptr) { }

            iterator& operator++() {
                if (!m_ptr)
                    throw(std::exception());

                m_ptr = m_ptr->next;
                return *this;
            }

            iterator& operator--() {
                if (!m_ptr)
                    throw(std::exception());

                m_ptr = m_ptr->prev;
                return *this;
            }

            iterator& operator+(int n) {
                Node<T>* temp = m_ptr;

                for (int i = 0; i < n; i++) {

                    if (!temp || !(temp = temp->next))
                        throw(std::exception());
                }

                m_ptr = temp;
                return *this;
            }

            iterator& operator-(int n) {
                Node<T>* temp = m_ptr;

                for (int i = 0; i < n; i++) {

                    if (!temp || !(temp = temp->prev))
                        throw(std::exception());
                }

                m_ptr = temp;
                return *this;
            }

            T& operator*() {
                if (!m_ptr)
                    throw(std::exception());

                return m_ptr->data;
            }

            iterator& operator=(const iterator& other) {
                m_ptr = other.m_ptr;
                return *this;
            }

            iterator& operator=(T& data) {
                if (!m_ptr)
                    throw(std::exception());

                m_ptr->data = data;
                return *this;
            }

            bool operator==(const iterator& other) { return m_ptr == other.m_ptr; }

            bool operator!=(const iterator& other) { return m_ptr != other.m_ptr; }

        };

        // Итератор на head
        iterator begin() {
            return head;
        }

        // Итератор на tail
        iterator end() {
            return tail;
        }
    };


}
#endif // NODE_LIST_H
