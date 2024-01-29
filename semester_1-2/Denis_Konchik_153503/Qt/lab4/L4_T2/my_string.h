#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <QDebug>

namespace my_string {

    class string;
    string operator+(const string& left, const string& right);
    string operator+(const string& str, const char* s);
    string operator+(const char* s, string& str);

    class string {
    private:
        char* str_;
        size_t size_;
        size_t capacity_;

    public:

        // Стандартный конструтор
        string() {
            size_ = 0;
            capacity_ = 10;
            str_ = new char[capacity_ + 1];
            str_[0] = '\0';
        }

        // Конструктор с массивом чаров
        string(const char* s)
            : size_(0), capacity_(1), str_(new char[1]{'\0'}) {

            if (s != nullptr) {
                resize(strlen(s));
                strcpy(str_, s);
            }
        }

        // Конструктор с чаром
        string(const char c) {

            capacity_ = 10;
            size_ = 1;
            str_ = new char[capacity_ + 1];
            str_[0] = c;
            str_[1] = '\0';

        }

        // Конструктор копии
        string(const string& other) {
            size_ = other.size_;
            capacity_ = other.capacity_;

            str_ = new char[capacity_ + 1];
            for (size_t i = 0; i < size_; i++)
                str_[i] = other.str_[i];

            str_[size_] = '\0';
        }

        // move-конструктор
        string(string&& other) noexcept {
            str_ = other.str_;
            capacity_ = other.capacity_;
            size_ = other.size_;

            other.capacity_ = 10;
            other.str_ = new char[capacity_ + 1]{ '\0' };
            other.size_ = 0;
        }

        ~string() {

            delete[] str_;
            str_ = nullptr;
        }

        // operator= с массивом чаров
        string& operator=(const char* s) {

            if (s == nullptr) {
                size_ = 0;
                str_[0] = '\0';
                return *this;
            }
            size_t new_size = strlen(s);

            if (new_size >= capacity_)
                resize(new_size);

            strcpy(str_, s);

            size_ = new_size;

            return *this;
        }

        // operator= копирующий
        string& operator=(const string& other) {

            delete[] str_;

            size_ = other.size_;
            capacity_ = other.capacity_;

            str_ = new char[capacity_ + 1];
            for (size_t i = 0; i < size_; i++)
                str_[i] = other.str_[i];

            str_[size_] = '\0';

            return *this;
        }

        // operator= move
        string& operator=(string&& other) noexcept {
            str_ = other.str_;
            capacity_ = other.capacity_;
            size_ = other.size_;

            other.capacity_ = 10;
            other.str_ = new char[capacity_ + 1]{ '\0' };
            other.size_ = 0;

            return *this;
        }

        // operator== для string
        bool operator==(const string& other) const {
            return !strcmp(str_, other.str_);
        }

        bool operator!=(const string& other) const {
            return strcmp(str_, other.str_);
        }

        // Размер строки
        size_t size() const {
            return size_;
        }

        // Вместимость строки
        size_t capacity() const {
            return capacity_;
        }

        // Пустая ли строка
        bool empty() const {
            return size_ == 0;
        }

        // Изменить длину строки
        void resize(size_t new_size) {

            if (new_size > size_) {

                size_t old_size = size_;

                size_ = new_size;
                capacity_ = size_ ? size_ * 2 : 10;

                char* del = str_;
                str_ = new char[capacity_ + 1];

                strcpy(str_, del);

                for (size_t i = old_size; i < size_; i++)
                    str_[i] = '\0';
                str_[size_] = '\0';

                delete[] del;
            }
            else {
                size_ = new_size;
            }
        }

        // Зарезервировать память
        void reserve(size_t res) {
            if (res > capacity_) {
                capacity_ = res;
                char* del = str_;
                str_ = new char[capacity_ + 1];

                for (size_t i = 0; i < size_; i++)
                    str_[i] = del[i];

                str_[size_] = '\0';
            }
        }

        // Очистить строку
        void clear() {
            delete[] str_;
            size_ = 0;
            capacity_ = 10;
            str_ = new char[capacity_ + 1]{ '\0' };
        }

