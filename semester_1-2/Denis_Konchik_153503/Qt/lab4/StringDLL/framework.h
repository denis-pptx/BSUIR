#pragma once

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#include <windows.h>

#include <stdexcept>
#include <iostream>

#ifdef MYDLL_MYSTRING_EXPORTS
#define MYSTRING __declspec(dllexport)
#else
#define MYSTRING __declspec(dllimport)
#endif

class MYSTRING String
{
public:

    String();

    String(const char* str);
    String(const String& other);
    String(String&& other);


    String& operator = (const String& other);
    String& operator = (char* s);


    char& operator [] (size_t i) const;
    char& at(size_t i) const;
    const char* c_str() const;

    size_t capacity() const;
    size_t size() const;
    
    void reserve(size_t res);
    bool empty() const;

    void clear();

    void push_back(char c);

    void pop_back();

    void insert(size_t pos, const String& other);
    void erase(size_t pos, size_t n = 1);
    String& operator += (const String& input);
    String& operator += (const char* input);
    String& operator + (const String& s);
    String& operator + (const char* input);
    

    bool operator ==(const String& other);
    bool operator !=(const String& other);

    void resize(size_t new_size);

 
    friend std::istream& operator >> (std::istream& stream, String& s);

    friend std::ostream& operator << (std::ostream& stream, const String& s);
    


    ~String();

private:

    char* str_;
    size_t size_;
    size_t capacity_;
};
