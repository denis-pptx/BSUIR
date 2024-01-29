#ifndef UNIQUE
#define UNIQUE

namespace p {


    template<class T>
    class unique_ptr
    {
    private:
        T* m_ptr;

        unique_ptr(T* ptr) : m_ptr(ptr) { };
    public:
        unique_ptr() : m_ptr(nullptr) { }

        unique_ptr(p::unique_ptr<T>& other) : m_ptr(other.m_ptr) {
            other.m_ptr = nullptr;
        }

        unique_ptr(p::unique_ptr<T>&& other) : m_ptr(other.m_ptr) {
            other.m_ptr = nullptr;
        }

        ~unique_ptr() {
            delete m_ptr;
            m_ptr = nullptr;
        };

        bool isNull() { return m_ptr == nullptr; }
        T* get_ptr() { return m_ptr; }

        T* release() {
            T* tmp = m_ptr;
            m_ptr = nullptr;
            return tmp;
        }

        void reset() {
            delete m_ptr;
            m_ptr = nullptr;
        };

        void swap(p::unique_ptr<T>& other) {
            if (&other == this)
                return;

            T* tmp_ptr = m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = tmp_ptr;
        };

        p::unique_ptr<T>& operator=(p::unique_ptr<T>& other) {
            if (&other == this)
                return *this;

            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;

            return *this;
        };

        p::unique_ptr<T>& operator=(p::unique_ptr<T>&& other) {
            if (&other == this)
                return *this;

            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;

            return *this;
        }

        T* operator->() { return m_ptr; }
        T& operator*() { return *m_ptr; }

        template<class U>
        friend p::unique_ptr<U> make_unique(U* ptr);

    };

    template<class T>
    p::unique_ptr<T> make_unique(T* ptr) {
        return p::unique_ptr<T>(ptr);
    }



    template<class T>
    class unique_ptr<T[]>
    {
    private:
        T* m_ptr;

        unique_ptr(T* ptr) : m_ptr(ptr) { };
    public:
        unique_ptr() : m_ptr(nullptr) { }

        unique_ptr(p::unique_ptr<T[]>& other) : m_ptr(other.m_ptr) {
            other.m_ptr = nullptr;
        }

        unique_ptr(p::unique_ptr<T[]>&& other) : m_ptr(other.m_ptr) {
            other.m_ptr = nullptr;
        }

        ~unique_ptr() {
            delete m_ptr;
            m_ptr = nullptr;
        };

        bool isNull() { return m_ptr == nullptr; }

        T* get_ptr() { return m_ptr; }

        T* release() {
            T* tmp = m_ptr;
            m_ptr = nullptr;
            return tmp;
        }

        void reset() {
            delete[] m_ptr;
            m_ptr = nullptr;
        };

        void swap(p::unique_ptr<T[]>& other) {
            T* tmp_ptr = m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = tmp_ptr;
        };

        T& operator[](int i) {
            return m_ptr[i];
        }

        p::unique_ptr<T[]>& operator=(p::unique_ptr<T[]>& other) {
            if (&other == this)
                return *this;

            delete[] m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;

            return *this;
        };

        p::unique_ptr<T[]>& operator=(p::unique_ptr<T[]>&& other) {
            if (&other == this)
                return *this;

            delete[] m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;

            return *this;
        }

        T* operator->() { return m_ptr; }
        T& operator*() { return *m_ptr; }

        template<class U>
        friend p::unique_ptr<U[]> make_unique(U* ptr);
    };


    template<class T[]>
    p::unique_ptr<T[]> make_unique(T* ptr) {
        return p::unique_ptr<T[]>(ptr);
    }

}
#endif
