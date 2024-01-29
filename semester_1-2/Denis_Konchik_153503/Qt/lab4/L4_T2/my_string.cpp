#include "my_string.h"

namespace my_string {

    // Оператор ввода
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


    // Оператор вывода
    std::ostream& operator<<(std::ostream& stream, const string& s) {
        for (size_t i = 0; i < s.size(); i++)
            stream << s[i];

        return stream;
    }

    // operator (string + string)
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

    // operator (string + char)
    string operator+(const string& str, const char* s) {
        return str + string(s);
    }

    // operator (char + string)
    string operator+(const char* s, string& str) {
        return string(s) + str;
    }

    bool string::Strtok::isFirst = true;
    int string::Strtok::start = 0;
    char* string::Strtok::string = nullptr;
    int string::Strtok::l_str = 0;
}