        // Получить сырой массив
        char* c_str() const {
            char* c = new char[size_ + 1];
            strcpy(c, str_);
            return c;
        }

        // Добавить в конец
        void push_back(char c) {

            if (size_ >= capacity_)
                resize(size_ + 1);
            else
                size_++;

            str_[size_ - 1] = c;
            str_[size_] = '\0';
        }

        // Добавить в начало
        void push_front(char c) {
            insert(0, c);
        }

        // Удалить с конца
        void pop_back() {
            if (!size_)
                throw(std::out_of_range(""));

            str_[--size_] = '\0';
        }

        // Удалить с начала
        void pop_front() {
            if (!size_)
                throw(std::out_of_range(""));

            erase(0);
        }

        // operator[]
        char& operator[](size_t i) {
            return str_[i];
        }

        char operator[](size_t i) const {
            return str_[i];
        }

        // [] с проверкой границы
        char& at(size_t i) {
            if (i <= size_)
                return str_[i];
            else
                throw(std::out_of_range(""));
        }

        char at(size_t i) const {
            if (i <= size_)
                return str_[i];
            else
                throw(std::out_of_range(""));
        }

        // Первый элемент
        char& front() {
            if (size_ == 0)
                throw(std::out_of_range(""));
            return str_[0];
        }

        char front() const {
            if (size_ == 0)
                throw(std::out_of_range(""));
            return str_[0];
        }

        // Последний элемент
        char& back() {
            if (size_ == 0)
                throw(std::out_of_range(""));
            return str_[size_ - 1];
        }

        char back() const {
            if (size_ == 0)
                throw(std::out_of_range(""));
            return str_[size_ - 1];
        }

        // Оператор ввода
        friend std::istream& operator>>(std::istream& stream, string& s);

        // Оператор вывода
        friend std::ostream& operator<<(std::ostream& stream, const string& s);

        // += string
        string& operator+=(const string& other) {
            *this = *this + other;
            return *this;
        }

        // Вставить строку
        string& insert(size_t pos, const string& other) {

            if (pos > size_)
                throw(std::out_of_range(""));

            string new_str;

            for (size_t i = 0; i < pos; i++)
                new_str.push_back(str_[i]);

            new_str = new_str + other;

            for (size_t i = pos; i < size_; i++)
                new_str.push_back(str_[i]);

            delete[] str_;

            *this = std::move(new_str);

            return *this;
        }

        // Вставить часть строки
        string& insert(size_t pos, const string& other, size_t subpos, size_t sublen) {

            if (pos > size_ || subpos > other.size())
                    throw(std::out_of_range(""));

            string ins;

            for (size_t i = subpos; i < subpos + sublen && i < other.size(); i++)
                ins.push_back(other[i]);

            insert(pos, ins);

            return *this;
        }

        // Вставить чары
        string& insert(size_t pos, const char* s) {

            if (pos > size_)
                throw(std::out_of_range(""));

            if (s == nullptr)
                throw(std::exception());

            insert(pos, string(s));

            return *this;
        }

        // Вставить n символов из строки чаров
        string& insert(size_t pos, const char* s, size_t n) {

            if (pos > size_)
                throw(std::out_of_range(""));

            if (s == nullptr)
                throw(std::exception());

            char* ins = new char[strlen(s) + 1];

            strcpy(ins, s);

            if (n < strlen(s))
                ins[n] = '\0';

            insert(pos, ins);

            delete[] ins;

            return *this;
        }

        // Вставить n чаров
        string& insert(size_t pos, size_t n, char c) {

            if (pos > size_) throw(std::out_of_range(""));

            char* ins = new char[n + 1];

            for (size_t i = 0; i < n; i++)
                ins[i] = c;
            ins[n] = '\0';

            insert(pos, ins);

            return *this;
        }

