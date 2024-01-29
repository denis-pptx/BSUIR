#include "string.h"

namespace my_string {

    string::string() {
        size_ = 0;
        capacity_ = 10;
        str_ = new char[capacity_ + 1];
        str_[0] = '\0';
    }


    string::string(const char* s)
        : size_(0), capacity_(1), str_(new char[1]{'\0'}) {

        if (s != nullptr) {
            resize(strlen(s));
            strcpy(str_, s);
        }
    }

    string::string(const char c) {

        capacity_ = 10;
        size_ = 1;
        str_ = new char[capacity_ + 1];
        str_[0] = c;
        str_[1] = '\0';

    }

    string::string(const string& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;

        str_ = new char[capacity_ + 1];
        for (size_t i = 0; i < size_; i++)
            str_[i] = other.str_[i];

        str_[size_] = '\0';
    }

    string::string(string&& other) noexcept {
        str_ = other.str_;
        capacity_ = other.capacity_;
        size_ = other.size_;

        other.capacity_ = 10;
        other.str_ = new char[capacity_ + 1]{ '\0' };
        other.size_ = 0;
    }

    string::~string() {

        delete[] str_;
        str_ = nullptr;
    }

    string& string::operator=(const char* s) {

        if (s == nullptr) {
            size_ = 0;
            str_[0] = '\0';
            return *this;
        }
        size_t new_size = strlen(s);

        if (new_size >= capacity_)
            resize(new_size);

        strcpy(str_, s);

        size_ = new_size;

        return *this;
    }

    string& string::operator=(const string& other) {

        if (this == &other)
            return *this;

        delete[] str_;

        size_ = other.size_;
        capacity_ = other.capacity_;

        str_ = new char[capacity_ + 1];
        for (size_t i = 0; i < size_; i++)
            str_[i] = other.str_[i];

        str_[size_] = '\0';

        return *this;
    }

    string& string::operator=(string&& other) noexcept {
        str_ = other.str_;
        capacity_ = other.capacity_;
        size_ = other.size_;

        other.capacity_ = 10;
        other.str_ = new char[capacity_ + 1]{ '\0' };
        other.size_ = 0;

        return *this;
    }

    bool string::operator==(const string& other) const {
        return !strcmp(str_, other.str_);
    }

    bool string::operator!=(const string& other) const {
        return strcmp(str_, other.str_);
    }

    size_t string::size() const {
        return size_;
    }

    size_t string::capacity() const {
        return capacity_;
    }

    bool string::empty() const {
        return size_ == 0;
    }

    void string::resize(size_t new_size) {

        if (new_size > size_) {

            size_t old_size = size_;

            size_ = new_size;
            capacity_ = size_ ? size_ * 2 : 10;

            char* del = str_;
            str_ = new char[capacity_ + 1];

            strcpy(str_, del);

            for (size_t i = old_size; i < size_; i++)
                str_[i] = '\0';
            str_[size_] = '\0';

            delete[] del;
        }
        else {
            size_ = new_size;
        }
    }

    void string::reserve(size_t res) {
        if (res > capacity_) {
            capacity_ = res;
            char* del = str_;
            str_ = new char[capacity_ + 1];

            for (size_t i = 0; i < size_; i++)
                str_[i] = del[i];

            str_[size_] = '\0';
        }
    }

    void string::clear() {
        delete[] str_;
        size_ = 0;
        capacity_ = 10;
        str_ = new char[capacity_ + 1]{ '\0' };
    }

    char* string::c_str() const {
        char* c = new char[size_ + 1];
        strcpy(c, str_);
        return c;
    }

    void string::push_back(char c) {

        if (size_ >= capacity_)
            resize(size_ + 1);
        else
            size_++;

        str_[size_ - 1] = c;
        str_[size_] = '\0';
    }

    void string::push_front(char c) {
        insert(0, c);
    }

    void string::pop_back() {
        if (!size_)
            throw(std::out_of_range(""));

        str_[--size_] = '\0';
    }

    void string::pop_front() {
        if (!size_)
            throw(std::out_of_range(""));

        erase(0);
    }

    char& string::operator[](size_t i) {
        return str_[i];
    }

    char string::operator[](size_t i) const {
        return str_[i];
    }

    char& string::at(size_t i) {
        if (i <= size_)
            return str_[i];
        else
            throw(std::out_of_range(""));
    }

    char string::at(size_t i) const {
        if (i <= size_)
            return str_[i];
        else
            throw(std::out_of_range(""));
    }

    char& string::front() {
        if (size_ == 0)
            throw(std::out_of_range(""));
        return str_[0];
    }

