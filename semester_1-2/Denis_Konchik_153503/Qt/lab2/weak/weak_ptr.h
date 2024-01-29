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
        weak_ptr()
            : m_ptr(nullptr), m_use_count(nullptr), m_weak_count(new int(1)) { }

        weak_ptr(p::weak_ptr<T>& other)
            : m_ptr(other.m_ptr), m_use_count(other.m_count), m_weak_count(other.m_weak_count)
        {
            (*m_weak_count)++;
        }

        weak_ptr(p::shared_ptr<T>& other)
            : m_weak_count(new int(1)) {
            m_ptr = other.get_ptr();
            m_use_count = other.get_count();
        }

        ~weak_ptr() {
            if (m_weak_count != nullptr) {

                (*m_weak_count)--;

                if (!*m_weak_count) {
                    delete m_weak_count;
                    m_weak_count = nullptr;
                }
            }
        }

        void reset() {
            if (*m_weak_count != 1) {
                (*m_weak_count)--;
                m_weak_count = new int(0);
            }

            m_use_count = new int(0);
            m_ptr = nullptr;
        }

        p::shared_ptr<T> lock() {
            if (*m_use_count > 0)
                return p::make_shared<T>(m_ptr, m_use_count);
            else
                return p::shared_ptr<T>();

        }
        void swap(p::weak_ptr<T>& other) {
            T* tmp_ptr = m_ptr;
            int* tmp_use_count = m_use_count;
            int* tmp_weak_count = m_weak_count;

            m_ptr = other.m_ptr;
            m_use_count = other.m_use_count;
            m_weak_count = other.m_weak_count;

            other.m_ptr = tmp_ptr;
            other.m_use_count = tmp_use_count;
            other.m_weak_count = tmp_weak_count;
        }


        p::weak_ptr<T>& operator=(p::weak_ptr<T>& other) {
            if (this == &other || m_weak_count == other.get_weak_count())
                return *this;

            (*m_weak_count)--;
            m_ptr = other.m_ptr;
            m_use_count = other.m_use_count;
            m_weak_count = other.m_weak_count;
            (*m_weak_count)++;

            return *this;
        }

        p::weak_ptr<T>& operator=(p::shared_ptr<T>& other) {
            if (m_ptr == other.get_ptr())
                return *this;

            m_ptr = other.get_ptr();
            m_use_count = other.get_count();

            if (*m_weak_count != 1) {
                (*m_weak_count)--;
                m_weak_count = new int(1);
            }

            return *this;
        }

        explicit operator T* () { return m_ptr; };
        bool expired() { return *m_use_count == 0; }
        int* get_use_count() { return m_use_count; }
        int* get_weak_count() { return m_weak_count; }

    };





    template<class T>
    class weak_ptr<T[]>
    {
    private:
        T* m_ptr;
        int* m_use_count;
        int* m_weak_count;
    public:
        weak_ptr()
            : m_ptr(nullptr), m_use_count(nullptr), m_weak_count(new int(1)) { }

        weak_ptr(p::weak_ptr<T[]>& other)
            : m_ptr(other.m_ptr), m_use_count(other.m_count), m_weak_count(other.m_weak_count)
        {
            (*m_weak_count)++;
        }

        weak_ptr(p::shared_ptr<T[]>& other)
            : m_weak_count(new int(1)) {
            m_ptr = other.get_ptr();
            m_use_count = other.get_count();
        }

        ~weak_ptr() {
            if (m_weak_count != nullptr) {

                (*m_weak_count)--;

                if (!*m_weak_count) {
                    delete m_weak_count;
                    m_weak_count = nullptr;
                }
            }
        }

        void reset() {
            if (*m_weak_count != 1) {
                (*m_weak_count)--;
                m_weak_count = new int(1);
            }

            m_ptr = nullptr;
        }

        p::shared_ptr<T[]> lock() {
            if (*m_use_count > 0)
                return p::make_shared<T[]>(m_ptr, m_use_count);
            else
                return p::shared_ptr<T[]>();

        }
        void swap(p::weak_ptr<T[]>& other) {
            T* tmp_ptr = m_ptr;
            int* tmp_use_count = m_use_count;
            int* tmp_weak_count = m_weak_count;

            m_ptr = other.m_ptr;
            m_use_count = other.m_use_count;
            m_weak_count = other.m_weak_count;

            other.m_ptr = tmp_ptr;
            other.m_use_count = tmp_use_count;
            other.m_weak_count = tmp_weak_count;
        }


        p::weak_ptr<T[]>& operator=(p::weak_ptr<T[]>& other) {
            if (this == &other || m_weak_count == other.get_weak_count())
                return *this;

            (*m_weak_count)--;
            m_ptr = other.m_ptr;
            m_use_count = other.m_use_count;
            m_weak_count = other.m_weak_count;
            (*m_weak_count)++;

            return *this;
        }

        p::weak_ptr<T[]>& operator=(p::shared_ptr<T[]>& other) {
            if (m_ptr == other.get_ptr())
                return *this;

            if (*m_weak_count != 1) {
                (*m_weak_count)--;
                m_weak_count = new int(1);
            }

            return *this;
        }

        explicit operator T* () { return m_ptr; };
        bool expired() { return *m_use_count == 0; }
        int* get_use_count() { return m_use_count; }
        int* get_weak_count() { return m_weak_count; }

    };





}





#endif
