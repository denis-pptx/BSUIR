#ifndef UNIQUE
#define UNIQUE

namespace p {


    template<class T>
    class unique_ptr
    {
    private:
        T* m_ptr;


    public:
        unique_ptr(T* ptr) : m_ptr(ptr) { };

        unique_ptr() : m_ptr(nullptr) { }

//        unique_ptr(p::unique_ptr<T>& other) : m_ptr(other.m_ptr) {
//            other.m_ptr = nullptr;
//        }

        unique_ptr(p::unique_ptr<T>&& other) : m_ptr(other.m_ptr) {
            m_ptr = other.m_ptr;
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

//        p::unique_ptr<T>& operator=(p::unique_ptr<T>& other) {
//            if (&other == this)
//                return *this;

//            delete m_ptr;
//            m_ptr = other.m_ptr;
//            other.m_ptr = nullptr;

//            return *this;
//        };

        p::unique_ptr<T>& operator=(p::unique_ptr<T>&& other) {
            if (&other == this)
                return *this;

            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;


            return *this;
        }

        bool operator==(p::unique_ptr<T>& other) {
            return m_ptr == other.m_ptr;
        }

        T* operator->() { return m_ptr; }
        T& operator*() { return *m_ptr; }


    };




}
#endif
