#ifndef SHARED
#define SHARED

namespace p {

    template<class T>
    class shared_ptr
    {
    private:
        T* m_ptr;
        int* m_count;

    public:
        shared_ptr(T* ptr = nullptr, int* count = new int(0));
        shared_ptr(p::shared_ptr<T>& other);
        shared_ptr(p::shared_ptr<T>&& other);
        ~shared_ptr();

        void reset(T* ptr = nullptr);
        T* get_ptr();
        int* get_count();

        p::shared_ptr<T>& operator=(p::shared_ptr<T>& other);
        p::shared_ptr<T>& operator=(p::shared_ptr<T>&& other);
        T* operator->();
        T& operator*();
        operator T* ();
    };


    template<class T>
    class shared_ptr<T[]>
    {
    private:
        T* m_ptr;
        int* m_count;

    public:
        shared_ptr(T* ptr = nullptr);
        shared_ptr(p::shared_ptr<T[]>& other);
        shared_ptr(p::shared_ptr<T[]>&& other);
        ~shared_ptr();
        
        void reset(T* ptr = nullptr); 
        T* get_ptr();
        int* get_count();

        T& operator[](int i);
        p::shared_ptr<T[]>& operator=(p::shared_ptr<T[]>& other);
        p::shared_ptr<T[]>& operator=(p::shared_ptr<T[]>&& other);
        T* operator->();
        T& operator*();
        operator T* ();
    };
}

template<class T>
p::shared_ptr<T>::shared_ptr(T* ptr, int* count)
    : m_ptr(ptr), m_count(count)
{
    (*m_count)++;
}

template<class T>
p::shared_ptr<T>::shared_ptr(p::shared_ptr<T>& other)
    : m_ptr(other.m_ptr), m_count(other.m_count)
{
    (*m_count)++;
}
template<class T>
p::shared_ptr<T>::shared_ptr(p::shared_ptr<T>&& other)
    : m_ptr(other.m_ptr), m_count(other.m_count)
{
    (*m_count)++;
}


template<class T>
p::shared_ptr<T>::~shared_ptr() {

    (*m_count)--;

    if (*m_count == 0) {
        delete m_count;
        delete m_ptr;
        m_count = nullptr;
        m_ptr = nullptr;
    }
    
}

template<class T>
p::shared_ptr<T>& p::shared_ptr<T>::operator=(p::shared_ptr<T>& other) {

    (*m_count)--;
    m_ptr = other.m_ptr;
    m_count = other.m_count;
    (*m_count)++;

    return *this;
}

template<class T>
p::shared_ptr<T>& p::shared_ptr<T>::operator=(p::shared_ptr<T>&& other) {

    (*m_count)--;
    m_ptr = other.m_ptr;
    m_count = other.m_count;
    (*m_count)++;

    return *this;
}




template<class T>
void p::shared_ptr<T>::reset(T* ptr) {

    if (*m_count != 1) {
        (*m_count)--;
        m_count = new int(1);
    }

    m_ptr = ptr;
}

template<class T>
T* p::shared_ptr<T>::get_ptr() {
    return m_ptr;
}

template<class T>
int* p::shared_ptr<T>::get_count() {
    return m_count;
}

template<class T>
T* p::shared_ptr<T>::operator->() {
    return m_ptr; 
}

template<class T>
T& p::shared_ptr<T>::operator*() {
    return *m_ptr; 
}

template<class T>
p::shared_ptr<T>::operator T* () {
    return m_ptr; 
}









template<class T>
p::shared_ptr<T[]>::shared_ptr(T* ptr)
    : m_ptr(ptr), m_count(new int(0))
{
    (*m_count)++;
}

template<class T>
p::shared_ptr<T[]>::shared_ptr(p::shared_ptr<T[]>& other)
    : m_ptr(other.m_ptr), m_count(other.m_count)
{
    (*m_count)++;
}

template<class T>
p::shared_ptr<T[]>::shared_ptr(p::shared_ptr<T[]>&& other)
    : m_ptr(other.m_ptr), m_count(other.m_count)
{
    (*m_count)++;
}

template<class T>
p::shared_ptr<T[]>::~shared_ptr() {
    (*m_count)--;

    if (*m_count == 0) {
        delete m_count;
        delete m_ptr;
        m_count = nullptr;
        m_ptr = nullptr;
    }
}

template<class T>
T& p::shared_ptr<T[]>::operator[](int i) {
    return m_ptr[i];
}

template<class T>
p::shared_ptr<T[]>& p::shared_ptr<T[]>::operator=(p::shared_ptr<T[]>& other) {

    (*m_count)--;
    m_ptr = other.m_ptr;
    m_count = other.m_count;
    (*m_count)++;

    return *this;
}

template<class T>
p::shared_ptr<T[]>& p::shared_ptr<T[]>::operator=(p::shared_ptr<T[]>&& other) {

    (*m_count)--;
    m_ptr = other.m_ptr;
    m_count = other.m_count;
    (*m_count)++;

    return *this;
}

template<class T>
void p::shared_ptr<T[]>::reset(T* ptr) {
    
    if (*m_count != 1) {
        (*m_count)--;
        m_count = new int(1);
    }

    m_ptr = ptr;
}

template<class T>
T* p::shared_ptr<T[]>::get_ptr() {
    return m_ptr;
}

template<class T>
int* p::shared_ptr<T[]>::get_count() {
    return m_count;
}

template<class T>
T* p::shared_ptr<T[]>::operator->() {
    return m_ptr;
}

template<class T>
T& p::shared_ptr<T[]>::operator*() {
    return *m_ptr;
}

template<class T>
p::shared_ptr<T[]>::operator T* () {
    return m_ptr;
}


#endif