        // Удаление символов
        string& erase(size_t pos, size_t n = 1) {
            if (pos > size_)
                throw(std::out_of_range(""));

            string new_str;

            for (size_t i = 0; i < pos; i++)
                new_str.push_back(str_[i]);

            for (size_t i = pos + n; i < size_; i++)
                new_str.push_back(str_[i]);

            *this = new_str;

            return *this;

        }

        // Получить подстроку
        string substr(size_t pos = 0, size_t len = 4294967295U) const {
            if (pos > size_)
                throw(std::out_of_range(""));

            string ret;

            for (size_t i = pos; i < pos + len && i < size_; i++)
                ret.push_back(str_[i]);

            return ret;
        }

        // Скопировать область памяти s2 в s1
        // (без учета перекрытия областей)
        static void* memcpy(void* s1, const void* s2, size_t n) {
            if (s1 == nullptr || s2 == nullptr)
                throw(std::exception());

            if (s1 == s2)
                return s1;

            void* ret = s1;

            char* dest = (char*)s1;
            char* src = (char*)s2;

            while (n) {
                *dest++ = *src++;
                n--;
            }

            return ret;
        }

        // Скопировать область памяти s2 в s1
        // (с учетом перекрытия областей)
        static void* memmove(void* s1, const void* s2, size_t n) {
            if (s1 == nullptr || s2 == nullptr)
                throw(std::exception());

            if (s1 == s2)
                return s1;

            void* ret = s1;

            if (s1 < s2) {
                char* dest = (char*)s1;
                char* src = (char*)s2;

                while (n) {
                    *dest++ = *src++;
                    n--;
                }

            }
            else {
                char* dest = (char*)s1 + n;
                char* src = (char*)s2 + n;

                while (n) {
                    *dest-- = *src--;
                    n--;
                }
            }

            return ret;
        }

        // Скопировать строку s2 в s1
        static char* strcpy(char* s1, const char* s2) {
            if (s1 == nullptr || s2 == nullptr)
                throw(std::exception());

            char* ret = s1;

            while (*s2 != '\0')
                *s1++ = *s2++;

            *s1 = '\0';

            return ret;
        }

        // Скопировать n символов строки s2 в s1
        static char* strncpy(char* s1, const char* s2, size_t n) {
            if (s1 == nullptr || s2 == nullptr)
                throw(std::exception());

            char* ret = s1;

            size_t i = 0;
            for (; i < n; i++)
                s1[i] = s2[i];

            s1[i] = '\0';

            return ret;
        }

        // Конкатенация строк
        static char* strcat(char* s1, const char* s2) {
            if (s1 == nullptr || s2 == nullptr)
                throw(std::exception());

            char* ret = s1;

            while (*s1 != '\0')
                s1++;

            while (*s2 != '\0')
                *s1++ = *s2++;

            *s1 = '\0';

            return ret;
        }

        // Добавление к s1 <= n символов от s2
        static char* strncat(char* s1, const char* s2, size_t n) {
            if (s1 == nullptr || s2 == nullptr)
                throw(std::exception());

            char* ret = s1;

            while (*s1 != '\0')
                s1++;

            while (*s2 != '\0' && n--)
                *s1++ = *s2++;

            *s1 = '\0';

            return ret;
        }

        // Сравнение n первых байт
        static int memcmp(const void* s1, const void* s2, size_t n) {
            if (s1 == nullptr || s2 == nullptr)
                throw(std::exception());

            char* a = (char*)s1;
            char* b = (char*)s2;

            while (n > 0) {

                if (*a++ != *b++)
                    return *a < *b ? -1 : 1;

                n--;
            }

            return 0;
        }

        // Сравнение строк
        static int strcmp(const char* s1, const char* s2) {
            if (s1 == nullptr || s2 == nullptr)
                throw(std::exception());

            while (*s1 && *s2) {
                if (*s1 != *s2)
                    return *s1 < *s2 ? -1 : 1;

                s1++; s2++;
            }

            if (*s1 && !*s2)
                return 1;

            if (!*s1 && *s2)
                return -1;

            return 0;
        }

