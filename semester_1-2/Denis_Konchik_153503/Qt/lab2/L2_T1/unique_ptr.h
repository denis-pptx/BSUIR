#ifndef UNIQUE
#define UNIQUE

namespace p {

    template<class T>
    class unique_ptr
    {
    private:
        T* m_ptr;

    public:
        unique_ptr(T* ptr = nullptr);
        unique_ptr(p::unique_ptr<T>& other);
        ~unique_ptr();

        T* get_ptr();
        T* release();
        void reset(T* ptr = nullptr);

        p::unique_ptr<T>& operator=(p::unique_ptr<T>& other);
        p::unique_ptr<T>& operator=(T* ptr);
        T* operator->();
        T& operator*();
        operator T* ();
    };

    template<class T>
    class unique_ptr<T[]>
    {
    private:
        T* m_ptr;

    public:
        unique_ptr(T* ptr = nullptr);
        unique_ptr(p::unique_ptr<T[]> & other);
        ~unique_ptr();

        T* get_ptr();
        T* release();
        void reset(T* ptr = nullptr);

        T& operator[](int i);
        p::unique_ptr<T[]>& operator=(p::unique_ptr<T[]>& other);
        p::unique_ptr<T[]>& operator=(T* ptr);
        T* operator->();
        T& operator*();
        operator T* ();
    };

}

template<class T>
p::unique_ptr<T>::unique_ptr(T* ptr)
    : m_ptr(ptr) { }

template<class T>
p::unique_ptr<T>::unique_ptr(p::unique_ptr<T>& other)
    : m_ptr(other.m_ptr) {

    other.m_ptr = nullptr;
}

template<class T>
p::unique_ptr<T>::~unique_ptr() {
    delete m_ptr;
    m_ptr = nullptr;
}

template<class T>
T* p::unique_ptr<T>::get_ptr() {
    return m_ptr;
}

template<class T>
T* p::unique_ptr<T>::release() {
    T* tmp = m_ptr;
    m_ptr = nullptr;
    return tmp;
}

template<class T>
void p::unique_ptr<T>::reset(T* ptr) {
    delete m_ptr;
    m_ptr = ptr;
}

template<class T>
p::unique_ptr<T>& p::unique_ptr<T>::operator=(unique_ptr<T>& other) {

    if (&other == this)
        return *this;

    delete m_ptr;
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;

    return *this;
}

template<class T>
p::unique_ptr<T>& p::unique_ptr<T>::operator=(T* ptr) {
    delete m_ptr;
    m_ptr = ptr;
    return *this;
}

template<class T>
T* p::unique_ptr<T>::operator->() {
    return m_ptr;
}

template<class T>
T& p::unique_ptr<T>::operator*() {
    return *m_ptr;
}

template<class T>
p::unique_ptr<T>::operator T*() {
    return m_ptr;
}











template<class T>
p::unique_ptr<T[]>::unique_ptr(T* ptr)
    : m_ptr(ptr) { }

template<class T>
p::unique_ptr<T[]>::unique_ptr(p::unique_ptr<T[]>& other)
    : m_ptr(other.m_ptr) {

    other.m_ptr = nullptr;
}

template<class T>
p::unique_ptr<T[]>::~unique_ptr() {
    delete[] m_ptr;
    m_ptr = nullptr;
}


template<class T>
T* p::unique_ptr<T[]>::get_ptr() {
    return m_ptr;
}

template<class T>
T* p::unique_ptr<T[]>::release() {
    T* tmp = m_ptr;
    m_ptr = nullptr;
    return tmp;
}

template<class T>
void p::unique_ptr<T[]>::reset(T* ptr) {
    delete[] m_ptr;
    m_ptr = ptr;
}

template<class T>
T& p::unique_ptr<T[]>::operator[](int i) {
    return m_ptr[i];
}

template<class T>
p::unique_ptr<T[]>& p::unique_ptr<T[]>::operator=(unique_ptr<T[]>& other) {

    if (&other == this)
        return *this;

    delete[] m_ptr;
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;

    return *this;
}

template<class T>
p::unique_ptr<T[]>& p::unique_ptr<T[]>::operator=(T* ptr) {
    delete[] m_ptr;
    m_ptr = ptr;
    return *this;
}

template<class T>
T* p::unique_ptr<T[]>::operator->() {
    return m_ptr;
}

template<class T>
T& p::unique_ptr<T[]>::operator*() {
    return *m_ptr;
}

template<class T>
p::unique_ptr<T[]>::operator T* () {
    return m_ptr;
}



#endif