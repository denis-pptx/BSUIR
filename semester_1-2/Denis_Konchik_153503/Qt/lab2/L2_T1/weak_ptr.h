#ifndef WEAK
#define WEAK
#include <iostream>
#include "shared_ptr.h"

namespace p {
    
    template<class T>
    class weak_ptr
    {
    private:
        T* m_ptr;
        int* m_use_count;
        int* m_weak_count;

    public:
        weak_ptr();
        weak_ptr(p::weak_ptr<T>& other);
        weak_ptr(p::shared_ptr<T>& other);
        ~weak_ptr();

        void reset();
        int* get_use_count();
        int* get_weak_count();
        p::shared_ptr<T> lock();

        p::weak_ptr<T>& operator=(p::weak_ptr<T>& other);
        p::weak_ptr<T>& operator=(p::shared_ptr<T>& other);

    };

    

    template<class T>
    class weak_ptr<T[]>
    {
    private:
        T* m_ptr;
        int* m_use_count;
        int* m_weak_count;

    public:
        weak_ptr();
        weak_ptr(p::weak_ptr<T[]>& other);
        weak_ptr(p::shared_ptr<T[]>& other);
        ~weak_ptr();

        void reset();
        int* get_use_count();
        int* get_weak_count();
        p::shared_ptr<T[]> lock();

        p::weak_ptr<T[]>& operator=(p::weak_ptr<T[]>& other);
        p::weak_ptr<T[]>& operator=(p::shared_ptr<T[]>& other);

    };
}


template<class T>
p::weak_ptr<T>::weak_ptr()
    : m_ptr(nullptr), m_use_count(nullptr), m_weak_count(new int(1)) { }

template<class T>
p::weak_ptr<T>::weak_ptr(weak_ptr& other)
    : m_ptr(other.m_ptr), m_use_count(other.m_count), m_weak_count(other.m_weak_count)
{
    (*m_weak_count)++;
}

template<class T>
p::weak_ptr<T>::weak_ptr(shared_ptr<T>& other)
    : m_weak_count(new int(1))
{
    m_ptr = other.get_ptr();
    m_use_count = other.get_count();
}

template<class T>
p::weak_ptr<T>::~weak_ptr() {

    (*m_weak_count)--;

    if (!*m_weak_count) {
        delete m_weak_count;
        m_weak_count = nullptr;
    }
}

template<class T>
void p::weak_ptr<T>::reset() {

    if (*m_weak_count != 1) {
        (*m_weak_count)--;
        m_weak_count = new int(1);
    }

    m_ptr = nullptr;
}

template<class T>
p::shared_ptr<T> p::weak_ptr<T>::lock() {
    if (*m_use_count > 0) 
        return p::shared_ptr<T>(m_ptr, m_use_count);
    else 
        return p::shared_ptr<T>();  
}

template<class T>
p::weak_ptr<T>& p::weak_ptr<T>::operator=(weak_ptr<T>& other) {

    m_ptr = other.m_ptr;
    m_use_count = other.m_use_count;
    m_weak_count = other.m_use_count;
    (*m_weak_count)++;

    return *this;
}

template<class T>
p::weak_ptr<T>& p::weak_ptr<T>::operator=(shared_ptr<T>& other) {

    m_ptr = other.get_ptr();
    m_use_count = other.get_count();

    if (*m_weak_count != 1) {
        (*m_weak_count)--;
        m_weak_count = new int(1);
    }

    return *this;
}

template<class T>
int* p::weak_ptr<T>::get_use_count() {
    return m_use_count;
}

template<class T>
int* p::weak_ptr<T>::get_weak_count() {
    return m_weak_count;
}







template<class T>
p::weak_ptr<T[]>::weak_ptr()
    : m_ptr(nullptr), m_use_count(nullptr), m_weak_count(new int(1)) { }

template<class T>
p::weak_ptr<T[]>::weak_ptr(weak_ptr& other)
    : m_ptr(other.m_ptr), m_use_count(other.m_count), m_weak_count(other.m_weak_count)
{
    (*m_weak_count)++;
}

template<class T>
p::weak_ptr<T[]>::weak_ptr(shared_ptr<T[]>& other)
    : m_weak_count(new int(1))
{
    m_ptr = other.get_ptr();
    m_use_count = other.get_count();
}

template<class T>
p::weak_ptr<T[]>::~weak_ptr() {

    (*m_weak_count)--;

    if (!*m_weak_count) {
        delete m_weak_count;
        m_weak_count = nullptr;
    }
}

template<class T>
void p::weak_ptr<T[]>::reset() {

    if (*m_weak_count != 1) {
        (*m_weak_count)--;
        m_weak_count = new int(1);
    }

    m_ptr = nullptr;
}

template<class T>
p::shared_ptr<T[]> p::weak_ptr<T[]>::lock() {
    if (*m_use_count > 0)
        return p::shared_ptr<T[]>(m_ptr, m_use_count);
    else
        return p::shared_ptr<T[]>();
}

template<class T>
p::weak_ptr<T[]>& p::weak_ptr<T[]>::operator=(weak_ptr<T[]>& other) {

    m_ptr = other.m_ptr;
    m_use_count = other.m_use_count;
    m_weak_count = other.m_use_count;
    (*m_weak_count)++;

    return *this;
}

template<class T>
p::weak_ptr<T[]>& p::weak_ptr<T[]>::operator=(shared_ptr<T[]>& other) {

    m_ptr = other.get_ptr();
    m_use_count = other.get_count();

    if (*m_weak_count != 1) {
        (*m_weak_count)--;
        m_weak_count = new int(1);
    }

    return *this;
}

template<class T>
int* p::weak_ptr<T[]>::get_use_count() {
    return m_use_count;
}

template<class T>
int* p::weak_ptr<T[]>::get_weak_count() {
    return m_weak_count;
}


#endif