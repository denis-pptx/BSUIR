#ifndef STRING_H
#define STRING_H

#include "string_global.h"
#include <iostream>



namespace my_string {




    class STRING_EXPORT string {
    private:
        char* str_;
        size_t size_;
        size_t capacity_;

    public:

        // CONSTRUCTORS
        string();
        string(const char* s);
        string(const char c);
        string(const string& other);
        string(string&& other) noexcept;

        // DESTRUCTOR
        ~string();



        // OPERATORS
        string& operator=(const char* s);
        string& operator=(const string& other);
        string& operator=(string&& other) noexcept;
        bool operator==(const string& other) const;
        bool operator!=(const string& other) const;
        char& operator[](size_t i);
        char operator[](size_t i) const;

        // METHODS
        size_t size() const;
        size_t capacity() const;
        bool empty() const;
        void resize(size_t new_size);
        void reserve(size_t res);
        void clear();
        char* c_str() const;
        void push_back(char c);
        void push_front(char c);
        void pop_back();
        void pop_front();
        char& at(size_t i);
        char at(size_t i) const;
        char& front();
        char front() const;
        char& back();
        char back() const;

        // Оператор ввода
        friend std::istream& operator>>(std::istream& stream, string& s);

        // Оператор вывода
        friend std::ostream& operator<<(std::ostream& stream, const string& s);

        string& operator+=(const string& other);
        string& insert(size_t pos, const string& other) ;
        string& insert(size_t pos, const string& other, size_t subpos, size_t sublen);
        string& insert(size_t pos, const char* s);
        string& insert(size_t pos, const char* s, size_t n);
        string& insert(size_t pos, size_t n, char c);
        string& erase(size_t pos, size_t n = 1);
        string substr(size_t pos = 0, size_t len = 4294967295U) const;

        // STATIC FUNCTIONS
        static void* memcpy(void* s1, const void* s2, size_t n);
        static void* memmove(void* s1, const void* s2, size_t n);
        static char* strcpy(char* s1, const char* s2);
        static char* strncpy(char* s1, const char* s2, size_t n);
        static char* strcat(char* s1, const char* s2);
        static char* strncat(char* s1, const char* s2, size_t n);
        static int memcmp(const void* s1, const void* s2, size_t n);
        static int strcmp(const char* s1, const char* s2);
        static int strcoll(const char* s1, const char* s2);
        static int strncmp(const char* s1, const char* s2, size_t n);
        static size_t strxfrm(char* s1, const char* s2);
        static void* memset(void* s, int c, size_t n);
        static size_t strlen(const char* s);

        /*
        // Указатель на код ошибки
        static char* strerror(int errnum) {
            return strerror(errnum);
        }
        */

        class Strtok {
        private:
            static bool isFirst;
            static int start;
            static char* string;
            static int l_str;
        public:

            static void reset();
            static char* strtok(char* str, const char* sep);
        };


    };
    string operator+(const string& left, const string& right);
    string operator+(const string& str, const char* s);
    string operator+(const char* s, string& str);


}

#endif // STRING_H