        // Сравнение строк в соответствии с локалью
        static int strcoll(const char* s1, const char* s2) {
            setlocale(LC_ALL, NULL);

            if (s1 == nullptr || s2 == nullptr)
                throw(std::exception());

            while (*s1 && *s2) {
                if (*s1 != *s2)
                    return *s1 < *s2 ? -1 : 1;

                s1++; s2++;
            }

            if (*s1 && !*s2)
                return 1;

            if (!*s1 && *s2)
                return -1;

            return 0;
        }

        // Сравнение <= n символов в строках
        static int strncmp(const char* s1, const char* s2, size_t n) {
            if (s1 == nullptr || s2 == nullptr)
                throw(std::exception());

            while (*s1 && *s2 && n - 1) {
                if (*s1 != *s2)
                    return *s1 < *s2 ? -1 : 1;

                s1++; s2++;
                n--;
            }

            if (*s1 > *s2)
                return 1;

            if (*s1 < *s2)
                return -1;

            return 0;
        }

        // Копировать s2 в s1 и вернуть длину s1 (+ локаль)
        static size_t strxfrm(char* s1, const char* s2) {
            setlocale(LC_ALL, NULL);

            if (s1 == nullptr || s2 == nullptr)
                throw(std::exception());

            char* ret = s1;

            while (*s2 != '\0')
                *s1++ = *s2++;

            *s1 = '\0';

            return strlen(ret);
        }

        // Класс разбиения строки
        class Strtok {
        private:
            static bool isFirst;
            static int start;
            static char* string;
            static int l_str;
        public:

            // Сбросить функцию
            static void reset() {
                isFirst = true;
                start = 0;
                delete[] string;
                string = nullptr;
                l_str = 0;
            }

            // Разделить строку
            static char* strtok(char* str, const char* sep) {
                if (sep == nullptr)
                    throw(std::exception());


                if (isFirst) {
                    start = 0;
                    string = str;
                    l_str = strlen(string);
                }

                isFirst = false;

                int l_sep = strlen(sep);

                // Первый вызов функции
                if (str != nullptr) {

                    bool isSuitable = true;

                    // Поиск первого элемента "не разделителя"
                    for (int i = 0; i < l_str; i++) {

                        isSuitable = true;

                        for (int j = 0; j < l_sep; j++) {
                            if (str[i] == sep[j]) {
                                isSuitable = false;
                                break;
                            }
                        }

                        if (isSuitable) {
                            start = i;
                            break;
                        }
                    }

                    // Если состоит из разделителей
                    if (!isSuitable)
                        return nullptr;
                }


                // Возвращаемая подстрока
                char* ret = new char[l_str + 2];
                int index = 0;

                // Доходим до следующего разделителя
                while (string[start] != '\0' && start < l_str) {

                    ret[index++] = string[start++];

                    // Если текущий символ - разделитель
                    for (int j = 0; j < l_sep; j++)
                        if (string[start] == sep[j]) {

                            ret[index] = '\0';
                            string[start++] = '\0';


                            // Если разделителей несколько подряд
                            bool isSep = false;
                            do {
                                isSep = false;
                                for (int i = 0; i < l_sep && !isSep; i++) {
                                    if (string[start] == sep[i]) {
                                        isSep = true;
                                        string[start++] = '\0';
                                    }
                                }
                            } while (isSep && string[start] != '\0');


                            return ret;
                        }
                        else if (string[start] == '\0') {
                            ret[index] = '\0';
                            start++;
                            return ret;
                        }
                }

                return nullptr;
            }
        };

        // Заполнить память символом с кодом 'c'
        static void* memset(void* s, int c, size_t n) {
            if (s == nullptr)
                throw(std::exception());

            char* tmp = (char*)s;
            while (n) {
                *tmp++ = c;
                n--;
            }

            return s;
        }

        // Указатель на код ошибки
        //static char* strerror(int errnum) {
        //    return strerror(errnum);
        //}

        // Длина строки
        static size_t strlen(const char* s) {
            if (s == nullptr)
                throw(std::exception());


            size_t n = 0;
            while (s[n] != '\0')
                n++;
            return n;
        }
    };


}


#endif
