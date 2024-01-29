#ifndef SHARED
#define SHARED

namespace p {

    //template<class T>
    //class weak_ptr;

    template<class T>
    class shared_ptr
    {
    private:
        T* m_ptr;
        int* m_count;

        shared_ptr(T* ptr, int* count)
            : m_ptr(ptr), m_count(count)
        {
            (*m_count)++;
        }
    public:
        shared_ptr() : m_ptr(nullptr), m_count(new int(1)) { }

        shared_ptr(p::shared_ptr<T>& other)
            : m_ptr(other.m_ptr), m_count(other.m_count)
        {
            (*m_count)++;
        }

        shared_ptr(p::shared_ptr<T>&& other)
            : m_ptr(other.m_ptr), m_count(other.m_count)
        {
            (*m_count)++;
        }

        ~shared_ptr() {
            if (m_count != nullptr && m_ptr != nullptr) {
                (*m_count)--;

                if (*m_count == 0) {
                    //delete m_count;
                    delete m_ptr;
                    //m_count = nullptr;
                    m_ptr = nullptr;
                }
            }
        }

        void reset() {
            if (*m_count != 1) {
                (*m_count)--;
                m_count = new int(1);
            }
            else {
                delete m_ptr;
            }
            m_ptr = nullptr;
        }


        void swap(p::shared_ptr<T>& other) {
            if (&other == this)
                return;

            T* tmp_ptr = m_ptr;
            int* tmp_count = m_count;

            m_ptr = other.m_ptr;
            m_count = other.m_count;

            other.m_ptr = tmp_ptr;
            other.m_count = tmp_count;
        }

        p::shared_ptr<T>& operator=(p::shared_ptr<T>& other) {
            if (this == &other)
                return *this;

            (*m_count)--;

            if (*m_count == 0) {
                //delete m_count;
                delete m_ptr;
            }

            m_ptr = other.m_ptr;
            m_count = other.m_count;
            (*m_count)++;

            return *this;
        }

        p::shared_ptr<T>& operator=(p::shared_ptr<T>&& other) {
            if (this == &other)
                return *this;

            (*m_count)--;

            if (*m_count == 0) {
                //delete m_count;
                delete m_ptr;
            }

            m_ptr = other.m_ptr;
            m_count = other.m_count;
            (*m_count)++;

            return *this;
        }

        T* get_ptr() { return m_ptr; };
        int* get_count() { return m_count; }
        T* operator->() { return m_ptr; };
        T& operator*() { return *m_ptr; };
        operator T* () { return m_ptr; };

        template<class U>
        friend p::shared_ptr<U> make_shared(U* ptr, int* count);

        //friend weak_ptr<T>;

    };

    template<class T>
    p::shared_ptr<T> make_shared(T* ptr, int* count = new int(0)) {
        return p::shared_ptr<T>(ptr, count);
    }





    template<class T>
    class shared_ptr<T[]>
    {
    private:
        T* m_ptr;
        int* m_count;

        shared_ptr(T* ptr, int* count)
            : m_ptr(ptr), m_count(count)
        {
            (*m_count)++;
        }
    public:
        shared_ptr() : m_ptr(nullptr), m_count(new int(1)) { }

        shared_ptr(p::shared_ptr<T[]>& other)
            : m_ptr(other.m_ptr), m_count(other.m_count)
        {
            (*m_count)++;
        }

        shared_ptr(p::shared_ptr<T[]>&& other)
            : m_ptr(other.m_ptr), m_count(other.m_count)
        {
            (*m_count)++;
        }

        ~shared_ptr() {
            if (m_count != nullptr && m_ptr != nullptr) {
                (*m_count)--;

                if (*m_count == 0) {
                    //delete m_count;
                    delete[] m_ptr;
                    //m_count = nullptr;
                    m_ptr = nullptr;
                }
            }
        }

        void reset() {
            if (*m_count != 1) {
                (*m_count)--;
                m_count = new int(1);
            }
            else {
                delete[] m_ptr;
            }
            m_ptr = nullptr;
        }


        void swap(p::shared_ptr<T[]>& other) {
            if (&other == this)
                return;

            T* tmp_ptr = m_ptr;
            int* tmp_count = m_count;

            m_ptr = other.m_ptr;
            m_count = other.m_count;

            other.m_ptr = tmp_ptr;
            other.m_count = tmp_count;
        }

        p::shared_ptr<T[]>& operator=(p::shared_ptr<T[]>& other) {
            if (this == &other)
                return *this;

            (*m_count)--;

            if (*m_count == 0) {
                delete m_count;
                delete[] m_ptr;
            }

            m_ptr = other.m_ptr;
            m_count = other.m_count;
            (*m_count)++;

            return *this;
        }

        p::shared_ptr<T[]>& operator=(p::shared_ptr<T[]>&& other) {
            if (this == &other)
                return *this;

            (*m_count)--;

            if (*m_count == 0) {
                delete m_count;
                delete[] m_ptr;
            }

            m_ptr = other.m_ptr;
            m_count = other.m_count;
            (*m_count)++;

            return *this;
        }

        T& operator[](int i) { return m_ptr[i]; };
        T* get_ptr() { return m_ptr; };
        int* get_count() { return m_count; }
        T* operator->() { return m_ptr; };
        T& operator*() { return *m_ptr; };
        operator T* () { return m_ptr; };

        template<class U>
        friend p::shared_ptr<U[]> make_shared(U* ptr, int* count);



    };

    template<class T[]>
    p::shared_ptr<T[]> make_shared(T* ptr, int* count = new int(0)) {
        return p::shared_ptr<T[]>(ptr, count);
    }



}



#endif
