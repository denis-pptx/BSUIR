// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"

#include <iostream>
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// Скопировать область памяти s2 в s1
// (без учета перекрытия областей)
void* Memcpy(void* s1, const void* s2, size_t n) {


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
void* Memmove(void* s1, const void* s2, size_t n) {
  

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
char* Strcpy(char* s1, const char* s2) {
  
    char* ret = s1;

    while (*s2 != '\0')
        *s1++ = *s2++;

    *s1 = '\0';

    return ret;
}

// Скопировать n символов строки s2 в s1
char* Strncpy(char* s1, const char* s2, size_t n) {
 
    char* ret = s1;

    size_t i = 0;
    for (; i < n; i++)
        s1[i] = s2[i];

    s1[i] = '\0';

    return ret;
}

// Конкатенация строк
char* Strcat(char* s1, const char* s2) {

    char* ret = s1;

    while (*s1 != '\0')
        s1++;

    while (*s2 != '\0')
        *s1++ = *s2++;

    *s1 = '\0';

    return ret;
}

// Добавление к s1 <= n символов от s2
char* Strncat(char* s1, const char* s2, size_t n) {
 
    char* ret = s1;

    while (*s1 != '\0')
        s1++;

    while (*s2 != '\0' && n--)
        *s1++ = *s2++;

    *s1 = '\0';

    return ret;
}

// Сравнение n первых байт
int Memcmp(const void* s1, const void* s2, size_t n) {

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
int Strcmp(const char* s1, const char* s2) {

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
int Strcoll(const char* s1, const char* s2) {
 
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
int Strncmp(const char* s1, const char* s2, size_t n) {

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
size_t Strxfrm(char* s1, const char* s2, size_t n) {

    char* ret = s1;

    while (*s2 != '\0')
        *s1++ = *s2++;

    *s1 = '\0';

    return strlen(ret);
}

// Заполнить память символом с кодом 'c'
void* Memset(void* s, int c, size_t n) {

    char* tmp = (char*)s;
    while (n) {
        *tmp++ = c;
        n--;
    }

    return s;
}



// Длина строки
size_t Strlen(const char* s) {

    size_t n = 0;
    while (s[n] != '\0')
        n++;
    return n;
}



String::String() {
    std::cout << "CONSTRUCTOR";
    size_ = 0;
    capacity_ = 10;
    str_ = new char[capacity_ + 1];
    str_[0] = '\0';
}

String::String(const char* s)
    : size_(0), capacity_(1), str_(new char[1]{ '\0' }) {

    resize(strlen(s));
    Strcpy(str_, s);
}


String::String(const String& other)
{
    size_ = other.size_;
    capacity_ = other.capacity_;

    str_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; i++)
        str_[i] = other.str_[i];

    str_[size_] = '\0';
}



String::String(String&& other)
{
    str_ = other.str_;
    capacity_ = other.capacity_;
    size_ = other.size_;

    other.capacity_ = 10;
    other.str_ = new char[capacity_ + 1]{ '\0' };
    other.size_ = 0;
}


String& String::operator = (const String& other)
{
    *this = other.str_;
    return *this;
}

String& String::operator = (char* s)
{
    size_t new_size = strlen(s);

    if (new_size >= capacity_)
        resize(new_size);

    Strcpy(str_, s);

    size_ = new_size;

    return *this;
}


char& String::operator [] (size_t i) const
{
    return str_[i];
}

char& String::at(size_t i) const
{
    if (i >= 0 && i <= size_)
        return str_[i];
    else
        throw(std::out_of_range(""));
}

const char* String::c_str() const
{
    return str_;
}





size_t String::size() const
{
    return size_;
}

size_t String::capacity() const
{
    return capacity_;
}

bool String::empty() const
{
    return size_;
}



void String::reserve(size_t res)
{
    if (res > capacity_) {
        capacity_ = res;
        char* del = str_;
        str_ = new char[capacity_ + 1];

        for (size_t i = 0; i < size_; i++)
            str_[i] = del[i];

        str_[size_] = '\0';
    }
}

void String::clear()
{
    delete[] str_;
    size_ = 0;
    capacity_ = 10;
    str_ = new char[capacity_ + 1]{ '\0' };
}

void String::push_back(char c)
{
    if (size_ >= capacity_)
        resize(size_ + 1);
    else
        size_++;

    str_[size_ - 1] = c;
    str_[size_] = '\0';
}

void String::pop_back()
{
    if (!size_)
        throw(std::out_of_range(""));

    str_[--size_] = '\0';
}

void String::insert(size_t pos, const String& other)
{
    if (pos < 0 || pos > size_)
        throw(std::out_of_range(""));

    String new_str;

    for (size_t i = 0; i < pos; i++)
        new_str.push_back(str_[i]);

    new_str = new_str + other;

    for (size_t i = pos; i < size_; i++)
        new_str.push_back(str_[i]);

    delete[] str_;

    *this = std::move(new_str);

}

void String::erase(size_t pos, size_t n)
{
    if (n < 0 || pos < 0 || pos > size_)
        throw(std::out_of_range(""));

    String new_str;

    for (size_t i = 0; i < pos; i++)
        new_str.push_back(str_[i]);

    for (size_t i = pos + n; i < size_; i++)
        new_str.push_back(str_[i]);

    *this = new_str;


}

String& String::operator + (const String& s)
{
    for (size_t i = 0; i < s.size() - 1; i++)
    {
        this->push_back(s[i]);
    }
    return *this;
}

String& String::operator + (const char* input)
{
    size_t len = strlen(input);
    for (size_t i = 0; i < len - 1; i++)
    {
        this->push_back(input[i]);
    }
    return *this;
}

String& String::operator += (const String& input)
{
    for (size_t i = 0; i < input.size() - 1; i++)
    {
        this->push_back(input[i]);
    }
    return *this;
}

String& String::operator += (const char* input)
{
    size_t len = strlen(input);
    for (size_t i = 0; i < len - 1; i++)
    {
        this->push_back(input[i]);
    }
    return *this;
}


bool String::operator ==(const String& other)
{
    return !Strcmp(str_, other.str_);
}

bool String::operator !=(const String& other)
{
    return Strcmp(str_, other.str_);
}


std::istream& operator>>(std::istream& stream, String& s) {

    if (stream.peek() == '\n')
        stream.ignore(1);

    size_t size = 10;
    char* str = (char*)calloc(size + 1, size + 1);

    stream.get(str, size, '\n');

    while (stream.peek() != '\n') {
        char* add = (char*)calloc(size + 1, size + 1);
        stream.get(add, size, '\n');

        str = (char*)realloc(str, (size *= 2));

        Strcat(str, add);

        free(add);
    }

    s.resize(strlen(str));

    Strcpy(s.str_, str);

    free(str);
    return stream;
}


void String::resize(size_t new_size) {

    if (new_size > size_) {

        size_t old_size = size_;

        size_ = new_size;
        capacity_ = size_ ? size_ * 2 : 10;

        char* del = str_;
        str_ = new char[capacity_ + 1];

        Strcpy(str_, del);

        for (size_t i = old_size; i < size_; i++)
            str_[i] = '\0';
        str_[size_] = '\0';

        delete[] del;
    }
    else {
        size_ = new_size;
    }
}

std::ostream& operator<<(std::ostream& stream, const String& s) {
    for (size_t i = 0; i < s.size(); i++)
        stream << s[i];

    return stream;
}


String::~String()
{
    clear();
}