    char string::front() const {
        if (size_ == 0)
            throw(std::out_of_range(""));
        return str_[0];
    }

    char& string::back() {
        if (size_ == 0)
            throw(std::out_of_range(""));
        return str_[size_ - 1];
    }

    char string::back() const {
        if (size_ == 0)
            throw(std::out_of_range(""));
        return str_[size_ - 1];
    }

    string& string::operator+=(const string& other) {
        *this = *this + other;
        return *this;
    }

    string& string::insert(size_t pos, const string& other) {

        if (pos > size_)
            throw(std::out_of_range(""));

        string new_str;

        for (size_t i = 0; i < pos; i++)
            new_str.push_back(str_[i]);

        new_str = new_str + other;

        for (size_t i = pos; i < size_; i++)
            new_str.push_back(str_[i]);

        delete[] str_;

        *this = std::move(new_str);

        return *this;
    }

    string& string::insert(size_t pos, const string& other, size_t subpos, size_t sublen) {

        if (pos > size_ || subpos > other.size())
                throw(std::out_of_range(""));

        string ins;

        for (size_t i = subpos; i < subpos + sublen && i < other.size(); i++)
            ins.push_back(other[i]);

        insert(pos, ins);

        return *this;
    }

    string& string::insert(size_t pos, const char* s) {

        if (pos > size_)
            throw(std::out_of_range(""));

        if (s == nullptr)
            throw(std::exception());

        insert(pos, string(s));

        return *this;
    }

    string& string::insert(size_t pos, const char* s, size_t n) {

        if (pos > size_)
            throw(std::out_of_range(""));

        if (s == nullptr)
            throw(std::exception());

        char* ins = new char[strlen(s) + 1];

        strcpy(ins, s);

        if (n < strlen(s))
            ins[n] = '\0';

        insert(pos, ins);

        delete[] ins;

        return *this;
    }

    string& string::insert(size_t pos, size_t n, char c) {

        if (pos > size_) throw(std::out_of_range(""));

        char* ins = new char[n + 1];

        for (size_t i = 0; i < n; i++)
            ins[i] = c;
        ins[n] = '\0';

        insert(pos, ins);

        return *this;
    }

    string& string::erase(size_t pos, size_t n) {
        if (pos > size_)
            throw(std::out_of_range(""));

        string new_str;

        for (size_t i = 0; i < pos; i++)
            new_str.push_back(str_[i]);

        for (size_t i = pos + n; i < size_; i++)
            new_str.push_back(str_[i]);

        *this = new_str;

        return *this;

    }

    string string::substr(size_t pos, size_t len) const {
        if (pos > size_)
            throw(std::out_of_range(""));

        string ret;

        for (size_t i = pos; i < pos + len && i < size_; i++)
            ret.push_back(str_[i]);

        return ret;
    }

    void* string::memcpy(void* s1, const void* s2, size_t n) {
        if (s1 == nullptr || s2 == nullptr)
            throw(std::exception());

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

    void* string::memmove(void* s1, const void* s2, size_t n) {
        if (s1 == nullptr || s2 == nullptr)
            throw(std::exception());

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

    char* string::strcpy(char* s1, const char* s2) {
        if (s1 == nullptr || s2 == nullptr)
            throw(std::exception());

        char* ret = s1;

        while (*s2 != '\0')
            *s1++ = *s2++;

        *s1 = '\0';

        return ret;
    }

    char* string::strncpy(char* s1, const char* s2, size_t n) {
        if (s1 == nullptr || s2 == nullptr)
            throw(std::exception());

        char* ret = s1;

        size_t i = 0;
        for (; i < n; i++)
            s1[i] = s2[i];

        s1[i] = '\0';

        return ret;
    }

    char* string::strcat(char* s1, const char* s2) {
        if (s1 == nullptr || s2 == nullptr)
            throw(std::exception());

        char* ret = s1;

        while (*s1 != '\0')
            s1++;

        while (*s2 != '\0')
            *s1++ = *s2++;

        *s1 = '\0';

        return ret;
    }

    char* string::strncat(char* s1, const char* s2, size_t n) {
        if (s1 == nullptr || s2 == nullptr)
            throw(std::exception());

        char* ret = s1;

        while (*s1 != '\0')
            s1++;

        while (*s2 != '\0' && n--)
            *s1++ = *s2++;

        *s1 = '\0';

        return ret;
    }

    int string::memcmp(const void* s1, const void* s2, size_t n) {
        if (s1 == nullptr || s2 == nullptr)
            throw(std::exception());

        char* a = (char*)s1;
        char* b = (char*)s2;

        while (n > 0) {

            if (*a++ != *b++)
                return *a < *b ? -1 : 1;

            n--;
        }

        return 0;
    }

    int string::strcmp(const char* s1, const char* s2) {
        if (s1 == nullptr || s2 == nullptr)
            throw(std::exception());

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

    int string::strcoll(const char* s1, const char* s2) {
        setlocale(LC_ALL, NULL);

        if (s1 == nullptr || s2 == nullptr)
            throw(std::exception());

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

    int string::strncmp(const char* s1, const char* s2, size_t n) {
        if (s1 == nullptr || s2 == nullptr)
            throw(std::exception());

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

    size_t string::strxfrm(char* s1, const char* s2) {
        setlocale(LC_ALL, NULL);

        if (s1 == nullptr || s2 == nullptr)
            throw(std::exception());

        char* ret = s1;

        while (*s2 != '\0')
            *s1++ = *s2++;

        *s1 = '\0';

        return strlen(ret);
    }

    void* string::memset(void* s, int c, size_t n) {
        if (s == nullptr)
            throw(std::exception());

        char* tmp = (char*)s;
        while (n) {
            *tmp++ = c;
            n--;
        }

        return s;
    }

    size_t string::strlen(const char* s) {
        if (s == nullptr)
            throw(std::exception());


        size_t n = 0;
        while (s[n] != '\0')
            n++;
        return n;
    }

    void string::Strtok::reset() {
        isFirst = true;
        start = 0;
        delete[] string;
        string = nullptr;
        l_str = 0;
    }

    char* string::Strtok::strtok(char* str, const char* sep) {
        if (sep == nullptr)
            throw(std::exception());


        if (isFirst) {
            start = 0;
            string = str;
            l_str = strlen(string);
        }

        isFirst = false;

        int l_sep = strlen(sep);

        // Первый вызов функции
        if (str != nullptr) {

            bool isSuitable = true;

            // Поиск первого элемента "не разделителя"
            for (int i = 0; i < l_str; i++) {

                isSuitable = true;

                for (int j = 0; j < l_sep; j++) {
                    if (str[i] == sep[j]) {
                        isSuitable = false;
                        break;
                    }
                }

                if (isSuitable) {
                    start = i;
                    break;
                }
            }

            // Если состоит из разделителей
            if (!isSuitable)
                return nullptr;
        }


        // Возвращаемая подстрока
        char* ret = new char[l_str + 2];
        int index = 0;

        // Доходим до следующего разделителя
        while (string[start] != '\0' && start < l_str) {

            ret[index++] = string[start++];

            // Если текущий символ - разделитель
            for (int j = 0; j < l_sep; j++)
                if (string[start] == sep[j]) {

                    ret[index] = '\0';
                    string[start++] = '\0';


                    // Если разделителей несколько подряд
                    bool isSep = false;
                    do {
                        isSep = false;
                        for (int i = 0; i < l_sep && !isSep; i++) {
                            if (string[start] == sep[i]) {
                                isSep = true;
                                string[start++] = '\0';
                            }
                        }
                    } while (isSep && string[start] != '\0');


                    return ret;
                }
                else if (string[start] == '\0') {
                    ret[index] = '\0';
                    start++;
                    return ret;
                }
        }

        return nullptr;
    }

    std::istream& operator>>(std::istream& stream, string& s) {

        if (stream.peek() == '\n')
            stream.ignore(1);

        size_t size = 10;
        char* str = (char*)calloc(size + 1, size + 1);

        stream.get(str, size, '\n');

        while (stream.peek() != '\n') {
            char* add = (char*)calloc(size + 1, size + 1);
            stream.get(add, size, '\n');

            str = (char*)realloc(str, (size *= 2));

            string::strcat(str, add);

            free(add);
        }

        s.resize(string::strlen(str));

        string::strcpy(s.c_str(), str);

        free(str);
        return stream;
    }


    std::ostream& operator<<(std::ostream& stream, const string& s) {
        for (size_t i = 0; i < s.size(); i++)
            stream << s[i];

        return stream;
    }

    string operator+(const string& left, const string& right) {

        string new_str;
        new_str.resize(left.size() + right.size());

        for (size_t i = 0; i < left.size(); i++)
            new_str[i] = left[i];

        size_t j = 0;
        for (size_t i = left.size(); i < new_str.size(); i++)
            new_str[i] = right[j++];

        new_str[new_str.size()] = '\0';

        return new_str;
    }

    string operator+(const string& str, const char* s) {
        return str + string(s);
    }

    string operator+(const char* s, string& str) {
        return string(s) + str;
    }

    bool string::Strtok::isFirst = true;
    int string::Strtok::start = 0;
    char* string::Strtok::string = nullptr;
    int string::Strtok::l_str = 0;

}
